let const = (x, _) => x;

module Ops = {
  let (>>>) = (f, g, x) => g(f(x));
};
