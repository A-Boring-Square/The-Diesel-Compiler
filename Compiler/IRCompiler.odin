package Compiler

import "Common"


// This file tokenizes, parses and then compiles the diesel source code into the equivalent IR

// Globally used objects

DSL_CodeString: [dynamic]rune // list of the actual diesel source code split into chars

DSL_FOUND_ENTRY_FUNCTION_MOD: bool = false // mainly used for error checking

DSL_AST: Common.AST_NODE


// Tokenizer
