#include <stdio.h>

#include <raylib.h>
#include <dynlib.h>

#include <common.h>

// TEMP
//#include "./scenes/mandelbrot.c"

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
    printf("Hello, World!\n");

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, World!");
    SetTargetFPS(120);

    while (!IsWindowReady()) printf("///////////////////////// WINDOW IS NOT READY /////////////////////////\n");

    DynLib scene = dynLibOpen("mandelbrot.dll");
    DynFunc load = dynLibLoadFunction(scene, "load");
    DynFunc update = dynLibLoadFunction(scene, "update");
    DynFunc unload = dynLibLoadFunction(scene, "unload");

    SceneState state = {0};
    load(&state);
    
    while (!WindowShouldClose()) {
        update(&state);
    }

    unload(&state);
    CloseWindow();

    return 0;
}

//  #define TITLE_FONT_SIZE 60

    //BeginDrawing();

    //    ClearBackground(RED);

    //    // void DrawText(const char *text, int posX, int posY, int fontSize, Color color);
    //    DrawText(TextFormat("FPS: %i", GetFPS()), 0, 0, 20, BLACK);
    //    DrawText("Hello, Raylib!", 200, (SCREEN_HEIGHT / 2) - (TITLE_FONT_SIZE / 2), TITLE_FONT_SIZE, BLACK);

    //EndDrawing();