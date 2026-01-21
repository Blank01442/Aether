#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <shlobj.h>
#include <string.h>

void print_banner() {
    printf("\033[1;36m");
    // Using raw bytes for the stylized logo to avoid encoding issues
    printf("  \xDB\xDB   \xDC\xDB\xDB\xDB\xDC     \xDC\xDC\xDC\xDC\xDF \xDC  \xDB \xDC\xDB\xDB\xDB\xDC   \xDB\xDC\xDC\xDC\xDC \n");
    printf("  \xDB \xDB  \xDB\xDF   \xDF \xDF\xDF\xDF \xDB   \xDB   \xDB \xDB\xDF   \xDF  \xDB  \xDC\xDF \n");
    printf("  \xDB\xDC\xDC\xDB \xDB\xDB\xDC\xDC       \xDB   \xDB\xDB\xDF\xDF\xDB \xDB\xDB\xDC\xDC    \xDB  \xDB  \n");
    printf("  \xDB  \xDB \xDB\xDC   \xDC\xDF   \xDB    \xDB   \xDB \xDB\xDC   \xDC\xDF \xDB  \xDB  \n");
    printf("     \xDB \xDF\xDB\xDB\xDB\xDF    \xDF        \xDB  \xDF\xDB\xDB\xDB\xDF     \xDB   \n");
    printf("    \xDB                   \xDF            \xDF    \n");
    printf("   \xDF                                      \n");
    printf("\033[0m");
    printf("\n        --- Aether Universal Setup Wizard v2.9.7 ---\n\n");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    print_banner();

    char install_path[] = "C:\\Aether";
    char bin_path[] = "C:\\Aether\\bin";
    char lib_path[] = "C:\\Aether\\lib";
    char example_path[] = "C:\\Aether\\examples";
    char ae_exe_dest[] = "C:\\Aether\\bin\\ae.exe";

    printf("[1/6] Initializing Ecosystem Directories...\n");
    char cmd[512];
    sprintf(cmd, "mkdir %s >nul 2>&1", install_path); system(cmd);
    sprintf(cmd, "mkdir %s >nul 2>&1", bin_path); system(cmd);
    sprintf(cmd, "mkdir %s >nul 2>&1", lib_path); system(cmd);
    sprintf(cmd, "mkdir %s >nul 2>&1", example_path); system(cmd);
    printf("      Success: bin, lib, examples ready.\n");

    printf("[2/6] Deploying Aether Compiler Core...\n");
    int deployed = 0;
    
    // Attempt local deployment first
    const char* local_src[] = {"bin\\ae.exe", "ae.exe"};
    for (int i = 0; i < 2; i++) {
        if (GetFileAttributes(local_src[i]) != INVALID_FILE_ATTRIBUTES) {
            if (CopyFile(local_src[i], ae_exe_dest, FALSE)) {
                printf("\033[1;32m      Success: Local compiler found and deployed to %s\033[0m\n", ae_exe_dest);
                deployed = 1;
                break;
            }
        }
    }

    if (!deployed) {
        printf("      Compiler not found locally. Connecting to Aether Cloud Registry...\n");
        char dl_cmd[1024];
        sprintf(dl_cmd, "powershell -Command \"Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/Blank01442/Aether/main/bin/ae.exe' -OutFile '%s'\"", ae_exe_dest);
        if (system(dl_cmd) == 0) {
            printf("\033[1;32m      Success: Compiler fetched and installed remotely!\033[0m\n");
        } else {
            printf("\033[1;31m      Error: Aether CLI could not be downloaded. Check internet connection.\033[0m\n");
            system("pause"); return 1;
        }
    }

    printf("[3/6] Synchronizing Standard Libraries...\n");
    const char* libs[] = {"math_pro", "neural_core", "win_ui", "app_core"};
    for (int i = 0; i < 4; i++) {
        printf("      Fetching %s.ae...\n", libs[i]);
        char dl_cmd[1024];
        sprintf(dl_cmd, "powershell -Command \"Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/Blank01442/Aether/main/Libraries/%s.ae' -OutFile '%s\\%s.ae'\"", libs[i], lib_path, libs[i]);
        system(dl_cmd);
    }

    printf("[4/6] Generating Sample Project...\n");
    char hello_ae[512];
    sprintf(hello_ae, "%s\\hello_aether.ae", example_path);
    FILE* f = fopen(hello_ae, "w");
    if (f) {
        fprintf(f, "import \"win_ui\"\n\nsay \"Hello Aether User!\"\nalert(\"Aether Installation Verified!\")\nsay \"You are ready to code.\"\n");
        fclose(f);
        printf("      Created: %s\n", hello_ae);
    }

    printf("[5/6] Broadening System Path (PATH persistence)...\n");
    char path_cmd[1024];
    sprintf(path_cmd, "setx PATH \"%%PATH%%;%s\" >nul 2>&1", bin_path);
    if (system(path_cmd) == 0) {
        printf("\033[1;32m      Success: 'ae' command is now global.\033[0m\n");
    } else {
        printf("      Warning: Manual PATH update required for %s.\n", bin_path);
    }

    printf("[6/6] Auditing Developer Toolchain...\n");
    int has_gcc = (system("gcc --version >nul 2>&1") == 0);
    int has_nasm = (system("nasm -v >nul 2>&1") == 0);
    if (has_gcc) printf("\033[1;32m      [OK] GCC Toolchain Found\033[0m\n");
    else printf("\033[1;33m      [!!] GCC Missing. Install MinGW-w64 for full compilation.\033[0m\n");
    if (has_nasm) printf("\033[1;32m      [OK] NASM Assembly Engine Found\033[0m\n");
    else printf("\033[1;33m      [!!] NASM Missing. Aether requires NASM for x86-64 builds.\033[0m\n");

    printf("\n\033[1;36m--------------------------------------------------\033[0m\n");
    printf("   AETHER ECOSYSTEM IS READY!\n");
    printf("   Restart your terminal and type 'ae' to begin.\n");
    printf("\033[1;36m--------------------------------------------------\033[0m\n\n");

    system("pause");
    return 0;
}
