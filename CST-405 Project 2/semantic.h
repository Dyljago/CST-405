#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "AST.h"         // Assuming this includes the definition of ASTNode
#include "symbolTable.h" // Assuming this includes the definition of SymbolTable

// Define a structure for TAC instructions

typedef struct TAC {
    char* op;   // Operator
    char* arg1; // Argument 1
    char* arg2; // Argument 2
    char* result; // Result
    struct TAC* next; // Next instruction
} TAC;

typedef struct {
    char* name; // Name of the register, e.g., "$t0"
    char* variableType; // What type the variable is e.g. word
} DataRegister;

int tempVars[20];
extern TAC* tacHead; // Global head of the TAC instructions list

int allocateNextAvailableTempVar(int tempVars[]);
int getNextAvailableTempVar(int tempVars[]);
void semanticAnalysis(ASTNode* node, SymbolTable* symTab);
TAC* generateTACForExpr(ASTNode* expr); //returns the TAC for the expression to print on console
TAC* generateTACForPrint(ASTNode* expr, ASTNode* varName); //returns the TAC for the expression to print on console
char* createTempVar();
char* createOperand(ASTNode* node);
int findAllocatedRegister(const char* variableName);
void printTAC(TAC* tac);
void initializeTempVars();
void deallocateTempVar(int tempVars[], int index);
int allocateNextAvailableTempVar(int tempVars[]);
void appendTAC(TAC** head, TAC* newInstruction);
void printTACToFile(const char* filename, TAC* tac);
void printFullTAC(TAC* tac);
// You can add more function declarations related to semantic analysis here

#endif // SEMANTIC_H
