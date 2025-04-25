/*
Adding an optimization phase for Three-Address Code (TAC) before generating MIPS assembly 
is a crucial step to enhance the efficiency of your generated code. 
Optimizations can reduce the number of instructions, minimize memory access, 
and improve overall execution speed. Below, we'll outline a basic approach for 
implementing a TAC optimizer. This optimizer will focus on simple peephole optimizations,
which look at small sets of instructions (or "peepholes") to apply local optimizations.

Basic Optimizations:
-------------------
1. Constant Folding: Evaluate expressions involving constants at compile time instead of runtime.
2. Constant Propagation: Replace variables with known constant values.
3. Copy Propagation: Replace uses of a variable that has been assigned the value of another variable.
4. Dead Code Elimination: Remove instructions that compute values not used by subsequent instructions 
   or the program's output.
*/

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "semantic.h"
#include <stdbool.h>
#include <ctype.h>

extern DataRegister tempRegisterData[];
extern DataRegister dataHolding[];
extern DataRegister variablesInSystem[];

TAC* optimizeTAC(TAC** head);
bool isConstant(const char* str);
bool isVariable(const char* str);
void constantFolding(TAC** head);
void constantPropagation(TAC** head);
void copyFolding(TAC** head);
void deadCodeElimination(TAC** head);
void printOptimizedTAC(const char* filename, TAC* head);
void printCurrentOptimizedTAC(TAC* current);
char* searchInFile(const char *filename, const char *phrase);
extern int dataInSystem(const char* variableName);
extern int isNumber(const char *arg);
extern void appendTAC(TAC** head, TAC* newInstruction);
extern void printTAC(TAC* tac);
extern void printTACToFile(const char* filename, TAC* tac);
extern void printFullTAC(TAC* tac);
int registerCalculatedAtIndex(char* result);
int registerCalculatedTo(char* sum);
int areTACListsEqual(TAC* a, TAC* b);
void clearTempRegisters(TAC** head);
void fillWriteStatements(TAC** head);
int nextFreeCopySlot();
int inCopyRegister(char* result);
int inCopyName(char* result);
extern int isRegister(char* result);
int isCopyRegister(char* result);

#endif // OPTIMIZER_H