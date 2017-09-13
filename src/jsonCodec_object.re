open JsonCodec_result.Ops;

let object1 ((enc1, dec1): JsonCodec_core.FieldCodec.t 'a) :JsonCodec_core.Codec.t 'a => {
  let encode v1 => Js.Json.object_ (JsonCodec_util.buildDict [enc1 v1]);
  let decode json => JsonCodec_util.decodeRawObject json >>= (fun dict => dec1 dict);
  (encode, decode)
};

let object2
    ((enc1, dec1): JsonCodec_core.FieldCodec.t 'a)
    ((enc2, dec2): JsonCodec_core.FieldCodec.t 'b)
    :JsonCodec_core.Codec.t ('a, 'b) => {
  let encode (v1, v2) => Js.Json.object_ (JsonCodec_util.buildDict [enc1 v1, enc2 v2]);
  let decode json =>
    JsonCodec_util.decodeRawObject json >>= (
      fun dict => dec1 dict >>= (fun v1 => dec2 dict >>= (fun v2 => Js.Result.Ok (v1, v2)))
    );
  (encode, decode)
};

let object3
    ((enc1, dec1): JsonCodec_core.FieldCodec.t 'a)
    ((enc2, dec2): JsonCodec_core.FieldCodec.t 'b)
    ((enc3, dec3): JsonCodec_core.FieldCodec.t 'c)
    :JsonCodec_core.Codec.t ('a, 'b, 'c) => {
  let encode (v1, v2, v3) =>
    Js.Json.object_ (JsonCodec_util.buildDict [enc1 v1, enc2 v2, enc3 v3]);
  let decode json =>
    JsonCodec_util.decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 => dec2 dict >>= (fun v2 => dec3 dict >>= (fun v3 => Js.Result.Ok (v1, v2, v3)))
        )
    );
  (encode, decode)
};

let object4
    ((enc1, dec1): JsonCodec_core.FieldCodec.t 'a)
    ((enc2, dec2): JsonCodec_core.FieldCodec.t 'b)
    ((enc3, dec3): JsonCodec_core.FieldCodec.t 'c)
    ((enc4, dec4): JsonCodec_core.FieldCodec.t 'd)
    :JsonCodec_core.Codec.t ('a, 'b, 'c, 'd) => {
  let encode (v1, v2, v3, v4) =>
    Js.Json.object_ (JsonCodec_util.buildDict [enc1 v1, enc2 v2, enc3 v3, enc4 v4]);
  let decode json =>
    JsonCodec_util.decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (fun v3 => dec4 dict >>= (fun v4 => Js.Result.Ok (v1, v2, v3, v4)))
            )
        )
    );
  (encode, decode)
};

let object5
    ((enc1, dec1): JsonCodec_core.FieldCodec.t 'a)
    ((enc2, dec2): JsonCodec_core.FieldCodec.t 'b)
    ((enc3, dec3): JsonCodec_core.FieldCodec.t 'c)
    ((enc4, dec4): JsonCodec_core.FieldCodec.t 'd)
    ((enc5, dec5): JsonCodec_core.FieldCodec.t 'e)
    :JsonCodec_core.Codec.t ('a, 'b, 'c, 'd, 'e) => {
  let encode (v1, v2, v3, v4, v5) =>
    Js.Json.object_ (JsonCodec_util.buildDict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5]);
  let decode json =>
    JsonCodec_util.decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 => dec5 dict >>= (fun v5 => Js.Result.Ok (v1, v2, v3, v4, v5))
                    )
                )
            )
        )
    );
  (encode, decode)
};

let object6
    ((enc1, dec1): JsonCodec_core.FieldCodec.t 'a)
    ((enc2, dec2): JsonCodec_core.FieldCodec.t 'b)
    ((enc3, dec3): JsonCodec_core.FieldCodec.t 'c)
    ((enc4, dec4): JsonCodec_core.FieldCodec.t 'd)
    ((enc5, dec5): JsonCodec_core.FieldCodec.t 'e)
    ((enc6, dec6): JsonCodec_core.FieldCodec.t 'f)
    :JsonCodec_core.Codec.t ('a, 'b, 'c, 'd, 'e, 'f) => {
  let encode (v1, v2, v3, v4, v5, v6) =>
    Js.Json.object_ (
      JsonCodec_util.buildDict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5, enc6 v6]
    );
  let decode json =>
    JsonCodec_util.decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 =>
                        dec5 dict >>= (
                          fun v5 => dec6 dict >>= (fun v6 => Js.Result.Ok (v1, v2, v3, v4, v5, v6))
                        )
                    )
                )
            )
        )
    );
  (encode, decode)
};

let object7
    ((enc1, dec1): JsonCodec_core.FieldCodec.t 'a)
    ((enc2, dec2): JsonCodec_core.FieldCodec.t 'b)
    ((enc3, dec3): JsonCodec_core.FieldCodec.t 'c)
    ((enc4, dec4): JsonCodec_core.FieldCodec.t 'd)
    ((enc5, dec5): JsonCodec_core.FieldCodec.t 'e)
    ((enc6, dec6): JsonCodec_core.FieldCodec.t 'f)
    ((enc7, dec7): JsonCodec_core.FieldCodec.t 'g)
    :JsonCodec_core.Codec.t ('a, 'b, 'c, 'd, 'e, 'f, 'g) => {
  let encode (v1, v2, v3, v4, v5, v6, v7) =>
    Js.Json.object_ (
      JsonCodec_util.buildDict [enc1 v1, enc2 v2, enc3 v3, enc4 v4, enc5 v5, enc6 v6, enc7 v7]
    );
  let decode json =>
    JsonCodec_util.decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 =>
                        dec5 dict >>= (
                          fun v5 =>
                            dec6 dict >>= (
                              fun v6 =>
                                dec7 dict >>= (fun v7 => Js.Result.Ok (v1, v2, v3, v4, v5, v6, v7))
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode)
};

let object8
    ((enc1, dec1): JsonCodec_core.FieldCodec.t 'a)
    ((enc2, dec2): JsonCodec_core.FieldCodec.t 'b)
    ((enc3, dec3): JsonCodec_core.FieldCodec.t 'c)
    ((enc4, dec4): JsonCodec_core.FieldCodec.t 'd)
    ((enc5, dec5): JsonCodec_core.FieldCodec.t 'e)
    ((enc6, dec6): JsonCodec_core.FieldCodec.t 'f)
    ((enc7, dec7): JsonCodec_core.FieldCodec.t 'g)
    ((enc8, dec8): JsonCodec_core.FieldCodec.t 'h)
    :JsonCodec_core.Codec.t ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h) => {
  let encode (v1, v2, v3, v4, v5, v6, v7, v8) =>
    Js.Json.object_ (
      JsonCodec_util.buildDict [
        enc1 v1,
        enc2 v2,
        enc3 v3,
        enc4 v4,
        enc5 v5,
        enc6 v6,
        enc7 v7,
        enc8 v8
      ]
    );
  let decode json =>
    JsonCodec_util.decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 =>
                        dec5 dict >>= (
                          fun v5 =>
                            dec6 dict >>= (
                              fun v6 =>
                                dec7 dict >>= (
                                  fun v7 =>
                                    dec8 dict >>= (
                                      fun v8 => Js.Result.Ok (v1, v2, v3, v4, v5, v6, v7, v8)
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
  (encode, decode)
};

let object9
    ((enc1, dec1): JsonCodec_core.FieldCodec.t 'a)
    ((enc2, dec2): JsonCodec_core.FieldCodec.t 'b)
    ((enc3, dec3): JsonCodec_core.FieldCodec.t 'c)
    ((enc4, dec4): JsonCodec_core.FieldCodec.t 'd)
    ((enc5, dec5): JsonCodec_core.FieldCodec.t 'e)
    ((enc6, dec6): JsonCodec_core.FieldCodec.t 'f)
    ((enc7, dec7): JsonCodec_core.FieldCodec.t 'g)
    ((enc8, dec8): JsonCodec_core.FieldCodec.t 'h)
    ((enc9, dec9): JsonCodec_core.FieldCodec.t 'i)
    :JsonCodec_core.Codec.t ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i) => {
  let encode (v1, v2, v3, v4, v5, v6, v7, v8, v9) =>
    Js.Json.object_ (
      JsonCodec_util.buildDict [
        enc1 v1,
        enc2 v2,
        enc3 v3,
        enc4 v4,
        enc5 v5,
        enc6 v6,
        enc7 v7,
        enc8 v8,
        enc9 v9
      ]
    );
  let decode json =>
    JsonCodec_util.decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 =>
                        dec5 dict >>= (
                          fun v5 =>
                            dec6 dict >>= (
                              fun v6 =>
                                dec7 dict >>= (
                                  fun v7 =>
                                    dec8 dict >>= (
                                      fun v8 =>
                                        dec9 dict >>= (
                                          fun v9 =>
                                            Js.Result.Ok (v1, v2, v3, v4, v5, v6, v7, v8, v9)
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
  (encode, decode)
};

let object10
    ((enc1, dec1): JsonCodec_core.FieldCodec.t 'a)
    ((enc2, dec2): JsonCodec_core.FieldCodec.t 'b)
    ((enc3, dec3): JsonCodec_core.FieldCodec.t 'c)
    ((enc4, dec4): JsonCodec_core.FieldCodec.t 'd)
    ((enc5, dec5): JsonCodec_core.FieldCodec.t 'e)
    ((enc6, dec6): JsonCodec_core.FieldCodec.t 'f)
    ((enc7, dec7): JsonCodec_core.FieldCodec.t 'g)
    ((enc8, dec8): JsonCodec_core.FieldCodec.t 'h)
    ((enc9, dec9): JsonCodec_core.FieldCodec.t 'i)
    ((enc10, dec10): JsonCodec_core.FieldCodec.t 'j)
    :JsonCodec_core.Codec.t ('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j) => {
  let encode (v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) =>
    Js.Json.object_ (
      JsonCodec_util.buildDict [
        enc1 v1,
        enc2 v2,
        enc3 v3,
        enc4 v4,
        enc5 v5,
        enc6 v6,
        enc7 v7,
        enc8 v8,
        enc9 v9,
        enc10 v10
      ]
    );
  let decode json =>
    JsonCodec_util.decodeRawObject json >>= (
      fun dict =>
        dec1 dict >>= (
          fun v1 =>
            dec2 dict >>= (
              fun v2 =>
                dec3 dict >>= (
                  fun v3 =>
                    dec4 dict >>= (
                      fun v4 =>
                        dec5 dict >>= (
                          fun v5 =>
                            dec6 dict >>= (
                              fun v6 =>
                                dec7 dict >>= (
                                  fun v7 =>
                                    dec8 dict >>= (
                                      fun v8 =>
                                        dec9 dict >>= (
                                          fun v9 =>
                                            dec10 dict >>= (
                                              fun v10 =>
                                                Js.Result.Ok (
                                                  v1,
                                                  v2,
                                                  v3,
                                                  v4,
                                                  v5,
                                                  v6,
                                                  v7,
                                                  v8,
                                                  v9,
                                                  v10
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
  (encode, decode)
};
