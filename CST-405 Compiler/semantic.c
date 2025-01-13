#include "semantic.h"
#include <stdio.h>

// Perform semantic analysis on the AST
TAC* tacHead = NULL;

void semanticAnalysis(ASTNode* node, SymbolTable* symTab) {
    // Perform semantic analysis on the AST
    // This function should traverse the AST and perform necessary checks
    if (node == NULL) return;


       // ... other code ...

    if (node->type == NodeType_Expr || node->type == NodeType_SimpleExpr) {
        // Generate TAC for expressions
    }

    // ... other code ...

}

// You can add more functions related to semantic analysis here
// Implement functions to generate TAC expressions



TAC* generateTACForExpr(ASTNode* expr) {
    // Depending on your AST structure, generate the appropriate TAC
    // If the TAC is generated successfully, append it to the global TAC list
    // Return the generated TAC, so that it can be used by the caller, e.g. for printing
    if (!expr) return NULL;

    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    // Generate TAC based on the expression type
    // Use switch statement or other logic to handle different expression types



    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
// Function to create a new temporary variable for TAC
char* createTempVar() {
    
}

char* createOperand(ASTNode* node) {
    // Depending on your AST structure, return the appropriate string
    // representation of the operand. For example, if the operand is a simple
    // expression or an identifier, return its string representation.
    // This function needs to be implemented based on your AST structure.
    if (!node) return NULL;

}

void printTAC(TAC* tac) {
    if (!tac) return;

}

// Print the TAC list to a file
// This function is provided for reference, you can modify it as needed

void printTACToFile(const char* filename, TAC* tac) {
    FILE* file = fopen(filename , "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }   
    
    fclose(file);
    printf("TAC written to %s\n", filename);
}


// Temporary variable allocation and deallocation functions //

void initializeTempVars() {
    // Initialize the tempVars array to keep track of allocated temp vars
    
}

int allocateNextAvailableTempVar(int tempVars[]) {
   // implement the temp var allocation logic
   // use the tempVars array to keep track of allocated temp vars

    // search for the next available temp var
    
    return -1; // No available temp var
}

void deallocateTempVar(int tempVars[], int index) {
    // implement the temp var deallocation logic
    // use the tempVars array to keep track of allocated temp vars
    
}   

void appendTAC(TAC** head, TAC* newInstruction) {
  // Append a new TAC instruction to the end of the list
}
