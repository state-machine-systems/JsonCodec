open Jest;
module C = JsonCodec;

let formatJsonString s => Js.Json.parseExn s |> Js.Json.stringify;

type tree 'a =
  | Leaf 'a
  | Branch (tree 'a) (tree 'a);

let () =
  describe "JsonCodec"
    ExpectJs.(fun () => {
      let jsonString = "\"foo\"";
      let jsonNumberArray = formatJsonString "[1.1, 2.2]";
      let jsonEmptyObject = "{}";
      let jsonSingleStringFieldObject = formatJsonString {js|{"foo": "bar"}|js};
      let jsonSingleNumberFieldObject = formatJsonString {js|{"foo": 12.34}|js};
      let jsonTwoFieldObject = formatJsonString {js|{"foo": "bar", "baz": true}|js};
      let jsonThreeFieldObject = formatJsonString {js|{"foo": "bar", "baz": true, "qux": 56.78}|js};
      let jsonFourFieldObject = formatJsonString {js|{"foo": "bar", "baz": true, "qux": 56.78, "quux": null}|js};

      describe "number" (fun () => {
        test "encoding" (fun () =>
          expect (C.encodeJson C.number 3.14) |> toEqual "3.14"
        );
        test "decoding success" (fun () =>
          expect (C.decodeJson C.number "3.14") |> toEqual (Js.Result.Ok 3.14)
        );
        test "decoding failure, not a number" (fun () =>
          expect (C.decodeJson C.number jsonString) |> toEqual (Js.Result.Error "Expected number")
        );
        test "decoding failure, invalid JSON" (fun () =>
          expect (C.decodeJson C.number "_") |> toEqual (Js.Result.Error "Unexpected token _ in JSON at position 0")
        );
      });

      describe "int" (fun () => {
        test "encoding" (fun () =>
          expect (C.encodeJson C.int 1) |> toEqual "1"
        );
        test "decoding success, no decimal point" (fun () =>
          expect (C.decodeJson C.int "1") |> toEqual (Js.Result.Ok 1)
        );
        test "decoding success, zero after decimal point" (fun () =>
          expect (C.decodeJson C.int "1.0") |> toEqual (Js.Result.Ok 1)
        );
        test "decoding failure, can't represent as int" (fun () =>
          expect (C.decodeJson C.int "1.234") |> toEqual (Js.Result.Error "Not an int: 1.234")
        );
      });

      describe "string" (fun () => {
        test "encoding" (fun () =>
          expect (C.encodeJson C.string "foo") |> toEqual jsonString
        );
        test "decoding success" (fun () =>
          expect (C.decodeJson C.string jsonString) |> toEqual (Js.Result.Ok "foo")
        );
        test "decoding failure" (fun () =>
          expect (C.decodeJson C.string "0.5") |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "bool" (fun () => {
        test "encoding" (fun () =>
          expect (C.encodeJson C.bool true) |> toEqual "true"
        );
        test "decoding success" (fun () =>
          expect (C.decodeJson C.bool "false") |> toEqual (Js.Result.Ok false)
        );
        test "decoding failure" (fun () =>
          expect (C.decodeJson C.bool jsonString) |> toEqual (Js.Result.Error "Expected boolean")
        );
      });

      describe "null" (fun () => {
        test "encoding" (fun () =>
          expect (C.encodeJson C.null ()) |> toEqual "null"
        );
        test "decoding success" (fun () =>
          expect (C.decodeJson C.null "null") |> toEqual (Js.Result.Ok ())
        );
        test "decoding failure" (fun () =>
          expect (C.decodeJson C.null "true") |> toEqual (Js.Result.Error "Expected null")
        );
      });

      describe "nullable" (fun () => {
        test "empty encoding" (fun () =>
          expect (C.encodeJson (C.nullable C.string) None) |> toEqual "null"
        );
        test "empty decoding success" (fun () =>
          expect (C.decodeJson (C.nullable C.string) "null") |> toEqual (Js.Result.Ok None)
        );
        test "non-empty encoding" (fun () =>
          expect (C.encodeJson (C.nullable C.string) (Some "foo")) |> toEqual jsonString
        );
        test "non-empty decoding success" (fun () =>
          expect (C.decodeJson (C.nullable C.number) "1.0") |> toEqual (Js.Result.Ok (Some 1.0))
        );
        test "decoding failure" (fun () =>
          expect (C.decodeJson (C.nullable C.string) "1.0") |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "array" (fun () => {
        test "empty encoding" (fun () =>
          expect (C.encodeJson (C.array C.number) [||]) |> toEqual "[]"
        );
        test "empty decoding" (fun () =>
          expect (C.decodeJson (C.array C.string) "[]") |> toEqual (Js.Result.Ok [||])
        );
        test "non-empty encoding" (fun () =>
          expect (C.encodeJson (C.array C.number) [| 1.1, 2.2 |] |> formatJsonString) |> toEqual jsonNumberArray
        );
        test "non-empty decoding success" (fun () =>
          expect (C.decodeJson (C.array C.number) jsonNumberArray) |> toEqual (Js.Result.Ok [| 1.1, 2.2 |])
        );
        test "decoding failure" (fun () =>
          expect (C.decodeJson (C.array C.string) "true") |> toEqual (Js.Result.Error "Expected array")
        );
        test "element decoding failure" (fun () =>
          expect (C.decodeJson (C.array C.string) jsonNumberArray) |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "object0" (fun () => {
        test "encoding" (fun () =>
          expect (C.encodeJson C.object0 ()) |> toEqual "{}"
        );
        test "decoding success" (fun () =>
          expect (C.decodeJson C.object0 "{}") |> toEqual (Js.Result.Ok ())
        );
        test "decoding success, ignoring extra fields" (fun () =>
          expect (C.decodeJson C.object0 jsonSingleStringFieldObject) |> toEqual (Js.Result.Ok ())
        );
        test "decoding failure" (fun () =>
          expect (C.decodeJson C.object0 "null") |> toEqual (Js.Result.Error "Expected object")
        );
      });

      describe "object1" (fun () => {
        let codec = C.object1 (C.field "foo" C.string);

        test "encoding" (fun () =>
          expect (C.encodeJson spaces::0 codec "bar") |> toEqual jsonSingleStringFieldObject
        );
        test "decoding success" (fun () =>
          expect (C.decodeJson codec jsonSingleStringFieldObject) |> toEqual (Js.Result.Ok "bar")
        );
        test "decoding success, ignoring extra fields" (fun () =>
          expect (C.decodeJson codec jsonTwoFieldObject) |> toEqual (Js.Result.Ok "bar")
        );
        test "decoding failure, not an object" (fun () =>
          expect (C.decodeJson codec "false") |> toEqual (Js.Result.Error "Expected object")
        );
        test "decoding failure, missing field" (fun () =>
          expect (C.decodeJson codec "{}") |> toEqual (Js.Result.Error "Field 'foo' not found")
        );
        test "decoding failure, wrong field type" (fun () =>
          expect (C.decodeJson codec jsonSingleNumberFieldObject) |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "object2" (fun () => {
        let codec = C.object2 (C.field "foo" C.string) (C.field "baz" C.bool);

        test "encoding" (fun () =>
          expect (C.encodeJson spaces::0 codec ("bar", true)) |> toEqual jsonTwoFieldObject
        );
        test "decoding success" (fun () => {
          expect (C.decodeJson codec jsonTwoFieldObject) |> toEqual (Js.Result.Ok ("bar", true))
        });
        test "decoding success, ignoring extra fields" (fun () => {
          expect (C.decodeJson codec jsonThreeFieldObject) |> toEqual (Js.Result.Ok ("bar", true))
        });
        test "decoding failure, not an object" (fun () =>
          expect (C.decodeJson codec "7.77") |> toEqual (Js.Result.Error "Expected object")
        );
        test "decoding failure, missing field" (fun () =>
          expect (C.decodeJson codec jsonSingleStringFieldObject) |> toEqual (Js.Result.Error "Field 'baz' not found")
        );
        test "decoding failure, wrong field type" (fun () =>
          expect (C.decodeJson codec jsonSingleNumberFieldObject) |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "object3" (fun () => {
        let codec = C.object3 (C.field "foo" C.string) (C.field "baz" C.bool) (C.field "qux" C.number);

        test "encoding" (fun () =>
          expect (C.encodeJson spaces::0 codec ("bar", true, 56.78)) |> toEqual jsonThreeFieldObject
        );
        test "decoding success" (fun () => {
          expect (C.decodeJson codec jsonThreeFieldObject) |> toEqual (Js.Result.Ok ("bar", true, 56.78))
        });
        test "decoding success, ignoring extra fields" (fun () => {
          expect (C.decodeJson codec jsonFourFieldObject) |> toEqual (Js.Result.Ok ("bar", true, 56.78))
        });
        test "decoding failure, not an object" (fun () =>
          expect (C.decodeJson codec "null") |> toEqual (Js.Result.Error "Expected object")
        );
        test "decoding failure, missing field" (fun () =>
          expect (C.decodeJson codec jsonTwoFieldObject) |> toEqual (Js.Result.Error "Field 'qux' not found")
        );
        test "decoding failure, wrong field type" (fun () =>
          expect (C.decodeJson codec jsonSingleNumberFieldObject) |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "object4" (fun () => {
        let codec = C.object4 (C.field "foo" C.string) (C.field "baz" C.bool) (C.field "qux" C.number) (C.field "quux" C.null);

        test "encoding" (fun () =>
          expect (C.encodeJson spaces::0 codec ("bar", true, 56.78, ())) |> toEqual jsonFourFieldObject
        );
        test "decoding" (fun () =>
          expect (C.decodeJson codec jsonFourFieldObject) |> toEqual (Js.Result.Ok ("bar", true, 56.78, ()))
        );
      });

      describe "object5" (fun () => {
        let json = formatJsonString {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5}|js};
        let codec = C.object5 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int);

        test "encoding" (fun () =>
          expect (C.encodeJson spaces::0 codec (1, 2, 3, 4, 5)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decodeJson codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5))
        );
      });

      describe "object6" (fun () => {
        let json = formatJsonString {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6}|js};
        let codec = C.object6 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int) (C.field "f6" C.int);

        test "encoding" (fun () =>
          expect (C.encodeJson spaces::0 codec (1, 2, 3, 4, 5, 6)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decodeJson codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5, 6))
        );
      });

      describe "object7" (fun () => {
        let json = formatJsonString {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7}|js};
        let codec = C.object7 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int) (C.field "f6" C.int) (C.field "f7" C.int);

        test "encoding" (fun () =>
          expect (C.encodeJson spaces::0 codec (1, 2, 3, 4, 5, 6, 7)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decodeJson codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5, 6, 7))
        );
      });

      describe "object8" (fun () => {
        let json = formatJsonString {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7, "f8": 8}|js};
        let codec = C.object8 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int) (C.field "f6" C.int) (C.field "f7" C.int) (C.field "f8" C.int);

        test "encoding" (fun () =>
          expect (C.encodeJson spaces::0 codec (1, 2, 3, 4, 5, 6, 7, 8)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decodeJson codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5, 6, 7, 8))
        );
      });

      describe "object9" (fun () => {
        let json = formatJsonString {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7, "f8": 8, "f9": 9}|js};
        let codec = C.object9 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int) (C.field "f6" C.int) (C.field "f7" C.int) (C.field "f8" C.int) (C.field "f9" C.int);

        test "encoding" (fun () =>
          expect (C.encodeJson spaces::0 codec (1, 2, 3, 4, 5, 6, 7, 8, 9)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decodeJson codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5, 6, 7, 8, 9))
        );
      });

      describe "object10" (fun () => {
        let json = formatJsonString {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7, "f8": 8, "f9": 9, "f10": 10}|js};
        let codec = C.object10 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int) (C.field "f6" C.int) (C.field "f7" C.int) (C.field "f8" C.int) (C.field "f9" C.int) (C.field "f10" C.int);

        test "encoding" (fun () =>
          expect (C.encodeJson spaces::0 codec (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decodeJson codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
        );
      });

      describe "optional and nullable fields" (fun () => {
        let nullableFieldCodec = C.(object1 (field "foo" (nullable string)));
        let optionalFieldCodec = C.(object1 (optional "foo" string));
        let optionalNullableFieldCodec = C.(object1 (optional "foo" (nullable string)));
        let flattenedFieldCodec = C.(object1 (C.optionalNullable "foo" string));

        let jsonNullField = formatJsonString "{\"foo\": null}";

        describe "nullable field" (fun () => {
          test "empty encoding" (fun () =>
            expect (C.encodeJson spaces::0 nullableFieldCodec None) |> toEqual jsonNullField
          );
          test "empty decoding" (fun () =>
            expect (C.decodeJson nullableFieldCodec jsonNullField) |> toEqual (Js.Result.Ok None)
          );
          test "non-empty encoding" (fun () =>
            expect (C.encodeJson spaces::0 nullableFieldCodec (Some "bar")) |> toEqual jsonSingleStringFieldObject
          );
          test "non-empty decoding" (fun () =>
            expect (C.decodeJson nullableFieldCodec jsonSingleStringFieldObject) |> toEqual (Js.Result.Ok (Some "bar"))
          );
        });

        describe "optional field" (fun () => {
          test "empty encoding" (fun () =>
            expect (C.encodeJson optionalFieldCodec None) |> toEqual jsonEmptyObject
          );
          test "empty decoding" (fun () =>
            expect (C.decodeJson optionalFieldCodec jsonEmptyObject) |> toEqual (Js.Result.Ok None)
          );
          test "non-empty encoding" (fun () =>
            expect (C.encodeJson spaces::0 optionalFieldCodec (Some "bar")) |> toEqual jsonSingleStringFieldObject
          );
          test "non-empty decoding success" (fun () =>
            expect (C.decodeJson optionalFieldCodec jsonSingleStringFieldObject) |> toEqual (Js.Result.Ok (Some "bar"))
          );
          test "non-empty decoding failure" (fun () =>
            expect (C.decodeJson optionalFieldCodec jsonSingleNumberFieldObject) |> toEqual (Js.Result.Error "Expected string")
          );
        });

        describe "optional nullable field" (fun () => {
          test "empty encoding" (fun () =>
            expect (C.encodeJson optionalNullableFieldCodec None) |> toEqual jsonEmptyObject
          );
          test "empty decoding" (fun () =>
            expect (C.decodeJson optionalNullableFieldCodec jsonEmptyObject) |> toEqual (Js.Result.Ok None)
          );
          test "null encoding" (fun () =>
            expect (C.encodeJson spaces::0 optionalNullableFieldCodec (Some None)) |> toEqual jsonNullField
          );
          test "null decoding" (fun () =>
            expect (C.decodeJson optionalNullableFieldCodec jsonNullField) |> toEqual (Js.Result.Ok (Some None))
          );
          test "non-null encoding" (fun () =>
            expect (C.encodeJson spaces::0 optionalNullableFieldCodec (Some (Some "bar"))) |> toEqual jsonSingleStringFieldObject
          );
          test "non-null decoding" (fun () =>
            expect (C.decodeJson optionalNullableFieldCodec jsonSingleStringFieldObject) |> toEqual (Js.Result.Ok (Some (Some "bar")))
          );
        });

        describe "flattened optional nullable field" (fun () => {
          test "empty encoding" (fun () =>
            expect (C.encodeJson spaces::0 flattenedFieldCodec None) |> toEqual jsonNullField
          );
          test "empty decoding, missing field" (fun () =>
            expect (C.decodeJson flattenedFieldCodec jsonEmptyObject) |> toEqual (Js.Result.Ok None)
          );
          test "empty decoding, null field" (fun () =>
            expect (C.decodeJson flattenedFieldCodec jsonNullField) |> toEqual (Js.Result.Ok None)
          );
          test "non-empty encoding" (fun () =>
            expect (C.encodeJson spaces::0 flattenedFieldCodec (Some "bar")) |> toEqual jsonSingleStringFieldObject
          );
          test "non-empty decoding" (fun () =>
            expect (C.decodeJson flattenedFieldCodec jsonSingleStringFieldObject) |> toEqual (Js.Result.Ok (Some "bar"))
          );
        });
      });

      describe "recursion" (fun () => {
        let intTree = Branch (Branch (Leaf 1) (Leaf 2)) (Leaf 3);

        let intTreeJson = formatJsonString {js|{"left": {"left": 1, "right": 2}, "right": 3}|js};

        let treeToXor = fun
        | Leaf x => C.Xor.left x
        | Branch l r  => C.Xor.right (l, r);

        let xorToTree = fun
        | C.Xor.Left x => Leaf x
        | C.Xor.Right (l, r) => Branch l r;

        let codec = JsonCodec.(fix (fun tree =>        
          xor int (object2 (field "left" tree) (field "right" tree)) |> wrap treeToXor xorToTree
        ));

        test "encoding" (fun () =>
          expect (C.encodeJson spaces::0 codec intTree) |> toEqual intTreeJson
        );
        test "decoding" (fun () =>
          expect (C.decodeJson codec intTreeJson) |> toEqual (Js.Result.Ok intTree)
        );
      });
    })
