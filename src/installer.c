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
    char ae_exe_dest[] = "C:\\Aether\\bin\\ae.exe";

    printf("[1/5] Initializing Master Ecosystem (%s)...\n", install_path);
    char cmd[512];
    sprintf(cmd, "mkdir %s >nul 2>&1", install_path); system(cmd);
    sprintf(cmd, "mkdir %s >nul 2>&1", bin_path); system(cmd);
    sprintf(cmd, "mkdir %s >nul 2>&1", lib_path); system(cmd);
    sprintf(cmd, "mkdir %s\\tools >nul 2>&1", install_path); system(cmd);
    
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
    char* token = getenv("AETHER_TOKEN");
    const char* libs[] = {"math_pro", "neural_core", "win_ui", "app_core", "file_io", "web_client", "utility", "sound"};
    for (int i = 0; i < 8; i++) {
        printf("      Auto-fetching %s.ae%s...\n", libs[i], token ? " (Auth)" : "");
        char dl_cmd[1024];
        if (token) {
            sprintf(dl_cmd, "powershell -Command \"$headers = @{ 'Authorization' = 'token %s' }; Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/Blank01442/Aether/main/Libraries/%s.ae' -Headers $headers -OutFile '%s\\%s.ae'\"", token, libs[i], lib_path, libs[i]);
        } else {
            sprintf(dl_cmd, "powershell -Command \"Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/Blank01442/Aether/main/Libraries/%s.ae' -OutFile '%s\\%s.ae'\"", libs[i], lib_path, libs[i]);
        }
        system(dl_cmd);
    }

    printf("[4/5] Provisioning AI Toolchain (NASM & GCC)...\n");
    char tool_check[] = "C:\\Aether\\tools\\w64devkit-1.23.0\\bin\\gcc.exe";
    FILE* check = fopen(tool_check, "r");
    if (check) {
        fclose(check);
        printf("\033[1;32m      Success: Neural toolchain already provisioned.\033[0m\n");
    } else {
        printf("      Toolchain missing. Downloading portable devkit (~37MB)...\n");
        printf("      This ensures Aether can compile logic to machine code natively.\n");
        // Try downloading from GitHub releases
        char dl_tools[] = "curl -L -o C:\\Aether\\tools\\devkit.zip https://github.com/skeeto/w64devkit/releases/download/v1.23.0/w64devkit-1.23.0.zip && powershell -Command \"Expand-Archive -Path 'C:\\Aether\\tools\\devkit.zip' -DestinationPath 'C:\\Aether\\tools' -Force; Remove-Item 'C:\\Aether\\tools\\devkit.zip'\"";
        system(dl_tools);
        // Check if toolchain was actually installed
        char check_cmd[256];
        sprintf(check_cmd, "if exist \"%s\" (echo success) else (echo failed)", tool_check);
        int check_result = system(check_cmd);
        if (check_result == 0) {
            printf("\033[1;32m      Success: Universal toolchain provisioned at C:\\Aether\\tools.\033[0m\n");
        } else {
            printf("\033[1;33m      Warning: Toolchain download failed.\033[0m\n");
            printf("      Aether will still work, but native compilation may be limited.\n");
            printf("      To install manually:\n");
            printf("      1. Visit: https://github.com/skeeto/w64devkit/releases\n");
            printf("      2. Download: w64devkit-1.23.0.zip\n");
            printf("      3. Extract to: C:\\Aether\\tools\n");
        }
    }

    printf("[5/5] Broadening System Path (User Environment)...\n");
    char path_cmd[2048];
    char tool_bin[] = "C:\\Aether\\tools\\w64devkit-1.23.0\\bin";
    // Consolidate both bin_path and tool_bin into the user PATH
    sprintf(path_cmd, "powershell -Command \"$p = [System.Environment]::GetEnvironmentVariable('PATH', 'User'); if ($p -notlike '*%s*') { $p += ';%s' }; if ($p -notlike '*%s*') { $p += ';%s' }; [System.Environment]::SetEnvironmentVariable('PATH', $p, 'User')\"", bin_path, bin_path, tool_bin, tool_bin);
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
