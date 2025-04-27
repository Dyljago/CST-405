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

    int whileLoop = 0;
    int whileCount = 0;
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
            if (notMain == 0) {
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
                if (isNumber(current->arg2) == 0) {
                    fprintf(outputFile, "\tlw %s, %s\n\tlw %s, %s\n\tadd $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, reg2, current->arg2, current->result, reg1, reg2, current->result, current->result);
                } else {
                    fprintf(outputFile, "\tlw %s, %s\n\tadd $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, current->result, reg1, reg2, current->result, current->result);
                }
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
            if (notMain == 0) {
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
                if (isNumber(current->arg2) == 0) {
                    fprintf(outputFile, "\tlw %s, %s\n\tlw %s, %s\n\tsub $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, reg2, current->arg2, current->result, reg1, reg2, current->result, current->result);
                } else {
                    fprintf(outputFile, "\tlw %s, %s\n\tsub $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, current->result, reg1, reg2, current->result, current->result);
                }
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
            if (notMain == 0) {
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
                if (isNumber(current->arg2) == 0) {
                    fprintf(outputFile, "\tlw %s, %s\n\tlw %s, %s\n\tmul $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, reg2, current->arg2, current->result, reg1, reg2, current->result, current->result);
                } else {
                    fprintf(outputFile, "\tlw %s, %s\n\tmul $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, current->result, reg1, reg2, current->result, current->result);
                }
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
            if (notMain == 0) {
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
                if (isNumber(current->arg2) == 0) {
                    fprintf(outputFile, "\tlw %s, %s\n\tlw %s, %s\n\tdiv $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, reg2, current->arg2, current->result, reg1, reg2, current->result, current->result);
                } else {
                    fprintf(outputFile, "\tlw %s, %s\n\tdiv $%s, %s, %s\n\tsw $%s, %s\n", reg1, current->arg1, current->result, reg1, reg2, current->result, current->result);
                }
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
                if (strcmp(current->result, "while") == 0) {
                    printf("Generating MIPS code for while loop\n");
                    whileCount++;
                    whileLoop = 1;
                    if (isNumber(current->arg1) != 0) {
                        fprintf(outputFile, "\tli $a0, %s\n\tjal %s_%d\n\n", current->arg1, current->result, whileCount);
                    } else {
                        fprintf(outputFile, "\tlw $%s, %s\n\tjal %s_%d\n\n", current->arg1, current->arg1, current->result, whileCount);
                    }

                    notMain = 0;
                }
                if (strcmp(current->result, "end_loop") == 0 && whileLoop == 1) {
                    whileLoop = 0;
                    // printf("Found end\n");
                    fprintf(outputFile, "\tj while_%d\n\n", whileCount);
                    notMain = 0;
                }
                functions[nextFunctionRegister()].variableType = current->result;
                if (strcmp(current->result, "while") == 0 || strcmp(current->result, "end_loop") == 0) {
                    fprintf(outputFile, "%s_%d:\n", current->result, whileCount);
                } else {
                    fprintf(outputFile, "%s:\n", current->result);
                }
                if (strcmp(current->result, "while") == 0) {
                    char* op = "";
                    whileLoop = 1;
                    if (current->op != NULL) {
                        if (strcmp(current->op, "==") == 0) {
                            op = "bne";
                        } else if (strcmp(current->op, "!=") == 0) {
                            op = "beq";
                        } else if (strcmp(current->op, ">") == 0) {
                            op = "ble";
                        } else if (strcmp(current->op, "<") == 0) {
                            op = "bge";
                        } else if (strcmp(current->op, ">=") == 0) {
                            op = "blt";
                        } else if (strcmp(current->op, "<=") == 0) {
                            op = "bgt";
                        } else {
                            op = "";
                        }
                    }
                    char* tempRegister = createTempVar();
                    int indexCheck = 0;
                    for (int i = 0; i < 10; i++) {
                        if (strcmp(tempRegisterData[i].name, tempRegister) == 0) {
                            indexCheck = 1;
                        }
                    }
                    if (indexCheck == 0) {
                        for (int i = 0; i < 10; i++) {
                            if (strcmp(dataHolding[i].variableType, "") == 0) {
                                tempRegister = dataHolding[i].name;
                                break;
                            }
                        }
                    }
                    if (isNumber(current->arg2) != 0) {
                        fprintf(outputFile, "\tli $%s, %s\n", tempRegister, current->arg2);
                    } else {
                        fprintf(outputFile, "\tmove $%s, $%s\n", tempRegister, current->arg2);
                    }
                    fprintf(outputFile, "\t%s $%s, $%s, end_loop_%d\n", op, current->arg1, tempRegister, whileCount);
                }
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
                    // printf("\nISNOTNUMBER ISNOTREGISTER\n");
                    char* reg2 = current->arg2;
                    for (int i = 0; i < 10; i++)
                    {
                        if (strcmp(variablesInSystem[i].variableType, current->arg2) == 0) {
                            reg2 = strdup(variablesInSystem[i].name);
                        }
                    }
                    int check = isVariableInSystem(current->arg2);
                    if (check == -1) {
                        for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
                            if (strcmp(tempRegisterData[i].variableType, "") == 0) {
                                variablesInSystem[i].variableType = strdup(current->arg2);
                                reg2 = tempRegisterData[i].name;
                                char *src = variablesInSystem[i].variableType;
                                char *dst = variablesInSystem[i].variableType;
                                while (*src) {
                                    if (*src != '"') {
                                        *dst++ = *src;
                                    }
                                    src++;
                                }
                                *dst = '\0';
                                size_t count = 0;
                                uint32_t *packed = pack_words(variablesInSystem[i].variableType, &count);
                                fprintf(outputFile, "\taddi $sp, $sp, -%d\n", count * 4);
                                for (size_t i = 0; i < count; ++i) {
                                    fprintf(outputFile, "\tli $%s, 0x%08X\n", reg2, packed[i]);
                                    fprintf(outputFile, "\tsw $%s, %d($sp)\n", reg2, (i * 4));
                                    printf("Packed word[%zu]: 0x%08X\n", i, packed[i]);
                                }
                                fprintf(outputFile, "\tsb $zero, %d($sp)\n", ((count - 1) * 4));

                                free(packed); // don't forget to free!
                                reg2 = "$sp";
                                break;
                            }
                        }
                        fprintf(outputFile, "\tli $v0, 4\n\tmove $a0, %s\n\tsyscall\n", reg2);
                        fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\n");
                    } else {
                        fprintf(outputFile, "\tli $v0, 4\n\tla $a0, %s\n\tsyscall\n", reg2);
                        fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\n");
                    }
                } else {
                    printf("REGOSTER Instruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
                    int regNum = findAllocatedRegister(current->arg2);
                    if (regNum == -1) {
                        for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
                            if (strcmp(copyRegisterData[i].name, current->arg2) == 0) {
                                regNum = i;
                            }
                        }
                    }
                    int checkStay = 0;
                    char* reg2 = current->arg2;
                    for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
                        if (strcmp(copyRegisterData[i].name, current->arg2) == 0) {
                            if (copyRegisterData[i].variableType == "") {
                                reg2 = variablesInSystem[i].variableType;
                                checkStay = 1;
                            }
                        }
                    }
                    if (checkStay == 0) {
                        if (notMain == 1) {
                            fprintf(outputFile, "\tmove $t%d, $a0\n", regNum);
                            fprintf(outputFile, "\tmove $a0, $t%d\n\tli $v0, 1\n\tsyscall\n", regNum);
                            fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\n");
                            fprintf(outputFile, "\tmove $a0, $t%d\n", regNum);
                        } else {
                            fprintf(outputFile, "\tlw $t%d, t%d\n", regNum, regNum);
                            fprintf(outputFile, "\tmove $a0, $t%d\n\tli $v0, 1\n\tsyscall\n", regNum);
                            fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\n");
                        }
                    } else {
                        if (strchr(current->arg2, '.') != NULL) {
                            fprintf(outputFile, "\tli $v0, 2\n\tl.s $f12, %s\n\tsyscall\n", reg2);
                            fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\tl.s $f12, %s\n", reg2);
                        } else {
                            // printf("\n\n\INTEGER\n\n\n");
                            fprintf(outputFile, "\tli $v0, 1\n\tli $a0, %s\n\tsyscall\n", reg2);
                            fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n\tli $a0, %s\n", reg2);
                        }
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
                        fprintf(outputFile, "\tli $a0, %s\n\tjal %s\n\tmove $%s, $v0\n\tla $a0, %s\n\tsw $%s, 0($a0)\n\n", current->arg2, current->arg1, current->result, current->result, current->result);
                    } else {
                        fprintf(outputFile, "\tlw $a0, %s\n\tjal %s\n\tmove $%s, $v0\n\tla $a0, %s\n\tsw $%s, 0($a0)\n\n", current->result, current->arg1, current->result, current->result, current->result);
                    }
                } else {
                    printf("INstruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
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

uint32_t* pack_words(const char *str, size_t *out_count) {
    size_t len = strlen(str);
    size_t padded_len = len + 1; // +1 for null terminator
    padded_len = (padded_len + 3) & ~3; // round up to multiple of 4

    size_t word_count = padded_len / 4;
    uint32_t *words = (uint32_t *)malloc(word_count * sizeof(uint32_t));

    for (size_t i = 0; i < word_count; ++i) {
        uint32_t word = 0;
        for (int j = 0; j < 4; ++j) {
            size_t idx = i * 4 + j;
            if (idx < len) {
                word |= ((uint8_t)str[idx]) << (j * 8);
            } else if (idx == len) {
                word |= 0 << (j * 8); // null terminator (already zero)
            } else {
                word |= 0 << (j * 8); // padding zeros
            }
        }
        words[i] = word;
    }

    *out_count = word_count;
    return words;
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
