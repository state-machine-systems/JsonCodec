open Jest;

module C = JsonCodec;
module Result = JsonCodec.Result;

let formatJsonString = s => Js.Json.parseExn(s) |> Js.Json.stringify;

type tree('a) =
  | Leaf('a)
  | Branch(tree('a), tree('a));

let () =
  describe(
    "JsonCodec",
    ExpectJs.(
      () => {
        let jsonString = "\"foo\"";
        let jsonNumberArray = formatJsonString("[1.1, 2.2]");
        let jsonEmptyObject = "{}";
        let jsonSingleStringFieldObject =
          formatJsonString({js|{"foo": "bar"}|js});
        let jsonSingleNumberFieldObject =
          formatJsonString({js|{"foo": 12.34}|js});
        let jsonTwoFieldObject =
          formatJsonString({js|{"foo": "bar", "baz": true}|js});
        let jsonThreeFieldObject =
          formatJsonString({js|{"foo": "bar", "baz": true, "qux": 56.78}|js});
        let jsonFourFieldObject =
          formatJsonString(
            {js|{"foo": "bar", "baz": true, "qux": 56.78, "quux": null}|js},
          );
        describe("number", () => {
          test("encoding", () =>
            expect(C.encodeJson(C.number, 3.14)) |> toEqual("3.14")
          );
          test("decoding success", () =>
            expect(C.decodeJson(C.number, "3.14"))
            |> toEqual(Result.Ok(3.14))
          );
          test("decoding failure, not a number", () =>
            expect(C.decodeJson(C.number, jsonString))
            |> toEqual(Result.Error("Expected number"))
          );
          test("decoding failure, invalid JSON", () =>
            expect(C.decodeJson(C.number, "_"))
            |> toEqual(
                 Result.Error("Unexpected token _ in JSON at position 0"),
               )
          );
        });
        describe("int", () => {
          test("encoding", () =>
            expect(C.encodeJson(C.int, 1)) |> toEqual("1")
          );
          test("decoding success, no decimal point", () =>
            expect(C.decodeJson(C.int, "1")) |> toEqual(Result.Ok(1))
          );
          test("decoding success, zero after decimal point", () =>
            expect(C.decodeJson(C.int, "1.0")) |> toEqual(Result.Ok(1))
          );
          test("decoding failure, can't represent as int", () =>
            expect(C.decodeJson(C.int, "1.234"))
            |> toEqual(Result.Error("Not an int: 1.234"))
          );
        });
        describe("string", () => {
          test("encoding", () =>
            expect(C.encodeJson(C.string, "foo")) |> toEqual(jsonString)
          );
          test("decoding success", () =>
            expect(C.decodeJson(C.string, jsonString))
            |> toEqual(Result.Ok("foo"))
          );
          test("decoding failure", () =>
            expect(C.decodeJson(C.string, "0.5"))
            |> toEqual(Result.Error("Expected string"))
          );
        });
        describe("bool", () => {
          test("encoding", () =>
            expect(C.encodeJson(C.bool, true)) |> toEqual("true")
          );
          test("decoding success", () =>
            expect(C.decodeJson(C.bool, "false"))
            |> toEqual(Result.Ok(false))
          );
          test("decoding failure", () =>
            expect(C.decodeJson(C.bool, jsonString))
            |> toEqual(Result.Error("Expected boolean"))
          );
        });
        describe("null", () => {
          test("encoding", () =>
            expect(C.encodeJson(C.null, ())) |> toEqual("null")
          );
          test("decoding success", () =>
            expect(C.decodeJson(C.null, "null")) |> toEqual(Result.Ok())
          );
          test("decoding failure", () =>
            expect(C.decodeJson(C.null, "true"))
            |> toEqual(Result.Error("Expected null"))
          );
        });
        describe("nullable", () => {
          test("empty encoding", () =>
            expect(C.encodeJson(C.nullable(C.string), None))
            |> toEqual("null")
          );
          test("empty decoding success", () =>
            expect(C.decodeJson(C.nullable(C.string), "null"))
            |> toEqual(Result.Ok(None))
          );
          test("non-empty encoding", () =>
            expect(C.encodeJson(C.nullable(C.string), Some("foo")))
            |> toEqual(jsonString)
          );
          test("non-empty decoding success", () =>
            expect(C.decodeJson(C.nullable(C.number), "1.0"))
            |> toEqual(Result.Ok(Some(1.0)))
          );
          test("decoding failure", () =>
            expect(C.decodeJson(C.nullable(C.string), "1.0"))
            |> toEqual(Result.Error("Expected string"))
          );
        });
        describe("array", () => {
          test("empty encoding", () =>
            expect(C.encodeJson(C.array(C.number), [||])) |> toEqual("[]")
          );
          test("empty decoding", () =>
            expect(C.decodeJson(C.array(C.string), "[]"))
            |> toEqual(Result.Ok([||]))
          );
          test("non-empty encoding", () =>
            expect(
              C.encodeJson(C.array(C.number), [|1.1, 2.2|])
              |> formatJsonString,
            )
            |> toEqual(jsonNumberArray)
          );
          test("non-empty decoding success", () =>
            expect(C.decodeJson(C.array(C.number), jsonNumberArray))
            |> toEqual(Result.Ok([|1.1, 2.2|]))
          );
          test("decoding failure", () =>
            expect(C.decodeJson(C.array(C.string), "true"))
            |> toEqual(Result.Error("Expected array"))
          );
          test("element decoding failure", () =>
            expect(C.decodeJson(C.array(C.string), jsonNumberArray))
            |> toEqual(Result.Error("Expected string"))
          );
        });
        describe("object0", () => {
          test("encoding", () =>
            expect(C.encodeJson(C.object0, ())) |> toEqual("{}")
          );
          test("decoding success", () =>
            expect(C.decodeJson(C.object0, "{}")) |> toEqual(Result.Ok())
          );
          test("decoding success, ignoring extra fields", () =>
            expect(C.decodeJson(C.object0, jsonSingleStringFieldObject))
            |> toEqual(Result.Ok())
          );
          test("decoding failure", () =>
            expect(C.decodeJson(C.object0, "null"))
            |> toEqual(Result.Error("Expected object"))
          );
        });
        describe("object1", () => {
          let codec = C.object1(C.field("foo", C.string));
          test("encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, "bar"))
            |> toEqual(jsonSingleStringFieldObject)
          );
          test("decoding success", () =>
            expect(C.decodeJson(codec, jsonSingleStringFieldObject))
            |> toEqual(Result.Ok("bar"))
          );
          test("decoding success, ignoring extra fields", () =>
            expect(C.decodeJson(codec, jsonTwoFieldObject))
            |> toEqual(Result.Ok("bar"))
          );
          test("decoding failure, not an object", () =>
            expect(C.decodeJson(codec, "false"))
            |> toEqual(Result.Error("Expected object"))
          );
          test("decoding failure, missing field", () =>
            expect(C.decodeJson(codec, "{}"))
            |> toEqual(Result.Error("Field 'foo' not found"))
          );
          test("decoding failure, wrong field type", () =>
            expect(C.decodeJson(codec, jsonSingleNumberFieldObject))
            |> toEqual(Result.Error("Expected string"))
          );
        });
        describe("object2", () => {
          let codec =
            C.object2(C.field("foo", C.string), C.field("baz", C.bool));
          test("encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, ("bar", true)))
            |> toEqual(jsonTwoFieldObject)
          );
          test("decoding success", () =>
            expect(C.decodeJson(codec, jsonTwoFieldObject))
            |> toEqual(Result.Ok(("bar", true)))
          );
          test("decoding success, ignoring extra fields", () =>
            expect(C.decodeJson(codec, jsonThreeFieldObject))
            |> toEqual(Result.Ok(("bar", true)))
          );
          test("decoding failure, not an object", () =>
            expect(C.decodeJson(codec, "7.77"))
            |> toEqual(Result.Error("Expected object"))
          );
          test("decoding failure, missing field", () =>
            expect(C.decodeJson(codec, jsonSingleStringFieldObject))
            |> toEqual(Result.Error("Field 'baz' not found"))
          );
          test("decoding failure, wrong field type", () =>
            expect(C.decodeJson(codec, jsonSingleNumberFieldObject))
            |> toEqual(Result.Error("Expected string"))
          );
        });
        describe("object3", () => {
          let codec =
            C.object3(
              C.field("foo", C.string),
              C.field("baz", C.bool),
              C.field("qux", C.number),
            );
          test("encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, ("bar", true, 56.78)))
            |> toEqual(jsonThreeFieldObject)
          );
          test("decoding success", () =>
            expect(C.decodeJson(codec, jsonThreeFieldObject))
            |> toEqual(Result.Ok(("bar", true, 56.78)))
          );
          test("decoding success, ignoring extra fields", () =>
            expect(C.decodeJson(codec, jsonFourFieldObject))
            |> toEqual(Result.Ok(("bar", true, 56.78)))
          );
          test("decoding failure, not an object", () =>
            expect(C.decodeJson(codec, "null"))
            |> toEqual(Result.Error("Expected object"))
          );
          test("decoding failure, missing field", () =>
            expect(C.decodeJson(codec, jsonTwoFieldObject))
            |> toEqual(Result.Error("Field 'qux' not found"))
          );
          test("decoding failure, wrong field type", () =>
            expect(C.decodeJson(codec, jsonSingleNumberFieldObject))
            |> toEqual(Result.Error("Expected string"))
          );
        });
        describe("object4", () => {
          let codec =
            C.object4(
              C.field("foo", C.string),
              C.field("baz", C.bool),
              C.field("qux", C.number),
              C.field("quux", C.null),
            );
          test("encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, ("bar", true, 56.78, ())))
            |> toEqual(jsonFourFieldObject)
          );
          test("decoding", () =>
            expect(C.decodeJson(codec, jsonFourFieldObject))
            |> toEqual(Result.Ok(("bar", true, 56.78, ())))
          );
        });
        describe("object5", () => {
          let json =
            formatJsonString(
              {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5}|js},
            );
          let codec =
            C.object5(
              C.field("f1", C.int),
              C.field("f2", C.int),
              C.field("f3", C.int),
              C.field("f4", C.int),
              C.field("f5", C.int),
            );
          test("encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, (1, 2, 3, 4, 5)))
            |> toEqual(json)
          );
          test("decoding", () =>
            expect(C.decodeJson(codec, json))
            |> toEqual(Result.Ok((1, 2, 3, 4, 5)))
          );
        });
        describe("object6", () => {
          let json =
            formatJsonString(
              {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6}|js},
            );
          let codec =
            C.object6(
              C.field("f1", C.int),
              C.field("f2", C.int),
              C.field("f3", C.int),
              C.field("f4", C.int),
              C.field("f5", C.int),
              C.field("f6", C.int),
            );
          test("encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, (1, 2, 3, 4, 5, 6)))
            |> toEqual(json)
          );
          test("decoding", () =>
            expect(C.decodeJson(codec, json))
            |> toEqual(Result.Ok((1, 2, 3, 4, 5, 6)))
          );
        });
        describe("object7", () => {
          let json =
            formatJsonString(
              {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7}|js},
            );
          let codec =
            C.object7(
              C.field("f1", C.int),
              C.field("f2", C.int),
              C.field("f3", C.int),
              C.field("f4", C.int),
              C.field("f5", C.int),
              C.field("f6", C.int),
              C.field("f7", C.int),
            );
          test("encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, (1, 2, 3, 4, 5, 6, 7)))
            |> toEqual(json)
          );
          test("decoding", () =>
            expect(C.decodeJson(codec, json))
            |> toEqual(Result.Ok((1, 2, 3, 4, 5, 6, 7)))
          );
        });
        describe("object8", () => {
          let json =
            formatJsonString(
              {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7, "f8": 8}|js},
            );
          let codec =
            C.object8(
              C.field("f1", C.int),
              C.field("f2", C.int),
              C.field("f3", C.int),
              C.field("f4", C.int),
              C.field("f5", C.int),
              C.field("f6", C.int),
              C.field("f7", C.int),
              C.field("f8", C.int),
            );
          test("encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, (1, 2, 3, 4, 5, 6, 7, 8)))
            |> toEqual(json)
          );
          test("decoding", () =>
            expect(C.decodeJson(codec, json))
            |> toEqual(Result.Ok((1, 2, 3, 4, 5, 6, 7, 8)))
          );
        });
        describe("object9", () => {
          let json =
            formatJsonString(
              {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7, "f8": 8, "f9": 9}|js},
            );
          let codec =
            C.object9(
              C.field("f1", C.int),
              C.field("f2", C.int),
              C.field("f3", C.int),
              C.field("f4", C.int),
              C.field("f5", C.int),
              C.field("f6", C.int),
              C.field("f7", C.int),
              C.field("f8", C.int),
              C.field("f9", C.int),
            );
          test("encoding", () =>
            expect(
              C.encodeJson(~spaces=0, codec, (1, 2, 3, 4, 5, 6, 7, 8, 9)),
            )
            |> toEqual(json)
          );
          test("decoding", () =>
            expect(C.decodeJson(codec, json))
            |> toEqual(Result.Ok((1, 2, 3, 4, 5, 6, 7, 8, 9)))
          );
        });
        describe("object10", () => {
          let json =
            formatJsonString(
              {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7, "f8": 8, "f9": 9, "f10": 10}|js},
            );
          let codec =
            C.object10(
              C.field("f1", C.int),
              C.field("f2", C.int),
              C.field("f3", C.int),
              C.field("f4", C.int),
              C.field("f5", C.int),
              C.field("f6", C.int),
              C.field("f7", C.int),
              C.field("f8", C.int),
              C.field("f9", C.int),
              C.field("f10", C.int),
            );
          test("encoding", () =>
            expect(
              C.encodeJson(
                ~spaces=0,
                codec,
                (1, 2, 3, 4, 5, 6, 7, 8, 9, 10),
              ),
            )
            |> toEqual(json)
          );
          test("decoding", () =>
            expect(C.decodeJson(codec, json))
            |> toEqual(Result.Ok((1, 2, 3, 4, 5, 6, 7, 8, 9, 10)))
          );
        });
        describe("optional and nullable fields", () => {
          let nullableFieldCodec =
            C.(object1(field("foo", nullable(string))));
          let optionalFieldCodec = C.(object1(optional("foo", string)));
          let optionalNullableFieldCodec =
            C.(object1(optional("foo", nullable(string))));
          let flattenedFieldCodec =
            C.(object1(C.optionalNullable("foo", string)));
          let jsonNullField = formatJsonString("{\"foo\": null}");
          describe("nullable field", () => {
            test("empty encoding", () =>
              expect(C.encodeJson(~spaces=0, nullableFieldCodec, None))
              |> toEqual(jsonNullField)
            );
            test("empty decoding", () =>
              expect(C.decodeJson(nullableFieldCodec, jsonNullField))
              |> toEqual(Result.Ok(None))
            );
            test("non-empty encoding", () =>
              expect(
                C.encodeJson(~spaces=0, nullableFieldCodec, Some("bar")),
              )
              |> toEqual(jsonSingleStringFieldObject)
            );
            test("non-empty decoding", () =>
              expect(
                C.decodeJson(nullableFieldCodec, jsonSingleStringFieldObject),
              )
              |> toEqual(Result.Ok(Some("bar")))
            );
          });
          describe("optional field", () => {
            test("empty encoding", () =>
              expect(C.encodeJson(optionalFieldCodec, None))
              |> toEqual(jsonEmptyObject)
            );
            test("empty decoding", () =>
              expect(C.decodeJson(optionalFieldCodec, jsonEmptyObject))
              |> toEqual(Result.Ok(None))
            );
            test("non-empty encoding", () =>
              expect(
                C.encodeJson(~spaces=0, optionalFieldCodec, Some("bar")),
              )
              |> toEqual(jsonSingleStringFieldObject)
            );
            test("non-empty decoding success", () =>
              expect(
                C.decodeJson(optionalFieldCodec, jsonSingleStringFieldObject),
              )
              |> toEqual(Result.Ok(Some("bar")))
            );
            test("non-empty decoding failure", () =>
              expect(
                C.decodeJson(optionalFieldCodec, jsonSingleNumberFieldObject),
              )
              |> toEqual(Result.Error("Expected string"))
            );
          });
          describe("optional nullable field", () => {
            test("empty encoding", () =>
              expect(C.encodeJson(optionalNullableFieldCodec, None))
              |> toEqual(jsonEmptyObject)
            );
            test("empty decoding", () =>
              expect(
                C.decodeJson(optionalNullableFieldCodec, jsonEmptyObject),
              )
              |> toEqual(Result.Ok(None))
            );
            test("null encoding", () =>
              expect(
                C.encodeJson(
                  ~spaces=0,
                  optionalNullableFieldCodec,
                  Some(None),
                ),
              )
              |> toEqual(jsonNullField)
            );
            test("null decoding", () =>
              expect(C.decodeJson(optionalNullableFieldCodec, jsonNullField))
              |> toEqual(Result.Ok(Some(None)))
            );
            test("non-null encoding", () =>
              expect(
                C.encodeJson(
                  ~spaces=0,
                  optionalNullableFieldCodec,
                  Some(Some("bar")),
                ),
              )
              |> toEqual(jsonSingleStringFieldObject)
            );
            test("non-null decoding", () =>
              expect(
                C.decodeJson(
                  optionalNullableFieldCodec,
                  jsonSingleStringFieldObject,
                ),
              )
              |> toEqual(Result.Ok(Some(Some("bar"))))
            );
          });
          describe("flattened optional nullable field", () => {
            test("empty encoding", () =>
              expect(C.encodeJson(~spaces=0, flattenedFieldCodec, None))
              |> toEqual(jsonNullField)
            );
            test("empty decoding, missing field", () =>
              expect(C.decodeJson(flattenedFieldCodec, jsonEmptyObject))
              |> toEqual(Result.Ok(None))
            );
            test("empty decoding, null field", () =>
              expect(C.decodeJson(flattenedFieldCodec, jsonNullField))
              |> toEqual(Result.Ok(None))
            );
            test("non-empty encoding", () =>
              expect(
                C.encodeJson(~spaces=0, flattenedFieldCodec, Some("bar")),
              )
              |> toEqual(jsonSingleStringFieldObject)
            );
            test("non-empty decoding", () =>
              expect(
                C.decodeJson(
                  flattenedFieldCodec,
                  jsonSingleStringFieldObject,
                ),
              )
              |> toEqual(Result.Ok(Some("bar")))
            );
          });
        });
        describe("recursion", () => {
          let intTree = Branch(Branch(Leaf(1), Leaf(2)), Leaf(3));
          let intTreeJson =
            formatJsonString(
              {js|{"left": {"left": 1, "right": 2}, "right": 3}|js},
            );
          let treeToXor =
            fun
            | Leaf(x) => C.Xor.left(x)
            | Branch(l, r) => C.Xor.right((l, r));
          let xorToTree =
            fun
            | C.Xor.Left(x) => Leaf(x)
            | C.Xor.Right((l, r)) => Branch(l, r);
          let codec =
            JsonCodec.(
              fix(tree =>
                xor(
                  int,
                  object2(field("left", tree), field("right", tree)),
                )
                |> wrap(treeToXor, xorToTree)
              )
            );
          test("encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, intTree))
            |> toEqual(intTreeJson)
          );
          test("decoding", () =>
            expect(C.decodeJson(codec, intTreeJson))
            |> toEqual(Result.Ok(intTree))
          );
        });
        describe("constant", () => {
          describe("constant string", () => {
            let codec = C.constant(C.string, "foo");
            test("encoding", () =>
              expect(C.encodeJson(codec, "anything")) |> toEqual(jsonString)
            );
            test("decoding success", () =>
              expect(C.decodeJson(codec, jsonString))
              |> toEqual(Result.Ok("foo"))
            );
            test("decoding failure, wrong value", () =>
              expect(C.decodeJson(codec, "\"bar\""))
              |> toEqual(Result.Error("Expected constant value \"foo\""))
            );
            test("decoding failure, wrong type", () =>
              expect(C.decodeJson(codec, jsonNumberArray))
              |> toEqual(Result.Error("Expected string"))
            );
          });
          describe("constant field value", () => {
            let fieldCodec = C.field("type", C.constant(C.string, "X"));
            let objectCodec = C.object1(fieldCodec);
            let expectedJson = {js|{"type":"X"}|js};
            test("encoding", () =>
              expect(C.encodeJson(~spaces=0, objectCodec, "..."))
              |> toEqual(expectedJson)
            );
            test("decoding", () =>
              expect(C.decodeJson(objectCodec, expectedJson))
              |> toEqual(Result.Ok("X"))
            );
          });
        });
        describe("dict", () => {
          let codec = C.dict(C.int);
          let emptyDict = Js.Dict.empty();
          let emptyDictJson = {js|{}|js};
          let nonEmptyDict = Js.Dict.fromArray([|("x", 1), ("y", 2)|]);
          let nonEmptyDictJson = {js|{"x":1,"y":2}|js};
          test("empty encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, emptyDict))
            |> toEqual(emptyDictJson)
          );
          test("empty decoding", () =>
            expect(C.decodeJson(codec, emptyDictJson))
            |> toEqual(Result.Ok(emptyDict))
          );
          test("non-empty encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, nonEmptyDict))
            |> toEqual(nonEmptyDictJson)
          );
          test("non-empty decoding", () =>
            expect(C.decodeJson(codec, nonEmptyDictJson))
            |> toEqual(Result.Ok(nonEmptyDict))
          );
        });
        describe("list", () => {
          let codec = C.list(C.int);
          let emptyList = [];
          let emptyListJson = {js|[]|js};
          let nonEmptyList = [1, 2, 3];
          let nonEmptyListJson = {js|[1,2,3]|js};
          test("empty encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, emptyList))
            |> toEqual(emptyListJson)
          );
          test("empty decoding", () =>
            expect(C.decodeJson(codec, emptyListJson))
            |> toEqual(Result.Ok(emptyList))
          );
          test("non-empty encoding", () =>
            expect(C.encodeJson(~spaces=0, codec, nonEmptyList))
            |> toEqual(nonEmptyListJson)
          );
          test("non-empty decoding", () =>
            expect(C.decodeJson(codec, nonEmptyListJson))
            |> toEqual(Result.Ok(nonEmptyList))
          );
        });
      }
    ),
  );
