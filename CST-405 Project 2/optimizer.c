#include "optimizer.h"
#include <stdbool.h>
#include <ctype.h>

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
DataRegister copyRegisterData[10] = {
    {"t0", ""}, {"t1", ""}, {"t2", ""}, {"t3", ""},
    {"t4", ""}, {"t5", ""}, {"t6", ""}, {"t7", ""},
    {"t8", ""}, {"t9", ""}
};

TAC* optimizedTACHead = NULL;
int finishCheck = 0;

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
                if (strcmp(calculatedRegisters[i].name, current->result) == 0) {
                    calculatedRegisters[i].variableType = current->arg1;
                }
            }
            // printf("%s = %s\n", current->result, current->arg1);
        } 
        else {
            if(current->result != NULL)
                // printf("%s = ", current->result);
                instruction->result = current->result;
            if(current->arg1 != NULL) {
                int index = registerCalculatedAtIndex(current->arg1);
                if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0) {
                    // printf("%s ", calculatedRegisters[index].variableType);
                    instruction->arg1 = calculatedRegisters[index].variableType;
                } else {
                    // printf("%s ", current->arg1);
                    instruction->arg1 = current->arg1;
                }
            }
            if(current->op != NULL)
                // printf("%s ", current->op);
                instruction->op = current->op;
            if(current->arg2 != NULL) {
                int index = registerCalculatedAtIndex(current->arg2);
                if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0) {
                    // printf("%s ", calculatedRegisters[index].variableType);
                    instruction->arg2 = calculatedRegisters[index].variableType;
                } else {
                    // printf("%s ", current->arg2);
                    instruction->arg2 = current->arg2;
                }
                if (isNumber(current->arg2) == 0) {
                    // printf("%s is NOT A NUMBER", current->arg2);
                    if (dataInSystem(current->arg2) != -1) {
                        // printf("Data in system: %d\n", dataInSystem(current->arg2));
                        instruction->arg2 = dataHolding[dataInSystem(current->arg2)].name;
                    }
                }
            }
            // printf("\n");
            // printf("Instruction: %s = %s %s %s\n", instruction->result, instruction->arg1, instruction->op, instruction->arg2);
            appendTAC(&optimizedTACHead, instruction);
        }
        current = current->next;
    } 
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
        } 
        else {
            if(current->result != NULL) {
                if (strcmp(current->op, "+") == 0) {
                    if (isNumber(current->arg1) != 0 && isNumber(current->arg2) != 0) {
                        int sum = atoi(current->arg1) + atoi(current->arg2);
                        // printf("NUMBER %d\n", sum);
                        char* buffer = malloc(20);
                        snprintf(buffer, sizeof(buffer), "%d", sum);
                        current->arg1 = buffer;
                        current->arg2 = NULL;
                        current->op = "=";
                        // printf("%s = %s\n", current->result, current->arg1);
                    }
                }
            }
        }
        current = current->next;
    } 
    
}

// A simplified copy propagation example that only handles assignment of variables to variables.
// This function replaces all uses of a variable with the value of the variable being assigned.
// For example, if the TAC contains "assign x, y", it will replace all uses of "y" with "x".

void copyFolding(TAC** head) {
    TAC* copyHead = optimizedTACHead;
    optimizedTACHead = NULL;
    TAC* current = head;
    for (int i = 0; i < 10; i++) {
        calculatedAlready[i].variableType = 0;
    }
    // printf("Folding TAC Again...\n");
    // const char *filename = "TAC.ir"; // Change to your filename
    // const char *phrase = "write ";

    // printf("%s\n", searchInFile(filename, phrase));

    while (current != NULL) {
        TAC* instruction = (TAC*)malloc(sizeof(TAC));
        if (!instruction) return;
        if (strcmp(current->op,"=") == 0) {
            for (int i = 0; i < 10; i++) {
                if (strcmp(calculatedRegisters[i].name, current->result) == 0) {
                    calculatedRegisters[i].variableType = current->arg1;
                }
            }
            // printf("%s = %s\n", current->result, current->arg1);
        } 
        else {
            if(current->result != NULL)
                // printf("%s = ", current->result);
                instruction->result = current->result;
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
                    instruction->arg1 = current->arg1;
                }
            }
            if(current->op != NULL)
                // printf("%s ", current->op);
                instruction->op = current->op;
            if(current->arg2 != NULL) {
                int index = registerCalculatedAtIndex(current->arg2);
                if (index != -1 && strcmp(calculatedRegisters[index].variableType, "") != 0) {
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
            // printf("Instruction: %s = %s %s %s\n", instruction->result, instruction->arg1, instruction->op, instruction->arg2);
            appendTAC(&optimizedTACHead, instruction);
        }
        current = current->next;
    } 
    if (areTACListsEqual(copyHead, optimizedTACHead) == 1) {
        // printf("Copied TAC is equal to optimized TAC\n");
        finishCheck = 1;
    }
    //  else {
    //     // printf("%d", areTACListsEqual(copyHead, optimizedTACHead));
    //     // printf("-----------------Copied TAC------------------\n");
    //     printFullTAC(copyHead);
    //     // printf("-----------------Optimized TAC------------------\n");
    //     printFullTAC(optimizedTACHead);
    // }
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
                if (strcmp(tempRegisterData[i].name, current->arg2) == 0) {
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

// Function to compare two TAC lists
int areTACListsEqual(TAC* a, TAC* b) {
    while (a != NULL && b != NULL) {
        // printf("Comparing: %s = %s %s %s\n", a->result, a->arg1, a->op, a->arg2);
        // printf("Comparing: %s = %s %s %s\n", b->result, b->arg1, b->op, b->arg2);
        if (a->result == NULL && b->result == NULL) {
            break;
        } else {
            return 0;
        }
        // Compare strings safely
        if ((strcmp(a->op, b->op) != 0) || (strcmp(a->arg1, b->arg1) != 0) || (strcmp(a->arg2, b->arg2) != 0) || (strcmp(a->result, b->result) != 0)) {
            return 0; // Lists are different
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
