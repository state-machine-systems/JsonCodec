module A = Array;

open Js;

type encoder 'a 'b = 'a => 'b;

type decoder_error = string;

type decoder_result 'a = Result.t 'a decoder_error;

type decoder 'a 'b = 'b => decoder_result 'a;

type json_encoder 'a = encoder 'a Json.t;

type json_decoder 'a = decoder 'a Json.t;

type codec 'a = (json_encoder 'a, json_decoder 'a);

type generic_codec 'a 'b 'c = (encoder 'a 'b, decoder 'a 'c);

type json_dict = Dict.t Json.t;

type field_encoder 'a = encoder 'a (option (Dict.key, Json.t));

type field_decoder 'a = decoder 'a json_dict;

type field_codec 'a = (field_encoder 'a, field_decoder 'a);

type alt 'a 'b =
  | Left 'a
  | Right 'b;

let (>>>) f g => fun x => g (f x);

let const x => fun _ => x;

let left a : alt 'a 'b => Left a;

let right b : alt 'a 'b => Right b;

let result_of_option o error => switch o {
| Some x => Result.Ok x
| None => Result.Error error
};

let either f g alt => switch alt {
| Left x => f x
| Right y => g y
};

let map f result => switch result {
| Result.Ok x => Result.Ok (f x)
| Result.Error y => Result.Error y
};

let (>>=) result f => switch result {
| Result.Ok x => f x
| Result.Error y => Result.Error y
};

let transform (f : 'b => 'a) (g : 'a => 'b) 
              ((enc, dec) : generic_codec 'a 'c 'd) : generic_codec 'b 'c 'd => (
  f >>> enc,
  dec >>> map g
);

let validate (f : 'a => decoder_result 'a)
              ((enc, dec) : generic_codec 'a 'c 'd) : generic_codec 'b 'c 'd => {
  (enc, fun x => dec x >>= f)
};  

let encode ((enc, _) : codec 'a) x => enc x;

let decode ((_, dec) : codec 'a) x => dec x;

let parse_json (s : string) : decoder_result Json.t => {
  try (Result.Ok (Json.parseExn s)) {
  | _ => Result.Error "JSON parsing failed"
  };
};

external format_json : Json.t => (_ [@bs.as {json|null|json}]) => int => string =
  "stringify" [@@bs.val] [@@bs.scope "JSON"];

let encode_json ::spaces=2 codec a => format_json (encode codec a) spaces;

let decode_json codec s => parse_json s >>= decode codec;

let decoder_of f error : json_decoder 'a => fun x => result_of_option (f x) error;

let decode_raw_object = decoder_of Json.decodeObject "Expected object";

let decode_raw_array = decoder_of Json.decodeArray "Expected array";

let decode_raw_float = decoder_of Json.decodeNumber "Expected number";

let decode_raw_bool = decoder_of Json.decodeBoolean "Expected boolean";

let decode_raw_string = decoder_of Json.decodeString "Expected string";

let decode_raw_null = decoder_of Json.decodeNull "Expected null";

let valid_int (x : float) : decoder_result 'float => {
  let x_as_int = int_of_float x;
  if (x == float_of_int x_as_int) {
    Result.Ok x
  } else {
    Result.Error ("Not an int: " ^ (string_of_float x))
  }
};

let float : codec float = (Json.number, decode_raw_float);

let int : codec int = float |> validate valid_int |> transform float_of_int int_of_float;

let bool : codec bool = (
  Json.boolean,
  decode_raw_bool
) |> transform Boolean.to_js_boolean to_bool;

let string : codec string = (Json.string, decode_raw_string);

let null : codec unit = (
  const Json.null,
  decode_raw_null >>> (map (const ()))
);

let alt ((enc1, dec1) : codec 'a) ((enc2, dec2): codec 'b) : codec (alt 'a 'b) => (
  either enc1 enc2,
  fun x => switch (dec1 x) {
  | Result.Ok y => Result.Ok (Left y)
  | Result.Error _ => map right (dec2 x)
  }
);

let nullable (codec : codec 'a) : codec (option 'a) => {
  let option_of_alt = either (const None) Option.some;
  let alt_of_option o => switch o {
  | Some x => right x
  | None => left ()
  };
  alt null codec |> transform alt_of_option option_of_alt
};

let decode_array_elements (decode : json_decoder 'a)
                          (elements : array Json.t) : decoder_result (array 'a) => {
  let length = Array.length elements;
  let output = [||];
  let rec loop i => {
    if (i == length) {
      Result.Ok output
    } else {
      switch (decode (A.get elements i)) {
      | Result.Ok decoded =>
          ignore (Array.push decoded output);
          loop (i + 1)

      | Result.Error error =>
          Result.Error error
      }
    }
  };
  loop 0;
};

let array ((enc, dec) : codec 'a) : codec (Array.t 'a) => {
  let encode value => Json.array (Array.map enc value);

  let decode json => decode_raw_array json >>= fun elements =>
    decode_array_elements dec elements;

  (encode, decode)
};

let decode_mandatory_field (decode : json_decoder 'a) name dict : decoder_result 'a =>
  result_of_option (Dict.get dict name) ("Field '" ^ name ^ "' not found") >>= decode;

let decode_optional_field (decode : json_decoder 'a) name dict : decoder_result (option 'a) =>
  Result.Ok (Dict.get dict name) >>= fun o =>
  switch o {
  | Some x => map Option.some (decode x)
  | None => Result.Ok None
  };

let build_dict (fields : list (option (Dict.key, Json.t))) : json_dict => {
  let dict = Dict.empty ();
  let rec loop remaining =>
    switch remaining {
    | [] => dict
    | [Some (name, value), ...tail] => Dict.set dict name value; loop tail
    | [_, ...tail] => loop tail
    };
  loop fields
};

let field (name : Dict.key) ((enc, dec) : codec 'a) : field_codec 'a => (
  fun value => Some (name, enc value),
  decode_mandatory_field dec name
);

let optional (name : Dict.key) ((enc, dec) : codec 'a) : field_codec (option 'a) => (
  /* TODO figure out why Option.map produces a compile error here */
  fun o => switch o {
  | Some value => Some (name, enc value)
  | None => None
  },
  decode_optional_field dec name
);

let optional_nullable (name : Dict.key) (codec: codec 'a) : field_codec (option 'a) => {
  let expand o => switch o {
  | Some x => Some (Some x)
  | None => Some None
  };

  let flatten o => switch o {
  | Some (Some x) => Some x
  | Some None | None => None
  };

  optional name (nullable codec) |> transform expand flatten
};

let object0 : codec unit = (
  const (Json.object_ (Dict.empty ())),
  decode_raw_object >>> map (const ())
);

let object1 ((enc1, dec1) : field_codec 'a) : codec 'a => {
  let encode v1 => Json.object_ (build_dict [enc1 v1]);

  let decode json => decode_raw_object json >>= fun dict =>
    dec1 dict;

  (encode, decode)
};

let object2 ((enc1, dec1) : field_codec 'a)
            ((enc2, dec2) : field_codec 'b) : codec ('a, 'b) => {

let encode (v1, v2) =>
  Json.object_ (build_dict [enc1 v1, enc2 v2]);

let decode json => decode_raw_object json >>= fun dict =>
  dec1 dict >>= fun v1 =>
  dec2 dict >>= fun v2 =>
  Result.Ok (v1, v2);

  (encode, decode)
};

let object3 ((enc1, dec1) : field_codec 'a)
            ((enc2, dec2) : field_codec 'b)
            ((enc3, dec3) : field_codec 'c) : codec ('a, 'b, 'c) => {

let encode (v1, v2, v3) =>
  Json.object_ (build_dict [enc1 v1, enc2 v2, enc3 v3]);

let decode json => decode_raw_object json >>= fun dict =>
  dec1 dict >>= fun v1 =>
  dec2 dict >>= fun v2 =>
  dec3 dict >>= fun v3 =>
  Result.Ok (v1, v2, v3);

  (encode, decode)
};

let object4 ((enc1, dec1) : field_codec 'a)
            ((enc2, dec2) : field_codec 'b)
            ((enc3, dec3) : field_codec 'c)
            ((enc4, dec4) : field_codec 'd) : codec ('a, 'b, 'c, 'd) => {

  let encode (v1, v2, v3, v4) =>
    Json.object_ (build_dict [enc1 v1, enc2 v2, enc3 v3, enc4 v4]);

  let decode json => decode_raw_object json >>= fun dict =>
    dec1 dict >>= fun v1 =>
    dec2 dict >>= fun v2 =>
    dec3 dict >>= fun v3 =>
    dec4 dict >>= fun v4 =>
    Result.Ok (v1, v2, v3, v4);

  (encode, decode)
};

let object5 ((enc1, dec1) : field_codec 'a)
            ((enc2, dec2) : field_codec 'b)
            ((enc3, dec3) : field_codec 'c)
            ((enc4, dec4) : field_codec 'd)
            ((enc5, dec5) : field_codec 'e) : codec ('a, 'b, 'c, 'd, 'e) => {

  let encode (v1, v2, v3, v4, v5) =>
    Json.object_ (build_dict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5]);

  let decode json => decode_raw_object json >>= fun dict =>
    dec1 dict >>= fun v1 =>
    dec2 dict >>= fun v2 =>
    dec3 dict >>= fun v3 =>
    dec4 dict >>= fun v4 =>
    dec5 dict >>= fun v5 =>
    Result.Ok (v1, v2, v3, v4, v5);

  (encode, decode)
};

let object6 ((enc1, dec1) : field_codec 'a)
            ((enc2, dec2) : field_codec 'b)
            ((enc3, dec3) : field_codec 'c)
            ((enc4, dec4) : field_codec 'd)
            ((enc5, dec5) : field_codec 'e)
            ((enc6, dec6) : field_codec 'f) : codec ('a, 'b, 'c, 'd, 'e, 'f) => {

  let encode (v1, v2, v3, v4, v5, v6) =>
    Json.object_ (build_dict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5, enc6 v6]);

  let decode json => decode_raw_object json >>= fun dict =>
    dec1 dict >>= fun v1 =>
    dec2 dict >>= fun v2 =>
    dec3 dict >>= fun v3 =>
    dec4 dict >>= fun v4 =>
    dec5 dict >>= fun v5 =>
    dec6 dict >>= fun v6 =>
    Result.Ok (v1, v2, v3, v4, v5, v6);

  (encode, decode)
};

let object7 ((enc1, dec1) : field_codec 'a)
            ((enc2, dec2) : field_codec 'b)
            ((enc3, dec3) : field_codec 'c)
            ((enc4, dec4) : field_codec 'd)
            ((enc5, dec5) : field_codec 'e)
            ((enc6, dec6) : field_codec 'f)
            ((enc7, dec7) : field_codec 'g) : codec ('a, 'b, 'c, 'd, 'e, 'f, 'g) => {

  let encode (v1, v2, v3, v4, v5, v6, v7) =>
    Json.object_ (build_dict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5, enc6 v6, enc7 v7]);

  let decode json => decode_raw_object json >>= fun dict =>
    dec1 dict >>= fun v1 =>
    dec2 dict >>= fun v2 =>
    dec3 dict >>= fun v3 =>
    dec4 dict >>= fun v4 =>
    dec5 dict >>= fun v5 =>
    dec6 dict >>= fun v6 =>
    dec7 dict >>= fun v7 =>
    Result.Ok (v1, v2, v3, v4, v5, v6, v7);

  (encode, decode)
};

let object8 ((enc1, dec1) : field_codec 'a)
            ((enc2, dec2) : field_codec 'b)
            ((enc3, dec3) : field_codec 'c)
            ((enc4, dec4) : field_codec 'd)
            ((enc5, dec5) : field_codec 'e)
            ((enc6, dec6) : field_codec 'f)
            ((enc7, dec7) : field_codec 'g)
            ((enc8, dec8) : field_codec 'h) : codec ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h) => {

  let encode (v1, v2, v3, v4, v5, v6, v7, v8) =>
    Json.object_ (build_dict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5, enc6 v6, enc7 v7, enc8 v8]);

  let decode json => decode_raw_object json >>= fun dict =>
    dec1 dict >>= fun v1 =>
    dec2 dict >>= fun v2 =>
    dec3 dict >>= fun v3 =>
    dec4 dict >>= fun v4 =>
    dec5 dict >>= fun v5 =>
    dec6 dict >>= fun v6 =>
    dec7 dict >>= fun v7 =>
    dec8 dict >>= fun v8 =>
    Result.Ok (v1, v2, v3, v4, v5, v6, v7, v8);

  (encode, decode)
};

let object9 ((enc1, dec1) : field_codec 'a)
            ((enc2, dec2) : field_codec 'b)
            ((enc3, dec3) : field_codec 'c)
            ((enc4, dec4) : field_codec 'd)
            ((enc5, dec5) : field_codec 'e)
            ((enc6, dec6) : field_codec 'f)
            ((enc7, dec7) : field_codec 'g)
            ((enc8, dec8) : field_codec 'h)
            ((enc9, dec9) : field_codec 'i) : codec ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i) => {

  let encode (v1, v2, v3, v4, v5, v6, v7, v8, v9) =>
    Json.object_ (build_dict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5, enc6 v6, enc7 v7, enc8 v8, enc9 v9]);

  let decode json => decode_raw_object json >>= fun dict =>
    dec1 dict >>= fun v1 =>
    dec2 dict >>= fun v2 =>
    dec3 dict >>= fun v3 =>
    dec4 dict >>= fun v4 =>
    dec5 dict >>= fun v5 =>
    dec6 dict >>= fun v6 =>
    dec7 dict >>= fun v7 =>
    dec8 dict >>= fun v8 =>
    dec9 dict >>= fun v9 =>
    Result.Ok (v1, v2, v3, v4, v5, v6, v7, v8, v9);

  (encode, decode)
};

let object10 ((enc1, dec1) : field_codec 'a)
             ((enc2, dec2) : field_codec 'b)
             ((enc3, dec3) : field_codec 'c)
             ((enc4, dec4) : field_codec 'd)
             ((enc5, dec5) : field_codec 'e)
             ((enc6, dec6) : field_codec 'f)
             ((enc7, dec7) : field_codec 'g)
             ((enc8, dec8) : field_codec 'h)
             ((enc9, dec9) : field_codec 'i)
             ((enc10, dec10) : field_codec 'j) : codec ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j) => {

  let encode (v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) =>
    Json.object_ (build_dict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5, enc6 v6, enc7 v7, enc8 v8, enc9 v9, enc10 v10]);

  let decode json => decode_raw_object json >>= fun dict =>
    dec1 dict >>= fun v1 =>
    dec2 dict >>= fun v2 =>
    dec3 dict >>= fun v3 =>
    dec4 dict >>= fun v4 =>
    dec5 dict >>= fun v5 =>
    dec6 dict >>= fun v6 =>
    dec7 dict >>= fun v7 =>
    dec8 dict >>= fun v8 =>
    dec9 dict >>= fun v9 =>
    dec10 dict >>= fun v10 =>
    Result.Ok (v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);

  (encode, decode)
};
