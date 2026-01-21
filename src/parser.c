#include "compiler.h"

int current_pos = 0;
Token* current_tokens;
int token_count;

typedef struct { char* name; DataType type; } Symbol;
Symbol symbols[4096];
int symbol_count = 0;

void set_symbol_type(char* name, DataType type) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbols[i].name, name) == 0) { symbols[i].type = type; return; }
    }
    symbols[symbol_count].name = strdup(name);
    symbols[symbol_count].type = type;
    symbol_count++;
}

DataType get_symbol_type(char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbols[i].name, name) == 0) return symbols[i].type;
    }
    return TYPE_UNKNOWN;
}

ASTNode* expression();
ASTNode* statement();

ASTNode* create_node(NodeType type, int line) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = type; node->line = line; node->result_type = TYPE_UNKNOWN;
    memset(&node->data, 0, sizeof(node->data));
    return node;
}

Token peek() { return current_tokens[current_pos]; }
Token consume() { return current_tokens[current_pos++]; }

void error_at(Token t, const char* msg, const char* fix) {
    fprintf(stderr, "\n--- AETHER SMART DEBUGGER ---\n");
    fprintf(stderr, "ISSUE at Line %d, Col %d: %s\n", t.line, t.col, msg);
    fprintf(stderr, "FOUND: \"%s\"\n", t.value);
    if (fix) fprintf(stderr, "PRO-TIP: %s\n", fix);
    fprintf(stderr, "-----------------------------\n");
    exit(1);
}

void match(TokenType type, const char* fix) {
    if (peek().type == type) consume();
    else error_at(peek(), "The compiler expected a specific keyword here.", fix);
}

ASTNode* factor() {
    Token t = peek();
    if (t.type == TOKEN_NUMBER) {
        consume(); ASTNode* n = create_node(NODE_NUM, t.line); n->data.num_value = atoi(t.value); n->result_type = TYPE_INT; return n;
    } else if (t.type == TOKEN_FLOAT) {
        consume(); ASTNode* n = create_node(NODE_FLOAT, t.line); n->data.float_value = atof(t.value); n->result_type = TYPE_FLOAT; return n;
    } else if (t.type == TOKEN_TRUE || t.type == TOKEN_FALSE) {
        consume(); ASTNode* n = create_node(NODE_BOOL, t.line); n->data.bool_value = (t.type == TOKEN_TRUE); n->result_type = TYPE_BOOL; return n;
    } else if (t.type == TOKEN_STRING) {
        consume(); ASTNode* n = create_node(NODE_STRING, t.line); n->data.string_value = strdup(t.value); n->result_type = TYPE_STRING; return n;
    } else if (t.type == TOKEN_SQRT || t.type == TOKEN_EXP) {
        consume(); match(TOKEN_LPAREN, "Functions need brackets, like sqrt(16)");
        ASTNode* expr = expression(); match(TOKEN_RPAREN, "Close the bracket.");
        ASTNode* n = create_node(NODE_MATH_UNARY, t.line); n->data.math_unary.op = strdup(t.value); n->data.math_unary.expr = expr; n->result_type = TYPE_FLOAT; return n;
    } else if (t.type == TOKEN_ID) {
        consume();
        if (peek().type == TOKEN_LBRACKET) {
            consume(); ASTNode* idx = expression(); match(TOKEN_RBRACKET, "Close bracket ']'.");
            ASTNode* n = create_node(NODE_ARRAY_ACCESS, t.line); n->data.array_access.name = strdup(t.value); n->data.array_access.index = idx;
            n->result_type = TYPE_INT; // Assuming int arrays for now
            return n;
        }
        ASTNode* n = create_node(NODE_VAR, t.line); n->data.var_name = strdup(t.value); n->result_type = get_symbol_type(t.value); return n;
    } else if (t.type == TOKEN_LPAREN) {
        consume(); ASTNode* n = expression(); match(TOKEN_RPAREN, "Close your '(' with ')'."); return n;
    } else if (t.type == TOKEN_RANDOM) {
        consume(); match(TOKEN_LPAREN, "(");
        ASTNode* min_e = expression(); match(TOKEN_COMMA, ",");
        ASTNode* max_e = expression(); match(TOKEN_RPAREN, ")");
        ASTNode* n = create_node(NODE_RANDOM_EXPR, t.line); n->data.random_expr.min_expr = min_e; n->data.random_expr.max_expr = max_e; n->result_type = TYPE_INT; return n;
    } else if (t.type == TOKEN_TIME) {
        consume(); ASTNode* n = create_node(NODE_TIME_EXPR, t.line); n->result_type = TYPE_INT; return n;
    }
    return NULL;
}

ASTNode* term() {
    ASTNode* node = factor();
    while (peek().type == TOKEN_MUL || peek().type == TOKEN_DIV) {
        Token t = consume(); ASTNode* next = factor();
        ASTNode* n = create_node(NODE_BIN_OP, t.line); n->data.bin_op.left = node; n->data.bin_op.op = strdup(t.value); n->data.bin_op.right = next;
        n->result_type = (node->result_type == TYPE_FLOAT || next->result_type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        node = n;
    }
    return node;
}

ASTNode* expression() {
    ASTNode* node = term();
    if (!node) return NULL;
    while (peek().type == TOKEN_PLUS || peek().type == TOKEN_MINUS) {
        Token t = consume(); ASTNode* next = term();
        ASTNode* n = create_node(NODE_BIN_OP, t.line); n->data.bin_op.left = node; n->data.bin_op.op = strdup(t.value); n->data.bin_op.right = next;
        n->result_type = (node->result_type == TYPE_FLOAT || next->result_type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        node = n;
    }
    if (peek().type == TOKEN_IS || peek().type == TOKEN_EQ || peek().type == TOKEN_NEQ || peek().type == TOKEN_LT || peek().type == TOKEN_GT) {
        Token t = consume(); ASTNode* next = expression();
        ASTNode* n = create_node(NODE_BIN_OP, t.line); n->data.bin_op.left = node; n->data.bin_op.op = (t.type == TOKEN_IS) ? strdup("==") : strdup(t.value); n->data.bin_op.right = next;
        n->result_type = TYPE_BOOL; node = n;
    }
    return node;
}

ASTNode* statement() {
    Token t = peek();
    if (t.type == TOKEN_SET) {
        consume(); char* name = consume().value; match(TOKEN_TO, "Use 'to' like this: 'set x to 10'");
        ASTNode* expr = expression(); set_symbol_type(name, expr->result_type);
        ASTNode* n = create_node(NODE_VAR_DECL, t.line); n->data.var_decl.name = strdup(name); n->data.var_decl.expr = expr; return n;
    } 
    else if (t.type == TOKEN_SAY) {
        consume(); ASTNode* n = create_node(NODE_PRINT_STMT, t.line); n->data.print_stmt.expr = expression(); return n;
    }
    else if (t.type == TOKEN_IMPORT) {
        consume(); consume(); // skip import and string
        return NULL; 
    }
    else if (t.type == TOKEN_TASK) {
        consume(); char* name = consume().value; ASTNode* body = statement();
        ASTNode* n = create_node(NODE_TASK_DECL, t.line); n->data.task_decl.name = strdup(name); n->data.task_decl.body = body; return n;
    }
    else if (t.type == TOKEN_CALL) {
        consume(); char* name = consume().value; ASTNode* n = create_node(NODE_TASK_CALL, t.line); n->data.task_call.name = strdup(name); return n;
    }
    else if (t.type == TOKEN_FOR) {
        consume(); char* var = consume().value; match(TOKEN_FROM, "Use 'for [var] from [start] to [end]'");
        ASTNode* start = expression(); match(TOKEN_TO, "Need 'to' in for loop");
        ASTNode* end = expression(); ASTNode* body = statement();
        ASTNode* n = create_node(NODE_FOR_STMT, t.line); n->data.for_stmt.var_name = strdup(var); n->data.for_stmt.start = start; n->data.for_stmt.end = end; n->data.for_stmt.body = body;
        return n;
    }
    else if (t.type == TOKEN_IF) {
        consume(); ASTNode* cond = expression(); ASTNode* th = statement(); ASTNode* el = NULL;
        if (peek().type == TOKEN_ELSE) { consume(); el = statement(); }
        ASTNode* n = create_node(NODE_IF_STMT, t.line); n->data.if_stmt.condition = cond; n->data.if_stmt.then_branch = th; n->data.if_stmt.else_branch = el; return n;
    }
    else if (t.type == TOKEN_WHILE) {
        consume(); ASTNode* cond = expression(); ASTNode* body = statement();
        ASTNode* n = create_node(NODE_WHILE_STMT, t.line); n->data.while_stmt.condition = cond; n->data.while_stmt.body = body; return n;
    }
    else if (t.type == TOKEN_ARRAY) {
        consume(); char* name = consume().value; match(TOKEN_FROM, "use 'from size'");
        set_symbol_type(name, TYPE_ARRAY);
        ASTNode* n = create_node(NODE_ARRAY_DECL, t.line); n->data.array_decl.name = strdup(name); n->data.array_decl.size = expression(); return n;
    }
    else if (t.type == TOKEN_LBRACE) {
        consume(); ASTNode* n = create_node(NODE_BLOCK, t.line); n->data.block.statements = malloc(sizeof(ASTNode*) * 8192); int count = 0;
        while (peek().type != TOKEN_RBRACE && peek().type != TOKEN_EOF) n->data.block.statements[count++] = statement();
        match(TOKEN_RBRACE, "Close blocks with '}'."); n->data.block.count = count; return n;
    }
    
    if (t.type == TOKEN_ID) {
        char* name = consume().value;
        if (peek().type == TOKEN_LBRACKET) {
            consume(); ASTNode* idx = expression(); match(TOKEN_RBRACKET, "]");
            match(TOKEN_TO, "To set array value: 'id[idx] to val'.");
            ASTNode* val = expression();
            ASTNode* n = create_node(NODE_ARRAY_SET, t.line); n->data.array_set.name = strdup(name); n->data.array_set.index = idx; n->data.array_set.value = val; return n;
        }
        if (peek().type == TOKEN_TO) {
            consume(); ASTNode* expr = expression(); set_symbol_type(name, expr->result_type);
            ASTNode* n = create_node(NODE_VAR_DECL, t.line); n->data.var_decl.name = strdup(name); n->data.var_decl.expr = expr; return n;
        }
    }

    consume(); return NULL;
}

ASTNode** parse(Token* tokens, int count, int* stmt_count) {
    current_tokens = tokens; token_count = count; current_pos = 0;
    ASTNode** stmts = malloc(sizeof(ASTNode*) * 2048); int c = 0;
    while (peek().type != TOKEN_EOF) { ASTNode* s = statement(); if (s) stmts[c++] = s; }
    *stmt_count = c; return stmts;
}
