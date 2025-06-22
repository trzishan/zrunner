#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <source_file.c/.cpp>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    if (access(filename, F_OK) != 0) {
        printf("File '%s' does not exist.\n", filename);
        return 1;
    }

    // Choose compiler
    const char *compiler = strstr(filename, ".cpp") ? "g++" : "gcc";

    // Generate a temporary output filename
    char tmpout[64];
    snprintf(tmpout, sizeof(tmpout), ".zrunner_tmp_%d", getpid());

    // Compile
    char compile_cmd[256];
    snprintf(compile_cmd, sizeof(compile_cmd), "%s \"%s\" -o \"%s\" -Wall", compiler, filename, tmpout);

    printf("Compiling with: %s\n", compile_cmd);
    int compile_status = system(compile_cmd);

    if (compile_status == 0) {
        printf("Compilation successful. Running the program:\n\n");
        char run_cmd[128];
        snprintf(run_cmd, sizeof(run_cmd), "./%s", tmpout);
        system(run_cmd);
    } else {
        printf("Compilation failed.\n");
        return 1;
    }

    // Delete the temporary binary
    remove(tmpout);

    return 0;
}
