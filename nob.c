#include <stdio.h>

#define NOB_IMPLEMENTATION
#include "includes/nob.h"

#include <stdint.h>
typedef int32_t i32;

#define CC "gcc"

#if defined(_WIN32)
#   define OUT_PATH "hello.exe"
#   define SYS_LIBS "-lgdi32", "-lwinmm"
#else
#   define OUT_PATH "hello.out"
#   define SYS_LIBS "-lm"
#endif // defined(_WIN32)

i32 main(i32 argc, char** argv) {
    GO_REBUILD_URSELF(argc, argv);
    
    Cmd cmd = {0};

    cmd_append(&cmd, CC);
    cmd_append(&cmd, "-o", OUT_PATH, "hello.c");
    cmd_append(&cmd, "-Iincludes", "-Llib", "-l:libraylib.a");
    cmd_append(&cmd, SYS_LIBS);
    cmd_run(&cmd);
    
    return 0;
}