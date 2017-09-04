module A = Array;

open Js;

type encoder 'a 'b = 'a => 'b;

type decoderError = string;

type decoderResult 'a = Result.t 'a decoderError;

type decoder 'a 'b = 'b => decoderResult 'a;

type jsonEncoder 'a = encoder 'a Json.t;

type jsonDecoder 'a = decoder 'a Json.t;

type codec 'a = (jsonEncoder 'a, jsonDecoder 'a);

type genericCodec 'a 'b 'c = (encoder 'a 'b, decoder 'a 'c);

type jsonDict = Dict.t Json.t;

type fieldEncoder 'a = encoder 'a (option (Dict.key, Json.t));

type fieldDecoder 'a = decoder 'a jsonDict;

type fieldCodec 'a = (fieldEncoder 'a, fieldDecoder 'a);

type xor 'a 'b =
  | Left 'a
  | Right 'b;

let (>>>) f g x => g (f x);

let const x _ => x;

let left a :xor 'a 'b => Left a;

let right b :xor 'a 'b => Right b;

let optionToResult o error =>
  switch o {
  | Some x => Result.Ok x
  | None => Result.Error error
  };

let either f g xor =>
  switch xor {
  | Left x => f x
  | Right y => g y
  };

let map f result =>
  switch result {
  | Result.Ok x => Result.Ok (f x)
  | Result.Error y => Result.Error y
  };

let (>>=) result f =>
  switch result {
  | Result.Ok x => f x
  | Result.Error y => Result.Error y
  };

let wrap (f: 'b => 'a) (g: 'a => 'b) ((enc, dec): genericCodec 'a 'c 'd) :genericCodec 'b 'c 'd => (
  f >>> enc,
  dec >>> map g
);

let validate
    (f: 'a => decoderResult 'a)
    ((enc, dec): genericCodec 'a 'c 'd)
    :genericCodec 'b 'c 'd => (
  enc,
  fun x => dec x >>= f
);

let encode ((enc, _): codec 'a) x => enc x;

let decode ((_, dec): codec 'a) x => dec x;

let parseJson (s: string) :decoderResult Json.t =>
  try (Result.Ok (Json.parseExn s)) {
  | _ => Result.Error "JSON parsing failed"
  };

external formatJson : Json.t => _ [@bs.as {json|null|json}] => int => string =
  "stringify" [@@bs.val] [@@bs.scope "JSON"];

let encodeJson ::spaces=2 codec a => formatJson (encode codec a) spaces;

let decodeJson codec s => parseJson s >>= decode codec;

let decoderOf f error :jsonDecoder 'a => fun x => optionToResult (f x) error;

let decodeRawObject = decoderOf Json.decodeObject "Expected object";

let decodeRawArray = decoderOf Json.decodeArray "Expected array";

let decodeRawNumber = decoderOf Json.decodeNumber "Expected number";

let decodeRawBool = decoderOf Json.decodeBoolean "Expected boolean";

let decodeRawString = decoderOf Json.decodeString "Expected string";

let decodeRawNull = decoderOf Json.decodeNull "Expected null";

let validInt (x: float) :decoderResult float => {
  let xInt = int_of_float x;
  if (x == float_of_int xInt) {
    Result.Ok x
  } else {
    Result.Error ("Not an int: " ^ string_of_float x)
  }
};

let number: codec float = (Json.number, decodeRawNumber);

let int: codec int = number |> validate validInt |> wrap float_of_int int_of_float;

let bool: codec bool = (Json.boolean, decodeRawBool) |> wrap Boolean.to_js_boolean to_bool;

let string: codec string = (Json.string, decodeRawString);

let null: codec unit = (const Json.null, decodeRawNull >>> map (const ()));

let xor ((enc1, dec1): codec 'a) ((enc2, dec2): codec 'b) :codec (xor 'a 'b) => (
  either enc1 enc2,
  fun x =>
    switch (dec1 x) {
    | Result.Ok y => Result.Ok (Left y)
    | Result.Error _ => map right (dec2 x)
    }
);

let nullable (codec: codec 'a) :codec (option 'a) => {
  let xorToOption = either (const None) Option.some;
  let optionToXor =
    fun
    | Some x => right x
    | None => left ();
  xor null codec |> wrap optionToXor xorToOption
};

let decodeArrayElements
    (decode: jsonDecoder 'a)
    (elements: array Json.t)
    :decoderResult (array 'a) => {
  let length = Array.length elements;
  let output = [||];
  let rec loop i =>
    if (i == length) {
      Result.Ok output
    } else {
      switch (decode (A.get elements i)) {
      | Result.Ok decoded =>
        ignore (Array.push decoded output);
        loop (i + 1)
      | Result.Error error => Result.Error error
      }
    };
  loop 0
};

let array ((enc, dec): codec 'a) :codec (Array.t 'a) => {
  let encode value => Json.array (Array.map enc value);
  let decode json => decodeRawArray json >>= decodeArrayElements dec;
  (encode, decode)
};

let fix (f: codec 'a => codec 'a) :codec 'a => {
  let encoderRef: ref (option (jsonEncoder 'a)) = ref None;
  let decoderRef: ref (option (jsonDecoder 'a)) = ref None;
  let emptyCodec: codec 'a = (
    fun value => Option.getExn !encoderRef @@ value,
    fun json => Option.getExn !decoderRef @@ json
  );
  let (encode, decode) = f (emptyCodec);
  encoderRef := Some encode;
  decoderRef := Some decode;
  (encode, decode)
};

let decodeMandatoryField (decode: jsonDecoder 'a) name dict :decoderResult 'a =>
  optionToResult (Dict.get dict name) ("Field '" ^ name ^ "' not found") >>= decode;

let decodeOptionalField (decode: jsonDecoder 'a) name dict :decoderResult (option 'a) =>
  Result.Ok (Dict.get dict name) >>= (
    fun
    | Some x => map Option.some (decode x)
    | None => Result.Ok None
  );

let buildDict (fields: list (option (Dict.key, Json.t))) :jsonDict => {
  let dict = Dict.empty ();
  let rec loop remaining =>
    switch remaining {
    | [] => dict
    | [Some (name, value), ...tail] =>
      Dict.set dict name value;
      loop tail
    | [None, ...tail] => loop tail
    };
  loop fields
};

let field (name: Dict.key) ((enc, dec): codec 'a) :fieldCodec 'a => (
  fun value => Some (name, enc value),
  decodeMandatoryField dec name
);

let optional (name: Dict.key) ((enc, dec): codec 'a) :fieldCodec (option 'a) => (
  /* TODO figure out why Option.map produces a compile error here */
  fun
  | Some value => Some (name, enc value)
  | None => None,
  decodeOptionalField dec name
);

let optionalNullable (name: Dict.key) (codec: codec 'a) :fieldCodec (option 'a) => {
  let flatten =
    fun
    | Some (Some x) => Some x
    | Some None
    | None => None;
  optional name (nullable codec) |> wrap Option.some flatten
};

let object0: codec unit = (
  const (Json.object_ (Dict.empty ())),
  decodeRawObject >>> map (const ())
);

let object1 ((enc1, dec1): fieldCodec 'a) :codec 'a => {
  let encode v1 => Json.object_ (buildDict [enc1 v1]);
  let decode json => decodeRawObject json >>= (fun dict => dec1 dict);
  (encode, decode)
};

let object2 ((enc1, dec1): fieldCodec 'a) ((enc2, dec2): fieldCodec 'b) :codec ('a, 'b) => {
  let encode (v1, v2) => Json.object_ (buildDict [enc1 v1, enc2 v2]);
  let decode json =>
    decodeRawObject json >>= (
      fun dict => dec1 dict >>= (fun v1 => dec2 dict >>= (fun v2 => Result.Ok (v1, v2)))
    );
  (encode, decode)
};

let object3
    ((enc1, dec1): fieldCodec 'a)
    ((enc2, dec2): fieldCodec 'b)
    ((enc3, dec3): fieldCodec 'c)
    :codec ('a, 'b, 'c) => {
  let encode (v1, v2, v3) => Json.object_ (buildDict [enc1 v1, enc2 v2, enc3 v3]);
  let decode json =>
    decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 => dec2 dict >>= (fun v2 => dec3 dict >>= (fun v3 => Result.Ok (v1, v2, v3)))
        )
    );
  (encode, decode)
};

let object4
    ((enc1, dec1): fieldCodec 'a)
    ((enc2, dec2): fieldCodec 'b)
    ((enc3, dec3): fieldCodec 'c)
    ((enc4, dec4): fieldCodec 'd)
    :codec ('a, 'b, 'c, 'd) => {
  let encode (v1, v2, v3, v4) => Json.object_ (buildDict [enc1 v1, enc2 v2, enc3 v3, enc4 v4]);
  let decode json =>
    decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (fun v3 => dec4 dict >>= (fun v4 => Result.Ok (v1, v2, v3, v4)))
            )
        )
    );
  (encode, decode)
};

let object5
    ((enc1, dec1): fieldCodec 'a)
    ((enc2, dec2): fieldCodec 'b)
    ((enc3, dec3): fieldCodec 'c)
    ((enc4, dec4): fieldCodec 'd)
    ((enc5, dec5): fieldCodec 'e)
    :codec ('a, 'b, 'c, 'd, 'e) => {
  let encode (v1, v2, v3, v4, v5) =>
    Json.object_ (buildDict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5]);
  let decode json =>
    decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 => dec5 dict >>= (fun v5 => Result.Ok (v1, v2, v3, v4, v5))
                    )
                )
            )
        )
    );
  (encode, decode)
};

let object6
    ((enc1, dec1): fieldCodec 'a)
    ((enc2, dec2): fieldCodec 'b)
    ((enc3, dec3): fieldCodec 'c)
    ((enc4, dec4): fieldCodec 'd)
    ((enc5, dec5): fieldCodec 'e)
    ((enc6, dec6): fieldCodec 'f)
    :codec ('a, 'b, 'c, 'd, 'e, 'f) => {
  let encode (v1, v2, v3, v4, v5, v6) =>
    Json.object_ (buildDict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5, enc6 v6]);
  let decode json =>
    decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 =>
                        dec5 dict >>= (
                          fun v5 => dec6 dict >>= (fun v6 => Result.Ok (v1, v2, v3, v4, v5, v6))
                        )
                    )
                )
            )
        )
    );
  (encode, decode)
};

let object7
    ((enc1, dec1): fieldCodec 'a)
    ((enc2, dec2): fieldCodec 'b)
    ((enc3, dec3): fieldCodec 'c)
    ((enc4, dec4): fieldCodec 'd)
    ((enc5, dec5): fieldCodec 'e)
    ((enc6, dec6): fieldCodec 'f)
    ((enc7, dec7): fieldCodec 'g)
    :codec ('a, 'b, 'c, 'd, 'e, 'f, 'g) => {
  let encode (v1, v2, v3, v4, v5, v6, v7) =>
    Json.object_ (buildDict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5, enc6 v6, enc7 v7]);
  let decode json =>
    decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 =>
                        dec5 dict >>= (
                          fun v5 =>
                            dec6 dict >>= (
                              fun v6 =>
                                dec7 dict >>= (fun v7 => Result.Ok (v1, v2, v3, v4, v5, v6, v7))
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode)
};

let object8
    ((enc1, dec1): fieldCodec 'a)
    ((enc2, dec2): fieldCodec 'b)
    ((enc3, dec3): fieldCodec 'c)
    ((enc4, dec4): fieldCodec 'd)
    ((enc5, dec5): fieldCodec 'e)
    ((enc6, dec6): fieldCodec 'f)
    ((enc7, dec7): fieldCodec 'g)
    ((enc8, dec8): fieldCodec 'h)
    :codec ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h) => {
  let encode (v1, v2, v3, v4, v5, v6, v7, v8) =>
    Json.object_ (
      buildDict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5, enc6 v6, enc7 v7, enc8 v8]
    );
  let decode json =>
    decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 =>
                        dec5 dict >>= (
                          fun v5 =>
                            dec6 dict >>= (
                              fun v6 =>
                                dec7 dict >>= (
                                  fun v7 =>
                                    dec8 dict >>= (
                                      fun v8 => Result.Ok (v1, v2, v3, v4, v5, v6, v7, v8)
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode)
};

let object9
    ((enc1, dec1): fieldCodec 'a)
    ((enc2, dec2): fieldCodec 'b)
    ((enc3, dec3): fieldCodec 'c)
    ((enc4, dec4): fieldCodec 'd)
    ((enc5, dec5): fieldCodec 'e)
    ((enc6, dec6): fieldCodec 'f)
    ((enc7, dec7): fieldCodec 'g)
    ((enc8, dec8): fieldCodec 'h)
    ((enc9, dec9): fieldCodec 'i)
    :codec ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i) => {
  let encode (v1, v2, v3, v4, v5, v6, v7, v8, v9) =>
    Json.object_ (
      buildDict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5, enc6 v6, enc7 v7, enc8 v8, enc9 v9]
    );
  let decode json =>
    decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 =>
                        dec5 dict >>= (
                          fun v5 =>
                            dec6 dict >>= (
                              fun v6 =>
                                dec7 dict >>= (
                                  fun v7 =>
                                    dec8 dict >>= (
                                      fun v8 =>
                                        dec9 dict >>= (
                                          fun v9 => Result.Ok (v1, v2, v3, v4, v5, v6, v7, v8, v9)
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode)
};

let object10
    ((enc1, dec1): fieldCodec 'a)
    ((enc2, dec2): fieldCodec 'b)
    ((enc3, dec3): fieldCodec 'c)
    ((enc4, dec4): fieldCodec 'd)
    ((enc5, dec5): fieldCodec 'e)
    ((enc6, dec6): fieldCodec 'f)
    ((enc7, dec7): fieldCodec 'g)
    ((enc8, dec8): fieldCodec 'h)
    ((enc9, dec9): fieldCodec 'i)
    ((enc10, dec10): fieldCodec 'j)
    :codec ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j) => {
  let encode (v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) =>
    Json.object_ (
      buildDict [
        enc1 v1,
        enc2 v2,
        enc3 v3,
        enc4 v4,
        enc5 v5,
        enc6 v6,
        enc7 v7,
        enc8 v8,
        enc9 v9,
        enc10 v10
      ]
    );
  let decode json =>
    decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 =>
                        dec5 dict >>= (
                          fun v5 =>
                            dec6 dict >>= (
                              fun v6 =>
                                dec7 dict >>= (
                                  fun v7 =>
                                    dec8 dict >>= (
                                      fun v8 =>
                                        dec9 dict >>= (
                                          fun v9 =>
                                            dec10 dict >>= (
                                              fun v10 =>
                                                Result.Ok (v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode)
};
