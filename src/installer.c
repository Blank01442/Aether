#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <shlobj.h>
#include <string.h>

void print_banner() {
    printf("\033[1;36m");
    printf("  ██   ▄███▄     ▄▄▄▄▀ ▄  █ ▄███▄   █▄▄▄▄ \n");
    printf("  █ █  █▀   ▀ ▀▀▀ █   █   █ █▀   ▀  █  ▄▀ \n");
    printf("  █▄▄█ ██▄▄       █   ██▀▀█ ██▄▄    █  █  \n");
    printf("  █  █ █▄   ▄▀   █    █   █ █▄   ▄▀ █  █  \n");
    printf("     █ ▀███▀    ▀        █  ▀███▀     █   \n");
    printf("    █                   ▀            ▀    \n");
    printf("   ▀                                      \n");
    printf("\033[0m");
    printf("\n        --- Aether Universal Setup Wizard ---\n\n");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    print_banner();

    char install_path[] = "C:\\Aether";
    char bin_path[] = "C:\\Aether\\bin";
    char ae_exe_dest[] = "C:\\Aether\\bin\\ae.exe";

    printf("[1/4] Creating Directory Structure (%s)...\n", install_path);
    char cmd[512];
    sprintf(cmd, "mkdir %s >nul 2>&1", install_path); system(cmd);
    sprintf(cmd, "mkdir %s >nul 2>&1", bin_path); system(cmd);

    printf("[2/4] Deploying Aether Compiler Core...\n");
    // Check local or bin/
    const char* src_file = "bin\\ae.exe";
    if (GetFileAttributes(src_file) == INVALID_FILE_ATTRIBUTES) {
        src_file = "ae.exe"; // Try current dir
    }

    if (CopyFile(src_file, ae_exe_dest, FALSE)) {
        printf("\033[1;32m      Success: Compiler deployed to %s\033[0m\n", ae_exe_dest);
    } else {
        printf("\033[1;31m      Error: could not find Aether Compiler (ae.exe).\033[0m\n");
        printf("      Please run this setup from the folder containing the Aether project.\n");
        system("pause");
        return 1;
    }

    printf("[3/4] Configuring System Environment (PATH)...\n");
    char path_cmd[1024];
    // Use setx to add to USER path (persistence)
    sprintf(path_cmd, "setx PATH \"%%PATH%%;%s\" >nul 2>&1", bin_path);
    if (system(path_cmd) == 0) {
        printf("\033[1;32m      Success: Aether added to PATH. (Restart terminal to apply)\033[0m\n");
    } else {
        printf("      Warning: Could not update PATH automatically. Please add %s manually.\n", bin_path);
    }

    printf("[4/4] Verifying Dependencies (GCC & NASM)...\n");
    int has_gcc = (system("gcc --version >nul 2>&1") == 0);
    int has_nasm = (system("nasm -v >nul 2>&1") == 0);

    if (has_gcc) printf("\033[1;32m      [OK] GCC Detected\033[0m\n");
    else printf("\033[1;33m      [!!] GCC Missing. Please install MinGW-w64.\033[0m\n");

    if (has_nasm) printf("\033[1;32m      [OK] NASM Detected\033[0m\n");
    else printf("\033[1;33m      [!!] NASM Missing. Aether needs it to compile to Assembly.\033[0m\n");

    printf("\n\033[1;36m--------------------------------------------------\033[0m\n");
    printf("   INSTALLATION COMPLETE!\n");
    printf("   Open a new terminal and type 'ae' to start.\n");
    printf("\033[1;36m--------------------------------------------------\033[0m\n\n");

    system("pause");
    return 0;
}
