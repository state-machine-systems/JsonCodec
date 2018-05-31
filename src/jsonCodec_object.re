/* This file is auto-generated. Please do not modify it. */
open JsonCodec_result.Ops;
let object1 =
    ((enc1, dec1): JsonCodec_core.FieldCodec.t('a))
    : JsonCodec_core.Codec.t('a) => {
  let encode = v1 => Js.Json.object_ @@ JsonCodec_util.buildDict([enc1(v1)]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json) >>= (dict => dec1(dict));
  (encode, decode);
};
let object2 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
    )
    : JsonCodec_core.Codec.t(('a, 'b)) => {
  let encode = ((v1, v2)) =>
    Js.Json.object_ @@ JsonCodec_util.buildDict([enc1(v1), enc2(v2)]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (v1 => dec2(dict) >>= (v2 => Belt.Result.Ok((v1, v2))))
    );
  (encode, decode);
};
let object3 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
    )
    : JsonCodec_core.Codec.t(('a, 'b, 'c)) => {
  let encode = ((v1, v2, v3)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([enc1(v1), enc2(v2), enc3(v3)]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (v2 => dec3(dict) >>= (v3 => Belt.Result.Ok((v1, v2, v3))))
        )
    );
  (encode, decode);
};
let object4 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
    )
    : JsonCodec_core.Codec.t(('a, 'b, 'c, 'd)) => {
  let encode = ((v1, v2, v3, v4)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([enc1(v1), enc2(v2), enc3(v3), enc4(v4)]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict) >>= (v4 => Belt.Result.Ok((v1, v2, v3, v4)))
                )
            )
        )
    );
  (encode, decode);
};
let object5 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
    )
    : JsonCodec_core.Codec.t(('a, 'b, 'c, 'd, 'e)) => {
  let encode = ((v1, v2, v3, v4, v5)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (v5 => Belt.Result.Ok((v1, v2, v3, v4, v5)))
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object6 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
    )
    : JsonCodec_core.Codec.t(('a, 'b, 'c, 'd, 'e, 'f)) => {
  let encode = ((v1, v2, v3, v4, v5, v6)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 => Belt.Result.Ok((v1, v2, v3, v4, v5, v6))
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object7 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
    )
    : JsonCodec_core.Codec.t(('a, 'b, 'c, 'd, 'e, 'f, 'g)) => {
  let encode = ((v1, v2, v3, v4, v5, v6, v7)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    Belt.Result.Ok((
                                      v1,
                                      v2,
                                      v3,
                                      v4,
                                      v5,
                                      v6,
                                      v7,
                                    ))
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object8 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
    )
    : JsonCodec_core.Codec.t(('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h)) => {
  let encode = ((v1, v2, v3, v4, v5, v6, v7, v8)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        Belt.Result.Ok((
                                          v1,
                                          v2,
                                          v3,
                                          v4,
                                          v5,
                                          v6,
                                          v7,
                                          v8,
                                        ))
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object9 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
    )
    : JsonCodec_core.Codec.t(('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i)) => {
  let encode = ((v1, v2, v3, v4, v5, v6, v7, v8, v9)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            Belt.Result.Ok((
                                              v1,
                                              v2,
                                              v3,
                                              v4,
                                              v5,
                                              v6,
                                              v7,
                                              v8,
                                              v9,
                                            ))
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object10 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
    )
    : JsonCodec_core.Codec.t(('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j)) => {
  let encode = ((v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                Belt.Result.Ok((
                                                  v1,
                                                  v2,
                                                  v3,
                                                  v4,
                                                  v5,
                                                  v6,
                                                  v7,
                                                  v8,
                                                  v9,
                                                  v10,
                                                ))
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object11 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
    )
    : JsonCodec_core.Codec.t(('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j, 'k)) => {
  let encode = ((v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    Belt.Result.Ok((
                                                      v1,
                                                      v2,
                                                      v3,
                                                      v4,
                                                      v5,
                                                      v6,
                                                      v7,
                                                      v8,
                                                      v9,
                                                      v10,
                                                      v11,
                                                    ))
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object12 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
    )
    : JsonCodec_core.Codec.t(
        ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j, 'k, 'l),
      ) => {
  let encode = ((v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        Belt.Result.Ok((
                                                          v1,
                                                          v2,
                                                          v3,
                                                          v4,
                                                          v5,
                                                          v6,
                                                          v7,
                                                          v8,
                                                          v9,
                                                          v10,
                                                          v11,
                                                          v12,
                                                        ))
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object13 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
    )
    : JsonCodec_core.Codec.t(
        ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j, 'k, 'l, 'm),
      ) => {
  let encode = ((v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            Belt.Result.Ok((
                                                              v1,
                                                              v2,
                                                              v3,
                                                              v4,
                                                              v5,
                                                              v6,
                                                              v7,
                                                              v8,
                                                              v9,
                                                              v10,
                                                              v11,
                                                              v12,
                                                              v13,
                                                            ))
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object14 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
    )
    : JsonCodec_core.Codec.t(
        ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j, 'k, 'l, 'm, 'n),
      ) => {
  let encode =
      ((v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                Belt.Result.Ok((
                                                                  v1,
                                                                  v2,
                                                                  v3,
                                                                  v4,
                                                                  v5,
                                                                  v6,
                                                                  v7,
                                                                  v8,
                                                                  v9,
                                                                  v10,
                                                                  v11,
                                                                  v12,
                                                                  v13,
                                                                  v14,
                                                                ))
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object15 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
    )
    : JsonCodec_core.Codec.t(
        ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j, 'k, 'l, 'm, 'n, 'o),
      ) => {
  let encode =
      ((v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15)) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    ))
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object16 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
      (enc16, dec16): JsonCodec_core.FieldCodec.t('p),
    )
    : JsonCodec_core.Codec.t(
        ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j, 'k, 'l, 'm, 'n, 'o, 'p),
      ) => {
  let encode =
      (
        (
          v1,
          v2,
          v3,
          v4,
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
        ),
      ) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
      enc16(v16),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    dec16(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v16 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    v16,
                                                                    ))
                                                                    )
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object17 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
      (enc16, dec16): JsonCodec_core.FieldCodec.t('p),
      (enc17, dec17): JsonCodec_core.FieldCodec.t('q),
    )
    : JsonCodec_core.Codec.t(
        ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j, 'k, 'l, 'm, 'n, 'o, 'p, 'q),
      ) => {
  let encode =
      (
        (
          v1,
          v2,
          v3,
          v4,
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17,
        ),
      ) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
      enc16(v16),
      enc17(v17),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    dec16(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v16 =>
                                                                    dec17(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v17 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    v16,
                                                                    v17,
                                                                    ))
                                                                    )
                                                                    )
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object18 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
      (enc16, dec16): JsonCodec_core.FieldCodec.t('p),
      (enc17, dec17): JsonCodec_core.FieldCodec.t('q),
      (enc18, dec18): JsonCodec_core.FieldCodec.t('r),
    )
    : JsonCodec_core.Codec.t(
        (
          'a,
          'b,
          'c,
          'd,
          'e,
          'f,
          'g,
          'h,
          'i,
          'j,
          'k,
          'l,
          'm,
          'n,
          'o,
          'p,
          'q,
          'r,
        ),
      ) => {
  let encode =
      (
        (
          v1,
          v2,
          v3,
          v4,
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17,
          v18,
        ),
      ) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
      enc16(v16),
      enc17(v17),
      enc18(v18),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    dec16(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v16 =>
                                                                    dec17(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v17 =>
                                                                    dec18(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v18 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    v16,
                                                                    v17,
                                                                    v18,
                                                                    ))
                                                                    )
                                                                    )
                                                                    )
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object19 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
      (enc16, dec16): JsonCodec_core.FieldCodec.t('p),
      (enc17, dec17): JsonCodec_core.FieldCodec.t('q),
      (enc18, dec18): JsonCodec_core.FieldCodec.t('r),
      (enc19, dec19): JsonCodec_core.FieldCodec.t('s),
    )
    : JsonCodec_core.Codec.t(
        (
          'a,
          'b,
          'c,
          'd,
          'e,
          'f,
          'g,
          'h,
          'i,
          'j,
          'k,
          'l,
          'm,
          'n,
          'o,
          'p,
          'q,
          'r,
          's,
        ),
      ) => {
  let encode =
      (
        (
          v1,
          v2,
          v3,
          v4,
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17,
          v18,
          v19,
        ),
      ) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
      enc16(v16),
      enc17(v17),
      enc18(v18),
      enc19(v19),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    dec16(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v16 =>
                                                                    dec17(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v17 =>
                                                                    dec18(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v18 =>
                                                                    dec19(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v19 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    v16,
                                                                    v17,
                                                                    v18,
                                                                    v19,
                                                                    ))
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object20 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
      (enc16, dec16): JsonCodec_core.FieldCodec.t('p),
      (enc17, dec17): JsonCodec_core.FieldCodec.t('q),
      (enc18, dec18): JsonCodec_core.FieldCodec.t('r),
      (enc19, dec19): JsonCodec_core.FieldCodec.t('s),
      (enc20, dec20): JsonCodec_core.FieldCodec.t('t),
    )
    : JsonCodec_core.Codec.t(
        (
          'a,
          'b,
          'c,
          'd,
          'e,
          'f,
          'g,
          'h,
          'i,
          'j,
          'k,
          'l,
          'm,
          'n,
          'o,
          'p,
          'q,
          'r,
          's,
          't,
        ),
      ) => {
  let encode =
      (
        (
          v1,
          v2,
          v3,
          v4,
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17,
          v18,
          v19,
          v20,
        ),
      ) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
      enc16(v16),
      enc17(v17),
      enc18(v18),
      enc19(v19),
      enc20(v20),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    dec16(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v16 =>
                                                                    dec17(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v17 =>
                                                                    dec18(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v18 =>
                                                                    dec19(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v19 =>
                                                                    dec20(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v20 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    v16,
                                                                    v17,
                                                                    v18,
                                                                    v19,
                                                                    v20,
                                                                    ))
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object21 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
      (enc16, dec16): JsonCodec_core.FieldCodec.t('p),
      (enc17, dec17): JsonCodec_core.FieldCodec.t('q),
      (enc18, dec18): JsonCodec_core.FieldCodec.t('r),
      (enc19, dec19): JsonCodec_core.FieldCodec.t('s),
      (enc20, dec20): JsonCodec_core.FieldCodec.t('t),
      (enc21, dec21): JsonCodec_core.FieldCodec.t('u),
    )
    : JsonCodec_core.Codec.t(
        (
          'a,
          'b,
          'c,
          'd,
          'e,
          'f,
          'g,
          'h,
          'i,
          'j,
          'k,
          'l,
          'm,
          'n,
          'o,
          'p,
          'q,
          'r,
          's,
          't,
          'u,
        ),
      ) => {
  let encode =
      (
        (
          v1,
          v2,
          v3,
          v4,
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17,
          v18,
          v19,
          v20,
          v21,
        ),
      ) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
      enc16(v16),
      enc17(v17),
      enc18(v18),
      enc19(v19),
      enc20(v20),
      enc21(v21),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    dec16(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v16 =>
                                                                    dec17(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v17 =>
                                                                    dec18(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v18 =>
                                                                    dec19(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v19 =>
                                                                    dec20(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v20 =>
                                                                    dec21(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v21 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    v16,
                                                                    v17,
                                                                    v18,
                                                                    v19,
                                                                    v20,
                                                                    v21,
                                                                    ))
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object22 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
      (enc16, dec16): JsonCodec_core.FieldCodec.t('p),
      (enc17, dec17): JsonCodec_core.FieldCodec.t('q),
      (enc18, dec18): JsonCodec_core.FieldCodec.t('r),
      (enc19, dec19): JsonCodec_core.FieldCodec.t('s),
      (enc20, dec20): JsonCodec_core.FieldCodec.t('t),
      (enc21, dec21): JsonCodec_core.FieldCodec.t('u),
      (enc22, dec22): JsonCodec_core.FieldCodec.t('v),
    )
    : JsonCodec_core.Codec.t(
        (
          'a,
          'b,
          'c,
          'd,
          'e,
          'f,
          'g,
          'h,
          'i,
          'j,
          'k,
          'l,
          'm,
          'n,
          'o,
          'p,
          'q,
          'r,
          's,
          't,
          'u,
          'v,
        ),
      ) => {
  let encode =
      (
        (
          v1,
          v2,
          v3,
          v4,
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17,
          v18,
          v19,
          v20,
          v21,
          v22,
        ),
      ) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
      enc16(v16),
      enc17(v17),
      enc18(v18),
      enc19(v19),
      enc20(v20),
      enc21(v21),
      enc22(v22),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    dec16(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v16 =>
                                                                    dec17(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v17 =>
                                                                    dec18(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v18 =>
                                                                    dec19(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v19 =>
                                                                    dec20(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v20 =>
                                                                    dec21(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v21 =>
                                                                    dec22(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v22 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    v16,
                                                                    v17,
                                                                    v18,
                                                                    v19,
                                                                    v20,
                                                                    v21,
                                                                    v22,
                                                                    ))
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object23 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
      (enc16, dec16): JsonCodec_core.FieldCodec.t('p),
      (enc17, dec17): JsonCodec_core.FieldCodec.t('q),
      (enc18, dec18): JsonCodec_core.FieldCodec.t('r),
      (enc19, dec19): JsonCodec_core.FieldCodec.t('s),
      (enc20, dec20): JsonCodec_core.FieldCodec.t('t),
      (enc21, dec21): JsonCodec_core.FieldCodec.t('u),
      (enc22, dec22): JsonCodec_core.FieldCodec.t('v),
      (enc23, dec23): JsonCodec_core.FieldCodec.t('w),
    )
    : JsonCodec_core.Codec.t(
        (
          'a,
          'b,
          'c,
          'd,
          'e,
          'f,
          'g,
          'h,
          'i,
          'j,
          'k,
          'l,
          'm,
          'n,
          'o,
          'p,
          'q,
          'r,
          's,
          't,
          'u,
          'v,
          'w,
        ),
      ) => {
  let encode =
      (
        (
          v1,
          v2,
          v3,
          v4,
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17,
          v18,
          v19,
          v20,
          v21,
          v22,
          v23,
        ),
      ) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
      enc16(v16),
      enc17(v17),
      enc18(v18),
      enc19(v19),
      enc20(v20),
      enc21(v21),
      enc22(v22),
      enc23(v23),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    dec16(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v16 =>
                                                                    dec17(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v17 =>
                                                                    dec18(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v18 =>
                                                                    dec19(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v19 =>
                                                                    dec20(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v20 =>
                                                                    dec21(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v21 =>
                                                                    dec22(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v22 =>
                                                                    dec23(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v23 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    v16,
                                                                    v17,
                                                                    v18,
                                                                    v19,
                                                                    v20,
                                                                    v21,
                                                                    v22,
                                                                    v23,
                                                                    ))
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object24 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
      (enc16, dec16): JsonCodec_core.FieldCodec.t('p),
      (enc17, dec17): JsonCodec_core.FieldCodec.t('q),
      (enc18, dec18): JsonCodec_core.FieldCodec.t('r),
      (enc19, dec19): JsonCodec_core.FieldCodec.t('s),
      (enc20, dec20): JsonCodec_core.FieldCodec.t('t),
      (enc21, dec21): JsonCodec_core.FieldCodec.t('u),
      (enc22, dec22): JsonCodec_core.FieldCodec.t('v),
      (enc23, dec23): JsonCodec_core.FieldCodec.t('w),
      (enc24, dec24): JsonCodec_core.FieldCodec.t('x),
    )
    : JsonCodec_core.Codec.t(
        (
          'a,
          'b,
          'c,
          'd,
          'e,
          'f,
          'g,
          'h,
          'i,
          'j,
          'k,
          'l,
          'm,
          'n,
          'o,
          'p,
          'q,
          'r,
          's,
          't,
          'u,
          'v,
          'w,
          'x,
        ),
      ) => {
  let encode =
      (
        (
          v1,
          v2,
          v3,
          v4,
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17,
          v18,
          v19,
          v20,
          v21,
          v22,
          v23,
          v24,
        ),
      ) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
      enc16(v16),
      enc17(v17),
      enc18(v18),
      enc19(v19),
      enc20(v20),
      enc21(v21),
      enc22(v22),
      enc23(v23),
      enc24(v24),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    dec16(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v16 =>
                                                                    dec17(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v17 =>
                                                                    dec18(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v18 =>
                                                                    dec19(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v19 =>
                                                                    dec20(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v20 =>
                                                                    dec21(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v21 =>
                                                                    dec22(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v22 =>
                                                                    dec23(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v23 =>
                                                                    dec24(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v24 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    v16,
                                                                    v17,
                                                                    v18,
                                                                    v19,
                                                                    v20,
                                                                    v21,
                                                                    v22,
                                                                    v23,
                                                                    v24,
                                                                    ))
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object25 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
      (enc16, dec16): JsonCodec_core.FieldCodec.t('p),
      (enc17, dec17): JsonCodec_core.FieldCodec.t('q),
      (enc18, dec18): JsonCodec_core.FieldCodec.t('r),
      (enc19, dec19): JsonCodec_core.FieldCodec.t('s),
      (enc20, dec20): JsonCodec_core.FieldCodec.t('t),
      (enc21, dec21): JsonCodec_core.FieldCodec.t('u),
      (enc22, dec22): JsonCodec_core.FieldCodec.t('v),
      (enc23, dec23): JsonCodec_core.FieldCodec.t('w),
      (enc24, dec24): JsonCodec_core.FieldCodec.t('x),
      (enc25, dec25): JsonCodec_core.FieldCodec.t('y),
    )
    : JsonCodec_core.Codec.t(
        (
          'a,
          'b,
          'c,
          'd,
          'e,
          'f,
          'g,
          'h,
          'i,
          'j,
          'k,
          'l,
          'm,
          'n,
          'o,
          'p,
          'q,
          'r,
          's,
          't,
          'u,
          'v,
          'w,
          'x,
          'y,
        ),
      ) => {
  let encode =
      (
        (
          v1,
          v2,
          v3,
          v4,
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17,
          v18,
          v19,
          v20,
          v21,
          v22,
          v23,
          v24,
          v25,
        ),
      ) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
      enc16(v16),
      enc17(v17),
      enc18(v18),
      enc19(v19),
      enc20(v20),
      enc21(v21),
      enc22(v22),
      enc23(v23),
      enc24(v24),
      enc25(v25),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    dec16(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v16 =>
                                                                    dec17(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v17 =>
                                                                    dec18(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v18 =>
                                                                    dec19(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v19 =>
                                                                    dec20(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v20 =>
                                                                    dec21(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v21 =>
                                                                    dec22(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v22 =>
                                                                    dec23(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v23 =>
                                                                    dec24(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v24 =>
                                                                    dec25(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v25 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    v16,
                                                                    v17,
                                                                    v18,
                                                                    v19,
                                                                    v20,
                                                                    v21,
                                                                    v22,
                                                                    v23,
                                                                    v24,
                                                                    v25,
                                                                    ))
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
let object26 =
    (
      (enc1, dec1): JsonCodec_core.FieldCodec.t('a),
      (enc2, dec2): JsonCodec_core.FieldCodec.t('b),
      (enc3, dec3): JsonCodec_core.FieldCodec.t('c),
      (enc4, dec4): JsonCodec_core.FieldCodec.t('d),
      (enc5, dec5): JsonCodec_core.FieldCodec.t('e),
      (enc6, dec6): JsonCodec_core.FieldCodec.t('f),
      (enc7, dec7): JsonCodec_core.FieldCodec.t('g),
      (enc8, dec8): JsonCodec_core.FieldCodec.t('h),
      (enc9, dec9): JsonCodec_core.FieldCodec.t('i),
      (enc10, dec10): JsonCodec_core.FieldCodec.t('j),
      (enc11, dec11): JsonCodec_core.FieldCodec.t('k),
      (enc12, dec12): JsonCodec_core.FieldCodec.t('l),
      (enc13, dec13): JsonCodec_core.FieldCodec.t('m),
      (enc14, dec14): JsonCodec_core.FieldCodec.t('n),
      (enc15, dec15): JsonCodec_core.FieldCodec.t('o),
      (enc16, dec16): JsonCodec_core.FieldCodec.t('p),
      (enc17, dec17): JsonCodec_core.FieldCodec.t('q),
      (enc18, dec18): JsonCodec_core.FieldCodec.t('r),
      (enc19, dec19): JsonCodec_core.FieldCodec.t('s),
      (enc20, dec20): JsonCodec_core.FieldCodec.t('t),
      (enc21, dec21): JsonCodec_core.FieldCodec.t('u),
      (enc22, dec22): JsonCodec_core.FieldCodec.t('v),
      (enc23, dec23): JsonCodec_core.FieldCodec.t('w),
      (enc24, dec24): JsonCodec_core.FieldCodec.t('x),
      (enc25, dec25): JsonCodec_core.FieldCodec.t('y),
      (enc26, dec26): JsonCodec_core.FieldCodec.t('z),
    )
    : JsonCodec_core.Codec.t(
        (
          'a,
          'b,
          'c,
          'd,
          'e,
          'f,
          'g,
          'h,
          'i,
          'j,
          'k,
          'l,
          'm,
          'n,
          'o,
          'p,
          'q,
          'r,
          's,
          't,
          'u,
          'v,
          'w,
          'x,
          'y,
          'z,
        ),
      ) => {
  let encode =
      (
        (
          v1,
          v2,
          v3,
          v4,
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17,
          v18,
          v19,
          v20,
          v21,
          v22,
          v23,
          v24,
          v25,
          v26,
        ),
      ) =>
    Js.Json.object_ @@
    JsonCodec_util.buildDict([
      enc1(v1),
      enc2(v2),
      enc3(v3),
      enc4(v4),
      enc5(v5),
      enc6(v6),
      enc7(v7),
      enc8(v8),
      enc9(v9),
      enc10(v10),
      enc11(v11),
      enc12(v12),
      enc13(v13),
      enc14(v14),
      enc15(v15),
      enc16(v16),
      enc17(v17),
      enc18(v18),
      enc19(v19),
      enc20(v20),
      enc21(v21),
      enc22(v22),
      enc23(v23),
      enc24(v24),
      enc25(v25),
      enc26(v26),
    ]);
  let decode = json =>
    JsonCodec_util.decodeRawObject(json)
    >>= (
      dict =>
        dec1(dict)
        >>= (
          v1 =>
            dec2(dict)
            >>= (
              v2 =>
                dec3(dict)
                >>= (
                  v3 =>
                    dec4(dict)
                    >>= (
                      v4 =>
                        dec5(dict)
                        >>= (
                          v5 =>
                            dec6(dict)
                            >>= (
                              v6 =>
                                dec7(dict)
                                >>= (
                                  v7 =>
                                    dec8(dict)
                                    >>= (
                                      v8 =>
                                        dec9(dict)
                                        >>= (
                                          v9 =>
                                            dec10(dict)
                                            >>= (
                                              v10 =>
                                                dec11(dict)
                                                >>= (
                                                  v11 =>
                                                    dec12(dict)
                                                    >>= (
                                                      v12 =>
                                                        dec13(dict)
                                                        >>= (
                                                          v13 =>
                                                            dec14(dict)
                                                            >>= (
                                                              v14 =>
                                                                dec15(dict)
                                                                >>= (
                                                                  v15 =>
                                                                    dec16(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v16 =>
                                                                    dec17(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v17 =>
                                                                    dec18(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v18 =>
                                                                    dec19(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v19 =>
                                                                    dec20(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v20 =>
                                                                    dec21(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v21 =>
                                                                    dec22(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v22 =>
                                                                    dec23(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v23 =>
                                                                    dec24(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v24 =>
                                                                    dec25(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v25 =>
                                                                    dec26(
                                                                    dict,
                                                                    )
                                                                    >>= (
                                                                    v26 =>
                                                                    Belt.Result.Ok((
                                                                    v1,
                                                                    v2,
                                                                    v3,
                                                                    v4,
                                                                    v5,
                                                                    v6,
                                                                    v7,
                                                                    v8,
                                                                    v9,
                                                                    v10,
                                                                    v11,
                                                                    v12,
                                                                    v13,
                                                                    v14,
                                                                    v15,
                                                                    v16,
                                                                    v17,
                                                                    v18,
                                                                    v19,
                                                                    v20,
                                                                    v21,
                                                                    v22,
                                                                    v23,
                                                                    v24,
                                                                    v25,
                                                                    v26,
                                                                    ))
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                    )
                                                                )
                                                            )
                                                        )
                                                    )
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode);
};
