// codeGenerator.h

#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "AST.h" // Include your AST definition
#include "semantic.h" // Include your TAC definition
#include <stdbool.h>

#define NUM_TEMP_REGISTERS 10

extern DataRegister tempRegisterData[];
extern DataRegister dataHolding[];
extern DataRegister variablesInSystem[];
extern DataRegister copyRegisterData[];

// Initializes code generation, setting up any necessary structures
void initCodeGenerator(const char* outputFilename, int optimize);

// Generates MIPS assembly code from the provided TAC
void generateMIPS(TAC* tacInstructions);

// Finalizes code generation, closing files and cleaning up
void finalizeCodeGenerator(const char* outputFilename);

extern int findAllocatedRegister(const char* variableName);
extern int isVariableInSystem(const char* variableName);

int isNumber(const char *arg);
int isRegister(char* result);
int nextFunctionRegister();
int isFunction(char* result);

// Allocate a register
int allocateRegister();

// Deallocate a register
void deallocateRegister(int regIndex);

// Print the current TAC instruction
void printCurrentTAC(TAC* tac);
uint32_t* pack_words(const char *str, size_t *out_count);

#endif // CODE_GENERATOR_H
