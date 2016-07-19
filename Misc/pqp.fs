module PQP
open System

[<EntryPoint>]
let main argv =
    printf "Vai mandar pra puta que pariu "

    let swearing = [|
        "quem manda pra puta que pariu";
        "quem come a puta que o pariu";
        "quem, advinha so? Manda ir pra puta que pariu";
        "o que manda ir pra puta que pariu";
        "na puta que te pariu";
        "pra puta que o pariu";
        "que manda pra puta que pariu"
    |]

    let getRand =
        let rnd = Random()
        fun (arr : string array) -> arr.[rnd.Next(arr.Length)]

    match argv.Length with
    | 0 -> ()
    | _ ->
        for i = 0 to (Int32.Parse <| argv.[0]) - 1 do
            let rnd = Random(0)
            printf "%s " (getRand swearing)
    printfn "na puta que te pariu, rapaz."
    0
