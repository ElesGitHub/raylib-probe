#include <stdio.h>

#include <raylib.h>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define TITLE_FONT_SIZE 60

int main() {
    printf("Hello, World!\n");

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, World!");
    SetTargetFPS(120);

    Shader shaderMandelbrot = LoadShader(0, "./shaders/mandelbrot.fs");

    RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    
    while (!WindowShouldClose()) {
        BeginTextureMode(target);
            ClearBackground(BLACK);
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        EndTextureMode();
    
        BeginDrawing();
            ClearBackground(BLACK);
            
            BeginShaderMode(shaderMandelbrot);
                DrawTextureEx(target.texture, (Vector2){0.0f, 0.0f}, 0.0f, 1.0f, WHITE);
            EndShaderMode();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


    //BeginDrawing();

    //    ClearBackground(RED);

    //    // void DrawText(const char *text, int posX, int posY, int fontSize, Color color);
    //    DrawText(TextFormat("FPS: %i", GetFPS()), 0, 0, 20, BLACK);
    //    DrawText("Hello, Raylib!", 200, (SCREEN_HEIGHT / 2) - (TITLE_FONT_SIZE / 2), TITLE_FONT_SIZE, BLACK);

    //EndDrawing();