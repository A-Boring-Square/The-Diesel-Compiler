package main

import "core:fmt"
import "core:mem"
import "core:mem/virtual"
import "Compiler"




when ODIN_ARCH == .wasm32 || ODIN_ARCH == .wasm64p32 {
    #panic("WASM not supported as a build target")
}


HELP_MENU :: "dieselc is the C transpiler for the Diesel programing language\n"


main :: proc() {
    
	when ODIN_DEBUG {
		track: mem.Tracking_Allocator
		mem.tracking_allocator_init(&track, context.allocator)
		context.allocator = mem.tracking_allocator(&track)

		defer {
			if len(track.allocation_map) > 0 {
				fmt.eprintf("=== %v allocations not freed: ===\n", len(track.allocation_map))
				for _, entry in track.allocation_map {
					fmt.eprintf("- %v bytes @ %v\n", entry.size, entry.location)
				}
			}
			mem.tracking_allocator_destroy(&track)
		}
	}

	
}