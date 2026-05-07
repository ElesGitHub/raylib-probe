#include <stdio.h>

#include <raylib.h>

#include <common.h>

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

void load(SceneState *state) {
    printf("Loading Mandelbrot set scene\n");

    state->shader = loadMandelbrotShader();
    state->target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
}

void update(SceneState *state) {
    if (IsKeyPressed(KEY_R)) {
        UnloadShader(state->shader);
        state->shader = loadMandelbrotShader();
    }

    BeginTextureMode(state->target);
        ClearBackground(BLACK);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    EndTextureMode();

    BeginDrawing();
        ClearBackground(BLACK);

        BeginShaderMode(state->shader);
            DrawTextureEx(state->target.texture, (Vector2){0.0f, 0.0f}, 0.0f, 1.0f, WHITE);
        EndShaderMode();
    EndDrawing();
}

void unload(SceneState *state) {
    UnloadShader(state->shader);
}
