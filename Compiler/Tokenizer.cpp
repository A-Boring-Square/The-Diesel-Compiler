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
	
}
   
std::list<Tokens> Tokenizer::GetTokensList() {
    return this->tokens;
}
