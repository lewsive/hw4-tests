#include "gen_code.h"
#include "AST.h"
#include "lexer.h"

// Function to generate code for a literal expression (constant)
code_seq genLiteralExpression(int literal) {
    code_seq seq;
    initcode_seq(&seq);

    // Generate code to load literal value into a register
    addInstruction(&seq, LWR, literal, 0, 0); // LOAD literal into a register
    return seq;
}

// Function to generate code for an identifier (variable or constant)
code_seq genIdentifierExpression(id_use *id) {
    code_seq seq;
    initcode_seq(&seq);

    // Check the type of the identifier and generate code accordingly
    if (id->attrs->type == INT) {
        addInstruction(&seq, LOAD, id->attrs->address, 0, 0); // LOAD integer into register
    }
    // Add more types if necessary (e.g., float, string)
    return seq;
}

// Function to generate code for binary operations (e.g., +, -, *, /)
code_seq genBinaryOperation(InstructionType op, id_use *left, id_use *right) {
    code_seq seq;
    initcode_seq(&seq);

    // Load the left operand into a register
    addInstruction(&seq, LOAD, left->attrs->address, 0, 0);

    // Load the right operand into a register
    addInstruction(&seq, LOAD, right->attrs->address, 0, 0);

    // Perform the binary operation (e.g., ADD, SUB)
    switch (op) {
        case ADD:
            addInstruction(&seq, ADD, left->attrs->address, right->attrs->address, 0);
            break;
        case SUB:
            addInstruction(&seq, SUB, left->attrs->address, right->attrs->address, 0);
            break;
        case MUL:
            addInstruction(&seq, MUL, left->attrs->address, right->attrs->address, 0);
            break;
        case DIV:
            addInstruction(&seq, DIV, left->attrs->address, right->attrs->address, 0);
            break;
        default:
            // Handle other operations if necessary
            break;
    }
    return seq;
}

// Function to generate code for assignment (e.g., a = b)
code_seq genAssignment(id_use *left, id_use *right) {
    code_seq seq;
    initcode_seq(&seq);

    // Load the value of the right operand into a register
    addInstruction(&seq, LOAD, right->attrs->address, 0, 0);

    // Store the value into the left operand (variable)
    addInstruction(&seq, STORE, left->attrs->address, 0, 0);

    return seq;
}

// Function to generate code for a function call
code_seq genFunctionCall(id_use *func) {
    code_seq seq;
    initcode_seq(&seq);

    // Prepare arguments for the function call (if any)
    // This could involve loading arguments into registers
    // For example: addInstruction(&seq, LOAD, arg_address, 0, 0);

    // Call the function
    addInstruction(&seq, CALL, func->attrs->address, 0, 0); // Call the function at func->address

    return seq;
}
