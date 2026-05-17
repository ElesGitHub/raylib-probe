#include <stdio.h>
#include <strings.h>

// Re-define rebuild command to include header files
//#ifndef NOB_REBUILD_URSELF
#  if defined(_WIN32)
#    if defined(__clang__)
#      if defined(__cplusplus)
#        define NOB_REBUILD_URSELF(binary_path, source_path) "clang", "-x", "c++", "-Iincludes", "-o", binary_path, source_path
#      else
#        define NOB_REBUILD_URSELF(binary_path, source_path) "clang", "-x", "c", "-Iincludes", "-o", binary_path, source_path
#      endif
#    elif defined(__GNUC__)
#      if defined(__cplusplus)
#        define NOB_REBUILD_URSELF(binary_path, source_path) "gcc", "-x", "c++", "-Iincludes", "-o", binary_path, source_path
#      else
#        define NOB_REBUILD_URSELF(binary_path, source_path) "gcc", "-x", "c", "-Iincludes", "-o", binary_path, source_path
#      endif
#    elif defined(_MSC_VER)
#       define NOB_REBUILD_URSELF(binary_path, source_path) "cl.exe", nob_temp_sprintf("/Fe:%s", (binary_path)), source_path
#    elif defined(__TINYC__)
#       define NOB_REBUILD_URSELF(binary_path, source_path) "tcc", "-Iincludes", "-o", binary_path, source_path
#    endif
#  else
#    if defined(__cplusplus)
#      define NOB_REBUILD_URSELF(binary_path, source_path) "cc", "-x", "c++", "-Iincludes", "-o", binary_path, source_path
#    else
#      define NOB_REBUILD_URSELF(binary_path, source_path) "cc", "-x", "c", "-Iincludes", "-o", binary_path, source_path
#    endif
#  endif
//#endif

#define NOB_IMPLEMENTATION
#include <nob.h>
#include <common.h>

bool compileScene(Walk_Entry entry) {
    printf("%*s%s\n", entry.level * 2, "", entry.path);
    if (entry.type != FILE_REGULAR) return true;
    
    String_View filename = sv_from_cstr(nob_temp_file_name(entry.path));
    String_View filename_trimmed = sv_chop_by_delim(&filename, '.');

    char *path_in = nob_temp_sprintf("./scenes/"SV_Fmt".c", SV_Arg(filename_trimmed));
    char *path_out = nob_temp_sprintf("./plugins/"SV_Fmt".so", SV_Arg(filename_trimmed));

    Cmd cmd = {0};
    cmd_append(&cmd, CC);
    cmd_append(&cmd, "-shared", "-fPIC", "-o", path_out, path_in);
    cmd_append(&cmd, COMMON_FLAGS);
    cmd_run(&cmd);

    return true;
}

int main(int argc, char** argv) {
    GO_REBUILD_URSELF(argc, argv);
    
    Cmd cmd = {0};

    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        cmd_append(&cmd, CC);
        cmd_append(&cmd, "-o", "test.out", "test.c");
        cmd_append(&cmd, COMMON_FLAGS);
        cmd_append(&cmd, SYS_LIBS);
        cmd_run(&cmd);
        return 0;
    }

    cmd_append(&cmd, CC);
    cmd_append(&cmd, "-o", OUT_PATH, SRC_PATH);
    cmd_append(&cmd, COMMON_FLAGS);
    cmd_append(&cmd, SYS_LIBS);
    cmd_run(&cmd);

    if (!mkdir_if_not_exists("plugins")) return 1;

    const char *dir_path = "./scenes";
    walk_dir(dir_path, compileScene);

    return 0;
}
