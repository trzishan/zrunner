#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SRC_FILE   "src/zrunner.c"
#define BIN_NAME   "zrunner"
#define INSTALL_PATH "/usr/local/bin/zrunner"

void install() {
    if (access(SRC_FILE, F_OK) != 0) {
        printf("Source file '%s' not found.\n", SRC_FILE);
        exit(1);
    }

    printf("Compiling %s...\n", SRC_FILE);
    char compile_cmd[256];
    snprintf(compile_cmd, sizeof(compile_cmd), "gcc \"%s\" -o \"%s\"", SRC_FILE, BIN_NAME);
    if (system(compile_cmd) != 0) {
        printf("Compilation failed.\n");
        exit(1);
    }

    printf("Installing to %s...\n", INSTALL_PATH);
    char install_cmd[256];
    snprintf(install_cmd, sizeof(install_cmd), "sudo cp \"%s\" \"%s\"", BIN_NAME, INSTALL_PATH);
    if (system(install_cmd) == 0) {
        printf("Installed successfully. You can now run: %s <file.c>\n", BIN_NAME);
    } else {
        printf("Installation failed.\n");
        exit(1);
    }

    // Optionally clean up the local binary
    remove(BIN_NAME);
}

void uninstall() {
    printf("Uninstalling from %s...\n", INSTALL_PATH);
    char uninstall_cmd[256];
    snprintf(uninstall_cmd, sizeof(uninstall_cmd), "sudo rm -f \"%s\"", INSTALL_PATH);
    if (system(uninstall_cmd) == 0) {
        printf("Uninstalled successfully.\n");
    } else {
        printf("Uninstallation failed or already removed.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage:\n");
        printf("  %s -S    Install zrunner\n", argv[0]);
        printf("  %s -R    Uninstall zrunner\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-S") == 0) {
        install();
    } else if (strcmp(argv[1], "-R") == 0) {
        uninstall();
    } else {
        printf("Invalid option '%s'\n", argv[1]);
        return 1;
    }

    return 0;
}