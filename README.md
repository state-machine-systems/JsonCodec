# JsonCodec

## JSON combinator library for BuckleScript/Reason

Using the magic of [pickler combinators](https://www.microsoft.com/en-us/research/wp-content/uploads/2004/01/picklercombinators.pdf), this library allows you to parse and serialize JSON structures in a declarative way, free of boilerplate.

Here's a little example:

```reason
let json = {js|
{
    "name": "Great Pyramid of Giza",
    "lat": 29.979175,
    "lon": 31.134358,
    "height": 146.5
}
|js};

/* Define a codec for the above object type */
let codec =
  JsonCodec.(
    object4(
      field("name", string),
      field("lat", number),
      field("long", number),
      field("height", number)
    )
  );

/* Decoding */
switch (JsonCodec.decodeJson(codec, json)) {
| Js.Result.Ok((name, lat, lon, height)) =>
  Printf.printf("name='%s' location=%f,%f height=%f\n", name, lat, lon, height)
| Js.Result.Error(error) => Printf.printf("Decoding error: %s", error)
};

/* Encoding */
let encoded =
  JsonCodec.encodeJson(codec, ("Machu Picchu", -13.163333, -72.545556, 2430.0));

Printf.printf("JSON: %s\n", encoded);
```


&copy; 2017 State Machine Systems Ltd. [Apache Licence, Version 2.0](http://www.apache.org/licenses/LICENSE-2.0)
