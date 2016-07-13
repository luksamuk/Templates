module Stack
    type 'a stack =
    | EmptyStack
    | StackNode of 'a * 'a stack
    
    let empty stack =
        match stack with
        | EmptyStack -> true
        | _          -> false
    
    let push x stack =
        StackNode(x, stack)
    
    let pop stack =
        match stack with
        | EmptyStack -> failwith "Pilha vazia!"
        | StackNode(head, tail) -> tail
    
    let top stack =
        match stack with
        | EmptyStack -> failwith "Pilha vazia!"
        | StackNode(head, tail) -> head

