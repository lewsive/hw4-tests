#include "gen_code.h"
#include "bof.h"
#include "ast.h"
#include "instruction.h"
#include "vm/assemble.h"

void gen_code_initialize() {
    // Initialize any needed state
}

void gen_code_program(BOFFILE bf, block_t prog) {
    // Generate code for declarations
    gen_code_declaration(bf, prog.const_decls);
    gen_code_declaration(bf, prog.var_decls);
    gen_code_declaration(bf, prog.proc_decls);
    
    // Generate code for statements
    gen_code_statements(bf, prog.stmts);
}

// Generate code for a single declaration
static void gen_code_declaration(BOFFILE bf, declaration_t dec) {
    // Handle variable declarations
    // Allocate space and initialize variables
    bof_write_declare(bf, dec.name, dec.type);
}

// Generate code for a single statement
static void gen_code_statement(BOFFILE bf, stmt_t stmt) {
    switch (stmt.stmt_kind) {
        case ASSIGN_STMT:
            gen_code_assignment(bf, stmt.data.assign_stmt);
            break;
        case IF_STMT:
            gen_code_if(bf, stmt.data.if_stmt);
            break;
        case WHILE_STMT:
            gen_code_while(bf, stmt.data.while_stmt);
            break;
        // Add other statement types as needed
    }
}

// Helper functions for specific statement types
static void gen_code_assignment(BOFFILE bf, assign_stmt_t stmt) {
    // Generate code for expression evaluation
    gen_code_expression(bf, stmt.expr);
    // Store result in variable
    bof_write_store(bf, stmt.name);
}

static void gen_code_if(BOFFILE bf, if_stmt_t stmt) {
    // Generate condition code
    gen_code_expression(bf, stmt.condition);
    
    // Generate branching logic
    int label_else = bof_new_label(bf);
    int label_end = bof_new_label(bf);
    
    bof_write_branch_zero(bf, label_else);
    gen_code_statement(bf, stmt.then_stmts);
    bof_write_branch(bf, label_end);
    
    bof_write_label(bf, label_else);
    if (stmt.else_stmts != NULL) {
        gen_code_statement(bf, stmt.else_stmts);
    }
    bof_write_label(bf, label_end);
}

static void gen_code_while(BOFFILE bf, while_stmt_t stmt) {
    int label_start = bof_new_label(bf);
    int label_end = bof_new_label(bf);
    
    bof_write_label(bf, label_start);
    gen_code_expression(bf, stmt.condition);
    bof_write_branch_zero(bf, label_end);
    
    gen_code_statement(bf, stmt.body);
    bof_write_branch(bf, label_start);
    
    bof_write_label(bf, label_end);
}

static void gen_code_expression(BOFFILE bf, expr_t expr) {
    // Generate code for expression evaluation
    // Handle different expression types (binary ops, literals, variables)
    switch (expr.expr_kind) {
        case BINARY_OP:
            gen_code_binary_op(bf, expr.data.binary);
            break;
        case ID_EXPR:
            bof_write_load(bf, expr.data.id);
            break;
        case NUM_EXPR:
            bof_write_int_const(bf, expr.data.num);
            break;
    }
}

static void gen_code_binary_op(BOFFILE bf, binary_op_expr_t op) {
    // Generate code for left and right operands
    gen_code_expression(bf, op.left);
    gen_code_expression(bf, op.right);
    
    // Generate appropriate operation code
    switch (op.operator) {
        case PLUS:
            bof_write_add(bf);
            break;
        case MINUS:
            bof_write_sub(bf);
            break;
        case TIMES:
            bof_write_mul(bf);
            break;
        case DIV:
            bof_write_div(bf);
            break;
        // Add other operators as needed
    }
}
