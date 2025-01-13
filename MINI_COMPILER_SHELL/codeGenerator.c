// codeGenerator.c

#include "codeGenerator.h"
#include <stdio.h>
#include <stdlib.h>

static FILE* outputFile;

typedef struct {
    char* name; // Name of the register, e.g., "$t0"
    bool inUse; // Whether the register is currently in use
} MIPSRegister;

// Array of temporary registers, used for register allocation
// and tracking which registers are currently in use

MIPSRegister tempRegisters[NUM_TEMP_REGISTERS] = {
    {"$t0", false}, {"$t1", false}, {"$t2", false}, {"$t3", false},
    {"$t4", false}, {"$t5", false}, {"$t6", false}, {"$t7", false},
    {"$t8", false}, {"$t9", false}
};

void initCodeGenerator(const char* outputFilename) {
    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }
    // Write the data section header
    fprintf(outputFile, ".data\n");
}

void generateMIPS(TAC* tacInstructions) {
    /*
    NOTE: This is a simple code generation function that generates MIPS assembly code
    from the provided TAC instructions. It assumes that the TAC is already optimized

    The generated code is written to the output file specified during initialization.
    The register allocation strategy used here is a simple linear scan of the temporary
    registers, without considering more advanced techniques such as liveness analysis.

    You can modify this function to implement more advanced register allocation
    and other optimizations as needed for your compiler.

    Not all generated MIPS uses the allocated registers, so you may need to modify
    the code to properly allocate registers for each operation.
    
    */
  

    printf("Generating MIPS code...\n");

    // Traverse the TAC instructions and generate MIPS code

    // Exit program
    fprintf(outputFile, "\tli $v0, 10\n\tsyscall\n");
}

void finalizeCodeGenerator(const char* outputFilename) {
    if (outputFile) {
        fclose(outputFile);
        printf("MIPS code generated and saved to file %s\n", outputFilename);
        outputFile = NULL;
    }
}


/*

Implementing register allocation in your MIPS code generation phase is a crucial step 
for optimizing the use of CPU resources. The goal is to map your temporary variables (from TAC) 
to a limited set of MIPS registers, ideally minimizing memory access by keeping 
frequently used values in registers.

MIPS architecture provides a set of general-purpose registers, 
$t0 to $t9 for temporary values, and $s0 to $s7 for saved values. 
For simplicity, let's focus on using the temporary registers.

Strategy for Register Allocation:
--------------------------------

A simple strategy for register allocation could involve:

Register Pool: Keep track of which registers are currently available.
Allocation and Deallocation: Allocate registers when needed for operations and 
                             deallocate them when they are no longer needed.
Spilling: If all registers are in use and another one is needed,
          "spill" a register's value to memory and reuse the register.

*/

// Allocate a register
// Returns the index of the allocated register
int allocateRegister() {
    // No available register, implement spilling if necessary
    return -1; // Indicate failure
}

// Deallocate a register
void deallocateRegister(int regIndex) {
}

void printCurrentTAC(TAC* tac) {
    // Print the current TAC instructions using the provided TAC struct
}
