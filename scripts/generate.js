let fs = require('fs');

let contents = [
    "/* This file is auto-generated. Please do not modify it. */",
    "open JsonCodec_result.Ops;"
];
for (let i = 1; i <= 26; i++) {
    contents.push(generateObjectCodec(i));
}

fs.writeFile("src/jsonCodec_object.re", contents.join("\n"), function(err) {
    if (err) {
        console.log(err);
        process.exit(1);
    }
});

function generateObjectCodec(n) {
    let letters = " abcdefghijklmnopqrstuvwxyz";
    let numbers = [...Array(n).keys()].map(k => k + 1);
    let typeVariable = i => `'${letters[i]}`;

    // start of declaration
    let code = [`let object${n}`];

    // arguments
    numbers.forEach(i => code.push(`((enc${i}, dec${i}): JsonCodec_core.FieldCodec.t ${typeVariable(i)})`));

    // return type
    code.push(":JsonCodec_core.Codec.t (");
    code.push(numbers.map(typeVariable).join(", "));
    code.push(")");

    // body start
    code.push("=> {");

    // encoder declaration
    code.push("let encode (");
    code.push(numbers.map(i => `v${i}`).join(", "));
    code.push(") => Js.Json.object_ @@ JsonCodec_util.buildDict [");
    code.push(numbers.map(i => `enc${i} v${i}`).join(", "));
    code.push("];");

    // decoder declaration
    code.push("let decode json => JsonCodec_util.decodeRawObject json >>=");
    code.push(`fun dict => dec1 dict`);
    for (let i = 1; i < n; i++) {
        code.push(`>>= fun v${i} => dec${i + 1} dict`);
    }
    if (n > 1) {
        code.push(`>>= fun v${n} => Js.Result.Ok (`);
        code.push(numbers.map(i => `v${i}`).join(", "));
        code.push(")");
    }
    code.push(";");

    // return value
    code.push("(encode, decode)");

    // body end
    code.push("};");

    return code.join(" ");
}
