module Hsv = {
  type t = {
    hue: int,
    saturation: int,
    value: int,
  };

  let decode = json => {
    Json.Decode.{
      hue: json |> field("hue", int),
      saturation: json |> field("saturation", int),
      value: json |> field("value", int),
    };
  };
};

module Hsl = {
  type t = {
    hue: int,
    saturation: int,
    lightness: int,
  };

  let decode = json => {
    Json.Decode.{
      hue: json |> field("hue", int),
      saturation: json |> field("saturation", int),
      lightness: json |> field("lightness", int),
    };
  };
};

type t = {
  name: string,
  hex: string,
  hsv: Hsv.t,
  hsl: Hsl.t,
};

let decode = json => {
  Json.Decode.{
    name: json |> field("name", string),
    hex: json |> field("hex", string),
    hsv: json |> field("hsv", Hsv.decode),
    hsl: json |> field("hsl", Hsl.decode),
  };
};
