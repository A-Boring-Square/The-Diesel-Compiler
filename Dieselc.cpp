// Dieselc.cpp : Defines the entry point for the application.
//
#include "Compiler/Tokenizer.hpp"
#include <iostream>

int main() {
    // Sample source code to tokenize
    std::string sampleCode = R"(
        const int x = 42;
        var y = 3.14;
        output "Hello, World!";
        #[
        This is a comment block
        ]#
        def myFunction() {
            var result = x + y;
            output result;
        }
    )";

    // Create a Tokenizer object
    Tokenizer tokenizer(sampleCode, sampleCode.length());

    // Perform tokenization
    tokenizer.Tokenize();

    // Retrieve the list of tokens
    std::list<BASE_TOKEN_TYPE<void>> tokens = tokenizer.GetTokensList();

    // Print out the tokens
    for (const auto& token : tokens) {
        token.PrintInfo();
        std::cout << "----------------------" << std::endl;
    }

    return 0;
}
