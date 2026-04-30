#include <stdio.h>

#define NOB_IMPLEMENTATION
#include "includes/nob.h"

#include <stdint.h>
typedef int32_t i32;

#define CC "gcc"
#define SRC_PATH "engine.c"
#define COMMON_LIBS "-Iincludes", "-Llib", "-l:libraylib.a"

#if defined(_WIN32)
#   define OUT_PATH "engine.exe"
#   define SYS_LIBS "-lgdi32", "-lwinmm"
#else
#   define OUT_PATH "engine.out"
#   define SYS_LIBS "-lm", "-ldl"
#endif // defined(_WIN32)

i32 main(i32 argc, char** argv) {
    GO_REBUILD_URSELF(argc, argv);
    
    Cmd cmd = {0};

    cmd_append(&cmd, CC);
    cmd_append(&cmd, "-shared", "-o", "mandelbrot.dll", "./scenes/mandelbrot.c");
    cmd_append(&cmd, COMMON_LIBS);
    cmd_append(&cmd, SYS_LIBS);
    cmd_run(&cmd);
    cmd.count = 0;

    cmd_append(&cmd, CC);
    cmd_append(&cmd, "-o", OUT_PATH, SRC_PATH);
    cmd_append(&cmd, COMMON_LIBS);
    cmd_append(&cmd, SYS_LIBS);
    cmd_run(&cmd);
    
    return 0;
}