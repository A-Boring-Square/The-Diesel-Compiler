package Compiler

import "core:mem"
import "core:strings"
import "core:unicode/utf8"
import "core:text/scanner"

import "Common"

DSL_CodeString: [dynamic]rune
DSL_TOKENS_LIST: [dynamic]Common.TOKEN
DSL_AST: Common.AST_NODE
current_token_index: int = 0

LoadCodeString :: proc(SourceCode: string, allocator := context.allocator) {
    Runes: []rune = utf8.string_to_runes(SourceCode, allocator)
    
    for Rune in Runes {
        append(&DSL_CodeString, Rune)
    }
}



Tokenize :: proc (allocator := context.allocator) {

}