module Encoder = {
  type t 'a 'b = 'a => 'b;
};

module Decoder = {
  type error = string;
  type result 'a = Js.Result.t 'a error;
  type t 'a 'b = 'b => result 'a;
};

module JsonEncoder = {
  type t 'a = Encoder.t 'a Js.Json.t;
};

module JsonDecoder = {
  type t 'a = Decoder.t 'a Js.Json.t;
};

module Codec = {
  type t 'a = (JsonEncoder.t 'a, JsonDecoder.t 'a);
};

module GenericCodec = {
  type t 'a 'b 'c = (Encoder.t 'a 'b, Decoder.t 'a 'c);
};

module FieldEncoder = {
  type t 'a = Encoder.t 'a (option (Js.Dict.key, Js.Json.t));
};

module FieldDecoder = {
  type dict = Js.Dict.t Js.Json.t;
  type t 'a = Decoder.t 'a dict;
};

module FieldCodec = {
  type t 'a = (FieldEncoder.t 'a, FieldDecoder.t 'a);
};
