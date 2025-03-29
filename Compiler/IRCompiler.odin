#+feature dynamic-literals


package Compiler

import "core:mem"
import "core:strings"
import "core:unicode/utf8"
import "core:unicode"
import "core:fmt"
import "core:strconv"

import "Common"

@(private)
DSLCodeString: [dynamic]rune

DSLTokensList: [dynamic]Common.Token

@(private)
CurrentTokenIndex: int = 0

// Initializes the tokenizer input string
InitTokenizerCodeString :: proc(SourceCode: string, Allocator := context.allocator) {
    Runes: []rune = utf8.string_to_runes(SourceCode, Allocator)
    for Rune in Runes {
        append(&DSLCodeString, Rune)
    }
}

@(private)
MatchToken :: proc() {
    if CurrentTokenIndex >= len(DSLCodeString) {
        return
    }
    
    Rune: rune = DSLCodeString[CurrentTokenIndex]
    TokenText: [dynamic]rune
    TokenType: Common.TokenType = .INVALID  

    if unicode.is_letter(Rune) || Rune == '_' {
        append_elem(&TokenText, Rune)
        for CurrentTokenIndex + 1 < len(DSLCodeString) && 
              (unicode.is_letter(DSLCodeString[CurrentTokenIndex + 1]) || unicode.is_digit(DSLCodeString[CurrentTokenIndex + 1]) || DSLCodeString[CurrentTokenIndex + 1] == '_') {
            CurrentTokenIndex += 1
            append_elem(&TokenText, DSLCodeString[CurrentTokenIndex])
        }
        TokenType = ClassifyIdentifier(utf8.runes_to_string(TokenText[:]))
    } 
    else if unicode.is_digit(Rune) {
        append_elem(&TokenText, Rune)
        for CurrentTokenIndex + 1 < len(DSLCodeString) && unicode.is_digit(DSLCodeString[CurrentTokenIndex + 1]) {
            CurrentTokenIndex += 1
            append_elem(&TokenText, DSLCodeString[CurrentTokenIndex])
        }
        TokenType = .INT_32  // Default type (can be adjusted later to specific type)

        // Convert token to integer for validation
        IntValue: i128 = cast(i128)strconv.atoi(utf8.runes_to_string(TokenText[:]))

        // Range checking based on token type
        if TokenType == .INT_8 && (IntValue < -128 || IntValue > 127) {
            fmt.eprint("Integer value", utf8.runes_to_string(TokenText[:]), "is out of range for type int8")
        } else if TokenType == .INT_16 && (IntValue < -32768 || IntValue > 32767) {
            fmt.eprint("Integer value", utf8.runes_to_string(TokenText[:]), "is out of range for type int16")
        } else if TokenType == .INT_32 && (IntValue < -2147483648 || IntValue > 2147483647) {
            fmt.eprint("Integer value", utf8.runes_to_string(TokenText[:]), "is out of range for type int32")
        } else if TokenType == .INT_64 && (IntValue < -9223372036854775808 || IntValue > 9223372036854775807) {
            fmt.eprint("Integer value", utf8.runes_to_string(TokenText[:]),"is out of range for type int64")
        } else if TokenType == .U_INT_8 && (IntValue < 0 || IntValue > 255) {
            fmt.eprint("Unsigned integer value", utf8.runes_to_string(TokenText[:]), "is out of range for type uint8")
        } else if TokenType == .U_INT_16 && (IntValue < 0 || IntValue > 65535) {
            fmt.eprint("Unsigned integer value", utf8.runes_to_string(TokenText[:]), "is out of range for type uint16")
        } else if TokenType == .U_INT_32 && (IntValue < 0 || IntValue > 4294967295) {
            fmt.eprint("Unsigned integer value ", utf8.runes_to_string(TokenText[:]), "is out of range for type uint32")
        } else if TokenType == .U_INT_64 && (IntValue < 0 || cast(uint)IntValue > 18446744073709551615) {
            fmt.eprint("Unsigned integer value", utf8.runes_to_string(TokenText[:]), "is out of range for type uint64")
        }
    } 
    else if Rune == '"' {
        for CurrentTokenIndex + 1 < len(DSLCodeString) && DSLCodeString[CurrentTokenIndex + 1] != '"' {
            CurrentTokenIndex += 1
            append_elem(&TokenText, DSLCodeString[CurrentTokenIndex])
        }
        if CurrentTokenIndex + 1 < len(DSLCodeString) {
            CurrentTokenIndex += 1 
            TokenType = .STRING
        }
    } 
    else if Rune == '\'' {
        if CurrentTokenIndex + 1 < len(DSLCodeString) && CurrentTokenIndex + 2 < len(DSLCodeString) && DSLCodeString[CurrentTokenIndex + 2] == '\'' {
            append_elem(&TokenText, DSLCodeString[CurrentTokenIndex + 1])
            CurrentTokenIndex += 2
            TokenType = .CHAR
        }
    } 
    else if Rune == '#' && CurrentTokenIndex + 1 < len(DSLCodeString) && DSLCodeString[CurrentTokenIndex + 1] == '[' {
        for CurrentTokenIndex + 1 < len(DSLCodeString) && !(DSLCodeString[CurrentTokenIndex] == ']' && DSLCodeString[CurrentTokenIndex + 1] == '#') {
            CurrentTokenIndex += 1
        }
        if CurrentTokenIndex + 1 < len(DSLCodeString) {
            CurrentTokenIndex += 1 
            TokenType = .COMMENT_END
        }
    } 
    else if IsOperator(Rune) {
        append_elem(&TokenText, Rune)
        // Check for continuation of the operator
        if CurrentTokenIndex + 1 < len(DSLCodeString) && IsOperatorContinuation(DSLCodeString[CurrentTokenIndex + 1]) {
            CurrentTokenIndex += 1
            append_elem(&TokenText, DSLCodeString[CurrentTokenIndex])
        }
        TokenType = ClassifyOperator(utf8.runes_to_string(TokenText[:]))
    } 
    else if IsSeparator(Rune) {
        RuneListBecauseOfTypeSystem: [1]rune = Rune
        TokenType = ClassifySeparator(utf8.runes_to_string(RuneListBecauseOfTypeSystem[:]))
    }
    
    if TokenType != .INVALID {
        append(&DSLTokensList, Common.Token{Type = TokenType, Text = utf8.runes_to_string(TokenText[:])})
    }
    
    CurrentTokenIndex += 1
}



@(private)
// Classifies identifiers (keywords and built-ins)
ClassifyIdentifier :: proc(Text: string) -> Common.TokenType {
    Keywords: map[string]Common.TokenType = {
        "const" = .CONST, "var" = .VAR, "func" = .FUNC,
        "while" = .WHILE, "for" = .FOR, "if" = .IF, "elif" = .ELIF, "else" = .ELSE,
        "int8" = .INT_8, "int16" = .INT_16, "int32" = .INT_32, "int64" = .INT_64,
        "uint8" = .U_INT_8, "uint16" = .U_INT_16, "uint32" = .U_INT_32, "uint64" = .U_INT_64
    }
    Builtins: map[string]Common.TokenType = {
        "Allocate" = .BUILTIN_ALLOCATE, "Free" = .BUILTIN_FREE,
        "Pointer" = .BUILTIN_POINTER, "ListAddToEnd" = .BUILTIN_LIST_ADD_TO_END,
        "ListAddToStart" = .BUILTIN_LIST_ADD_TO_START, "ListInsert" = .BUILTIN_LIST_INSERT,
        "ListRemove" = .BUILTIN_LIST_REMOVE, "Input" = .BUILTIN_INPUT, "Output" = .BUILTIN_OUTPUT
    }

    if Text in Keywords {
        return Keywords[Text]
    }
    else if Text in Builtins {
        return Builtins[Text]
    } else {
        return .SYMBOL
    }
}

@(private)
// Classifies operators
ClassifyOperator :: proc(Text: string) -> Common.TokenType {
    Operators: map[string]Common.TokenType = {
        "+"  = .PLUS, "-"  = .MINUS, "*"  = .MULTIPLY, "/"  = .DIVIDE, "%"  = .MODULO,
        "++" = .INCREMENT, "--" = .DECREMENT, "="  = .ASSIGN, "==" = .EQUAL,
        "!=" = .NOT_EQUAL, "<"  = .LESS_THAN, ">"  = .GREATER_THAN,
        "<=" = .LESS_THAN_EQUAL_TO, ">=" = .GREATER_THAN_EQUAL_TO,
        "||" = .OR, "&&" = .AND, "!"  = .NOT
    }
    return Operators[Text] 
}

@(private)
// Classifies separators and delimiters
ClassifySeparator :: proc(Text: string) -> Common.TokenType {
    Separators: map[string]Common.TokenType = {
        "(" = .L_PAREN, ")" = .R_PAREN, "[" = .R_SQUARE_BRACKET, "]" = .R_SQUARE_BRACKET,
        "{" = .L_CURLY_BRACKET, "}" = .R_CURLY_BRACKET, "," = .COMMA,
        ";" = .SEMI_COLON, ":" = .COLON, "@" = .AT_SIGN
    }
    return Separators[Text]
}

@(private)
// Checks if a rune is an operator
IsOperator :: proc(R: rune) -> bool {
    switch R {
        case '+', '-', '*', '/', '%', '=', '<', '>', '!', '|', '&':
            return true
        case:
            return false
    }
}

@(private)
// Checks if a rune is a valid operator continuation
IsOperatorContinuation :: proc(R: rune) -> bool {
    switch R {
        case '(', ')', '[', ']', '{', '}', ',', ';', ':', '@':
            return true
        case:
            return false
    }
}

@(private)
// Checks if a rune is a separator
IsSeparator :: proc(R: rune) -> bool {
    switch R {
        case '(', ')', '[', ']', '{', '}', ',', ';', ':', '@':
            return true
        case:
            return false
        }
}

// Main tokenizer function
Tokenize :: proc(Allocator := context.allocator) {
    for CurrentTokenIndex < len(DSLCodeString) {
        MatchToken()
    }
}
