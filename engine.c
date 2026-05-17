#include <stdio.h>

#include <raylib.h>
#include <dynlib.h>

#define NOB_IMPLEMENTATION
#include <nob.h>

#include <common.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

#define TITLE_FONT_SIZE 60

typedef void (*SceneAction)(SceneState *state);

typedef struct {
    DynLib dll;
    const char *path;
    
    SceneAction load;
    SceneAction update;
    SceneAction unload;

    SceneState state;
} Scene;

// TODO Use walk_dir function from nob.h
const char *pluginPaths[2] = {
    "./plugins/hello_raylib.so",
    "./plugins/mandelbrot.so"
};

void loadScene(Scene *scene, const char *path) {
    if (scene->unload) scene->unload(&scene->state);
    scene->state = (SceneState){0};

    if (scene->dll) dynLibClose(scene->dll);

    scene->path = path;
    scene->dll  = dynLibOpen(path);

    scene->load   = (SceneAction) dynLibLoadFunction(scene->dll, "load");
    scene->update = (SceneAction) dynLibLoadFunction(scene->dll, "update");
    scene->unload = (SceneAction) dynLibLoadFunction(scene->dll, "unload");

    scene->load(&scene->state);
}

void recompileScene(Scene *scene) {
    String_View filename = sv_from_cstr(nob_temp_file_name(scene->path));
    String_View filename_trimmed = sv_chop_by_delim(&filename, '.');

    char *path_in = nob_temp_sprintf("./scenes/"SV_Fmt".c", SV_Arg(filename_trimmed));
    char *path_out = nob_temp_sprintf("./plugins/"SV_Fmt".so", SV_Arg(filename_trimmed));

    Cmd cmd = {0};
    cmd_append(&cmd, CC);
    cmd_append(&cmd, "-shared", "-fPIC", "-o", path_out, path_in);
    cmd_append(&cmd, COMMON_FLAGS);
    cmd_run(&cmd);

    loadScene(scene, scene->path);
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, World!");
    SetTargetFPS(120);

    Scene scene = {0};
    loadScene(&scene, pluginPaths[0]);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE)) {
            loadScene(&scene, pluginPaths[0]);
        } else if (IsKeyPressed(KEY_TWO)) {
            loadScene(&scene, pluginPaths[1]);
        } else if (IsKeyPressed(KEY_R)) {
            recompileScene(&scene);
        }
        scene.update(&scene.state);
    }

    scene.unload(&scene.state);
    CloseWindow();

    return 0;
}
