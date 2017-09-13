module Result = JsonCodec_result;

open Result.Ops;

module Encoder = {
  type t 'a 'b = 'a => 'b;
};

module Decoder = {
  type error = string;
  type result 'a = Result.t 'a error;
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

let encode ((enc, _): Codec.t 'a) x => enc x;

let decode ((_, dec): Codec.t 'a) x => dec x;

let parseJson (s: string) :Decoder.result Js.Json.t =>
  try (Result.Ok (Js.Json.parseExn s)) {
  | Js.Exn.Error e => Result.Error (Js.Exn.message e |> Js.Option.default "JSON parsing failed")
  };

external formatJson : Js.Json.t => _ [@bs.as {json|null|json}] => int => string =
  "stringify" [@@bs.val] [@@bs.scope "JSON"];

let encodeJson ::spaces=2 codec a => formatJson (encode codec a) spaces;

let decodeJson codec s => parseJson s >>= decode codec;
