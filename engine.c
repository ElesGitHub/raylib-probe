#include <stdio.h>

#include <raylib.h>
#include <dynlib.h>

#include <common.h>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

#define TITLE_FONT_SIZE 60

Shader loadMandelbrotShader() {
    Shader shaderMandelbrot = LoadShader(0, "./shaders/mandelbrot.fs");
    int locRes = GetShaderLocation(shaderMandelbrot, "res");
    int locMaxIter = GetShaderLocation(shaderMandelbrot, "maxIter");

    float res = (float) GetScreenWidth() / (float) GetScreenHeight();
    SetShaderValue(shaderMandelbrot, locRes, &res, SHADER_UNIFORM_FLOAT);

    int maxIter = 100;
    SetShaderValue(shaderMandelbrot, locMaxIter, &maxIter, SHADER_UNIFORM_INT);

    return shaderMandelbrot;
}

int main() {
    printf("Hello, World!\n");

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, World!");
    SetTargetFPS(120);

    DynLib scene = dynLibOpen("./plugins/mandelbrot.so");
    void (*load)(SceneState *) = (void(*)(SceneState*)) dynLibLoadFunction(scene, "load");
    void (*update)(SceneState *) = (void(*)(SceneState*)) dynLibLoadFunction(scene, "update");
    void (*unload)(SceneState *) = (void(*)(SceneState*)) dynLibLoadFunction(scene, "unload");

    SceneState state = {0};
    load(&state);

    while (!WindowShouldClose()) {
        update(&state);
    }

    unload(&state);
    CloseWindow();

    return 0;
}


    //BeginDrawing();

    //    ClearBackground(RED);

    //    // void DrawText(const char *text, int posX, int posY, int fontSize, Color color);
    //    DrawText(TextFormat("FPS: %i", GetFPS()), 0, 0, 20, BLACK);
    //    DrawText("Hello, Raylib!", 200, (SCREEN_HEIGHT / 2) - (TITLE_FONT_SIZE / 2), TITLE_FONT_SIZE, BLACK);

    //EndDrawing();
