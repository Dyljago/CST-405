#include "optimizer.h"
#include <stdbool.h>
#include <ctype.h>

// TODO: Bug when printing (3 + 3) in optimizer after write(5 + x + 3 + 4);
// TODO: Fix bug with printing variables in incorrect order (x = 3; write x; x = 5; write x; will be 5 5 )

DataRegister calculatedRegisters[10] = {
    {"t0", ""}, {"t1", ""}, {"t2", ""}, {"t3", ""},
    {"t4", ""}, {"t5", ""}, {"t6", ""}, {"t7", ""},
    {"t8", ""}, {"t9", ""}
};
DataRegister calculatedAlready[10] = {
    {"t0", ""}, {"t1", ""}, {"t2", ""}, {"t3", ""},
    {"t4", ""}, {"t5", ""}, {"t6", ""}, {"t7", ""},
    {"t8", ""}, {"t9", ""}
};
DataRegister extraRegister[10] = {
    {"c0", ""}, {"c1", ""}, {"c2", ""}, {"c3", ""},
    {"c4", ""}, {"c5", ""}, {"c6", ""}, {"c7", ""},
    {"c8", ""}, {"c9", ""}
};
DataRegister finalWrite[10] = {
    {"t0", ""}, {"t1", ""}, {"t2", ""}, {"t3", ""},
    {"t4", ""}, {"t5", ""}, {"t6", ""}, {"t7", ""},
    {"t8", ""}, {"t9", ""}
};
DataRegister copyRegisterData[10] = {
    {"t0", ""}, {"t1", ""}, {"t2", ""}, {"t3", ""},
    {"t4", ""}, {"t5", ""}, {"t6", ""}, {"t7", ""},
    {"t8", ""}, {"t9", ""}
};
FunctionDataRegister functionData[10] = {
    {"", "", ""}, {"", "", ""}, {"", "", ""}, {"", "", ""},
    {"", "", ""}, {"", "", ""}, {"", "", ""}, {"", "", ""},
    {"", "", ""}, {"", "", ""}
};

// TODO: Use this to mark hits going through code so that if the register is hit then it cannot be printed but otherwise a write statement will print out the finalWrite[index] system
// IMPLEMENT A SYSTEM WHERE IF THINGS ARE NOT USED THEY CAN
// BE PRINTED BUT IF THEY ARE UPDATED THEY CAN'T BE PRINTED
DataRegister hitRegisterData[10] = {
    {"t0", ""}, {"t1", ""}, {"t2", ""}, {"t3", ""},
    {"t4", ""}, {"t5", ""}, {"t6", ""}, {"t7", ""},
    {"t8", ""}, {"t9", ""}
};

TAC* optimizedTACHead = NULL;
int finishCheck = 0;

int openFunction() {
    for (int i = 0; i < 10; i++) {
        if (strcmp(functionData[i].name, "") == 0) {
            return i;
        }
    }
    return -1;
}

int findFunction(char* result) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(functionData[i].variableType, result) == 0) {
            return i;
        }
    }
    return -1;
}

TAC* optimizeTAC(TAC** head) {
    // printf("Optimizing TAC...\n");
    printFullTAC(*head);
    constantFolding(head);
    // printf("Folding complete\n");
    constantPropagation(optimizedTACHead);
    // printf("Propagation complete\n");
    while (finishCheck == 0) {
        copyFolding(optimizedTACHead);
        constantPropagation(optimizedTACHead);
    }
    fillWriteStatements(optimizedTACHead);
    checkIfStatements(optimizedTACHead);
    printf("--------------\n");
    printFullTAC(optimizedTACHead);
    clearTempRegisters(optimizedTACHead);
    printOptimizedTAC("TACOptimized.ir", optimizedTACHead);
    return optimizedTACHead;
    /*
    constantPropagation(head);
    copyPropagation(head);
    deadCodeElimination(head);
    */
}

/**
 * Check if a string represents an integer constant.
 * 
 * @param str The string to check.
 * @return true if the string is an integer constant, false otherwise.
 * 
 * 
 * Functionality:
The function first checks if the input is 'NULL' or an empty string, 
returning 'false' in these cases as they don't represent a valid constant.

If your language supports negative numbers as constants, the function optionally checks 
for a leading - character, skipping it for the subsequent numeric check.

The main part of the function iterates over each character of the string using a while loop. 
For each character, it uses isdigit() to check if it's a numeric digit.

If any character is not a digit, the function immediately returns 'false'.

If the end of the string is reached without encountering any non-digit characters, 
the function returns 'true', indicating the string is a numeric constant.
 */
bool isConstant(const char* str) {
   

    return true; // All characters were digits
}


/**
 * Checks if a string represents a valid variable name according to a simple naming convention.
 * 
 * @param str The string to check.
 * @return true if the string is a valid variable name, false otherwise.
 
Functionality:
-------------
Initially, the function checks if the input is 'NULL' or an empty string, 
returning false in either case since these don't represent valid variable names.

It then checks if the first character is either a letter or an underscore, 
as per the common naming convention that variable names must start with 
an alphabetic character or underscore.

For the rest of the string, the function checks each character to ensure 
it is either a letter, a digit, or an underscore. This loop starts from the second character, 
as the first character's check was already performed.

If any character does not meet these criteria, the function returns 'false'.

If the string passes all checks, it is considered a valid variable name, and the function returns 'true'.
 */
bool isVariable(const char* str) {
    

    return true; // String meets the criteria for a variable name
}



// A simplified constant folding example that only handles addition of integer constants. 
void constantFolding(TAC** head) {
    TAC* current = *head; // Current TAC instruction
    for (int i = 0; i < 10; i++) {
        calculatedAlready[i].variableType = 0;
    }
    // printf("Folding TAC...\n");
    // const char *filename = "TAC.ir"; // Change to your filename
    // const char *phrase = "write ";

    // printf("%s\n", searchInFile(filename, phrase));

    while (current != NULL) {
        TAC* instruction = (TAC*)malloc(sizeof(TAC));
        if (!instruction) return;
        if (strcmp(current->op,"=") == 0) {
            for (int i = 0; i < 10; i++) {
                if (isRegister(current->result) != -1 && strcmp(functionData[i].variableType, current->arg1) == 0) {
                    if (findFunction(current->arg1) != -1) { 
                        printf("FUNCTIONHEREa%s = %s\n", current->arg1, current->result);
                        functionData[findFunction(current->arg1)].variableType = current->result;   
                    }
                }
                if (strcmp(calculatedRegisters[i].name, current->result) == 0) {
                    // TODO: values are set for calculated registers
                    calculatedRegisters[i].variableType = current->arg1;
                    if (isRegister(current->arg1) == -1 && inCopyName(current->arg1) != -1) {
                        // TODO: t1 = list[0]
                        // printf("FHEREH%s = %s\n", current->result, current->arg1);
                        for(int j = 0; j < 10; j++) {
                            if (strcmp(extraRegister[j].name, current->arg1) == 0 && isNumber(extraRegister[j].variableType) != 0) {
                                // TODO: t0 = t1
                                // printf("EROEROEOREOROROROEOREOR%s -> %s\n", calculatedRegisters[i].name, calculatedRegisters[i].variableType);
                                calculatedRegisters[i].variableType = extraRegister[j].variableType;
                                finalWrite[i].variableType = extraRegister[j].variableType;
                                // printf("EROEROEOREOROROROEOREOR%s : %s\n", calculatedRegisters[i].name, calculatedRegisters[i].variableType);
                            }
                        }
                        // printf("\nEROERJOEROEJROIEJRIEWHSORIJEOIR\n");
                    }
                    // printf("HEREH%s = %s\n", current->result, current->arg1);
                    // printf("FHEREF %s : %s\n", calculatedRegisters[i].name, calculatedRegisters[i].variableType);
                } else if (isRegister(current->arg1) != -1 && current->arg1 != NULL && strcmp(calculatedRegisters[i].variableType, "") != 0) {
                    // printf("READCHED %s : %s\n", calculatedRegisters[i].name, calculatedRegisters[i].variableType);
                    // calculatedRegisters[i].variableType = current->arg1;
                    extraRegister[nextFreeCopySlot()].variableType = current->arg1;
                    extraRegister[inCopyRegister(current->arg1)].name = current->result;
                    // printf("HEREH%s = %s\n", extraRegister[inCopyRegister(current->arg1)].name, extraRegister[inCopyRegister(current->arg1)].variableType);
                    for(int j = 0; j < 10; j++) {
                        if (strcmp(calculatedRegisters[j].name, current->arg1) == 0) {
                            // printf("HEREHp%s = %s\n", current->result, current->arg1);
                            extraRegister[inCopyName(current->result)].variableType = calculatedRegisters[j].variableType;
                        }
                    }
                    // printf("HEREH%s = %s\n", extraRegister[inCopyName(current->result)].name, extraRegister[inCopyName(current->result)].variableType);
                    // printf("SHEREH%s = %s\n", current->result, current->arg1);
                }
            }
            // printf("%s = %s\n", current->result, current->arg1);
        } 
        else {
            // printf("TAC: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
            if(current->result != NULL) {
                // printf("%s = ", current->result);int index = registerCalculatedAtIndex(current->arg2);
                int index = registerCalculatedAtIndex(current->result);
                if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0 && isRegister(current->result) == -1) {
                    // printf("\nINSTRCT: %s ", calculatedRegisters[index].variableType);
                    instruction->result = calculatedRegisters[index].variableType;
                } else {
                    // printf("%s ", current->arg2);
                    if (strcmp(current->op, " -> ") == 0) {
                        int index = openFunction();
                        int check = 0;
                        for (int i = 0; i < 10; i++) {
                            if (strcmp(functionData[i].name, current->arg1) == 0) {
                                check = 1;
                                index = i;
                            }
                        }
                        if (index != -1 && check != 1) {
                            if (isRegister(current->result) == -1) {
                                printf("FUNCTIONHEREb%s = %s\n", current->result, current->arg1);
                                functionData[index].originalVariableType = current->arg1;
                                functionData[index].name = current->result;
                            }
                            printf("FUNCTIONHEREc%s = %s\n", current->result, current->arg1);
                            functionData[index].variableType = current->arg1;
                        } else if (index != -1) {
                            printf("FUNCTIONHEREd%s = %s\n", current->result, current->arg1);
                            functionData[index].variableType = current->result;
                        }
                    }
                    instruction->result = current->result;
                }
                if (isNumber(current->result) == 0 && isRegister(current->result) == -1) {
                    // printf("%s is NOT A NUMBER", current->result);
                    if (dataInSystem(current->result) != -1) {
                        // printf("Data in system: %s\n", dataHolding[dataInSystem(current->result)].name);
                        instruction->result = dataHolding[dataInSystem(current->result)].name;
                        int index = registerCalculatedAtIndex(instruction->result);
                        if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0) {
                            // calculatedRegisters[index].variableType = "";
                            calculatedAlready[index].variableType = 1;
                        }
                    }
                }
            }
            if(current->arg1 != NULL) {
                int index = registerCalculatedAtIndex(current->arg1);
                if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0) {
                    // printf("%s ", calculatedRegisters[index].variableType);
                    // TODO: t0 is replaced
                    // printf("\nHEREH%s = %s\n", current->result, current->arg1);
                    instruction->arg1 = calculatedRegisters[index].variableType;
                    calculatedRegisters[index].variableType = "";
                    // printf("HEREH%s = %s\n", instruction->result, instruction->arg1);
                } else {
                    // printf("\nSHERES%s \n", current->arg1);
                    if (isNumber(current->arg1) == 0) {
                        // printf("%s is NOT A NUMBER", current->arg2);
                        if (dataInSystem(current->arg1) != -1) {
                            // printf("Data in system: %d\n", dataInSystem(current->arg1));
                            instruction->arg1 = dataHolding[dataInSystem(current->arg1)].name;
                        } else {
                            instruction->arg1 = current->arg1;   
                        }
                    } else {
                        instruction->arg1 = current->arg1;   
                    }
                }
            }
            if(current->op != NULL)
                // printf("%s ", current->op);
                instruction->op = current->op;
            if(current->arg2 != NULL) {
                if (strcmp(current->arg1, "write") == 0) {
                    int index = registerCalculatedAtIndex(current->arg2); 
                    if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0) {
                        // printf("\nINSTRCT: %s ", calculatedRegisters[index].variableType);
                        if (calculatedAlready[index].variableType != 1 && isRegister(current->arg2) == -1) {
                            instruction->arg2 = calculatedRegisters[index].variableType;
                            calculatedAlready[index].variableType = 1;
                        } else {
                            instruction->arg2 = current->arg2;
                        }
                    } else {
                        instruction->arg2 = current->arg2;
                    }
                } else {
                    int index = registerCalculatedAtIndex(current->arg2);
                    if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0) {
                        // printf("\nINSTRCT: %s ", calculatedRegisters[index].variableType);
                        instruction->arg2 = calculatedRegisters[index].variableType;
                    } else {
                        // printf("%s ", current->arg2);
                        instruction->arg2 = current->arg2;
                    }
                    if (isNumber(current->arg2) == 0) {
                        // printf("%s is NOT A NUMBER", current->arg2);
                        if (dataInSystem(current->arg2) != -1) {
                            // printf("Data in system: %s\n", dataHolding[dataInSystem(current->arg2)]);
                            instruction->arg2 = dataHolding[dataInSystem(current->arg2)].name;
                            int index = registerCalculatedAtIndex(instruction->arg2);
                            // printf("INDEX: %d\n", index);
                            if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0) {
                                // printf("\nINSTRCT: %s \n", calculatedRegisters[index].variableType);
                                instruction->arg2 = calculatedRegisters[index].variableType;
                                calculatedRegisters[index].variableType = "";
                            } else {
                                // printf("\nINSTRCT: %s ", instruction->arg2);
                            }
                        }
                    }
                }
            }
            // printf("\n");
            // printf("Instruction: %s = %s %s %s\n", instruction->result, instruction->arg1, instruction->op, instruction->arg2);
            appendTAC(&optimizedTACHead, instruction);
        }
        current = current->next;
        // if (instruction->result != NULL) {
        //     printf("\n");
        //     printf("Instruction: %s = %s %s %s\n", instruction->result, instruction->arg1, instruction->op, instruction->arg2);
        // } else if (instruction->arg1 != NULL) {
        //     printf("\n");
        //     printf("Instruction: %s %s\n", instruction->arg1, instruction->arg2);
        // }
    } 
    // printf("\n-------------------------------\n");
    // Apply constant folding optimization
}

// A simplified constant propagation example that only handles assignment of integer constants to variables.
void constantPropagation(TAC** head) {
    /*
    This function performs constant propagation on the provided TAC list.
    It iterates through the list and looks for assignments of integer constants to variables.
    When such an assignment is found, it propagates the constant value to all uses of the variable.
    */
    TAC* current = head;
    // printf("Propagating TAC...\n");

    while (current != NULL) {
        TAC* instruction = (TAC*)malloc(sizeof(TAC));
        if (!instruction) return;

        if (strcmp(current->op,"=") == 0) {
            // printf("%s = %s\n", current->result, current->arg1);
            int index = registerCalculatedAtIndex(current->result);
            finalWrite[index].variableType = current->arg1;
        } 
        else {
            if(current->result != NULL) {
                if (strcmp(current->op, "+") == 0) {
                    if (isNumber(current->arg1) != 0 && isNumber(current->arg2) != 0) {
                        char* buffer = malloc(20);
                        if (strchr(current->arg2, '.') != NULL) {
                            double sum = atof(current->arg1) + atof(current->arg2);
                            snprintf(buffer, sizeof(buffer), "%f", sum);
                        } else {
                            int sum = atoi(current->arg1) + atoi(current->arg2);
                            snprintf(buffer, sizeof(buffer), "%d", sum);
                        }
                        current->arg1 = buffer;
                        current->arg2 = NULL;
                        current->op = "=";
                        // printf("\n%s = %s\n", current->result, current->arg1);
                        int index = registerCalculatedAtIndex(current->result);
                        finalWrite[index].variableType = current->arg1;
                        variablesInSystem[index].variableType = current->arg1;
                        hitRegisterData[index].variableType = "1";
                    }
                } else if (strcmp(current->op, "-") == 0) {
                    if (isNumber(current->arg1) != 0 && isNumber(current->arg2) != 0) {
                        char* buffer = malloc(20);
                        if (strchr(current->arg2, '.') != NULL) {
                            double sum = atof(current->arg1) - atof(current->arg2);
                            snprintf(buffer, sizeof(buffer), "%f", sum);
                        } else {
                            int sum = atoi(current->arg1) - atoi(current->arg2);
                            snprintf(buffer, sizeof(buffer), "%d", sum);
                        }
                        current->arg1 = buffer;
                        current->arg2 = NULL;
                        current->op = "=";
                        // printf("\n%s = %s\n", current->result, current->arg1);
                        int index = registerCalculatedAtIndex(current->result);
                        finalWrite[index].variableType = current->arg1;
                        variablesInSystem[index].variableType = current->arg1;
                        hitRegisterData[index].variableType = "1";
                    }
                } else if (strcmp(current->op, "*") == 0) {
                    if (isNumber(current->arg1) != 0 && isNumber(current->arg2) != 0) {
                        char* buffer = malloc(20);
                        if (strchr(current->arg2, '.') != NULL) {
                            double sum = atof(current->arg1) * atof(current->arg2);
                            snprintf(buffer, sizeof(buffer), "%f", sum);
                        } else {
                            int sum = atoi(current->arg1) * atoi(current->arg2);
                            snprintf(buffer, sizeof(buffer), "%d", sum);
                        }
                        current->arg1 = buffer;
                        current->arg2 = NULL;
                        current->op = "=";
                        // printf("\n%s = %s\n", current->result, current->arg1);
                        int index = registerCalculatedAtIndex(current->result);
                        finalWrite[index].variableType = current->arg1;
                        variablesInSystem[index].variableType = current->arg1;
                        hitRegisterData[index].variableType = "1";
                    }
                } else if (strcmp(current->op, "/") == 0) {
                    if (isNumber(current->arg1) != 0 && isNumber(current->arg2) != 0) {
                        char* buffer = malloc(20);
                        if (strchr(current->arg2, '.') != NULL) {
                            double sum = atof(current->arg1) / atof(current->arg2);
                            snprintf(buffer, sizeof(buffer), "%f", sum);
                        } else {
                            int sum = atoi(current->arg1) / atoi(current->arg2);
                            snprintf(buffer, sizeof(buffer), "%d", sum);
                        }
                        current->arg1 = buffer;
                        current->arg2 = NULL;
                        current->op = "=";
                        // printf("\n%s = %s\n", current->result, current->arg1);
                        int index = registerCalculatedAtIndex(current->result);
                        finalWrite[index].variableType = current->arg1;
                        variablesInSystem[index].variableType = current->arg1;
                        hitRegisterData[index].variableType = "1";
                    }
                }
            } 
        }
        current = current->next;
    } 

    // printf("\n-------------------------------\n");
    
}

// A simplified copy propagation example that only handles assignment of variables to variables.
// This function replaces all uses of a variable with the value of the variable being assigned.
// For example, if the TAC contains "assign x, y", it will replace all uses of "y" with "x".

void copyFolding(TAC** head) {
    TAC* copyHead = optimizedTACHead;
    optimizedTACHead = NULL;
    TAC* current = head;
    // printf("Copy folding...\n");
    for (int i = 0; i < 10; i++) {
        calculatedAlready[i].variableType = 0;
    }

    while (current != NULL) {
        TAC* instruction = (TAC*)malloc(sizeof(TAC));
        if (!instruction) return;
        if (strcmp(current->op,"=") == 0) {
            for (int i = 0; i < 10; i++) {
                if (strcmp(calculatedRegisters[i].name, current->result) == 0) {
                    calculatedRegisters[i].variableType = current->arg1;
                }
            }
        } 
        else {
            if(current->result != NULL) {
                if (inCopyRegister(current->result) != -1) {
                    instruction->result = extraRegister[inCopyRegister(current->result)].name;
                    // printf("EROEROEOREOROROROEOREOR%s = %s\n", current->result, current->arg1);
                } else if (inCopyName(current->result) != -1) {
                    // TODO: c0 = 5
                    extraRegister[inCopyName(current->result)].variableType = current->arg1;
                    instruction->result = extraRegister[inCopyName(current->result)].name;
                    // printf("EROEROEOREOROROROEOREOR%s = %s\n", current->result, current->arg1);
                } else {
                    if (strcmp(current->op, " -> ") == 0) {
                        int index = openFunction();
                        int check = 0;
                        for (int i = 0; i < 10; i++) {
                            if (strcmp(functionData[i].name, current->arg1) == 0) {
                                check = 1;
                                index = i;
                            } else if (strcmp(functionData[i].name, current->result) == 0) {
                                index = i;
                                check = 1;
                            }
                        }
                        if (index != -1 && check != 1) {
                            if (isRegister(current->result) == -1) {
                                printf("FUNCTIONHEREb%s = %s\n", current->result, current->arg1);
                                functionData[index].name = current->result;
                            }
                            printf("FUNCTIONHEREc%s = %s\n", current->result, current->arg1);
                            functionData[index].variableType = current->arg1;
                        } else if (index != -1) {
                            printf("FUNCTIONHEREd%s = %s\n", current->result, current->arg1);
                            functionData[index].variableType = current->result;
                        }
                    }
                    // printf("%s = ", current->result);
                    instruction->result = current->result;
                }
            }
            if(current->arg1 != NULL) {
                int index = registerCalculatedAtIndex(current->arg1); 
                if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0) {
                    if (calculatedAlready[index].variableType != 1) {
                        instruction->arg1 = calculatedRegisters[index].variableType;
                        calculatedAlready[index].variableType = 1;
                    } else {
                        instruction->arg1 = current->arg1;
                    }
                } else {
                    // printf("EROEROEOREOROROROEOREOR%s = %s\n", current->result, current->arg1);
                    if (dataInSystem(current->arg1) != -1) {
                        // printf("Data in system: %d\n", dataInSystem(current->arg1));
                        instruction->arg1 = dataHolding[dataInSystem(current->arg1)].name;
                    } else {
                        // printf("EROEROEOREOROROROEOREOR%s = %s\n", current->result, current->arg1);
                        instruction->arg1 = current->arg1;
                    }
                }
            }
            if(current->op != NULL)
                // printf("OP: %s ", current->op);
                instruction->op = current->op;
            if(current->arg2 != NULL) {
                int index = registerCalculatedAtIndex(current->arg2);
                if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0) {
                    // printf("EROEROEOREOROROROEOREOR%s = %s\n", current->result, current->arg1);
                    if (calculatedAlready[index].variableType != 1) {
                        instruction->arg2 = calculatedRegisters[index].variableType;
                        calculatedAlready[index].variableType = 1;
                    } else {
                        instruction->arg2 = current->arg2;
                    }
                } else {
                    instruction->arg2 = current->arg2;
                }
            }
            // printf("\n");
            // if (instruction->result != NULL) {
            //     printf("Instruction: %s = %s %s %s", instruction->result, instruction->arg1, instruction->op, instruction->arg2);
            // } else {
            //     printf("Instruction: %s %s", instruction->arg1, instruction->arg2);
            // }
            appendTAC(&optimizedTACHead, instruction);
        }
        current = current->next;
    } 

    // printf("\n-------------------------------\n");
    if (areTACListsEqual(copyHead, optimizedTACHead) == 1) {
        // printf("Copied TAC is equal to optimized TAC\n");
        finishCheck = 1;
    }
    //  else {
    //     // printf("%d", areTACListsEqual(copyHead, optimizedTACHead));
    //     printf("-----------------Copied TAC------------------\n");
    //     printFullTAC(copyHead);
    //     printf("-----------------Optimized TAC------------------\n");
    //     printFullTAC(optimizedTACHead);
    // }
}

void fillWriteStatements(TAC** head) {
    TAC* copyHead = optimizedTACHead;
    optimizedTACHead = NULL;
    TAC* current = head;

    while (current != NULL) {
        TAC* instruction = (TAC*)malloc(sizeof(TAC));
        if (!instruction) return;
        if (strcmp(current->op,"=") == 0) {
            // printf("%s = %s\n", current->result, current->arg1);
        } 
        else {
            if(current->result != NULL)
                // printf("%s = ", current->result);
                instruction->result = current->result;
            if(current->arg1 != NULL) {
                instruction->arg1 = current->arg1;
            }
            if(current->op != NULL)
                // printf("%s ", current->op);
                instruction->op = current->op;
            if(current->arg2 != NULL) {
                int index = registerCalculatedAtIndex(current->arg2);
                if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0) {
                    if (strcmp(finalWrite[index].variableType, "") != 0) {
                        instruction->arg2 = finalWrite[index].variableType;
                    } else {
                        instruction->arg2 = current->arg2;
                    }
                } else {
                    instruction->arg2 = current->arg2;
                }
            }
            // printf("\n");
            // if (instruction->result != NULL) {
            //     printf("Instruction: %s = %s %s %s", instruction->result, instruction->arg1, instruction->op, instruction->arg2);
            // } else {
            //     printf("Instruction: %s %s", instruction->arg1, instruction->arg2);
            // }
            appendTAC(&optimizedTACHead, instruction);
        }
        current = current->next;
    } 
}

void checkIfStatements(TAC** head) {
    // TODO: Check if statements
    // for (int i = 0; i < 10; i++) {
    //     printf("%s: %s\n", functionData[i].name, functionData[i].variableType);
    // }
    printf("\n-------------------------------\n");
    TAC* copyHead = optimizedTACHead;
    optimizedTACHead = NULL;
    TAC* current = head;

    int finished = 0;
    int ifStatementSeen = 0;
    int endPrintDone = 0;
    while (current != NULL) {
        TAC* instruction = (TAC*)malloc(sizeof(TAC));
        if (!instruction) return;
        printf("%s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
        if (current->result != NULL && strcmp(current->result,"if") == 0) {
            printf("Found if statement %d\n", finished);
            ifStatementSeen = 1;
            endPrintDone = 0;
            finished = 0;
            printf("IF STATEMENT %s %s %s\n", current->arg1, current->op, current->arg2);
            if (current->arg2 != NULL) {
                if (isRegister(current->arg1) != -1) {
                    // printf("Found register: %s\n", current->arg1);
                    int index = registerCalculatedAtIndex(current->arg1);
                    if (strcmp(variablesInSystem[index].variableType, "") == 0) {
                        for (int i = 0; i < 10; i++) {
                            if (strcmp(functionData[i].originalVariableType, dataHolding[index].variableType) == 0) {
                                printf("Found variable: %s\n", functionData[i].variableType);
                                printf("REPLACING %s with %s\n", current->arg1, variablesInSystem[registerCalculatedAtIndex(functionData[i].variableType)].variableType);
                                current->arg1 = variablesInSystem[registerCalculatedAtIndex(functionData[i].variableType)].variableType;
                            }
                        }
                    } else {
                        current->arg1 = variablesInSystem[index].variableType;
                    }
                }
                if (isRegister(current->arg2) != -1) {
                    // printf("Found register: %s\n", current->arg2);
                    int index = registerCalculatedAtIndex(current->arg2);
                    if (strcmp(variablesInSystem[index].variableType, "") == 0) {
                        for (int i = 0; i < 10; i++) {
                            if (strcmp(functionData[i].originalVariableType, dataHolding[index].variableType) == 0) {
                                printf("Found variable: %s\n", functionData[i].variableType);
                                printf("REPLACING %s with %s\n", current->arg2, variablesInSystem[registerCalculatedAtIndex(functionData[i].variableType)].variableType);
                                current->arg2 = variablesInSystem[registerCalculatedAtIndex(functionData[i].variableType)].variableType;
                            }
                        }
                    } else {
                        current->arg2 = variablesInSystem[index].variableType;
                    }
                }
                if (evaluateCondition(current->arg1, current->arg2, current->op) == 1) {
                    finished = 1;
                    printf("Finished if statement\n");
                }
            }
        } else if (current->result != NULL && strcmp(current->result,"else if") == 0) {
            ifStatementSeen = 1;
            if (finished == 0) {
                printf("Found else if statement %d\n", finished);
                if (isRegister(current->arg1) != -1) {
                    // printf("Found register: %s\n", current->arg2);
                    int index = registerCalculatedAtIndex(current->arg1);
                    current->arg1 = variablesInSystem[index].variableType;
                }
                if (isRegister(current->arg2) != -1) {
                    // printf("Found register: %s\n", current->arg2);
                    int index = registerCalculatedAtIndex(current->arg2);
                    current->arg2 = variablesInSystem[index].variableType;
                }
                if (evaluateCondition(current->arg1, current->arg2, current->op) == 1) {
                    finished = 1;
                    printf("Finished else if statement\n");
                }
            }
        } else if (current->result != NULL && strcmp(current->result,"else") == 0) {
            ifStatementSeen = 1;
            if (finished == 0) {
                printf("Found else statement %d\n", finished);
                finished = 1;
            }
        } else if (current->result != NULL && strcmp(current->result,"end") == 0) {
            printf("Found end statement\n");
            ifStatementSeen = 0;
        } else {
            // printf("MADE IT INSIDE: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
            if (ifStatementSeen != 1) {
                endPrintDone = 0;
                finished = 0;
                // printf("Found instruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
                if(current->result != NULL)
                    instruction->result = current->result;
                if(current->arg1 != NULL) {
                    instruction->arg1 = current->arg1;
                }
                if(current->op != NULL)
                    instruction->op = current->op;
                if(current->arg2 != NULL) {
                        instruction->arg2 = current->arg2;
                }
                appendTAC(&optimizedTACHead, instruction);
            } else {
                // printf("Found if instruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
                if (finished == 1 && endPrintDone == 0) {
                    printf("Chosen if instruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
                    instruction->result = current->result;
                    instruction->op = current->op;
                    instruction->arg1 = current->arg1;
                    if (isRegister(current->arg2) != -1) {
                        printf("Found register: %s\n", current->arg2);
                        int index = registerCalculatedAtIndex(current->arg2);
                        if (strcmp(variablesInSystem[index].variableType, "") == 0) {
                            for (int i = 0; i < 10; i++) {
                                if (strcmp(functionData[i].originalVariableType, dataHolding[index].variableType) == 0) {
                                    printf("Found variable: %s\n", functionData[i].variableType);
                                    printf("REPLACING %s with %s\n", current->arg2, variablesInSystem[registerCalculatedAtIndex(functionData[i].variableType)].variableType);
                                    instruction->arg2 = variablesInSystem[registerCalculatedAtIndex(functionData[i].variableType)].variableType;
                                }
                            }
                        } else {
                            instruction->arg2 = variablesInSystem[index].variableType;
                        }
                    } else {
                        // printf("Did not find register: %s\n", current->arg2);
                        instruction->arg2 = current->arg2;
                    }
                    appendTAC(&optimizedTACHead, instruction);
                    endPrintDone = 1;
                }
            }
        }
        // printf("MADE IT OUTSIDE: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
        current = current->next;
    } 
}

int evaluateCondition(char* lhs, char* rhs, char* op) {
    if (isNumber(lhs) == 0 || isNumber(rhs) == 0) {
        printf("Evaluating condition: %s %s %s\n", lhs, op, rhs);
        if (strcmp(op, "==") == 0) return strcmp(lhs, rhs) == 0;
        if (strcmp(op, "!=") == 0) return strcmp(lhs, rhs) != 0;
    } else {
        double left = strchr(lhs, '.') ? atof(lhs) : atoi(lhs);
        double right = strchr(rhs, '.') ? atof(rhs) : atoi(rhs);

        printf("Evaluating condition: %s %s %s\n", lhs, op, rhs);
        if (strcmp(op, "==") == 0) return left == right;
        if (strcmp(op, "!=") == 0) return left != right;
        if (strcmp(op, ">=") == 0) return left >= right;
        if (strcmp(op, "<=") == 0) return left <= right;
        if (strcmp(op, ">") == 0)  return left > right;
        if (strcmp(op, "<") == 0)  return left < right;
    }

    printf("ERROR: Invalid comparison operator\n");
    return 0;
}


// A simplified dead code elimination example that only handles removal of unused assignments.
// This function removes assignments that are not used in any subsequent TAC instructions.
// For example, if the TAC contains "assign x, 5" and "assign y, x", and "x" is not used after that, 
// it will remove the "assign x, 5" instruction.

void deadCodeElimination(TAC** head) {
    TAC* current = *head; // Current TAC instruction
    TAC* prev = NULL;     // Previous TAC instruction

    
}

void clearTempRegisters(TAC** head) {
    // printf("Clearing temp registers...\n");
    TAC* current = head;

    while (current != NULL) {
        if(current->result != NULL)
            for (int i = 0; i < 10; i++) {
                if (strcmp(tempRegisterData[i].name, current->result) == 0) {
                    copyRegisterData[i].variableType = tempRegisterData[i].variableType;
                }
            }
        if(current->arg1 != NULL) {
            for (int i = 0; i < 10; i++) {
                if (strcmp(tempRegisterData[i].name, current->arg1) == 0) {
                    copyRegisterData[i].variableType = tempRegisterData[i].variableType;
                }
            }
        }                
        if(current->arg2 != NULL) {
            for (int i = 0; i < 10; i++) {
                if (strcmp(variablesInSystem[i].variableType, current->arg2) == 0) {
                    copyRegisterData[i].variableType = tempRegisterData[i].variableType;
                }
            }
        }
        current = current->next;
    } 
}

// Print the optimized TAC list to a file
void printOptimizedTAC(const char* filename, TAC* head) {
    // FILE* outputFile = fopen(filename, "w");
    FILE* file = fopen(filename , "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }   
    TAC* current = head;
    while (current != NULL) {
        if (strcmp(current->op,"=") == 0) {
            fprintf(file, "%s = %s\n", current->result, current->arg1);
        } 
        else {
            if(current->result != NULL)
                fprintf(file, "%s = ", current->result);
            if(current->arg1 != NULL)
                fprintf(file, "%s ", current->arg1);
            if(current->op != NULL)
                fprintf(file, "%s ", current->op);
            if(current->arg2 != NULL)
                fprintf(file, "%s ", current->arg2);
            fprintf(file, "\n");
    }
        current = current->next;
    }   
    fclose(file);
    printf("Optimized TAC written to %s\n", filename);
    // fclose(outputFile);
}

// Print current TAC instruction
void printCurrentOptimizedTAC(TAC* current) {
    
}

int registerCalculatedAtIndex(char* result) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(calculatedRegisters[i].name, result) == 0) {
            return i;
        }
    }
    return -1;
}

int registerCalculatedTo(char* sum) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(calculatedRegisters[i].variableType, sum) == 0) {
            return i;
        }
    }
    return -1;
}

int isCopyRegister(char* result) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(extraRegister[i].name, result) == 0) {
            // printf("Found %s at %d\n", result, i);
            return i;
        }
    }
    return -1;
}

int nextFreeCopySlot() {
    for (int i = 0; i < 10; i++) {
        if (strcmp(extraRegister[i].variableType, "") == 0) {
            return i;
        }
    }
    return 0;
}

int inCopyRegister(char* result) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(extraRegister[i].variableType, result) == 0) {
            return i;
        }
    }
    return -1;
}

int inCopyName(char* result) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(extraRegister[i].name, result) == 0) {
            // printf("Found %s at %d\n", result, i);
            return i;
        }
    }
    return -1;
}

// Function to compare two TAC lists
int areTACListsEqual(TAC* a, TAC* b) {
    while (a != NULL && b != NULL) {
        // printf("Comparing: %s = %s %s %s\n", a->result, a->arg1, a->op, a->arg2);
        // printf("Comparing: %s = %s %s %s\n", b->result, b->arg1, b->op, b->arg2);
        if (a->result == NULL && b->result == NULL) {
            break;
        } 
        // else {
        //     return 0;
        // }
        // Compare strings safely
        if (a->op != NULL && b->op != NULL) {
            if (strcmp(a->op, b->op) != 0) {
                return 0; // Lists are different
            }
        } else if (a->arg1 != NULL && b->arg1 == NULL) {
            if (strcmp(a->arg1, b->arg1) != 0) {
                return 0; // Lists are different
            }
        } else if (a->arg2 == NULL && b->arg2 != NULL) {
            if (strcmp(a->arg2, b->arg2) != 0) {
                return 0; // Lists are different
            }
        } else if (a->result != NULL && b->result == NULL) {
            if (strcmp(a->result, b->result) != 0) {
                return 0; // Lists are different
            }
        }

        a = a->next;
        b = b->next;
    }
    if (a == NULL && b != NULL) {
        return 0;
    } else if (a != NULL && b == NULL) {
        return 0;
    }
    
    // If both reached NULL, they are the same length and identical
    return 1;
}
