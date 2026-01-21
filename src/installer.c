#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <shlobj.h>
#include <string.h>

void print_banner() {
    printf("\033[1;36m");
    printf("  ██   ▄███▄     ▄▄▄▄▀ ▄  █ ▄███▄   █▄▄▄▄ \n");
    printf("  █ █  █▀   ▀ ▀▀▀ █   █   █ █▀   ▀  █  ▄▀ \n");
    printf("  █▄▄█ ██▄▄       █   ██▀▀█ ██▄▄    █▀▀▌ \n");
    printf("  █  █ █▄   ▄▀   █    █   █ █▄   ▄▀ █  █  \n");
    printf("     █ ▀███▀    ▀        █  ▀███▀     █   \n");
    printf("    █                   ▀            ▀    \n");
    printf("   ▀                                      \n");
    printf("\033[0m");
    printf("\n        --- Aether All-In-One Setup v1.0 ---\n\n");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    print_banner();

    char install_path[] = "C:\\Aether";
    char bin_path[] = "C:\\Aether\\bin";
    char lib_path[] = "C:\\Aether\\lib";
    char example_path[] = "C:\\Aether\\examples";
    char ae_exe_dest[] = "C:\\Aether\\bin\\ae.exe";

    printf("[1/5] Initializing Master Ecosystem (%s)...\n", install_path);
    char cmd[512];
    sprintf(cmd, "mkdir %s >nul 2>&1", install_path); system(cmd);
    sprintf(cmd, "mkdir %s >nul 2>&1", bin_path); system(cmd);
    sprintf(cmd, "mkdir %s >nul 2>&1", lib_path); system(cmd);
    sprintf(cmd, "mkdir %s >nul 2>&1", example_path); system(cmd);      

    printf("[2/5] Extracting Embedded Compiler Core...\n");
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(100), RT_RCDATA);
    if (hRes) {
        HGLOBAL hGlob = LoadResource(NULL, hRes);
        void* pData = LockResource(hGlob);
        DWORD size = SizeofResource(NULL, hRes);
        
        FILE* f = fopen(ae_exe_dest, "wb");
        if (f) {
            fwrite(pData, 1, size, f);
            fclose(f);
            printf("\033[1;32m      Success: Aether Master Binary deployed natively.\033[0m\n");
        } else {
            printf("\033[1;31m      Error: Permissions denied to C:\\Aether. Run as Administrator!\033[0m\n");
            system("pause"); return 1;
        }
    } else {
        printf("\033[1;31m      Error: Internal blob missing. Rebuilding installer...\033[0m\n");
        system("pause"); return 1;
    }

    printf("[3/5] Synchronizing Aether Global Libraries...\n");
    const char* libs[] = {"math_pro", "neural_core", "win_ui", "app_core"};
    for (int i = 0; i < 4; i++) {
        printf("      Auto-fetching %s.ae...\n", libs[i]);
        char dl_cmd[1024];
        sprintf(dl_cmd, "powershell -Command \"Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/Blank01442/Aether/main/Libraries/%s.ae' -OutFile '%s\\%s.ae'\"", libs[i], lib_path, libs[i]);
        system(dl_cmd);
    }

    printf("[4/5] Deploying Starter Suite...\n");
    char hello_ae[512];
    sprintf(hello_ae, "%s\\hello_aether.ae", example_path);
    FILE* f = fopen(hello_ae, "w");
    if (f) {
        fprintf(f, "import \"win_ui\"\n\nsay \"Hello Aether User!\"\nalert(\"Aether v1.0 Master Setup Success!\")\nsay \"Ecosystem is ready to code.\"\n");
        fclose(f);
    }
    printf("      Success: examples/hello_aether.ae created.\n");

    printf("[5/5] Broadening System Path (User Environment)...\n");
    char path_cmd[2048];
    // This PowerShell command checks if the bin path is already in the USER Path, and if not, appends it.
    sprintf(path_cmd, "powershell -Command \"$path = [System.Environment]::GetEnvironmentVariable('PATH', 'User'); if ($path -notlike '*%s*') { [System.Environment]::SetEnvironmentVariable('PATH', $path + ';%s', 'User') }\"", bin_path, bin_path);
    if (system(path_cmd) == 0) {
        printf("\033[1;32m      Success: 'ae' command is now registered globally.\033[0m\n");
    } else {
        printf("      Warning: Manual PATH update may be required for %s.\n", bin_path);
    }

    printf("\n\033[1;36m--------------------------------------------------\033[0m\n");
    printf("   AETHER MASTER SETUP COMPLETE!\n");
    printf("   Open a new terminal and type 'ae' to begin.\n");
    printf("\033[1;36m--------------------------------------------------\033[0m\n\n");

    system("pause");
    return 0;
}
