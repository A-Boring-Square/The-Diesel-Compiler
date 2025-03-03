#+feature dynamic-literals

package Compiler

import "core:mem"
import "core:strings"
import "core:unicode/utf8"
import "core:unicode"
import "core:odin/tokenizer"
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
        TokenType = .INT_32  
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
        if CurrentTokenIndex + 1 < len(DSLCodeString) && IsOperator(DSLCodeString[CurrentTokenIndex + 1]) {
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
        "while" = .WHILE, "for" = .FOR, "if" = .IF, "elif" = .ELIF, "else" = .ELSE
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
