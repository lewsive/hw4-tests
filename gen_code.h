#ifndef GEN_CODE_H
#define GEN_CODE_H

#include "code.h"          // Functions for generating VM instructions
#include "code_seq.h"      // Code sequence type and manipulation functions
#include "scope_check.h"   // For accessing id_use during code generation
#include "id_use.h"        // For accessing identifier use information
#include "id_attrs.h"      // For accessing identifier attributes
#include "literal_table.h" // For handling literal values

// Function to generate code for a literal expression (constant)
code_seq genLiteralExpression(int literal);

// Function to generate code for an identifier (variable or constant)
code_seq genIdentifierExpression(id_use *id);

// Function to generate code for binary operations (e.g., +, -, *, /)
code_seq genBinaryOperation(instr_type op, id_use *left, id_use *right);

// Function to generate code for assignment (e.g., a = b)
code_seq genAssignment(id_use *left, id_use *right);

// Function to generate code for a function call
code_seq genFunctionCall(id_use *func);

// Additional functions for more complex AST node types would go here.

#endif // GEN_CODE_H
