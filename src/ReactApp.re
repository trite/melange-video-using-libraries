let colorsUrl = "https://raw.githubusercontent.com/trite/trite.io-content/main/exampleData/colorPalette.json";

module App = {
  // This sample forces an import of Belt.*, so that CI builds can ensure that
  // Melange has been installed correctly for JS bundlers to be able to find it.
  [@react.component]
  let make = () => {
    let (colors, setColors) = React.useState(() => "");

    React.useEffect(() => {
      let _ =
        Js.Promise.(
          Fetch.fetch(colorsUrl)
          |> then_(Fetch.Response.text)
          |> then_(text => setColors(_ => text) |> resolve)
        );

      Some(() => ());
    });

    <div>
      <h1> "Colors"->React.string </h1>
      <p> colors->React.string </p>
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
