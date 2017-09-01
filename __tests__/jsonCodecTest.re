open Jest;
module C = JsonCodec;

let format_json_string s => Js.Json.parseExn s |> Js.Json.stringify;

let () =
  describe "JsonCodec"
    ExpectJs.(fun () => {
      let json_string = "\"foo\"";
      let json_float_array = format_json_string "[1.1, 2.2]";
      let json_empty_object = "{}";
      let json_single_string_field_object = format_json_string {js|{"foo": "bar"}|js};
      let json_single_float_field_object = format_json_string {js|{"foo": 12.34}|js};
      let json_two_field_object = format_json_string {js|{"foo": "bar", "baz": true}|js};
      let json_three_field_object = format_json_string {js|{"foo": "bar", "baz": true, "qux": 56.78}|js};
      let json_four_field_object = format_json_string {js|{"foo": "bar", "baz": true, "qux": 56.78, "quux": null}|js};

      describe "float" (fun () => {
        test "encoding" (fun () =>
          expect (C.encode_json C.float 3.14) |> toEqual "3.14"
        );
        test "decoding success" (fun () =>
          expect (C.decode_json C.float "3.14") |> toEqual (Js.Result.Ok 3.14)
        );
        test "decoding failure" (fun () =>
          expect (C.decode_json C.float json_string) |> toEqual (Js.Result.Error "Expected number")
        );
      });

      describe "int" (fun () => {
        test "encoding" (fun () =>
          expect (C.encode_json C.int 1) |> toEqual "1"
        );
        test "decoding success, no decimal point" (fun () =>
          expect (C.decode_json C.int "1") |> toEqual (Js.Result.Ok 1)
        );
        test "decoding success, zero after decimal point" (fun () =>
          expect (C.decode_json C.int "1.0") |> toEqual (Js.Result.Ok 1)
        );
        test "decoding failure, can't represent as int" (fun () =>
          expect (C.decode_json C.int "1.234") |> toEqual (Js.Result.Error "Not an int: 1.234")
        );
      });

      describe "string" (fun () => {
        test "encoding" (fun () =>
          expect (C.encode_json C.string "foo") |> toEqual json_string
        );
        test "decoding success" (fun () =>
          expect (C.decode_json C.string json_string) |> toEqual (Js.Result.Ok "foo")
        );
        test "decoding failure" (fun () =>
          expect (C.decode_json C.string "0.5") |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "bool" (fun () => {
        test "encoding" (fun () =>
          expect (C.encode_json C.bool true) |> toEqual "true"
        );
        test "decoding success" (fun () =>
          expect (C.decode_json C.bool "false") |> toEqual (Js.Result.Ok false)
        );
        test "decoding failure" (fun () =>
          expect (C.decode_json C.bool json_string) |> toEqual (Js.Result.Error "Expected boolean")
        );
      });

      describe "null" (fun () => {
        test "encoding" (fun () =>
          expect (C.encode_json C.null ()) |> toEqual "null"
        );
        test "decoding success" (fun () =>
          expect (C.decode_json C.null "null") |> toEqual (Js.Result.Ok ())
        );
        test "decoding failure" (fun () =>
          expect (C.decode_json C.null "true") |> toEqual (Js.Result.Error "Expected null")
        );
      });

      describe "nullable" (fun () => {
        test "empty encoding" (fun () =>
          expect (C.encode_json (C.nullable C.string) None) |> toEqual "null"
        );
        test "empty decoding success" (fun () =>
          expect (C.decode_json (C.nullable C.string) "null") |> toEqual (Js.Result.Ok None)
        );
        test "non-empty encoding" (fun () =>
          expect (C.encode_json (C.nullable C.string) (Some "foo")) |> toEqual json_string
        );
        test "non-empty decoding success" (fun () =>
          expect (C.decode_json (C.nullable C.float) "1.0") |> toEqual (Js.Result.Ok (Some 1.0))
        );
        test "decoding failure" (fun () =>
          expect (C.decode_json (C.nullable C.string) "1.0") |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "array" (fun () => {
        test "empty encoding" (fun () =>
          expect (C.encode_json (C.array C.float) [||]) |> toEqual "[]"
        );
        test "empty decoding" (fun () =>
          expect (C.decode_json (C.array C.string) "[]") |> toEqual (Js.Result.Ok [||])
        );
        test "non-empty encoding" (fun () =>
          expect (C.encode_json (C.array C.float) [| 1.1, 2.2 |] |> format_json_string) |> toEqual json_float_array
        );
        test "non-empty decoding success" (fun () =>
          expect (C.decode_json (C.array C.float) json_float_array) |> toEqual (Js.Result.Ok [| 1.1, 2.2 |])
        );
        test "decoding failure" (fun () =>
          expect (C.decode_json (C.array C.string) "true") |> toEqual (Js.Result.Error "Expected array")
        );
        test "element decoding failure" (fun () =>
          expect (C.decode_json (C.array C.string) json_float_array) |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "object0" (fun () => {
        test "encoding" (fun () =>
          expect (C.encode_json C.object0 ()) |> toEqual "{}"
        );
        test "decoding success" (fun () =>
          expect (C.decode_json C.object0 "{}") |> toEqual (Js.Result.Ok ())
        );
        test "decoding success, ignoring extra fields" (fun () =>
          expect (C.decode_json C.object0 json_single_string_field_object) |> toEqual (Js.Result.Ok ())
        );
        test "decoding failure" (fun () =>
          expect (C.decode_json C.object0 "null") |> toEqual (Js.Result.Error "Expected object")
        );
      });

      describe "object1" (fun () => {
        let codec = C.object1 (C.field "foo" C.string);

        test "encoding" (fun () =>
          expect (C.encode_json spaces::0 codec "bar") |> toEqual json_single_string_field_object
        );
        test "decoding success" (fun () =>
          expect (C.decode_json codec json_single_string_field_object) |> toEqual (Js.Result.Ok "bar")
        );
        test "decoding success, ignoring extra fields" (fun () =>
          expect (C.decode_json codec json_two_field_object) |> toEqual (Js.Result.Ok "bar")
        );
        test "decoding failure, not an object" (fun () =>
          expect (C.decode_json codec "false") |> toEqual (Js.Result.Error "Expected object")
        );
        test "decoding failure, missing field" (fun () =>
          expect (C.decode_json codec "{}") |> toEqual (Js.Result.Error "Field 'foo' not found")
        );
        test "decoding failure, wrong field type" (fun () =>
          expect (C.decode_json codec json_single_float_field_object) |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "object2" (fun () => {
        let codec = C.object2 (C.field "foo" C.string) (C.field "baz" C.bool);

        test "encoding" (fun () =>
          expect (C.encode_json spaces::0 codec ("bar", true)) |> toEqual json_two_field_object
        );
        test "decoding success" (fun () => {
          expect (C.decode_json codec json_two_field_object) |> toEqual (Js.Result.Ok ("bar", true))
        });
        test "decoding success, ignoring extra fields" (fun () => {
          expect (C.decode_json codec json_three_field_object) |> toEqual (Js.Result.Ok ("bar", true))
        });
        test "decoding failure, not an object" (fun () =>
          expect (C.decode_json codec "7.77") |> toEqual (Js.Result.Error "Expected object")
        );
        test "decoding failure, missing field" (fun () =>
          expect (C.decode_json codec json_single_string_field_object) |> toEqual (Js.Result.Error "Field 'baz' not found")
        );
        test "decoding failure, wrong field type" (fun () =>
          expect (C.decode_json codec json_single_float_field_object) |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "object3" (fun () => {
        let codec = C.object3 (C.field "foo" C.string) (C.field "baz" C.bool) (C.field "qux" C.float);

        test "encoding" (fun () =>
          expect (C.encode_json spaces::0 codec ("bar", true, 56.78)) |> toEqual json_three_field_object
        );
        test "decoding success" (fun () => {
          expect (C.decode_json codec json_three_field_object) |> toEqual (Js.Result.Ok ("bar", true, 56.78))
        });
        test "decoding success, ignoring extra fields" (fun () => {
          expect (C.decode_json codec json_four_field_object) |> toEqual (Js.Result.Ok ("bar", true, 56.78))
        });
        test "decoding failure, not an object" (fun () =>
          expect (C.decode_json codec "null") |> toEqual (Js.Result.Error "Expected object")
        );
        test "decoding failure, missing field" (fun () =>
          expect (C.decode_json codec json_two_field_object) |> toEqual (Js.Result.Error "Field 'qux' not found")
        );
        test "decoding failure, wrong field type" (fun () =>
          expect (C.decode_json codec json_single_float_field_object) |> toEqual (Js.Result.Error "Expected string")
        );
      });

      describe "object4" (fun () => {
        let codec = C.object4 (C.field "foo" C.string) (C.field "baz" C.bool) (C.field "qux" C.float) (C.field "quux" C.null);

        test "encoding" (fun () =>
          expect (C.encode_json spaces::0 codec ("bar", true, 56.78, ())) |> toEqual json_four_field_object
        );
        test "decoding" (fun () =>
          expect (C.decode_json codec json_four_field_object) |> toEqual (Js.Result.Ok ("bar", true, 56.78, ()))
        );
      });

      describe "object5" (fun () => {
        let json = format_json_string {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5}|js};
        let codec = C.object5 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int);

        test "encoding" (fun () =>
          expect (C.encode_json spaces::0 codec (1, 2, 3, 4, 5)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decode_json codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5))
        );
      });

      describe "object6" (fun () => {
        let json = format_json_string {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6}|js};
        let codec = C.object6 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int) (C.field "f6" C.int);

        test "encoding" (fun () =>
          expect (C.encode_json spaces::0 codec (1, 2, 3, 4, 5, 6)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decode_json codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5, 6))
        );
      });

      describe "object7" (fun () => {
        let json = format_json_string {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7}|js};
        let codec = C.object7 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int) (C.field "f6" C.int) (C.field "f7" C.int);

        test "encoding" (fun () =>
          expect (C.encode_json spaces::0 codec (1, 2, 3, 4, 5, 6, 7)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decode_json codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5, 6, 7))
        );
      });

      describe "object8" (fun () => {
        let json = format_json_string {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7, "f8": 8}|js};
        let codec = C.object8 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int) (C.field "f6" C.int) (C.field "f7" C.int) (C.field "f8" C.int);

        test "encoding" (fun () =>
          expect (C.encode_json spaces::0 codec (1, 2, 3, 4, 5, 6, 7, 8)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decode_json codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5, 6, 7, 8))
        );
      });

      describe "object9" (fun () => {
        let json = format_json_string {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7, "f8": 8, "f9": 9}|js};
        let codec = C.object9 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int) (C.field "f6" C.int) (C.field "f7" C.int) (C.field "f8" C.int) (C.field "f9" C.int);

        test "encoding" (fun () =>
          expect (C.encode_json spaces::0 codec (1, 2, 3, 4, 5, 6, 7, 8, 9)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decode_json codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5, 6, 7, 8, 9))
        );
      });

      describe "object10" (fun () => {
        let json = format_json_string {js|{"f1": 1, "f2": 2, "f3": 3, "f4": 4, "f5": 5, "f6": 6, "f7": 7, "f8": 8, "f9": 9, "f10": 10}|js};
        let codec = C.object10 (C.field "f1" C.int) (C.field "f2" C.int) (C.field "f3" C.int) (C.field "f4" C.int) (C.field "f5" C.int) (C.field "f6" C.int) (C.field "f7" C.int) (C.field "f8" C.int) (C.field "f9" C.int) (C.field "f10" C.int);

        test "encoding" (fun () =>
          expect (C.encode_json spaces::0 codec (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)) |> toEqual json
        );
        test "decoding" (fun () =>
          expect (C.decode_json codec json) |> toEqual (Js.Result.Ok (1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
        );
      });

      describe "optional and nullable fields" (fun () => {
        let nullable_field_codec = C.(object1 (field "foo" (nullable string)));
        let optional_field_codec = C.(object1 (optional "foo" string));
        let optional_nullable_field_codec = C.(object1 (optional "foo" (nullable string)));
        let flattened_field_codec = C.(object1 (optional_nullable "foo" string));

        let json_null_field = format_json_string "{\"foo\": null}";

        describe "nullable field" (fun () => {
          test "empty encoding" (fun () =>
            expect (C.encode_json spaces::0 nullable_field_codec None) |> toEqual json_null_field
          );
          test "empty decoding" (fun () =>
            expect (C.decode_json nullable_field_codec json_null_field) |> toEqual (Js.Result.Ok None)
          );
          test "non-empty encoding" (fun () =>
            expect (C.encode_json spaces::0 nullable_field_codec (Some "bar")) |> toEqual json_single_string_field_object
          );
          test "non-empty decoding" (fun () =>
            expect (C.decode_json nullable_field_codec json_single_string_field_object) |> toEqual (Js.Result.Ok (Some "bar"))
          );
        });

        describe "optional field" (fun () => {
          test "empty encoding" (fun () =>
            expect (C.encode_json optional_field_codec None) |> toEqual json_empty_object
          );
          test "empty decoding" (fun () =>
            expect (C.decode_json optional_field_codec json_empty_object) |> toEqual (Js.Result.Ok None)
          );
          test "non-empty encoding" (fun () =>
            expect (C.encode_json spaces::0 optional_field_codec (Some "bar")) |> toEqual json_single_string_field_object
          );
          test "non-empty decoding success" (fun () =>
            expect (C.decode_json optional_field_codec json_single_string_field_object) |> toEqual (Js.Result.Ok (Some "bar"))
          );
          test "non-empty decoding failure" (fun () =>
            expect (C.decode_json optional_field_codec json_single_float_field_object) |> toEqual (Js.Result.Error "Expected string")
          );
        });

        describe "optional nullable field" (fun () => {
          test "empty encoding" (fun () =>
            expect (C.encode_json optional_nullable_field_codec None) |> toEqual json_empty_object
          );
          test "empty decoding" (fun () =>
            expect (C.decode_json optional_nullable_field_codec json_empty_object) |> toEqual (Js.Result.Ok None)
          );
          test "null encoding" (fun () =>
            expect (C.encode_json spaces::0 optional_nullable_field_codec (Some None)) |> toEqual json_null_field
          );
          test "null decoding" (fun () =>
            expect (C.decode_json optional_nullable_field_codec json_null_field) |> toEqual (Js.Result.Ok (Some None))
          );
          test "non-null encoding" (fun () =>
            expect (C.encode_json spaces::0 optional_nullable_field_codec (Some (Some "bar"))) |> toEqual json_single_string_field_object
          );
          test "non-null decoding" (fun () =>
            expect (C.decode_json optional_nullable_field_codec json_single_string_field_object) |> toEqual (Js.Result.Ok (Some (Some "bar")))
          );
        });

        describe "flattened optional nullable field" (fun () => {
          test "empty encoding" (fun () =>
            expect (C.encode_json spaces::0 flattened_field_codec None) |> toEqual json_null_field
          );
          test "empty decoding, missing field" (fun () =>
            expect (C.decode_json flattened_field_codec json_empty_object) |> toEqual (Js.Result.Ok None)
          );
          test "empty decoding, null field" (fun () =>
            expect (C.decode_json flattened_field_codec json_null_field) |> toEqual (Js.Result.Ok None)
          );
          test "non-empty encoding" (fun () =>
            expect (C.encode_json spaces::0 flattened_field_codec (Some "bar")) |> toEqual json_single_string_field_object
          );
          test "non-empty decoding" (fun () =>
            expect (C.decode_json flattened_field_codec json_single_string_field_object) |> toEqual (Js.Result.Ok (Some "bar"))
          );
        });
      });
    })
