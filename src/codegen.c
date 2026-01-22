#include "compiler.h"

int label_count = 0;
int string_label_count = 0;

typedef struct { char* label; char* value; } StringData;
StringData strings[2048];
int string_count = 0;

char* tasks[4096];
int task_count = 0;

int next_label() { return label_count++; }

char* add_string(char* val) {
    char* label = malloc(16); sprintf(label, "str_%d", string_label_count++);
    strings[string_count].label = label; strings[string_count].value = strdup(val);
    string_count++; return label;
}

void gen_expr(ASTNode* node, FILE* out) {
    if (!node) return;
    if (node->type == NODE_NUM) {
        fprintf(out, "    mov rax, %d\n", node->data.num_value);
        fprintf(out, "    cvtsi2sd xmm0, rax\n");
    } else if (node->type == NODE_BOOL) {
        fprintf(out, "    mov rax, %d\n", node->data.bool_value);
    } else if (node->type == NODE_FLOAT) {
        unsigned long long bits; memcpy(&bits, &node->data.float_value, 8);
        fprintf(out, "    mov rax, %llu\n    movq xmm0, rax\n", bits);
    } else if (node->type == NODE_STRING) {
        char* label = add_string(node->data.string_value); fprintf(out, "    lea rax, [rel %s]\n", label);
    } else if (node->type == NODE_VAR) {
        fprintf(out, "    mov rax, [rel %s]\n", node->data.var_name);
        if (node->result_type == TYPE_FLOAT) fprintf(out, "    movq xmm0, rax\n");
        else fprintf(out, "    cvtsi2sd xmm0, rax\n");
    } else if (node->type == NODE_ARRAY_ACCESS) {
        gen_expr(node->data.array_access.index, out);
        fprintf(out, "    mov rbx, [rel %s]\n", node->data.array_access.name);
        fprintf(out, "    mov rax, [rbx + rax*8]\n"); // assumes 64-bit array elements
    } else if (node->type == NODE_MATH_UNARY) {
        gen_expr(node->data.math_unary.expr, out);
        if (strcmp(node->data.math_unary.op, "sqrt") == 0) fprintf(out, "    sqrtsd xmm0, xmm0\n");
        else if (strcmp(node->data.math_unary.op, "exp") == 0) fprintf(out, "    call exp\n");
        fprintf(out, "    movq rax, xmm0\n");
    } else if (node->type == NODE_ALERT) {
        gen_expr(node->data.print_stmt.expr, out);
        char* caption = add_string("Aether Alert");
        fprintf(out, "    mov r9, 0\n"); // uType MB_OK
        fprintf(out, "    lea r8, [rel %s]\n", caption); // lpCaption
        fprintf(out, "    mov rdx, rax\n"); // lpText
        fprintf(out, "    xor rcx, rcx\n"); // hWnd NULL
        fprintf(out, "    call MessageBoxA\n");
    } else if (node->type == NODE_FILE_WRITE) {
        gen_expr(node->data.bin_op.right, out); // Path
        fprintf(out, "    mov rcx, rax\n    lea rdx, [rel %c_mode]\n", (strcmp(node->data.bin_op.op, "write") == 0) ? 'w' : 'a');
        fprintf(out, "    sub rsp, 32\n    call fopen\n    add rsp, 32\n    push rax\n"); // Save FILE*
        gen_expr(node->data.bin_op.left, out); // Data
        fprintf(out, "    mov r8, rax\n    pop rcx\n    push rcx\n"); // rcx = FILE*, r8 = Data
        fprintf(out, "    lea rdx, [rel file_fmt]\n");
        if (node->data.bin_op.left->result_type == TYPE_INT) fprintf(out, "    lea rdx, [rel num_fmt]\n");
        else if (node->data.bin_op.left->result_type == TYPE_FLOAT) fprintf(out, "    lea rdx, [rel flt_fmt]\n");
        fprintf(out, "    sub rsp, 32\n    call fprintf\n    add rsp, 32\n    pop rcx\n    sub rsp, 32\n    call fclose\n    add rsp, 32\n");
    } else if (node->type == NODE_SYSTEM) {
        gen_expr(node->data.print_stmt.expr, out);
        fprintf(out, "    mov rcx, rax\n    sub rsp, 32\n    call system\n    add rsp, 32\n");
    } else if (node->type == NODE_BEEP) {
        gen_expr(node->data.bin_op.right, out); // Duration
        fprintf(out, "    push rax\n");
        gen_expr(node->data.bin_op.left, out);  // Frequency
        fprintf(out, "    mov rcx, rax\n    pop rdx\n    sub rsp, 32\n    call Beep\n    add rsp, 32\n");
    } else if (node->type == NODE_EXIT) {
        fprintf(out, "    xor rcx, rcx\n    sub rsp, 32\n    call ExitProcess\n    add rsp, 32\n");
    } else if (node->type == NODE_SCREEN_INFO) {
        if (strcmp(node->data.var_name, "screen_width") == 0) fprintf(out, "    mov rcx, 0\n"); // SM_CXSCREEN
        else fprintf(out, "    mov rcx, 1\n"); // SM_CYSCREEN
        fprintf(out, "    sub rsp, 32\n    call GetSystemMetrics\n    add rsp, 32\n");
    } else if (node->type == NODE_RANDOM_EXPR) {
        gen_expr(node->data.random_expr.max_expr, out); fprintf(out, "    push rax\n"); 
        gen_expr(node->data.random_expr.min_expr, out); fprintf(out, "    push rax\n");
        fprintf(out, "    call rand\n    pop rbx\n    pop rcx\n    sub rcx, rbx\n    inc rcx\n    xor rdx, rdx\n    idiv rcx\n    mov rax, rdx\n    add rax, rbx\n");
    } else if (node->type == NODE_TIME_EXPR) { fprintf(out, "    call GetTickCount64\n"); }
    else if (node->type == NODE_BIN_OP) {
        gen_expr(node->data.bin_op.left, out);
        if (node->data.bin_op.left->result_type == TYPE_FLOAT || node->data.bin_op.right->result_type == TYPE_FLOAT || node->result_type == TYPE_FLOAT) {
            fprintf(out, "    sub rsp, 8\n    movq [rsp], xmm0\n");
            gen_expr(node->data.bin_op.right, out);
            fprintf(out, "    movq xmm1, xmm0\n");
            fprintf(out, "    movq xmm0, [rsp]\n");
            fprintf(out, "    add rsp, 8\n");
            if (strcmp(node->data.bin_op.op, "+") == 0) fprintf(out, "    addsd xmm0, xmm1\n");
            else if (strcmp(node->data.bin_op.op, "-") == 0) fprintf(out, "    subsd xmm0, xmm1\n");
            else if (strcmp(node->data.bin_op.op, "*") == 0) fprintf(out, "    mulsd xmm0, xmm1\n");
            else if (strcmp(node->data.bin_op.op, "/") == 0) fprintf(out, "    divsd xmm0, xmm1\n");
            fprintf(out, "    movq rax, xmm0\n");
        } else {
            fprintf(out, "    push rax\n");
            gen_expr(node->data.bin_op.right, out);
            fprintf(out, "    mov rbx, rax\n");
            fprintf(out, "    pop rax\n");
            if (strcmp(node->data.bin_op.op, "+") == 0) fprintf(out, "    add rax, rbx\n");
            else if (strcmp(node->data.bin_op.op, "-") == 0) fprintf(out, "    sub rax, rbx\n");
            else if (strcmp(node->data.bin_op.op, "*") == 0) fprintf(out, "    imul rax, rbx\n");
            else if (strcmp(node->data.bin_op.op, "/") == 0) { fprintf(out, "    xor rdx, rdx\n    idiv rbx\n"); }
            else if (strcmp(node->data.bin_op.op, "==") == 0) { fprintf(out, "    cmp rax, rbx\n    sete al\n    movzx rax, al\n"); }
            else if (strcmp(node->data.bin_op.op, "<") == 0) { fprintf(out, "    cmp rax, rbx\n    setl al\n    movzx rax, al\n"); }
            else if (strcmp(node->data.bin_op.op, ">") == 0) { fprintf(out, "    cmp rax, rbx\n    setg al\n    movzx rax, al\n"); }
        }
    }
}

void gen_statement(ASTNode* node, FILE* out);
void gen_block(ASTNode* node, FILE* out) { for (int i = 0; i < node->data.block.count; i++) gen_statement(node->data.block.statements[i], out); }

void gen_statement(ASTNode* node, FILE* out) {
    if (!node) return;
    if (node->type == NODE_VAR_DECL) {
        gen_expr(node->data.var_decl.expr, out); fprintf(out, "    mov [rel %s], rax\n", node->data.var_decl.name);
    } 
    else if (node->type == NODE_ARRAY_DECL) {
        gen_expr(node->data.array_decl.size, out);
        fprintf(out, "    shl rax, 3\n    mov rcx, rax\n    call malloc\n    mov [rel %s], rax\n", node->data.array_decl.name);
    }
    else if (node->type == NODE_ARRAY_SET) {
        gen_expr(node->data.array_set.index, out);
        fprintf(out, "    push rax\n");
        gen_expr(node->data.array_set.value, out);
        fprintf(out, "    pop rbx\n");
        fprintf(out, "    mov rcx, [rel %s]\n", node->data.array_set.name);
        fprintf(out, "    mov [rcx + rbx*8], rax\n");
    }
    else if (node->type == NODE_PRINT_STMT) {
        gen_expr(node->data.print_stmt.expr, out);
        if (node->data.print_stmt.expr->result_type == TYPE_STRING) { fprintf(out, "    lea rcx, [rel str_fmt]\n    mov rdx, rax\n"); }
        else if (node->data.print_stmt.expr->result_type == TYPE_FLOAT) { fprintf(out, "    lea rcx, [rel flt_fmt]\n    movq rdx, xmm0\n    movq xmm1, xmm0\n"); }
        else { fprintf(out, "    lea rcx, [rel num_fmt]\n    mov rdx, rax\n"); }
        fprintf(out, "    call printf\n");
    }
    else if (node->type == NODE_FOR_STMT) {
        int l_s = next_label(), l_e = next_label();
        gen_expr(node->data.for_stmt.start, out); fprintf(out, "    mov [rel %s], rax\n", node->data.for_stmt.var_name);
        fprintf(out, "label_%d:\n", l_s);
        gen_expr(node->data.for_stmt.end, out); fprintf(out, "    mov rbx, rax\n    mov rax, [rel %s]\n    cmp rax, rbx\n    jg label_%d\n", node->data.for_stmt.var_name, l_e);
        gen_statement(node->data.for_stmt.body, out);
        fprintf(out, "    mov rax, [rel %s]\n    inc rax\n    mov [rel %s], rax\n    jmp label_%d\nlabel_%d:\n", node->data.for_stmt.var_name, node->data.for_stmt.var_name, l_s, l_e);
    }
    else if (node->type == NODE_IF_STMT) {
        int l_else = next_label(), l_end = next_label();
        gen_expr(node->data.if_stmt.condition, out); fprintf(out, "    test rax, rax\n    jz label_%d\n", l_else);
        gen_statement(node->data.if_stmt.then_branch, out); fprintf(out, "    jmp label_%d\nlabel_%d:\n", l_end, l_else);
        if (node->data.if_stmt.else_branch) gen_statement(node->data.if_stmt.else_branch, out);
        fprintf(out, "label_%d:\n", l_end);
    }
    else if (node->type == NODE_TASK_DECL) {
        int already = 0;
        for (int i = 0; i < task_count; i++) {
            if (strcmp(tasks[i], node->data.task_decl.name) == 0) {
                already = 1;
                break;
            }
        }
        if (!already) {
            tasks[task_count++] = strdup(node->data.task_decl.name);
            int l_skip = next_label();
            fprintf(out, "    jmp label_%d\n", l_skip);
            fprintf(out, "task_%s:\n", node->data.task_decl.name);
            fprintf(out, "    push rbp\n    mov rbp, rsp\n    sub rsp, 32\n");
            gen_statement(node->data.task_decl.body, out);
            fprintf(out, "    add rsp, 32\n    pop rbp\n    ret\n");
            fprintf(out, "label_%d:\n", l_skip);
        }
    }
    else if (node->type == NODE_TASK_CALL) { fprintf(out, "    call task_%s\n", node->data.task_call.name); }
    else if (node->type == NODE_WHILE_STMT) {
        int l_start = next_label(), l_end = next_label();
        fprintf(out, "label_%d:\n", l_start);
        gen_expr(node->data.while_stmt.condition, out); fprintf(out, "    test rax, rax\n    jz label_%d\n", l_end);
        gen_statement(node->data.while_stmt.body, out); fprintf(out, "    jmp label_%d\nlabel_%d:\n", l_start, l_end);
    }
    else if (node->type == NODE_BLOCK) gen_block(node, out);
    else { gen_expr(node, out); }
}

char* vars[4096]; int var_count = 0;
void find_vars(ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_VAR_DECL || node->type == NODE_FOR_STMT || node->type == NODE_ARRAY_DECL || node->type == NODE_VAR) {
        char* name = (node->type == NODE_VAR_DECL) ? node->data.var_decl.name : (node->type == NODE_FOR_STMT) ? node->data.for_stmt.var_name : (node->type == NODE_ARRAY_DECL) ? node->data.array_decl.name : node->data.var_name;
        for (int i = 0; i < var_count; i++) if (strcmp(vars[i], name) == 0) return;
        vars[var_count++] = name;
    }
    if (node->type == NODE_BLOCK) for (int i = 0; i < node->data.block.count; i++) find_vars(node->data.block.statements[i]);
    else if (node->type == NODE_IF_STMT) { find_vars(node->data.if_stmt.then_branch); find_vars(node->data.if_stmt.else_branch); }
    else if (node->type == NODE_FOR_STMT) find_vars(node->data.for_stmt.body);
    else if (node->type == NODE_TASK_DECL) find_vars(node->data.task_decl.body);
    else if (node->type == NODE_WHILE_STMT) find_vars(node->data.while_stmt.body);
}

void generate_code(ASTNode** stmts, int stmt_count, FILE* out) {
    FILE* t_code = tmpfile(); for (int i = 0; i < stmt_count; i++) gen_statement(stmts[i], t_code);
    fprintf(out, "extern printf, scanf, rand, srand, time, GetTickCount64, malloc, exp, system, Beep\n");
    fprintf(out, "extern MessageBoxA, GetSystemMetrics, ExitProcess, fopen, fprintf, fclose\n");
    fprintf(out, "section .data\n    num_fmt db \"%%lld\", 10, 0\n    str_fmt db \"%%s\", 10, 0\n    flt_fmt db \"%%.4f\", 10, 0\n");
    fprintf(out, "    w_mode db \"w\", 0\n    a_mode db \"a\", 0\n    file_fmt db \"%%s\", 0\n");
    for (int i = 0; i < string_count; i++) {
        fprintf(out, "    %s db ", strings[i].label);
        for (int j = 0; strings[i].value[j] != '\0'; j++) {
            fprintf(out, "0x%02X, ", (unsigned char)strings[i].value[j]);
        }
        fprintf(out, "0\n");
    }
    var_count = 0; for (int i = 0; i < stmt_count; i++) find_vars(stmts[i]);
    for (int i = 0; i < var_count; i++) fprintf(out, "    %s dq 0\n", vars[i]);
    fprintf(out, "section .text\nglobal main\nmain:\n    push rbp\n    mov rbp, rsp\n    sub rsp, 48\n    xor rcx, rcx\n    call time\n    mov rcx, rax\n    call srand\n");
    rewind(t_code); char ch; while ((ch = fgetc(t_code)) != EOF) fputc(ch, out);
    fclose(t_code); fprintf(out, "    xor rax, rax\n    add rsp, 48\n    pop rbp\n    ret\n");
}
