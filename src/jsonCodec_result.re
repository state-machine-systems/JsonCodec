include Belt.Result;

let fromOption = (o: option('a), error: 'b) : t('a, 'b) =>
  switch (o) {
  | Some(x) => Ok(x)
  | None => Error(error)
  };

let map = (f: 'a => 'b, result: t('a, 'c)) : t('b, 'c) =>
  switch (result) {
  | Ok(x) => Ok(f(x))
  | Error(y) => Error(y)
  };

module Ops = {
  let (>>=) = (result: t('a, 'c), f: 'a => t('b, 'c)) : t('b, 'c) =>
    switch (result) {
    | Ok(x) => f(x)
    | Error(y) => Error(y)
    };
};
