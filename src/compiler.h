#ifndef AETHER_COMPILER_H
#define AETHER_COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token types for Aether v2.9 "Global Edition"
typedef enum {
    TOKEN_SET, TOKEN_TO, TOKEN_SAY, TOKEN_ASK,
    TOKEN_IF, TOKEN_IS, TOKEN_ELSE, TOKEN_WHILE,
    TOKEN_REPEAT, TOKEN_TIMES,
    TOKEN_FOR, TOKEN_FROM,
    TOKEN_TASK, TOKEN_CALL,
    TOKEN_IMPORT, // "import"
    TOKEN_TRUE, TOKEN_FALSE,
    TOKEN_RANDOM, TOKEN_TIME,
    TOKEN_SQRT, TOKEN_EXP,
    TOKEN_ARRAY,
    TOKEN_ID, TOKEN_NUMBER, TOKEN_FLOAT, TOKEN_STRING,
    TOKEN_ASSIGN, TOKEN_PLUS, TOKEN_MINUS, TOKEN_MUL, TOKEN_DIV,
    TOKEN_EQ, TOKEN_NEQ, TOKEN_LT, TOKEN_GT,
    TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_LBRACE, TOKEN_RBRACE, TOKEN_LBRACKET, TOKEN_RBRACKET,
    TOKEN_COMMA, TOKEN_SEMI, TOKEN_EOF, TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type; char* value; int line; int col;
} Token;

typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_STRING, TYPE_BOOL, TYPE_ARRAY, TYPE_UNKNOWN } DataType;

typedef enum {
    NODE_VAR_DECL, NODE_PRINT_STMT, NODE_IF_STMT, NODE_WHILE_STMT,
    NODE_REPEAT_STMT, NODE_FOR_STMT, NODE_BLOCK, NODE_BIN_OP, 
    NODE_NUM, NODE_FLOAT, NODE_VAR, NODE_BOOL,
    NODE_STRING, NODE_INPUT_STMT, NODE_RANDOM_EXPR, NODE_TIME_EXPR,
    NODE_ARRAY_DECL, NODE_ARRAY_ACCESS, NODE_ARRAY_SET,
    NODE_TASK_DECL, NODE_TASK_CALL, NODE_MATH_UNARY,
    NODE_ALERT, NODE_EXIT, NODE_SCREEN_INFO,
    NODE_SYSTEM, NODE_FILE_IO
} NodeType;

typedef struct ASTNode {
    NodeType type;
    int line;
    DataType result_type;
    union {
        struct { char* name; struct ASTNode* expr; } var_decl;
        struct { struct ASTNode* expr; } print_stmt;
        struct { char* var_name; } input_stmt;
        struct { struct ASTNode* condition; struct ASTNode* then_branch; struct ASTNode* else_branch; } if_stmt;
        struct { struct ASTNode* condition; struct ASTNode* body; } while_stmt;
        struct { struct ASTNode* count_expr; struct ASTNode* body; } repeat_stmt;
        struct { char* var_name; struct ASTNode* start; struct ASTNode* end; struct ASTNode* body; } for_stmt;
        struct { struct ASTNode** statements; int count; } block;
        struct { struct ASTNode* left; char* op; struct ASTNode* right; } bin_op;
        struct { struct ASTNode* min_expr; struct ASTNode* max_expr; } random_expr;
        struct { char* name; struct ASTNode* size; } array_decl;
        struct { char* name; struct ASTNode* index; } array_access;
        struct { char* name; struct ASTNode* index; struct ASTNode* value; } array_set;
        struct { char* name; struct ASTNode* body; } task_decl;
        struct { char* name; } task_call;
        struct { char* op; struct ASTNode* expr; } math_unary;
        int num_value;
        double float_value;
        char* var_name;
        char* string_value;
        int bool_value;
    } data;
} ASTNode;

Token* get_tokens(const char* source, int* count);
ASTNode** parse(Token* tokens, int count, int* stmt_count);
void generate_code(ASTNode** stmts, int stmt_count, FILE* output);

#endif
