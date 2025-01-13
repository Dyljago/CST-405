#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



// Function to create a new symbol table
SymbolTable* createSymbolTable(int size) {
    SymbolTable* newTable = (SymbolTable*)malloc(sizeof(SymbolTable));
    
    return newTable;
}

// Hash function to map a name to an index
unsigned int hash(SymbolTable* table, char* name) {
    unsigned int hashval = 0;
    for (; *name != '\0'; name++) hashval = *name + (hashval << 5) - hashval;
    return hashval % table->size;
}

// Function to add a symbol to the table
void addSymbol(SymbolTable* table, char* name, char* type) {
    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));
   //
}
// Function to look up a name in the table
Symbol* lookupSymbol(SymbolTable* table, char* name) {
    printf("Looking up %s\n", name);
  
    return NULL;
}
// Function to free the symbol table
void freeSymbolTable(SymbolTable* table) {
  
    free(table);
}

// Function to print the symbol table
void printSymbolTable(SymbolTable* table) {
    printf("----- SYMBOL TABLE -----\n");
    
    printf("------------------------\n");
}
