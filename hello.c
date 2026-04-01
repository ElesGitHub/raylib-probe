#include <stdio.h>

#include <raylib.h>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define TITLE_FONT_SIZE 60

int main() {
    printf("Hello, World!\n");

    InitWindow(800, 600, "Hello, World!");
    
    while (!WindowShouldClose()) {
    BeginDrawing();

        ClearBackground(RED);

        // void DrawText(const char *text, int posX, int posY, int fontSize, Color color);
        DrawText(TextFormat("FPS: %i", GetFPS()), 0, 0, 20, BLACK);
        DrawText("Hello, Raylib!", 200, (SCREEN_HEIGHT / 2) - (TITLE_FONT_SIZE / 2), TITLE_FONT_SIZE, BLACK);

    EndDrawing();
    }

    CloseWindow();

    return 0;
}