package Common

// This file defines types used in the compiler such as the tokenizer and parser

// Tokenizer types

TOKEN_TYPE :: enum {
    
    // Data types
    INT_8,
    INT_16,
    INT_32,
    INT_64,
    U_INT_8,
    U_INT_16,
    U_INT_32,
    U_INT_64,
    FLOAT_32,
    FLOAT_64,
    BOOL,
    INHERIT,
    CHAR,
    STRING,

    // Keywords
    CONST,
    VAR,
    FUNC,
    WHILE,
    FOR,
    IF,
    ELIF,
    ELSE,
    BUILTIN_ALLOCATE,
    BUILTIN_FREE,
    BUILTIN_POINTER,
    BUILTIN_REFERENCE,
    BUILTIN_LIST_ADD_TO_END,
    BUILTIN_LIST_ADD_TO_START,
    BUILTIN_LIST_INSERT,
    BUILTIN_LIST_REMOVE,
    BUILTIN_INPUT,
    BUILTIN_OUTPUT,
    FUNC_MOD_ENTRY,

    // Operators
    PLUS,                // +
    MINUS,               // -
    MULTIPLY,            // *
    DIVIDE,              // /
    MODULO,              // %
    INCREMENT,           // ++
    DECREMENT,           // --
    ASSIGN,              // =
    LESS_THAN,           // <
    GREATER_THAN,        // >
    LESS_THAN_EQUAL_TO,  // <=
    GREATER_THAN_EQUAL_TO, // >=
    NOT_EQUAL,           // !=
    EQUAL,               // ==
    OR,                  // ||
    AND,                 // &&
    NOT,                 // !

    // Symbols & Delimiters
    L_PAREN,             // (
    R_PAREN,             // )
    L_SQUARE_BRACKET,    // [
    R_SQUARE_BRACKET,    // ]
    L_CURLY_BRACKET,     // {
    R_CURLY_BRACKET,     // }
    COMMA,               // ,
    SEMI_COLON,          // ;
    COLON,               // :
    AT_SIGN,             // @
    

    // Comments
    COMMENT_START,       // #[
    COMMENT_END,         // ]#

    // String & Char Specific
    DOUBLE_QUOTE,        // "
    SINGLE_QUOTE,        // '

    // General Identifiers
    SYMBOL,
    WHITE_SPACE
}

TOKEN :: struct {
    
    TOKEN_TEXT: string,
    TOKEN_TYPE: TOKEN_TYPE

}




// Parser types

AST_NODE :: struct {
    TOKEN_IN_NODE: TOKEN,
    NEXT_AST_NODE: ^AST_NODE

}



// General Types

DSL_ERRORS :: enum {
    SYNTAX_ERROR,            // General syntax error (e.g., unexpected token)
    UNEXPECTED_TOKEN,        // Encountered an unexpected token in the current context
    MISSING_SEMICOLON,       // Expected a semicolon but didn't find one
    UNMATCHED_BRACKETS,      // Unmatched parentheses, square brackets, or curly braces
    INVALID_TYPE,            // Invalid type for a variable or expression
    EXPECTED_EXPRESSION,     // Expected an expression, but none found (e.g., in an assignment)
    MISSING_IDENTIFIER,      // Missing identifier (e.g., variable name in declaration)
    UNDEFINED_VARIABLE,      // Using a variable that hasn't been declared
    UNDEFINED_FUNCTION,      // Calling a function that hasn't been declared
    UNEXPECTED_END_OF_STATEMENT, // Missing statement terminator (semicolon or closing bracket)
    EXPECTED_CONDITION,      // Missing condition in `if`, `while`, or other control structures
    EXPECTED_BODY,           // Missing body in a function or control structure
    FUNCTION_PARAMETER_ERROR, // Error in function parameters (e.g., mismatched types)
    PREPROCESSOR_ERROR,      // Error related to a preprocessor directive (e.g., `!using`)
}
