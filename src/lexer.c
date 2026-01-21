#include "compiler.h"

Token* create_token(TokenType type, const char* value, int line, int col) {
    Token* t = malloc(sizeof(Token));
    t->type = type;
    t->value = strdup(value);
    t->line = line;
    t->col = col;
    return t;
}

Token* get_tokens(const char* source, int* count) {
    Token* tokens = malloc(sizeof(Token) * 65536);
    int c = 0, i = 0, line = 1, col = 1;

    while (source[i] != '\0') {
        if (source[i] == '\n') { line++; col = 1; i++; continue; }
        if (isspace(source[i])) { col++; i++; continue; }

        if (source[i] == '/' && source[i+1] == '/') {
            while (source[i] != '\n' && source[i] != '\0') i++;
            continue;
        }

        if (source[i] == '"') {
            int sc = col; i++; col++;
            char buf[2048] = {0}; int j = 0;
            while (source[i] != '"' && source[i] != '\0') { buf[j++] = source[i++]; col++; }
            if (source[i] == '"') { i++; col++; }
            tokens[c++] = *create_token(TOKEN_STRING, buf, line, sc);
            continue;
        }

        if (isdigit(source[i])) {
            int sc = col; char buf[64] = {0}; int j = 0, is_f = 0;
            while (isdigit(source[i]) || (source[i] == '.' && !is_f)) {
                if (source[i] == '.') is_f = 1;
                buf[j++] = source[i++]; col++;
            }
            tokens[c++] = *create_token(is_f ? TOKEN_FLOAT : TOKEN_NUMBER, buf, line, sc);
            continue;
        }

        if (isalpha(source[i])) {
            int sc = col; char buf[64] = {0}; int j = 0;
            while (isalnum(source[i]) || source[i] == '_') { buf[j++] = source[i++]; col++; }
            
            if (strcmp(buf, "set") == 0) tokens[c++] = *create_token(TOKEN_SET, buf, line, sc);
            else if (strcmp(buf, "to") == 0) tokens[c++] = *create_token(TOKEN_TO, buf, line, sc);
            else if (strcmp(buf, "say") == 0) tokens[c++] = *create_token(TOKEN_SAY, buf, line, sc);
            else if (strcmp(buf, "ask") == 0) tokens[c++] = *create_token(TOKEN_ASK, buf, line, sc);
            else if (strcmp(buf, "if") == 0) tokens[c++] = *create_token(TOKEN_IF, buf, line, sc);
            else if (strcmp(buf, "is") == 0) tokens[c++] = *create_token(TOKEN_IS, buf, line, sc);
            else if (strcmp(buf, "else") == 0) tokens[c++] = *create_token(TOKEN_ELSE, buf, line, sc);
            else if (strcmp(buf, "while") == 0) tokens[c++] = *create_token(TOKEN_WHILE, buf, line, sc);
            else if (strcmp(buf, "repeat") == 0) tokens[c++] = *create_token(TOKEN_REPEAT, buf, line, sc);
            else if (strcmp(buf, "times") == 0) tokens[c++] = *create_token(TOKEN_TIMES, buf, line, sc);
            else if (strcmp(buf, "for") == 0) tokens[c++] = *create_token(TOKEN_FOR, buf, line, sc);
            else if (strcmp(buf, "from") == 0) tokens[c++] = *create_token(TOKEN_FROM, buf, line, sc);
            else if (strcmp(buf, "task") == 0) tokens[c++] = *create_token(TOKEN_TASK, buf, line, sc);
            else if (strcmp(buf, "call") == 0) tokens[c++] = *create_token(TOKEN_CALL, buf, line, sc);
            else if (strcmp(buf, "import") == 0) tokens[c++] = *create_token(TOKEN_IMPORT, buf, line, sc);
            else if (strcmp(buf, "true") == 0) tokens[c++] = *create_token(TOKEN_TRUE, buf, line, sc);
            else if (strcmp(buf, "false") == 0) tokens[c++] = *create_token(TOKEN_FALSE, buf, line, sc);
            else if (strcmp(buf, "random") == 0) tokens[c++] = *create_token(TOKEN_RANDOM, buf, line, sc);
            else if (strcmp(buf, "time") == 0) tokens[c++] = *create_token(TOKEN_TIME, buf, line, sc);
            else if (strcmp(buf, "sqrt") == 0) tokens[c++] = *create_token(TOKEN_SQRT, buf, line, sc);
            else if (strcmp(buf, "exp") == 0) tokens[c++] = *create_token(TOKEN_EXP, buf, line, sc);
            else if (strcmp(buf, "array") == 0) tokens[c++] = *create_token(TOKEN_ARRAY, buf, line, sc);
            else tokens[c++] = *create_token(TOKEN_ID, buf, line, sc);
            continue;
        }

        int sc = col; col++;
        if (source[i] == '=' && source[i+1] == '=') { tokens[c++] = *create_token(TOKEN_EQ, "==", line, sc); i += 2; col++; continue; }
        if (source[i] == '!' && source[i+1] == '=') { tokens[c++] = *create_token(TOKEN_NEQ, "!=", line, sc); i += 2; col++; continue; }

        switch (source[i]) {
            case '=': tokens[c++] = *create_token(TOKEN_ASSIGN, "=", line, sc); break;
            case '+': tokens[c++] = *create_token(TOKEN_PLUS, "+", line, sc); break;
            case '-': tokens[c++] = *create_token(TOKEN_MINUS, "-", line, sc); break;
            case '*': tokens[c++] = *create_token(TOKEN_MUL, "*", line, sc); break;
            case '/': tokens[c++] = *create_token(TOKEN_DIV, "/", line, sc); break;
            case '<': tokens[c++] = *create_token(TOKEN_LT, "<", line, sc); break;
            case '>': tokens[c++] = *create_token(TOKEN_GT, ">", line, sc); break;
            case '(': tokens[c++] = *create_token(TOKEN_LPAREN, "(", line, sc); break;
            case ')': tokens[c++] = *create_token(TOKEN_RPAREN, ")", line, sc); break;
            case '{': tokens[c++] = *create_token(TOKEN_LBRACE, "{", line, sc); break;
            case '}': tokens[c++] = *create_token(TOKEN_RBRACE, "}", line, sc); break;
            case '[': tokens[c++] = *create_token(TOKEN_LBRACKET, "[", line, sc); break;
            case ']': tokens[c++] = *create_token(TOKEN_RBRACKET, "]", line, sc); break;
            case ',': tokens[c++] = *create_token(TOKEN_COMMA, ",", line, sc); break;
            case ';': tokens[c++] = *create_token(TOKEN_SEMI, ";", line, sc); break;
            default: break;
        }
        i++;
    }
    tokens[c++] = *create_token(TOKEN_EOF, "EOF", line, col);
    *count = c;
    return tokens;
}
