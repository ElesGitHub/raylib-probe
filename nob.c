#include <stdio.h>

#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIXES
#include "nob.h"

#include <stdint.h>
typedef int32_t i32;

#if defined(__TINYC__)
#   define CC "tcc"
#elif defined(__GNUC__)
#   define CC "gcc"
#endif // __TINYC__

#ifdef _WIN32
#   define BIN_PATH "hello.exe"
#else
#   define BIN_PATH "hello.out"
#endif // _WIN32

i32 main(i32 argc, char** argv) {
    GO_REBUILD_URSELF(argc, argv);
    
    Cmd cmd = {0};

    cmd_append(&cmd, CC, "-o", BIN_PATH, "hello.c");
    cmd_run(&cmd);
    
    return 0;
}