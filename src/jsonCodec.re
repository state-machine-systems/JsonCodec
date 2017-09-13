module Option = Js.Option;

module Json = Js.Json;

module Dict = Js.Dict;

include JsonCodec_core;

include JsonCodec_object;

module Function = JsonCodec_function;

open Function.Ops;

module Xor = JsonCodec_xor;

open Result.Ops;

let wrap (f: 'b => 'a) (g: 'a => 'b) ((enc, dec): GenericCodec.t 'a 'c 'd) :GenericCodec.t 'b 'c 'd => (
  f >>> enc,
  dec >>> Result.map g
);

let validate
    (f: 'a => Decoder.result 'a)
    ((enc, dec): GenericCodec.t 'a 'c 'd)
    :GenericCodec.t 'b 'c 'd => (
  enc,
  fun x => dec x >>= f
);

let number: Codec.t float = (Json.number, Util.decodeRawNumber);

let int: Codec.t int = number |> validate Util.validInt |> wrap float_of_int int_of_float;

let bool: Codec.t bool =
  (Json.boolean, Util.decodeRawBool) |> wrap Js.Boolean.to_js_boolean Js.to_bool;

let string: Codec.t string = (Json.string, Util.decodeRawString);

let null: Codec.t unit = (
  Function.const Json.null,
  Util.decodeRawNull >>> Result.map (Function.const ())
);

let xor ((enc1, dec1): Codec.t 'a) ((enc2, dec2): Codec.t 'b) :Codec.t (Xor.t 'a 'b) => (
  Xor.either enc1 enc2,
  fun x =>
    switch (dec1 x) {
    | Result.Ok y => Result.Ok (Xor.left y)
    | Result.Error _ => Result.map Xor.right (dec2 x)
    }
);

let nullable (codec: Codec.t 'a) :Codec.t (option 'a) =>
  xor null codec |> wrap Xor.fromOption Xor.toOption;

let array ((enc, dec): Codec.t 'a) :Codec.t (Js.Array.t 'a) => {
  let encode value => Json.array (Js.Array.map enc value);
  let decode json => Util.decodeRawArray json >>= Util.decodeArrayElements dec;
  (encode, decode)
};

let fix (f: Codec.t 'a => Codec.t 'a) :Codec.t 'a => {
  let encoderRef: ref (option (JsonEncoder.t 'a)) = ref None;
  let decoderRef: ref (option (JsonDecoder.t 'a)) = ref None;
  let emptyCodec: Codec.t 'a = (
    fun value => Option.getExn !encoderRef @@ value,
    fun json => Option.getExn !decoderRef @@ json
  );
  let (encode, decode) = f emptyCodec;
  encoderRef := Some encode;
  decoderRef := Some decode;
  (encode, decode)
};

let field (name: Dict.key) ((enc, dec): Codec.t 'a) :FieldCodec.t 'a => (
  fun value => Some (name, enc value),
  Util.decodeMandatoryField dec name
);

let optional (name: Dict.key) ((enc, dec): Codec.t 'a) :FieldCodec.t (option 'a) => (
  Option.map ((fun value => (name, enc value)) [@bs]),
  Util.decodeOptionalField dec name
);

let optionalNullable (name: Dict.key) (codec: Codec.t 'a) :FieldCodec.t (option 'a) => {
  let flatten =
    fun
    | Some (Some x) => Some x
    | Some None
    | None => None;
  optional name (nullable codec) |> wrap Option.some flatten
};

let object0: Codec.t unit = (
  Function.const (Json.object_ (Dict.empty ())),
  Util.decodeRawObject >>> Result.map (Function.const ())
);
