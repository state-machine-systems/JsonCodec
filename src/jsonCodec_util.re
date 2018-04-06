module Result = JsonCodec_result;

open Result.Ops;

let parseJson = s =>
  try (Result.Ok(Js.Json.parseExn(s))) {
  | Js.Exn.Error(e) =>
    Result.Error(
      Js.Exn.message(e) |> Js.Option.getWithDefault("JSON parsing failed"),
    )
  };

[@bs.val] [@bs.scope "JSON"]
external formatJson : (Js.Json.t, [@bs.as {json|null|json}] _, int) => string =
  "stringify";

let decodeArrayElements = (decode, elements) => {
  let length = Js.Array.length(elements);
  let output = [||];
  let rec loop = i =>
    if (i == length) {
      Result.Ok(output);
    } else {
      switch (decode(elements[i])) {
      | Result.Ok(decoded) =>
        ignore(Js.Array.push(decoded, output));
        loop(i + 1);
      | Result.Error(error) => Result.Error(error)
      };
    };
  loop(0);
};

let decoderOf = (f, error, x) => Result.fromOption(f(x), error);

let decodeRawObject = decoderOf(Js.Json.decodeObject, "Expected object");

let decodeRawArray = decoderOf(Js.Json.decodeArray, "Expected array");

let decodeRawNumber = decoderOf(Js.Json.decodeNumber, "Expected number");

let decodeRawBool = decoderOf(Js.Json.decodeBoolean, "Expected boolean");

let decodeRawString = decoderOf(Js.Json.decodeString, "Expected string");

let decodeRawNull = decoderOf(Js.Json.decodeNull, "Expected null");

let validInt = (x: float) => {
  let xInt = int_of_float(x);
  if (x == float_of_int(xInt)) {
    Result.Ok(x);
  } else {
    Result.Error("Not an int: " ++ string_of_float(x));
  };
};

let decodeMandatoryField = (decode, name, dict) =>
  Result.fromOption(
    Js.Dict.get(dict, name),
    "Field '" ++ name ++ "' not found",
  )
  >>= decode;

let decodeOptionalField = (decode, name, dict) =>
  Result.Ok(Js.Dict.get(dict, name))
  >>= (
    fun
    | Some(x) => decode(x) |> Result.map(Js.Option.some)
    | None => Result.Ok(None)
  );

let buildDict = fields => {
  let dict = Js.Dict.empty();
  let rec loop = remaining =>
    switch (remaining) {
    | [] => dict
    | [Some((name, value)), ...tail] =>
      Js.Dict.set(dict, name, value);
      loop(tail);
    | [None, ...tail] => loop(tail)
    };
  loop(fields);
};
