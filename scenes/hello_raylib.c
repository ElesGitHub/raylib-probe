#include <stdio.h>

#include <raylib.h>

#include <common.h>

void load(void *state) {}

void unload(void *state) {}

#define TITLE_FONT_SIZE 120

void update(void *state) {
    BeginDrawing();

        ClearBackground(BLACK);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RAYWHITE);

        // void DrawText(const char *text, int posX, int posY, int fontSize, Color color);
        DrawText(TextFormat("FPS: %i", GetFPS()), 0, 0, 20, BLACK);
        DrawText("Hello, Raylib!", 200, (GetScreenHeight() / 2) - (TITLE_FONT_SIZE / 2), TITLE_FONT_SIZE, BLACK);

    EndDrawing();
}
