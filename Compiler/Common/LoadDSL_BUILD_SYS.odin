package Common

import "core:dynlib"
import "core:fmt"

BuildSystem :: struct {
    // Add all exported symbols later

    _handle: dynlib.Library,
}

load_build_system :: proc(bs: ^BuildSystem) {
    LIB_PATH :: "DSL_BUILD_SYS." + dynlib.LIBRARY_FILE_EXTENSION

    count, ok := dynlib.initialize_symbols(bs, LIB_PATH, "", "_handle")
    if !ok {
        panic("Failed to load symbols from:" + LIB_PATH)
    }
}
