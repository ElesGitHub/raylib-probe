#include <raylib.h>

#include <common.h>

typedef struct {
    RenderTexture2D target;
    Shader shader;
    int locTime;
} SceneState;

void load(SceneState *state) {
    state->shader = LoadShader(0, "./shaders/rain.fs");
    state->target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    int locRes  = GetShaderLocation(state->shader, "res");
    Vector2 res = (Vector2){ (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(state->shader, locRes, &res, SHADER_UNIFORM_VEC2);

    state->locTime = GetShaderLocation(state->shader, "t");
}

void update(SceneState *state) {
    float time = (float) GetTime();
    SetShaderValue(state->shader, state->locTime, &time, SHADER_UNIFORM_FLOAT);

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
