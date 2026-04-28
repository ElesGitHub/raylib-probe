#include <stdio.h>

#include <raylib.h>

#if defined(_WIN32)
// Including the windows.h header induces a lot of collisions with raylib symbols.
// For now, symbols needed by the program will be defined in a helper header file.
//#   include <windows.h>
#   include <windows/miniwin.h>
#   define LIBTYPE HINSTANCE
#   define OPENLIB(libname) LoadLibraryW(L ## libname)
#   define LIBFUNC(lib, fn) GetProcAddress((lib), (fn))
#   define CLOSELIB(lib) FreeLibrary((lib))
#else
#   include <dlfcn.h>
#   define LIBTYPE void*
#   define OPENLIB(libname) dlopen((libname), RTLD_LAZY)
#   define LIBFUNC(lib, fn) dlsym((lib), (fn))
#   define CLOSELIB(lib) dlclose((lib))
#endif // defined(_WIN32)

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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

    LIBTYPE dl = OPENLIB("test.dll");
    FARPROC myDynSum = LIBFUNC(dl, "myDynSum");
    printf("myDynSum(2, 8) -> %d\n", myDynSum(2, 8));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, World!");
    SetTargetFPS(120);

    Shader shaderMandelbrot = loadMandelbrotShader();

    RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {
            UnloadShader(shaderMandelbrot);
            shaderMandelbrot = loadMandelbrotShader();
        }

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

    UnloadShader(shaderMandelbrot);
    CloseWindow();

    return 0;
}


    //BeginDrawing();

    //    ClearBackground(RED);

    //    // void DrawText(const char *text, int posX, int posY, int fontSize, Color color);
    //    DrawText(TextFormat("FPS: %i", GetFPS()), 0, 0, 20, BLACK);
    //    DrawText("Hello, Raylib!", 200, (SCREEN_HEIGHT / 2) - (TITLE_FONT_SIZE / 2), TITLE_FONT_SIZE, BLACK);

    //EndDrawing();