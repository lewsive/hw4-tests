#include <stdio.h>
#include <string.h>
#include "literal_table.h"

// Initialize the literal table
void initLiteralTable(LiteralTable *table) {
    table->size = 0;
    table->next_address = 0x1000;  // Starting memory address for literals
}

// Function to add a literal to the table
int addLiteral(LiteralTable *table, void *value, LiteralType type) {
    // Check if the literal already exists in the table (to avoid duplicates)
    for (int i = 0; i < table->size; ++i) {
        // Check if the value and type match
        if (table->entries[i].value == value && table->entries[i].type == type) {
            return table->entries[i].address;  // Return the existing address if found
        }
    }

    // Add new entry if there is space in the table
    if (table->size < 100) {
        table->entries[table->size].value = value;
        table->entries[table->size].type = type;
        table->entries[table->size].address = table->next_address;
        table->next_address += 4;  // Assume each literal occupies 4 bytes (adjust as needed)
        table->size++;
        return table->entries[table->size - 1].address;
    }

    return -1;  // Return -1 if the table is full
}

// Function to print the contents of the literal table
void printLiteralTable(LiteralTable *table) {
    printf("Literal Table:\n");
    for (int i = 0; i < table->size; ++i) {
        printf("Literal: ");
        switch (table->entries[i].type) {
            case INT:
                printf("Int: %d", *(int *)table->entries[i].value);
                break;
            case FLOAT:
                printf("Float: %.2f", *(float *)table->entries[i].value);
                break;
            case STRING:
                printf("String: %s", (char *)table->entries[i].value);
                break;
        }
        printf(" Address: 0x%x\n", table->entries[i].address);
    }
}
