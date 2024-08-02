#include "Tokenizer.hpp"
#include <regex>
#include <iostream>

// Constructor to initialize the Tokenizer with source code
Tokenizer::Tokenizer(std::string& SrcCode, unsigned int SrcLen)
    : sourceCode(SrcCode), sourceLength(SrcLen) {}

// Destructor to clean up resources
Tokenizer::~Tokenizer() {}

// Function to tokenize the source code
void Tokenizer::Tokenize() {
    std::vector<std::pair<std::string, BASE_TOKEN_TYPE<void>*>> tokenPatterns = {
        {"#\\[", new TokenCommentStart()},
        {"\\]#", new TokenCommentEnd()},
        {"output", new TokenIOOutput()},
        {"input", new TokenIOInput()},
        {"const", new TokenVarConstant()},
        {"var", new TokenVar()},
        {"uint4", new TokenTypeUnsignedInt4()},
        {"int4", new TokenTypeSignedInt4()},
        {"uint8", new TokenTypeUnsignedInt8()},
        {"int8", new TokenTypeSignedInt8()},
        {"uint16", new TokenTypeUnsignedInt16()},
        {"int16", new TokenTypeSignedInt16()},
        {"uint32", new TokenTypeUnsignedInt32()},
        {"int32", new TokenTypeSignedInt32()},
        {"uint64", new TokenTypeUnsignedInt64()},
        {"int64", new TokenTypeSignedInt64()},
        {"float32", new TokenTypeFloat32()},
        {"float64", new TokenTypeFloat64()},
        {"char", new TokenTypeChar()},
        {"string", new TokenTypeString()},
        {"bool", new TokenTypeBool()},
        {"inherit", new TokenTypeInherit()},
        {"def", new TokenFunctionDef()},
        {"\\.", new TokenPeriod()},
        {",", new TokenComma()},
        {";", new TokenSemicolon()},
        {":", new TokenColon()},
        {"\\(", new TokenParenOpen()},
        {"\\)", new TokenParenClose()},
        {"\\[", new TokenSquareParenOpen()},
        {"\\]", new TokenSquareParenClose()},
        {"\\{", new TokenCurlyParenOpen()},
        {"\\}", new TokenCurlyParenClose()},
        {"=", new TokenVarAssign()},
        {">", new TokenCompareGreater()},
        {"<", new TokenCompareLess()},
        {"==", new TokenCompareEqual()},
        {">=", new TokenCompareGreaterOrEqual()},
        {"<=", new TokenCompareLessOrEqual()},
        {"[0-9]+", new TokenNumber()},
        {"\".*\"", new TokenText()},
        {"EOF", new TokenEndOfFile()}
    };

    // Tokenize the source code
    std::string code = sourceCode;  // Use the stored source code
    std::list<BASE_TOKEN_TYPE<void>> tokens;

    for (const auto& [pattern, tokenType] : tokenPatterns) {
        std::regex re(pattern);
        std::smatch match;
        std::string::const_iterator searchStart(code.cbegin());

        while (std::regex_search(searchStart, code.cend(), match, re)) {
            // Create the token and store it
            tokens.push_back(*tokenType);
            searchStart = match.suffix().first;
        }
    }

    // Store tokens in the class
    this->tokens = tokens;
}

// Function to get the list of tokens
std::list<BASE_TOKEN_TYPE<void>> Tokenizer::GetTokensList() {
    return this->tokens;
}
