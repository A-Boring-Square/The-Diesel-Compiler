#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <map>
#include <list>
#include <algorithm>



// Enumeration of token types
enum Tokens {
    // Comment tokens
    COMMENT_START,   // Token representing the start of a comment
    COMMENT_END,     // Token representing the end of a comment

    // I/O operation tokens
    IO_OUTPUT,       // Token representing an output operation
    IO_INPUT,        // Token representing an input operation

    // Variable tokens
    VAR_CONSTANT,    // Token representing a constant variable
    VAR,             // Token representing a variable
    VAR_LIST,        // Token representing a variable list (with optional array notation)

    // Data type tokens
    TYPE_UNSIGNED_INT_4,  // Token for 4-byte unsigned integer
    TYPE_SIGNED_INT_4,    // Token for 4-byte signed integer
    TYPE_UNSIGNED_INT_8,  // Token for 8-byte unsigned integer
    TYPE_SIGNED_INT_8,    // Token for 8-byte signed integer
    TYPE_UNSIGNED_INT_16, // Token for 16-byte unsigned integer
    TYPE_SIGNED_INT_16,   // Token for 16-byte signed integer
    TYPE_UNSIGNED_INT_32, // Token for 32-byte unsigned integer
    TYPE_SIGNED_INT_32,   // Token for 32-byte signed integer
    TYPE_UNSIGNED_INT_64, // Token for 64-byte unsigned integer
    TYPE_SIGNED_INT_64,   // Token for 64-byte signed integer
    TYPE_FLOAT_32,        // Token for 32-bit floating point
    TYPE_FLOAT_64,        // Token for 64-bit floating point
    TYPE_CHAR,            // Token for character data type
    TYPE_STRING,          // Token for string data type
    TYPE_BOOL,            // Token for boolean data type
    TYPE_INHERIT,         // Token for inheriting data type

    // Function tokens
    FUNCTION_DEF,        // Token representing a function definition
    FUNCTION_MODIFIER_ENTRY, // Token representing function modifier `%entry%` (entry point)

    // Delimiter tokens
    PERIOD,              // Token for period `.` 
    COMMA,               // Token for comma `,`
    SEMICOLON,           // Token for semicolon `;`
    COLON,               // Token for colon `:`
    PAREN_OPEN,          // Token for open parenthesis `(`
    PAREN_CLOSE,         // Token for close parenthesis `)`
    SQUARE_PAREN_OPEN,   // Token for open square bracket `[`
    SQUARE_PAREN_CLOSE,  // Token for close square bracket `]`
    CURLY_PAREN_OPEN,    // Token for open curly brace `{`
    CURLY_PAREN_CLOSE,   // Token for close curly brace `}`

    // Operator tokens
    VAR_ASSIGN,          // Token for variable assignment `=`
    COMPARE_GREATER,     // Token for greater than `>`
    COMPARE_LESS,        // Token for less than `<`
    COMPARE_EQUAL,       // Token for equality `==`
    COMPARE_GREATER_OR_EQUAL, // Token for greater than or equal to `>=`
    COMPARE_LESS_OR_EQUAL,    // Token for less than or equal to `<=`

    // Miscellaneous tokens
    NUMBER,              // Token representing a number (digits)
    TEXT,                // Token representing text (string literals)
    END_OF_FILE,         // Token representing end of file marker
};


#define COMMENT_START_REGEX ""
#define COMMENT_END_REGEX ""
#define IO_OUTPUT_REGEX ""
#define IO_INPUT_REGEX ""

// Tokenizer class definition
class Tokenizer {
private:

    std::list<Tokens> tokens;

    unsigned int sourceLength;
    std::string sourceCode;

public:
    Tokenizer(std::string& SrcCode, unsigned int SrcLen);
    ~Tokenizer();

    void Tokenize();

    std::list<Tokens> GetTokensList();


};
