#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



// Function to create a new symbol table
SymbolTable* createSymbolTable(int size) {
    SymbolTable* newTable = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (!newTable) return 0;

    newTable->size = size;
    newTable->table = (Symbol**)malloc(sizeof(Symbol*) * size);
    if (!newTable->table) {
        free(newTable);
        return 0;
    }

    for (int i = 0; i < size; i++) {
        newTable->table[i] = 0;
    }

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
    if (!newSymbol) return;
    newSymbol->name = strdup(name);
    newSymbol->type = strdup(type);
    // Initialize other fields of Symbol

    if (table == NULL || table->table == NULL) {
        fprintf(stderr, "Symbol table or table array not initialized\n");
    }

    unsigned int hashval = hash(table, name);
    newSymbol->next = table->table[hashval];
    table->table[hashval] = newSymbol;
}
// Function to look up a name in the table
Symbol* lookupSymbol(SymbolTable* table, char* name) {
    printf("Looking up %s\n", name);
    unsigned int hashval = hash(table, name);
    #include <stddef.h> // Include the header file for NULL macro

    // Search the linked list at table->table[hashval]
    // Check if the entry at hashval is null

    
    if (table->table[hashval] == NULL) {
        printf("No symbol found at hash value %u\n", hashval);
        return NULL;
    } else {
            printf("Symbol found at hash value %u\n", hashval);
            for (Symbol* sym = table->table[hashval]; sym != 0; sym = sym->next) {
                printf("Symbol name: %s\n", sym->name);
                if (strcmp(name, sym->name) == 0) return sym;
            }
      }   
    
    return NULL;
}
// Function to free the symbol table
void freeSymbolTable(SymbolTable* table) {
  
    free(table);
}

// Function to print the symbol table
void printSymbolTable(SymbolTable* table) {
    printf("----- SYMBOL TABLE -----\n");
    for (int i = 0; i < table->size; i++) {
        Symbol* symbol = table->table[i];
        while (symbol != 0) {
            printf("Name: %s, Type: %s\n", symbol->name, symbol->type);
            symbol = symbol->next;
        }
    }
    printf("------------------------\n");
}
