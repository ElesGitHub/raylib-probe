#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>

#include <raylib.h>

#define debugbp(message) fprintf(stderr, "[DEBUG] %s:%d: %s\n", __FILE__, __LINE__, message)

#define CC "gcc"
#define SRC_PATH "engine.c"
#define COMMON_FLAGS "-Iincludes", "-Llib", "-lraylib", "-Wl,-rpath,$ORIGIN/lib"

#if defined(_WIN32)
#   define OUT_PATH "engine.exe"
#   define SYS_LIBS "-lgdi32", "-lwinmm"
#else
#   define OUT_PATH "engine.out"
#   define SYS_LIBS "-lm", "-ldl"
#endif // defined(_WIN32)

typedef struct {
    Shader shader;
    RenderTexture2D target;
} SceneState;

#endif // COMMON_H_
