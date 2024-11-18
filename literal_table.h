#ifndef LITERAL_TABLE_H
#define LITERAL_TABLE_H

// Define the literal types
typedef enum {
    INT,
    FLOAT,
    STRING
} LiteralType;

// Literal entry structure to store details about each literal
typedef struct {
    void *value;          // Pointer to the value (generic for int, float, etc.)
    LiteralType type;     // Type of the literal (INT, FLOAT, STRING)
    int address;          // Memory address or offset for this literal
} LiteralEntry;

// Literal table structure to manage a collection of literals
typedef struct {
    LiteralEntry entries[100];  // Array to store the literal entries (max 100 literals)
    int size;                   // Current number of entries in the table
    int next_address;           // Next available memory address for a literal
} LiteralTable;

// Function declarations

// Initialize the literal table
void initLiteralTable(LiteralTable *table);

// Add a literal to the table and return its memory address
int addLiteral(LiteralTable *table, void *value, LiteralType type);

// Print the contents of the literal table
void printLiteralTable(LiteralTable *table);

#endif // LITERAL_TABLE_H
