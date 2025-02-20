package main

import "core:fmt"



when ODIN_ARCH == .wasm32 || ODIN_ARCH == .wasm64p32 {
    #panic("WASM not supported as a build target")
}



main :: proc() {

    
}