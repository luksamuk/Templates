// Unfolding Fibonacci sequence

let fibonacci =
    Seq.unfold
        (fun (n0, n1) ->
            Some(n0, (n1, n0 + n1)))
        (1I, 1I)

for a in (Seq.take 15 fibonacci) do
    printfn "%A" a
