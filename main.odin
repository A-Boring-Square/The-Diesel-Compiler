package main

import "core:fmt"
import "core:mem"
import "core:mem/virtual"
import "Compiler"
import "Compiler/Common"



when ODIN_ARCH == .wasm32 || ODIN_ARCH == .wasm64p32 {
    #panic("WASM not supported as a build target")
}


HELP_MENU :: "dieselc is the C transpiler for the Diesel programing language\n"


main :: proc() {
    
	when ODIN_DEBUG {
		track: virtual.Tracking_Allocator
		virtual.tracking_allocator_init(&track, context.allocator)
		context.allocator = virtual.tracking_allocator(&track)

		defer {
			if len(track.allocation_map) > 0 {
				fmt.eprintf("=== %v allocations not freed: ===\n", len(track.allocation_map))
				for _, entry in track.allocation_map {
					fmt.eprintf("- %v bytes @ %v\n", entry.size, entry.location)
				}
			}
			virtual.tracking_allocator_destroy(&track)
		}
	}
	fmt.println(HELP_MENU)
	Compiler.InitTokenizerCodeString("var bob: int8 = 6/2;")
	Compiler.Tokenize()
	token: Common.Token 
	for &token in Compiler.DSLTokensList {
		Common.PrintToken(&token)
	}
}