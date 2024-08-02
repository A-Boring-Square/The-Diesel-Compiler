#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <map>
#include <list>
#include <algorithm>

// Base token type with templated data equivalent
template<typename DataEquivalent>
struct BASE_TOKEN_TYPE
{
    std::string RegexString;       // Regular expression pattern to match this token
    DataEquivalent* CppDataEquivalent; // Pointer to a C++ equivalent data for the token
    unsigned int TypeByteSize;     // Size of the token's data type in bytes
    bool IsConst;                  // Flag to indicate if the token represents a constant value

    // Constructor to initialize the token type
    BASE_TOKEN_TYPE(
        std::string RegexString,
        DataEquivalent* CppDataEquivalent,
        unsigned int TypeByteSize,
        bool IsConst
    ) : RegexString(RegexString),           // Initialize RegexString with given value
        CppDataEquivalent(CppDataEquivalent), // Initialize CppDataEquivalent with given pointer
        TypeByteSize(TypeByteSize),           // Initialize TypeByteSize with given value
        IsConst(IsConst)                      // Initialize IsConst with given value
    {}

    // Print detailed information about the token
    void PrintInfo() const {
        std::cout << "RegexString: " << RegexString << std::endl; // Print regex pattern
        if (CppDataEquivalent) {                           // Check if CppDataEquivalent is not null
            std::cout << "CppDataEquivalent: " << *CppDataEquivalent << std::endl; // Print value pointed by CppDataEquivalent
        }
        else {
            std::cout << "CppDataEquivalent: nullptr" << std::endl; // Print nullptr if CppDataEquivalent is null
        }
        std::cout << "TypeByteSize: " << TypeByteSize << std::endl; // Print size of the token's data type
        std::cout << "IsConst: " << (IsConst ? "true" : "false") << std::endl; // Print whether the token is constant
    }
};

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

// Token-specific structs

// Token for the start of a comment
struct TokenCommentStart : public BASE_TOKEN_TYPE<void> {
    TokenCommentStart()
        : BASE_TOKEN_TYPE<void>("#\\[", nullptr, 0, false) {} // Initialize with regex for start of comment
};

// Token for the end of a comment
struct TokenCommentEnd : public BASE_TOKEN_TYPE<void> {
    TokenCommentEnd()
        : BASE_TOKEN_TYPE<void>("\\]#", nullptr, 0, false) {} // Initialize with regex for end of comment
};

// Token for output operation
struct TokenIOOutput : public BASE_TOKEN_TYPE<void> {
    TokenIOOutput()
        : BASE_TOKEN_TYPE<void>("output", nullptr, 0, false) {} // Initialize with regex for output operation
};

// Token for input operation
struct TokenIOInput : public BASE_TOKEN_TYPE<void> {
    TokenIOInput()
        : BASE_TOKEN_TYPE<void>("input", nullptr, 0, false) {} // Initialize with regex for input operation
};

// Token for constant variable
struct TokenVarConstant : public BASE_TOKEN_TYPE<void> {
    TokenVarConstant()
        : BASE_TOKEN_TYPE<void>("const", nullptr, 0, false) {} // Initialize with regex for constant variable
};

// Token for variable
struct TokenVar : public BASE_TOKEN_TYPE<void> {
    TokenVar()
        : BASE_TOKEN_TYPE<void>("var", nullptr, 0, false) {} // Initialize with regex for variable
};

// Token for variable list (with optional array notation)
struct TokenVarList : public BASE_TOKEN_TYPE<void> {
    unsigned int ListLen; // is 0 if a vector
    TokenVarList()
        : BASE_TOKEN_TYPE<void>("var\\s+\\w+\\s*(\\[\\d*\\])?", nullptr, 0, false) {} // Initialize with regex for variable list
};

// Data type tokens (representing various data types)
struct TokenTypeUnsignedInt4 : public BASE_TOKEN_TYPE<void> {
    TokenTypeUnsignedInt4()
        : BASE_TOKEN_TYPE<void>("uint4", nullptr, 1, false) {} // Initialize with regex for 4-byte unsigned integer
};

struct TokenTypeSignedInt4 : public BASE_TOKEN_TYPE<void> {
    TokenTypeSignedInt4()
        : BASE_TOKEN_TYPE<void>("int4", nullptr, 1, false) {} // Initialize with regex for 4-byte signed integer
};

struct TokenTypeUnsignedInt8 : public BASE_TOKEN_TYPE<void> {
    TokenTypeUnsignedInt8()
        : BASE_TOKEN_TYPE<void>("uint8", nullptr, 1, false) {} // Initialize with regex for 8-byte unsigned integer
};

struct TokenTypeSignedInt8 : public BASE_TOKEN_TYPE<void> {
    TokenTypeSignedInt8()
        : BASE_TOKEN_TYPE<void>("int8", nullptr, 1, false) {} // Initialize with regex for 8-byte signed integer
};

struct TokenTypeUnsignedInt16 : public BASE_TOKEN_TYPE<void> {
    TokenTypeUnsignedInt16()
        : BASE_TOKEN_TYPE<void>("uint16", nullptr, 2, false) {} // Initialize with regex for 16-byte unsigned integer
};

struct TokenTypeSignedInt16 : public BASE_TOKEN_TYPE<void> {
    TokenTypeSignedInt16()
        : BASE_TOKEN_TYPE<void>("int16", nullptr, 2, false) {} // Initialize with regex for 16-byte signed integer
};

struct TokenTypeUnsignedInt32 : public BASE_TOKEN_TYPE<void> {
    TokenTypeUnsignedInt32()
        : BASE_TOKEN_TYPE<void>("uint32", nullptr, 4, false) {} // Initialize with regex for 32-byte unsigned integer
};

struct TokenTypeSignedInt32 : public BASE_TOKEN_TYPE<void> {
    TokenTypeSignedInt32()
        : BASE_TOKEN_TYPE<void>("int32", nullptr, 4, false) {} // Initialize with regex for 32-byte signed integer
};

struct TokenTypeUnsignedInt64 : public BASE_TOKEN_TYPE<void> {
    TokenTypeUnsignedInt64()
        : BASE_TOKEN_TYPE<void>("uint64", nullptr, 8, false) {} // Initialize with regex for 64-byte unsigned integer
};

struct TokenTypeSignedInt64 : public BASE_TOKEN_TYPE<void> {
    TokenTypeSignedInt64()
        : BASE_TOKEN_TYPE<void>("int64", nullptr, 8, false) {} // Initialize with regex for 64-byte signed integer
};

struct TokenTypeFloat32 : public BASE_TOKEN_TYPE<void> {
    TokenTypeFloat32()
        : BASE_TOKEN_TYPE<void>("float32", nullptr, 4, false) {} // Initialize with regex for 32-bit floating point
};

struct TokenTypeFloat64 : public BASE_TOKEN_TYPE<void> {
    TokenTypeFloat64()
        : BASE_TOKEN_TYPE<void>("float64", nullptr, 8, false) {} // Initialize with regex for 64-bit floating point
};

struct TokenTypeChar : public BASE_TOKEN_TYPE<void> {
    TokenTypeChar()
        : BASE_TOKEN_TYPE<void>("char", nullptr, 1, false) {} // Initialize with regex for character data type
};

struct TokenTypeString : public BASE_TOKEN_TYPE<void> {
    TokenTypeString()
        : BASE_TOKEN_TYPE<void>("string", nullptr, 0, false) {} // Initialize with regex for string data type
};

struct TokenTypeBool : public BASE_TOKEN_TYPE<void> {
    TokenTypeBool()
        : BASE_TOKEN_TYPE<void>("bool", nullptr, 1, false) {} // Initialize with regex for boolean data type
};

struct TokenTypeInherit : public BASE_TOKEN_TYPE<void> {
    TokenTypeInherit()
        : BASE_TOKEN_TYPE<void>("inherit", nullptr, 0, false) {} // Initialize with regex for inheriting data type
};

// Token for function definition
struct TokenFunctionDef : public BASE_TOKEN_TYPE<void> {
    TokenFunctionDef()
        : BASE_TOKEN_TYPE<void>("def", nullptr, 0, false) {} // Initialize with regex for function definition
};

// Token for function modifier `%entry%` (entry point)
struct TokenFunctionModifierEntry : public BASE_TOKEN_TYPE<void> {
    TokenFunctionModifierEntry()
        : BASE_TOKEN_TYPE<void>("%entr%", nullptr, 0, false) {} // Initialize with regex for function modifier `%entr%`
};

// Token for period `.` 
struct TokenPeriod : public BASE_TOKEN_TYPE<void> {
    TokenPeriod()
        : BASE_TOKEN_TYPE<void>(".", nullptr, 0, false) {}
};

// Token for comma `,`
struct TokenComma : public BASE_TOKEN_TYPE<void> {
    TokenComma()
        : BASE_TOKEN_TYPE<void>(",", nullptr, 0, false) {}
};         

// Token for semicolon `;`
struct TokenSemicolon : public BASE_TOKEN_TYPE<void> {
    TokenSemicolon()
        : BASE_TOKEN_TYPE<void>(";", nullptr, 0, false) {}
};

// Token for colon `:`
struct TokenColon : public BASE_TOKEN_TYPE<void> {
    TokenColon()
        : BASE_TOKEN_TYPE<void>(":", nullptr, 0, false) {}
};

// Token for open parenthesis `(`
struct TokenParenOpen : public BASE_TOKEN_TYPE<void> {
    TokenParenOpen()
        : BASE_TOKEN_TYPE<void>("(", nullptr, 0, false) {}
};         

// Token for close parenthesis `)`
struct TokenParenClose : public BASE_TOKEN_TYPE<void> {
    TokenParenClose()
        : BASE_TOKEN_TYPE<void>(")", nullptr, 0, false) {}
};

// Token for open square bracket `[`
struct TokenSquareParenOpen : public BASE_TOKEN_TYPE<void> {
    TokenSquareParenOpen()
        : BASE_TOKEN_TYPE<void>("[", nullptr, 0, false) {}
};

// Token for close square bracket `]`
struct TokenSquareParenClose : public BASE_TOKEN_TYPE<void> {
    TokenSquareParenClose()
        : BASE_TOKEN_TYPE<void>("]", nullptr, 0, false) {}
};

// Token for open curly brace `{`
struct TokenCurlyParenOpen : public BASE_TOKEN_TYPE<void> {
    TokenCurlyParenOpen()
        : BASE_TOKEN_TYPE<void>("{", nullptr, 0, false) {}

};

// Token for close curly brace `}`
struct TokenCurlyParenClose : public BASE_TOKEN_TYPE<void> {
    TokenCurlyParenClose()
        : BASE_TOKEN_TYPE<void>("}", nullptr, 0, false) {}
};


// Tokenizer class definition
class Tokenizer {
private:
    std::vector<BASE_TOKEN_TYPE<void>> Vars;
    std::vector<BASE_TOKEN_TYPE<void>> Consts;
    std::map<BASE_TOKEN_TYPE<void>, std::list<BASE_TOKEN_TYPE<void>>> FunctionsAndCodeTokensInsideThem;
    unsigned int sourceLength;
    std::string sourceCode;

public:
    Tokenizer(std::string& SrcCode, unsigned int SrcLen);
    ~Tokenizer();

    void Tokenize();

    std::list<BASE_TOKEN_TYPE<void>> GetTokensList();


};
