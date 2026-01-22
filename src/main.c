#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

// Recursive token acquisition for imports
Token* acquire_tokens(const char* filename, int* total_count) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        char path[512];
        sprintf(path, "lib/%s", filename); f = fopen(path, "rb");
        if (!f) { sprintf(path, "C:\\Aether\\lib\\%s", filename); f = fopen(path, "rb"); }
    }
    if (!f && !strstr(filename, ".ae")) {
        char path[512];
        sprintf(path, "%s.ae", filename); f = fopen(path, "rb");
        if (!f) { sprintf(path, "lib/%s.ae", filename); f = fopen(path, "rb"); }
        if (!f) { sprintf(path, "C:\\Aether\\lib\\%s.ae", filename); f = fopen(path, "rb"); }
    }
    if (!f) {
        fprintf(stderr, "\033[1;31mError: Could not find file '%s'\033[0m\n", filename);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* src = malloc(size + 1);
    fread(src, 1, size, f);
    src[size] = '\0';
    fclose(f);

    int count = 0;
    Token* tokens = get_tokens(src, &count);
    Token* all_tokens = malloc(sizeof(Token) * 262144);
    int current_all = 0;

    for (int i = 0; i < count; i++) {
        if (tokens[i].type == TOKEN_IMPORT) {
            i++; 
            if (i < count && tokens[i].type == TOKEN_STRING) {
                int imported_count = 0;
                Token* imported = acquire_tokens(tokens[i].value, &imported_count);
                for (int j = 0; j < imported_count - 1; j++) {
                    all_tokens[current_all++] = imported[j];
                }
            } else {
                fprintf(stderr, "Error: 'import' must be followed by a string filename.\n");
                exit(1);
            }
        } else {
            all_tokens[current_all++] = tokens[i];
        }
    }
    *total_count = current_all;
    return all_tokens;
}

void install_library(const char* lib_name) {
    char* token = getenv("AETHER_TOKEN");
    printf("\033[1;36mConnecting to Aether Global Registry%s...\033[0m\n", token ? " (Authenticated)" : "");
    system("if not exist lib mkdir lib");
    char cmd[1024];
    if (token) {
        sprintf(cmd, "powershell -Command \"$headers = @{ 'Authorization' = 'token %s' }; Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/Blank01442/Aether/main/Libraries/%s.ae' -Headers $headers -OutFile 'lib/%s.ae'\"", token, lib_name, lib_name);
    } else {
        sprintf(cmd, "powershell -Command \"Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/Blank01442/Aether/main/Libraries/%s.ae' -OutFile 'lib/%s.ae'\"", lib_name, lib_name);
    }
    
    if (system(cmd) == 0) {
        printf("\033[1;32mSUCCESS: Library '%s' installed to lib/%s.ae\033[0m\n", lib_name, lib_name);
    } else {
        printf("\033[1;31mERROR: Could not find library '%s' in the registry. Check connection or AETHER_TOKEN.\033[0m\n", lib_name);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Aether v1.0 Universal Edition\nUsage: ae <file.ae> [-r] | ae install <lib>\n");
        return 1;
    }

    if (strcmp(argv[1], "install") == 0) {
        if (argc < 3) { printf("Error: provide a library name.\n"); return 1; }
        install_library(argv[2]);
        return 0;
    }

    printf("\033[1;34m");
    printf("  ██   ▄███▄     ▄▄▄▄▀ ▄  █ ▄███▄   █▄▄▄▄ \n");
    printf("  █ █  █▀   ▀ ▀▀▀ █   █   █ █▀   ▀  █  ▄▀ \n");
    printf("  █▄▄█ ██▄▄       █   ██▀▀█ ██▄▄    █▀▀▌ \n");
    printf("  █  █ █▄   ▄▀   █    █   █ █▄   ▄▀ █  █  \n");
    printf("     █ ▀███▀    ▀        █  ▀███▀     █   \n");
    printf("    █                   ▀            ▀    \n");
    printf("   ▀                                      \n");
    printf("\033[0m");
    printf("\033[1;30m        --- v1.0 Universal Edition (Imports + Registry) ---\033[0m\n\n");

    int run_after = 0;
    if (argc > 2 && strcmp(argv[2], "-r") == 0) run_after = 1;

    int total_tokens = 0;
    Token* tokens = acquire_tokens(argv[1], &total_tokens);

    int stmt_count = 0;
    ASTNode** stmts = parse(tokens, total_tokens, &stmt_count);

    char base_name[256];
    strcpy(base_name, argv[1]);
    char* dot = strrchr(base_name, '.');
    if (dot) *dot = '\0';

    printf("\033[1;32mCompiling %s...\033[0m\n", argv[1]);

    FILE* out = fopen("temp_output.asm", "w");
    generate_code(stmts, stmt_count, out);
    fclose(out);

    if (system("nasm -f win64 temp_output.asm -o temp_output.obj") != 0) {
        fprintf(stderr, "\033[1;31mError: NASM failed to assemble.\nPro-Tip: Ensure NASM is installed and added to your System PATH.\033[0m\n");
        exit(1);
    }

    char gcmd[512];
    sprintf(gcmd, "gcc temp_output.obj -o %s.exe -luser32", base_name);
    if (system(gcmd) != 0) {
        fprintf(stderr, "\033[1;31mError: GCC failed to link.\nPro-Tip: Ensure MinGW-w64 is installed and added to your System PATH.\033[0m\n");
        exit(1);
    }

    remove("temp_output.asm");
    remove("temp_output.obj");

    printf("\033[1;32mBuild Success: %s.exe\033[0m\n", base_name);

    if (run_after) {
        printf("\033[1;33mExecuting Program...\033[0m\n\n");
        char run_cmd[512];
        for (int i = 0; base_name[i]; i++) if (base_name[i] == '/') base_name[i] = '\\';
        sprintf(run_cmd, ".\\%s.exe", base_name);
        system(run_cmd);
    }
    return 0;
}
