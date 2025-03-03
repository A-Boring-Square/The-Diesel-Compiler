package Common

import "core:fmt"

PrintToken :: proc(token: ^Token) {
    if token == nil {
        fmt.printfln("ERROR: Null token reference")
        return
    }

    TokenTypeToPrint := token.Type
    TokenText := token.Text 

    fmt.printfln("TOKEN:")
    fmt.printfln("\tTYPE: %s", TokenTypeToPrint)
    fmt.printfln("\tTEXT: \"%s\"", TokenText)

    #partial switch TokenTypeToPrint {
    case .AND:                     fmt.printfln("\tDESCRIPTION: Logical AND operator (&&)")
    case .OR:                      fmt.printfln("\tDESCRIPTION: Logical OR operator (||)")
    case .NOT:                     fmt.printfln("\tDESCRIPTION: Logical NOT operator (!)")
    case .PLUS:                    fmt.printfln("\tDESCRIPTION: Addition operator (+)")
    case .MINUS:                   fmt.printfln("\tDESCRIPTION: Subtraction operator (-)")
    case .MULTIPLY:                fmt.printfln("\tDESCRIPTION: Multiplication operator (*)")
    case .DIVIDE:                  fmt.printfln("\tDESCRIPTION: Division operator (/)")
    case .MODULO:                  fmt.printfln("\tDESCRIPTION: Modulus operator (%)")
    case .INCREMENT:               fmt.printfln("\tDESCRIPTION: Increment operator (++)")
    case .DECREMENT:               fmt.printfln("\tDESCRIPTION: Decrement operator (--)")
    case .ASSIGN:                  fmt.printfln("\tDESCRIPTION: Assignment operator (=)")
    case .EQUAL:                   fmt.printfln("\tDESCRIPTION: Equality comparison (==)")
    case .NOT_EQUAL:               fmt.printfln("\tDESCRIPTION: Inequality comparison (!=)")
    case .LESS_THAN:               fmt.printfln("\tDESCRIPTION: Less than comparison (<)")
    case .GREATER_THAN:            fmt.printfln("\tDESCRIPTION: Greater than comparison (>)")
    case .LESS_THAN_EQUAL_TO:      fmt.printfln("\tDESCRIPTION: Less than or equal (<=)")
    case .GREATER_THAN_EQUAL_TO:   fmt.printfln("\tDESCRIPTION: Greater than or equal (>=)")

    // Data types
    case .INT_8:                   fmt.printfln("\tDESCRIPTION: 8-bit integer")
    case .INT_16:                  fmt.printfln("\tDESCRIPTION: 16-bit integer")
    case .INT_32:                  fmt.printfln("\tDESCRIPTION: 32-bit integer")
    case .INT_64:                  fmt.printfln("\tDESCRIPTION: 64-bit integer")
    case .U_INT_8:                 fmt.printfln("\tDESCRIPTION: Unsigned 8-bit integer")
    case .U_INT_16:                fmt.printfln("\tDESCRIPTION: Unsigned 16-bit integer")
    case .U_INT_32:                fmt.printfln("\tDESCRIPTION: Unsigned 32-bit integer")
    case .U_INT_64:                fmt.printfln("\tDESCRIPTION: Unsigned 64-bit integer")
    case .FLOAT_32:                fmt.printfln("\tDESCRIPTION: 32-bit floating-point number")
    case .FLOAT_64:                fmt.printfln("\tDESCRIPTION: 64-bit floating-point number")
    case .BOOL:                    fmt.printfln("\tDESCRIPTION: Boolean (true/false)")
    case .CHAR:                    fmt.printfln("\tDESCRIPTION: Character")
    case .STRING:                  fmt.printfln("\tDESCRIPTION: String literal")

    // Keywords
    case .CONST:                   fmt.printfln("\tDESCRIPTION: Constant declaration")
    case .VAR:                     fmt.printfln("\tDESCRIPTION: Variable declaration")
    case .FUNC:                    fmt.printfln("\tDESCRIPTION: Function definition")
    case .WHILE:                   fmt.printfln("\tDESCRIPTION: While loop")
    case .FOR:                      fmt.printfln("\tDESCRIPTION: For loop")
    case .IF:                      fmt.printfln("\tDESCRIPTION: If statement")
    case .ELIF:                    fmt.printfln("\tDESCRIPTION: Else-if statement")
    case .ELSE:                    fmt.printfln("\tDESCRIPTION: Else statement")
    case .INHERIT:                 fmt.printfln("\tDESCRIPTION: Inheritance keyword")

    // Built-in functions
    case .BUILTIN_ALLOCATE:        fmt.printfln("\tDESCRIPTION: Built-in memory allocation function")
    case .BUILTIN_FREE:            fmt.printfln("\tDESCRIPTION: Built-in memory deallocation function")
    case .BUILTIN_POINTER:         fmt.printfln("\tDESCRIPTION: Built-in pointer function")
    case .BUILTIN_REFERENCE:       fmt.printfln("\tDESCRIPTION: Built-in reference function")
    case .BUILTIN_LIST_ADD_TO_END: fmt.printfln("\tDESCRIPTION: Built-in list operation (add to end)")
    case .BUILTIN_LIST_ADD_TO_START: fmt.printfln("\tDESCRIPTION: Built-in list operation (add to start)")
    case .BUILTIN_LIST_INSERT:     fmt.printfln("\tDESCRIPTION: Built-in list insertion function")
    case .BUILTIN_LIST_REMOVE:     fmt.printfln("\tDESCRIPTION: Built-in list removal function")
    case .BUILTIN_INPUT:           fmt.printfln("\tDESCRIPTION: Built-in input function")
    case .BUILTIN_OUTPUT:          fmt.printfln("\tDESCRIPTION: Built-in output function")

    // Function modifiers
    case .FUNC_MOD_ENTRY:          fmt.printfln("\tDESCRIPTION: Function entry point modifier")

    // Symbols & punctuation
    case .L_PAREN:                 fmt.printfln("\tDESCRIPTION: Left parenthesis (()")
    case .R_PAREN:                 fmt.printfln("\tDESCRIPTION: Right parenthesis ())")
    case .L_SQUARE_BRACKET:        fmt.printfln("\tDESCRIPTION: Left square bracket ([)")
    case .R_SQUARE_BRACKET:        fmt.printfln("\tDESCRIPTION: Right square bracket (])")
    case .L_CURLY_BRACKET:         fmt.printfln("\tDESCRIPTION: Left curly bracket ({)")
    case .R_CURLY_BRACKET:         fmt.printfln("\tDESCRIPTION: Right curly bracket (})")
    case .SEMI_COLON:              fmt.printfln("\tDESCRIPTION: Semicolon (;)")
    case .AT_SIGN:                 fmt.printfln("\tDESCRIPTION: At sign (@)")
    case .COMMA:                   fmt.printfln("\tDESCRIPTION: Comma (,) - separates values")
    case .COLON:                   fmt.printfln("\tDESCRIPTION: Colon (:) - often used in declarations")

    // Comments
    case .COMMENT_START:           fmt.printfln("\tDESCRIPTION: Start of multi-line comment (# [ ... )")
    case .COMMENT_END:             fmt.printfln("\tDESCRIPTION: End of multi-line comment ( ... ] #)")
    
    // String & character literals
    case .DOUBLE_QUOTE:            fmt.printfln("\tDESCRIPTION: Double quote for string literals (\")")
    case .SINGLE_QUOTE:            fmt.printfln("\tDESCRIPTION: Single quote for character literals (')")

    // Miscellaneous
    case .SYMBOL:                  fmt.printfln("\tDESCRIPTION: Symbol (unknown classification)")
    case .WHITE_SPACE:             fmt.printfln("\tDESCRIPTION: Whitespace (ignored during parsing)")
    case:                          fmt.printfln("\tDESCRIPTION: Unknown token type")
    }

    fmt.printfln("") // Adds spacing for readability
}
