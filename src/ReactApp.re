let colorsUrl = "https://raw.githubusercontent.com/trite/trite.io-content/main/exampleData/colorPalette.json";

module App = {
  // This sample forces an import of Belt.*, so that CI builds can ensure that
  // Melange has been installed correctly for JS bundlers to be able to find it.
  [@react.component]
  let make = () => {
    let (colors, setColors) = React.useState(() => [||]);

    React.useEffect(() => {
      let _ =
        Js.Promise.(
          Fetch.fetch(colorsUrl)
          |> then_(Fetch.Response.json)
          |> then_(json =>
               json
               ->Js.Json.decodeArray
               ->Belt.Option.getExn
               ->Belt.Array.map(Color.decode)
               ->resolve
             )
          |> then_(colors => {setColors(_ => colors) |> resolve})
        );

      Some(() => ());
    });

    <div>
      <h1> "Colors"->React.string </h1>
      {colors
       |> Array.map(({name, hex}: Color.t) =>
            <div style={ReactDOM.Style.make(~display="flex", ())}>
              <div
                style={ReactDOM.Style.make(
                  ~backgroundColor=hex,
                  ~width="400px",
                  ~height="50px",
                  (),
                )}
              />
              <p> {name |> React.string} </p>
            </div>
          )
       |> React.array}
    </div>;
  };
};

ReactDOM.querySelector("#root")
->(
    fun
    | Some(root) => ReactDOM.render(<App />, root)
    | None =>
      Js.Console.error(
        "Failed to start React: couldn't find the #root element",
      )
  );
