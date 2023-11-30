type t = {
  name: string,
  hex: string,
};

let decode = json => {
  Json.Decode.{
    name: json |> field("name", string),
    hex: json |> field("hex", string),
  };
};
