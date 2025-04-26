// codeGenerator.c

#include "codeGenerator.h"
#include <stdio.h>
#include <stdlib.h>

static FILE* outputFile;

typedef struct {
    char* name; // Name of the register, e.g., "$t0"
    bool inUse; // Whether the register is currently in use
} MIPSRegister;

int optimized = 0;

int notMain;

// Array of temporary registers, used for register allocation
// and tracking which registers are currently in use

MIPSRegister tempRegisters[NUM_TEMP_REGISTERS] = {
    {"$t0", false}, {"$t1", false}, {"$t2", false}, {"$t3", false},
    {"$t4", false}, {"$t5", false}, {"$t6", false}, {"$t7", false},
    {"$t8", false}, {"$t9", false}
};
DataRegister functions[10] = {
    {"t0", ""}, {"t1", ""}, {"t2", ""}, {"t3", ""},
    {"t4", ""}, {"t5", ""}, {"t6", ""}, {"t7", ""},
    {"t8", ""}, {"t9", ""}
};

void initCodeGenerator(const char* outputFilename, int optimize) {
    optimized = optimize;
    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }
    // Write the data section header
    fprintf(outputFile, ".data\n");
    for (int i = 0; i < NUM_TEMP_REGISTERS; i++)
    {   
        if (optimized == 0) {
            if (copyRegisterData[i].variableType != "")
            {
                if (copyRegisterData[i].variableType == "asciiz") {
                    size_t len = strlen(variablesInSystem[i].variableType);
                    if (len >= 2 && variablesInSystem[i].variableType[0] == '"' && variablesInSystem[i].variableType[len - 1] == '"') {
                        // Already quoted, return a copy
                        char* result = strdup(variablesInSystem[i].variableType);
                        fprintf(outputFile, "%s: .%s %s\n", copyRegisterData[i].name, copyRegisterData[i].variableType, result);
                    } else {
                        // Allocate new string: 2 extra for quotes + 1 for null terminator
                        char* result = malloc(len + 3);

                        result[0] = '"';
                        strcpy(result + 1, variablesInSystem[i].variableType);
                        result[len + 1] = '"';
                        result[len + 2] = '\0';
                        fprintf(outputFile, "%s: .%s %s\n", copyRegisterData[i].name, copyRegisterData[i].variableType, result);
                    }
                } else {
                    fprintf(outputFile, "%s: .%s %s\n", copyRegisterData[i].name, copyRegisterData[i].variableType, variablesInSystem[i].variableType);
                }
            }
        } else {
            if (tempRegisterData[i].variableType != "")
            {
                fprintf(outputFile, "%s: .%s 0\n", tempRegisterData[i].name, tempRegisterData[i].variableType);
            }
        }
    }
    
}

int isNumber(const char *arg) {
    // printf("Checking if %s is a number\n", arg);
    if (arg == NULL || *arg == '\0') return 0; // Null or empty string is not a number

    char *endptr;
    strtod(arg, &endptr); // Try converting to a number

    return (*endptr == '\0'); // If endptr points to '\0', it's a valid number
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
  
    TAC* current = tacInstructions;
    fprintf(outputFile, ".text\n.globl main\n");

    int regIndex = allocateRegister(); // Allocate a register, e.g., $t0
    if (regIndex == -1) {
        // Handle register allocation failure
        return;
    }

    printf("Generating MIPS code...\n");
    while (current != NULL) {
        // printCurrentTAC(current);
        // printf("Current Instruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
        if(strcmp(current->op, "=") == 0){
            printf("Generating MIPS for Assignment operation\n");
            fprintf(outputFile, "\tli $t0, %s\n\tsw $t0, %s\n", current->arg1, current->result);
        }
        else if (strcmp(current->op, "+") == 0) {
            // Modify the command below, to properly allocate registers for the operands
            printf("Generating MIPS code for addition operation\n");
            if (notMain = 0) {
                char* reg1 = "";
                char* reg2 = "";
                if (current->arg1[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$%s", current->arg1);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg1 = strdup(result); 
                } else {
                    reg1 = current->arg1;
                }
                if (current->arg2[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$%s", current->arg2);
                    // printf("CHECKTHISRESUKT2: %s\n", result);
                    reg2 = strdup(result); 
                } else {
                    reg2 = current->arg2;
                }
                fprintf(outputFile, "\tlw %s, %s\n\tlw %s, %s\n\tadd $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, reg2, current->arg2, current->result, reg1, reg2, current->result, current->result);
            } else {
                // printf("Current Instruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
                char* reg1 = "";
                char* reg2 = "";
                if (current->result[0] == 't') {
                    // printf("HERE");
                    char result[10];
                    snprintf(result, sizeof(result), "$a%c", current->result[1]);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg1 = strdup(result); 
                } else {
                    reg1 = current->result;
                }
                if (current->arg1[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$a%c", current->arg1[1]);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg2 = strdup(result); 
                } else {
                    reg2 = current->arg1;
                }
                // printf("CHECKTHISRESUKT: %s\n", reg1);
                // printf("CHECKTHISRESUKT: %s\n", reg2);
                char* endptr;
                int imm = strtol(current->arg2, &endptr, 10);
                if (*endptr != '\0') {
                    fprintf(stderr, "ERROR: arg2 is not a valid number: %s\n", current->arg2);
                    exit(1);
                } 
                else {
                    // printf("CHECKTHISRESUKT: %d\n", imm);
                }
                // printf("CHECK\taddi %s, %s, %d\n", reg1, reg2, imm);
                fprintf(outputFile, "\taddi %s, %s, %d\n", reg1, reg2, imm);
                free(reg1);
                free(reg2); 
            }
        }
        else if (strcmp(current->op, "-") == 0) {
            // Modify the command below, to properly allocate registers for the operands
            printf("Generating MIPS code for subtraction operation\n");
            if (notMain = 0) {
                char* reg1 = "";
                char* reg2 = "";
                if (current->arg1[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$%s", current->arg1);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg1 = strdup(result); 
                } else {
                    reg1 = current->arg1;
                }
                if (current->arg2[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$%s", current->arg2);
                    // printf("CHECKTHISRESUKT2: %s\n", result);
                    reg2 = strdup(result); 
                } else {
                    reg2 = current->arg2;
                }
                fprintf(outputFile, "\tlw %s, %s\n\tlw %s, %s\n\tsub $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, reg2, current->arg2, current->result, reg1, reg2, current->result, current->result);
            } else {
                // printf("Current Instruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
                char* reg1 = "";
                char* reg2 = "";
                if (current->result[0] == 't') {
                    // printf("HERE");
                    char result[10];
                    snprintf(result, sizeof(result), "$a%c", current->result[1]);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg1 = strdup(result); 
                } else {
                    reg1 = current->result;
                }
                if (current->arg1[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$a%c", current->arg1[1]);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg2 = strdup(result); 
                } else {
                    reg2 = current->arg1;
                }
                // printf("CHECKTHISRESUKT: %s\n", reg1);
                // printf("CHECKTHISRESUKT: %s\n", reg2);
                char* endptr;
                int imm = strtol(current->arg2, &endptr, 10);
                if (*endptr != '\0') {
                    fprintf(stderr, "ERROR: arg2 is not a valid number: %s\n", current->arg2);
                    exit(1);
                } 
                else {
                    // printf("CHECKTHISRESUKT: %d\n", imm);
                }
                // printf("CHECK\taddi %s, %s, %d\n", reg1, reg2, imm);
                fprintf(outputFile, "\taddi $a0, $a0, -%d\n", imm);
                free(reg1);
                free(reg2); 
            }
        }
        else if (strcmp(current->op, "*") == 0) {
            // Modify the command below, to properly allocate registers for the operands
            printf("Generating MIPS code for multiplication operation\n");
            if (notMain = 0) {
                char* reg1 = "";
                char* reg2 = "";
                if (current->arg1[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$%s", current->arg1);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg1 = strdup(result); 
                } else {
                    reg1 = current->arg1;
                }
                if (current->arg2[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$%s", current->arg2);
                    // printf("CHECKTHISRESUKT2: %s\n", result);
                    reg2 = strdup(result); 
                } else {
                    reg2 = current->arg2;
                }
                fprintf(outputFile, "\tlw %s, %s\n\tlw %s, %s\n\tmul $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, reg2, current->arg2, current->result, reg1, reg2, current->result, current->result);
            } else {
                // printf("Current Instruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
                char* reg1 = "";
                char* reg2 = "";
                if (current->result[0] == 't') {
                    // printf("HERE");
                    char result[10];
                    snprintf(result, sizeof(result), "$a%c", current->result[1]);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg1 = strdup(result); 
                } else {
                    reg1 = current->result;
                }
                if (current->arg1[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$a%c", current->arg1[1]);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg2 = strdup(result); 
                } else {
                    reg2 = current->arg1;
                }
                // printf("CHECKTHISRESUKT: %s\n", reg1);
                // printf("CHECKTHISRESUKT: %s\n", reg2);
                char* endptr;
                int imm = strtol(current->arg2, &endptr, 10);
                if (*endptr != '\0') {
                    fprintf(stderr, "ERROR: arg2 is not a valid number: %s\n", current->arg2);
                    exit(1);
                } 
                else {
                    // printf("CHECKTHISRESUKT: %d\n", imm);
                }
                // printf("CHECK\taddi %s, %s, %d\n", reg1, reg2, imm);
                fprintf(outputFile, "\tmul $a0, $a0, %d\n", imm);
                free(reg1);
                free(reg2); 
            }
        } else if (strcmp(current->op, "/") == 0) {
            // Modify the command below, to properly allocate registers for the operands
            printf("Generating MIPS code for division operation\n");
            if (notMain = 0) {
                char* reg1 = "";
                char* reg2 = "";
                if (current->arg1[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$%s", current->arg1);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg1 = strdup(result); 
                } else {
                    reg1 = current->arg1;
                }
                if (current->arg2[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$%s", current->arg2);
                    // printf("CHECKTHISRESUKT2: %s\n", result);
                    reg2 = strdup(result); 
                } else {
                    reg2 = current->arg2;
                }
                fprintf(outputFile, "\tlw %s, %s\n\tlw %s, %s\n\tdiv $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, reg2, current->arg2, current->result, reg1, reg2, current->result, current->result);
            } else {
                // printf("Current Instruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
                char* reg1 = "";
                char* reg2 = "";
                if (current->result[0] == 't') {
                    // printf("HERE");
                    char result[10];
                    snprintf(result, sizeof(result), "$a%c", current->result[1]);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg1 = strdup(result); 
                } else {
                    reg1 = current->result;
                }
                if (current->arg1[0] == 't') {
                    char result[10];
                    snprintf(result, sizeof(result), "$a%c", current->arg1[1]);
                    // printf("CHECKTHISRESUKT: %s\n", result);
                    reg2 = strdup(result); 
                } else {
                    reg2 = current->arg1;
                }
                // printf("CHECKTHISRESUKT: %s\n", reg1);
                // printf("CHECKTHISRESUKT: %s\n", reg2);
                char* endptr;
                int imm = strtol(current->arg2, &endptr, 10);
                if (*endptr != '\0') {
                    fprintf(stderr, "ERROR: arg2 is not a valid number: %s\n", current->arg2);
                    exit(1);
                } 
                else {
                    // printf("CHECKTHISRESUKT: %d\n", imm);
                }
                // printf("CHECK\taddi %s, %s, %d\n", reg1, reg2, imm);
                fprintf(outputFile, "\tdiv $a0, $a0, %d\n", imm);
                free(reg1);
                free(reg2); 
            }
        }
        else if (current->result != NULL && isRegister(current->result) == -1) {
            if (isRegister(current->result) == -1) {
                // Modify the command below, to properly allocate registers for the operands
                printf("Generating MIPS code for function\n");
                if (strcmp(current->result, "main") != 0) {
                    notMain = 1;
                } else {
                    notMain = 0;
                }
                functions[nextFunctionRegister()].variableType = current->result;
                fprintf(outputFile, "%s:\n", current->result);
                // printf(current->arg2);
                // printf(regNum);
            }
        }
        else if (current->arg1 != NULL) {
            if (strcmp(current->arg1, "write") == 0) {
                // Modify the command below, to properly allocate registers for the operands
                printf("Generating MIPS code for print operation\n");
                if (isNumber(current->arg2) != 0) {
                    if (strchr(current->arg2, '.') != NULL) {
                        // printf("\n\n\nDECIMAL\n\n\n");
                        char* reg2 = current->arg2;
                        for (int i = 0; i < 10; i++)
                        {
                            if (strcmp(variablesInSystem[i].variableType, current->arg2) == 0) {
                                reg2 = strdup(variablesInSystem[i].name);
                            }
                        }
                        fprintf(outputFile, "\tli $v0, 2\n\tl.s $f12, %s\n\tsyscall\n", reg2);
                        fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\tl.s $f12, %s\n", reg2);
                    } else {
                        // printf("\n\n\INTEGER\n\n\n");
                        if (optimized == 0) {
                            fprintf(outputFile, "\tli $v0, 1\n\tli $a0, %s\n\tsyscall\n",current->arg2);
                            fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\tli $a0, %s\n", current->arg2);
                        } else {
                            int regNum = isVariableInSystem(current->arg2);
                            fprintf(outputFile, "\tlw $a0, t%d\n\tli $v0, 1\n\tsyscall\n", regNum);
                            fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\tlw $a0, t%d\n", regNum);
                        }
                    }
                    // printf("\nISNUMBER\n");
                } else if (isRegister(current->arg2) == -1) {
                    printf("\nISNOTNUMBER ISNOTREGISTER\n");
                    char* reg2 = current->arg2;
                    for (int i = 0; i < 10; i++)
                    {
                        if (strcmp(variablesInSystem[i].variableType, current->arg2) == 0) {
                            reg2 = strdup(variablesInSystem[i].name);
                        }
                    }
                    fprintf(outputFile, "\tli $v0, 4\n\tla $a0, %s\n\tsyscall\n", reg2);
                    fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\n");
                } else {
                    // printf("Current Instruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
                    int regNum = findAllocatedRegister(current->arg2);
                    if (regNum == -1) {
                        for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
                            if (strcmp(tempRegisterData[i].name, current->arg2) == 0) {
                                regNum = i;
                            }
                        }
                    }
                    if (notMain == 1) {
                        fprintf(outputFile, "\tmove $t%d, $a0\n", regNum);
                        fprintf(outputFile, "\tmove $a0, $t%d\n\tli $v0, 1\n\tsyscall\n", regNum);
                        fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\n");
                        fprintf(outputFile, "\tmove $a0, $t%d\n", regNum);
                    } else {
                        fprintf(outputFile, "\tmove $a0, $t%d\n\tli $v0, 1\n\tsyscall\n", regNum);
                        fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\n");
                    }
                }
                // printf(current->arg2);
                // printf(regNum);
            } else if (strcmp(current->arg1, "return") == 0) {
                // Modify the command below, to properly allocate registers for the operands
                printf("Generating MIPS code for return operation\n");
                if (isNumber(current->arg2) != 0) {
                    // printf("\nISNUMBER\n");
                    if (optimized == 0) {
                        fprintf(outputFile, "\tli $v0, 1\n\tli $a0, %s\n\tsyscall\n", current->arg2);
                        fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n");
                    } else {
                        int regNum = isVariableInSystem(current->arg2);
                        fprintf(outputFile, "\tlw $a0, t%d\n\tli $v0, 1\n\tsyscall\n", regNum);
                        fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n");
                    }
                } else {
                    char* reg1 = "";
                    if (current->arg2[0] == 't') {
                        char result[10];
                        snprintf(result, sizeof(result), "$a%c", current->arg2[1]);
                        // printf("CHECKTHISRESUKT: %s\n", result);
                        reg1 = strdup(result); 
                    } else {
                        reg1 = current->arg2;
                    }
                    fprintf(outputFile, "\tmove $v0, $a0\n\tjr $ra\n\n");
                }
                notMain = 0;
            } else {
                printf("Generating MIPS code for function call\n");
                if (isFunction(current->arg1) != -1) {
                    if (isNumber(current->arg2) != 0) {
                        fprintf(outputFile, "\tli $a0, %s\n\tjal %s\n\tmove $%s, $v0\n\n", current->arg2, current->arg1, current->result);
                    } else {
                        fprintf(outputFile, "\tmove $a0, $%s\n\tjal %s\n\tmove $%s, $v0\n\n", current->arg2, current->arg1, current->result);
                    }
                } else {
                    printf("Unknown function: %s\n", current->arg1);
                    exit(1);
                }
            }
        }
        else {
            printf("Unknown operation: %s\n", current->op);
            exit(1);
        }
        // Add more operations here (subtraction, multiplication, etc.)

        current = current->next;
    }
    // lw $a0, t2       # Load the value of t2 into $a0
    // li $v0, 1        # System call code for print_int
    // syscall          # Print the integer

    for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
        printf("\033[1;34m\tDataHolding-\t\t%s: %s\033[0m\n", dataHolding[i].name, dataHolding[i].variableType);
    }
    for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
        printf("\033[1;31m\tVariables In System->\t%s: %s\033[0m\n", variablesInSystem[i].name, variablesInSystem[i].variableType);
    }
    for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
        printf("\033[1;32m\tTemp Register->\t\t%s: %s\033[0m\n", tempRegisterData[i].name, tempRegisterData[i].variableType);
    }
    for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
        printf("\033[1;35m\tNew Temp Register->\t%s: %s\033[0m\n", copyRegisterData[i].name, copyRegisterData[i].variableType);
    }
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

// int findAllocatedRegister(const char* variableName) {
//     // printf("Finding allocated register for variable: %s\n", variableName);
//     for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
//         // printf("Searching");
//         if (strcmp(dataHolding[i].variableType, variableName) == 0) {
//             // printf("Found\n");
//             return i;
//         }
//     }
//     // printf("Not found\n");
//     return -1; // Register not found
// }


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
int isRegister(char* result) {
    for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
        if (strcmp(tempRegisterData[i].name, result) == 0) {
            return i;
        }
    }
    // printf("Register not found %s\n", result);
    return -1;
}

int nextFunctionRegister() {
    for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
        if (functions[i].variableType == "") {
            return i;
        }
    }
    return -1;
}

int isFunction(char* result) {
    for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
        if (strcmp(functions[i].variableType, result) == 0) {
            return i;
        }
    }
    return -1;
}

// Allocate a register
int allocateRegister() {
    for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
        if (!tempRegisters[i].inUse) {
            tempRegisters[i].inUse = true;
            return i; // Return the register index
        }
    }
    // No available register, implement spilling if necessary
    return -1; // Indicate failure
}

// Deallocate a register
void deallocateRegister(int regIndex) {
    if (regIndex >= 0 && regIndex < NUM_TEMP_REGISTERS) {
        tempRegisters[regIndex].inUse = false;
    }
}

void printCurrentTAC(TAC* tac) {
    TAC* current = tac;
    while (current != NULL) {
        printf("\n--- CURRENT TAC %s ---\n", current->op);
        if (strcmp(current->op,"=") == 0) {
            printf("%s = %s\n", current->result, current->arg1);
        } 
        else {
            if(current->result != NULL)
                printf("%s = ", current->result);
            if(current->arg1 != NULL)
                printf("%s ", current->arg1);
            if(current->op != NULL)
                printf("%s ", current->op);
            if(current->arg2 != NULL)
                printf("%s ", current->arg2);
            printf("\n");
    }
        current = current->next;
    }   
}
