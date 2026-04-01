#include <stdio.h>

#define NOB_IMPLEMENTATION
#include "includes/nob.h"

#include <stdint.h>
typedef int32_t i32;

i32 main(i32 argc, char** argv) {
    GO_REBUILD_URSELF(argc, argv);
    
    Cmd cmd = {0};

    cmd_append(&cmd, "gcc");
    cmd_append(&cmd, "-o", "hello.exe", "hello.c");
    cmd_append(&cmd, "-Iincludes");
    cmd_append(&cmd, "-Llib");
    cmd_append(&cmd, "-l:libraylib.a");
    cmd_append(&cmd, "-lgdi32", "-lwinmm");
    cmd_run(&cmd);
    
    return 0;
}