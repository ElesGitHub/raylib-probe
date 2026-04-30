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

__declspec(dllexport) void load(SceneState *state) {
    state->target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    state->shader = loadMandelbrotShader();
}


__declspec(dllexport) void update(SceneState *state) {
    if (IsKeyPressed(KEY_R)) {
        UnloadShader(state->shader);
        state->shader = loadMandelbrotShader();
    }
    
    Shader shaderMandelbrot = state->shader;
    RenderTexture2D target = state->target;

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

__declspec(dllexport) void unload(SceneState *state) {
    UnloadShader(state->shader);
}