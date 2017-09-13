module Function = JsonCodec_function;

type t 'a 'b =
  | Left 'a
  | Right 'b;

let left a :t 'a 'b => Left a;

let right b :t 'a 'b => Right b;

let either f g xor =>
  switch xor {
  | Left x => f x
  | Right y => g y
  };

let toOption x => either (Function.const None) Js.Option.some @@ x;

let fromOption =
  fun
  | Some x => right x
  | None => left ();
