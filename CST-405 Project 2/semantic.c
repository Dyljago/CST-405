#include "semantic.h"
#include <stdio.h>

// Perform semantic analysis on the AST
TAC* tacHead = NULL;

DataRegister tempRegisterData[10] = {
    {"t0", ""}, {"t1", ""}, {"t2", ""}, {"t3", ""},
    {"t4", ""}, {"t5", ""}, {"t6", ""}, {"t7", ""},
    {"t8", ""}, {"t9", ""}
};

DataRegister variablesInSystem[10] = {
    {"t0", ""}, {"t1", ""}, {"t2", ""}, {"t3", ""},
    {"t4", ""}, {"t5", ""}, {"t6", ""}, {"t7", ""},
    {"t8", ""}, {"t9", ""}
};

DataRegister dataHolding[10] = {
    {"t0", ""}, {"t1", ""}, {"t2", ""}, {"t3", ""},
    {"t4", ""}, {"t5", ""}, {"t6", ""}, {"t7", ""},
    {"t8", ""}, {"t9", ""}
};

char* varDeclHold;
int pullNextVariable;
int redeclare = 0;
char* lastArgument;

int findAllocatedRegister(const char* variableName) {
    // printf("Finding allocated register for variable: %s\n", variableName);
    for (int i = 0; i < 10; i++) {
        // printf("Searching");
        if (strcmp(dataHolding[i].variableType, variableName) == 0) {
            // printf("Found\n");
            return i;
        }
    }
    // printf("Not found\n");
    return -1; // Register not found
}

int isVariableInSystem(const char* variableName) {
    // printf("Finding data in system for variable: %s\n", variableName);
    if (variableName == NULL) return -1;
    for (int i = 0; i < 10; i++) {
        // printf("Searching");
        if (strcmp(variablesInSystem[i].variableType, variableName) == 0) {
            // printf("Found\n");
            // printf("SUCCESSFULLY FOUND at %d\n", i);
            return i;
        }
        //  else {
        //     printf("\t\t%s != %s\n", variableName, variablesInSystem[i].variableType);
        // }
    }
    // printf("Not found\n");
    return -1; // Register not found
}

int isVariableInSystemReverse(const char* variableName) {
    // printf("Finding data in system for variable: %s\n", variableName);
    if (variableName == NULL) return -1;
    for (int i = 0; i < 10; i++) {
        // printf("Searching");
        if (strcmp(variablesInSystem[i].name, variableName) == 0) {
            // printf("Found\n");
            // printf("SUCCESSFULLY FOUND at %d\n", i);
            return i;
        }
        //  else {
        //     printf("\t\t%s != %s\n", variableName, variablesInSystem[i].variableType);
        // }
    }
    // printf("Not found\n");
    return -1; // Register not found
}

int dataInSystem(const char* variableName) {
    // printf("Finding data in system for variable: %s\n", variableName);
    if (variableName == NULL) return -1;
    for (int i = 0; i < 10; i++) {
        // printf("Searching");
        if (strcmp(dataHolding[i].variableType, variableName) == 0) {
            // printf("Found\n");
            // printf("SUCCESSFULLY FOUND at %d\n", i);
            return i;
        }
        //  else {
        //     printf("\t\t%s != %s\n", variableName, variablesInSystem[i].variableType);
        // }
    }
    // printf("Not found\n");
    return -1; // Register not found
}

void semanticAnalysis(ASTNode* node, SymbolTable* symTab) {
    if (node == NULL) return;

    switch (node->type) {
         case NodeType_Program:
            // printf("Performing semantic analysis on program\n");
            semanticAnalysis(node->program.varDeclList, symTab);
            semanticAnalysis(node->program.stmtList, symTab);
            break;
        case NodeType_VarDeclList:
            semanticAnalysis(node->varDeclList.varDecl, symTab);
            semanticAnalysis(node->varDeclList.varDeclList, symTab);
            break;
        case NodeType_VarDecl:
            // printf("\033[1;34mVariable declaration type: %s\033[0m\n", node->varDecl.varType);
            // printf("\033[1;34mVariable declaration name: %s\033[0m\n", node->varDecl.varName);
            // Check for redeclaration of variables
            break;
        case NodeType_VarDeclAssign:
            // printf("\033[1;34mVariable declaration type: %s\033[0m\n", node->varDeclAssign.varType);
            // printf("\033[1;34mVariable declaration name: %s\033[0m\n", node->varDeclAssign.varName);
            // printf("\033[1;34mVariable declaration assignment: %s\033[0m\n", node->varDeclAssign.varAssign);
            // printf("\033[1;34mVarDeclHold ADD\033[0m\n");
            varDeclHold = node->assignStmt.varName;
            pullNextVariable = 1;
            // printf("\033[1;34mVarDeclHold SEARCH: %s\033[0m\n", varDeclHold);
            if (findAllocatedRegister(varDeclHold) != -1) {
                // printf("\033[1;34mVarDeclHold FOUND\033[0m\n");
                lastArgument = dataHolding[findAllocatedRegister(varDeclHold)].name;
            }
            // Check for redeclaration of variables
            semanticAnalysis(node->varDeclAssign.varAssign, symTab);
            break;
        case NodeType_StmtList:
            semanticAnalysis(node->stmtList.stmt, symTab);
            semanticAnalysis(node->stmtList.stmtList, symTab);
            break;
        case NodeType_AssignStmt:
            // printf("Assign statement type: %s\n", node->assignStmt.varName);
            // printf("\033[1;31mASSIGMENT STATEMENT: %s\033[0m\n", node->assignStmt.operator);
            varDeclHold = node->assignStmt.varName;
            pullNextVariable = 1;
            // printf("\033[1;34mVarDeclHold ADD\033[0m\n");
            if (findAllocatedRegister(varDeclHold) != -1) {
                // printf("\033[1;34mVarDeclHold FOUND\033[0m\n");
                lastArgument = dataHolding[findAllocatedRegister(varDeclHold)].name;
            }
            // TODO: Check for redeclaration of variables (e.g. x = 2;)
            semanticAnalysis(node->assignStmt.expr, symTab);
            break;  
        case NodeType_OtherStmt:
            printf("");
            // printf("\n\n\n\n\n----------------------Performing semantic analysis on other statement----------------------\n\n\n\n\n");
            // printf("Other statement type: %s\n", node->otherStmt.varName);
            // TODO: FIX PRINTING FOR EXPRESSIONS
            redeclare = 1;
            semanticAnalysis(node->otherStmt.expr, symTab);
            TAC* tac = generateTACForPrint(node->otherStmt.expr, node->otherStmt.varName);
            // Process or store the generated TAC
            // printTAC(tac);
            break;  
        case NodeType_Expr:
            // printf("\n\n\nEXPR Type\n\n\n");
            // printf("EXPR Operator: %c\n", node->expr.operator);
            pullNextVariable = 0;
            semanticAnalysis(node->expr.left, symTab);
            semanticAnalysis(node->expr.right, symTab);
            break;
        case NodeType_BinOp:
            // printf("\n\n\nBinOP Type\n\n\n");
            // Check for declaration of variables
            if (lookupSymbol(symTab, node->binOp.left->varDecl.varName) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->varDecl.varName);
            }
            if (lookupSymbol(symTab, node->binOp.right->varDecl.varName) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->varDecl.varName);
            }
            semanticAnalysis(node->binOp.left, symTab);
            break;
        case NodeType_SimpleID:
            // printf("\n\n\nSimple ID Type\n\n\n");
            // Check for declaration of variable
            if (redeclare == 1) {
                varDeclHold = node->simpleID.name;
                lastArgument = node->simpleID.name;
                redeclare = 0;
            } 
            if (lookupSymbol(symTab, node->simpleID.name) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->simpleID.name);
            }
        case NodeType_SimpleExpr:
            // no checks necessary for number
        // ... handle other node types ...

        default:
            // fprintf(stderr, "Unknown Nodes Type\n");
    }

       // ... other code ...

    if (node->type == NodeType_Expr || node->type == NodeType_SimpleExpr) {
        // printf("Generating TAC for expression or simple expr\n");
        // if (node->type == NodeType_Expr) {
        //     printf("Operator: %c\n", node->expr.operator);
        //     if (node->expr.left->type == NodeType_SimpleID) {
        //         printf("\033[1;35mFOUND SIMPLE ID %s\033[0m\n", node->expr.left->simpleID.name);
        //     } else if (node->expr.left->type == NodeType_SimpleExpr) {
        //         printf("\033[1;35mFOUND SIMPLE EXPR\033[0m\n");
        //     } else {
        //         printf("\033[1;35mFOUND NOTHING\033[0m\n");
        //     }
        // } else {
        //     printf("Simple expression num: %d\n", node->simpleExpr.number);
        // }
        if (varDeclHold != NULL) {
            if (findAllocatedRegister(varDeclHold) != -1) {
                // printf("\033[1;34mVarDeclHold FOUND\033[0m\n");
                lastArgument = dataHolding[findAllocatedRegister(varDeclHold)].name;
            }
        }
        TAC* tac = generateTACForExpr(node);
        if (tac == NULL) {
            return;
        }
        // Process or store the generated TAC
        // printTAC(tac);
        if (node->type == NodeType_Expr) {
            // printf("Result: %s\n", tac->result);
            for (int i = 0; i < 10; i++) {
                if (strcmp(dataHolding[i].name, tac->result) == 0) {
                    // for (int j = 0; j < 10; j++) {
                    //     if (strcmp(dataHolding[j].variableType, varDeclHold) == 0) {
                    //         printf("REMOVING %s -> %s at %d\n", dataHolding[j].name, dataHolding[j].variableType, j);
                    //         // dataHolding[j].variableType = "";
                    //     }
                    // }
                    dataHolding[i].variableType = varDeclHold;
                    // printf("\033[1;36mAllocated register: %s\033[0m\n", dataHolding[i].name);
                    // printf("\033[1;36mVariable type: %s\033[0m\n", dataHolding[i].variableType);
                    // printf("\033[1;36m%s -> %s\033[0m\n", varDeclHold, lastArgument);
                }
            }
            pullNextVariable = 0;
        } else {
            if (pullNextVariable == 1) {
                for (int i = 0; i < 10; i++) {
                    if (strcmp(dataHolding[i].name, tac->result) == 0) {
                        dataHolding[i].variableType = varDeclHold;
                        // printf("\033[1;36mAllocated register: %s\033[0m\n", dataHolding[i].name);
                        // printf("\033[1;36mVariable type: %s\033[0m\n", dataHolding[i].variableType);
                    }
                }
                pullNextVariable = 0;
            }
        }
    }

    // ... other code ...

}

// You can add more functions related to semantic analysis here
// Implement functions to generate TAC expressions

TAC* generateTACForExpr(ASTNode* expr) {
    // printf("BEGINNING GENERATION\n");
    // Depending on your AST structure, generate the appropriate TAC
    // If the TAC is generated successfully, append it to the global TAC list
    // Return the generated TAC, so that it can be used by the caller, e.g. for printing
    if (!expr) return NULL;

    // printf("STILL GENERATION\n");

    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    // printf("STILL GENERATION\n");

    switch (expr->type) {
        case NodeType_Expr: {

            // printf("EXPR GENERATION\n");
            // if (expr->expr.right->type == NodeType_SimpleID) {
            //     printf("SIMPLE ID EREJRJES");
            // } else if (expr->expr.right->type == NodeType_SimpleExpr) {
            //     printf("SIMPLE EXPR EREJRJES");
            // }
            // printf("\n\n\n%s %c %s\nEREOROROORE\n\n", expr->expr.left, expr->expr.operator, expr->expr.right);
            char* leftBuffer = malloc(20);
            // snprintf(leftBuffer, 20, "%d", expr->expr.left->simpleExpr.number);
            if (expr->expr.left->type == NodeType_SimpleID) {
                // printf("SIMPLE ID EREJRJES");
                snprintf(leftBuffer, 20, "%s", expr->expr.left->simpleID.name);
            } else if (expr->expr.left->type == NodeType_SimpleExpr) {
                // printf("SIMPLE EXPR EREJRJES");
                snprintf(leftBuffer, 20, "%d", expr->expr.left->simpleExpr.number);
            } 
            // else {
            //     printf("NOTHING EREJRJES");
            // }
            char* rightBuffer = malloc(20);
            if (expr->expr.right->type == NodeType_SimpleID) {
                // printf("SIMPLE ID EREJRJES");
                snprintf(rightBuffer, 20, "%s", expr->expr.right->simpleID.name);
            } else if (expr->expr.right->type == NodeType_SimpleExpr) {
                // printf("SIMPLE EXPR EREJRJES");
                snprintf(rightBuffer, 20, "%d", expr->expr.right->simpleExpr.number);
            } 
            // else {
            //     printf("NOTHING EREJRJES");
            // }

            // printf("\n\n\n%s %c %s\nEREOROROORE\n\n", leftBuffer, expr->expr.operator, rightBuffer);
            
            if (expr->expr.left->type == NodeType_SimpleExpr) {
                // printf("EXPR GOOD");
                if (isVariableInSystem(leftBuffer) == -1) {
                    // printf("%s NOT IN SYSTEM\n", leftBuffer);
                    instruction->arg1 = createOperand(expr->expr.left);
                } else {
                    instruction->arg1 = variablesInSystem[isVariableInSystem(leftBuffer)].name;
                }
            } else if (expr->expr.left->type == NodeType_SimpleID) {
                // printf("ID GOOD");
                if (dataInSystem(leftBuffer) == -1) {
                    // printf("%s NOT IN SYSTEM\n", leftBuffer);
                    instruction->arg1 = createOperand(expr->expr.left);
                } else {
                    instruction->arg1 = dataHolding[dataInSystem(leftBuffer)].name;
                }
            } else {
                // printf("\033[1;36mLEFT BUFFER IS NULL\033[0m\n");
                instruction->arg1 = lastArgument;
            }

            if (expr->expr.right->type == NodeType_SimpleExpr) {
                // printf("EXPR GOOD");    
                if (isVariableInSystem(rightBuffer) == -1) {
                    // printf("%s NOT IN SYSTEM\n", rightBuffer);
                    instruction->arg2 = createOperand(expr->expr.right);
                } else {
                    instruction->arg2 = variablesInSystem[isVariableInSystem(rightBuffer)].name;
                }
            } else if (expr->expr.right->type == NodeType_SimpleID) {
                // printf("ID GOOD");
                if (dataInSystem(rightBuffer) == -1) {
                    // printf("%s NOT IN SYSTEM\n", rightBuffer);
                    instruction->arg2 = createOperand(expr->expr.right);
                } else {
                    instruction->arg2 = dataHolding[dataInSystem(rightBuffer)].name;
                }
            } else {
                // printf("\033[1;36mRIGHT BUFFER IS NULL\033[0m\n");
                instruction->arg2 = lastArgument;
            }
            instruction->op = strdup("+"); //strdup(expr->expr.operator);
            if (lastArgument == NULL) {
                int temp = getNextAvailableTempVar(tempVars);
                tempRegisterData[temp].variableType = "word";
                instruction->result = createTempVar();
                lastArgument = instruction->result;
            } else {
                instruction->result = lastArgument;
            }
            break;
        }

        case NodeType_SimpleExpr: {
            // printf("SIMPLE EXPR GENERATION\n");
            // printf("\033[1;32mThis is green text\033[0m\n");
            // printf("Generating TAC for simple expression\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->simpleExpr.number);
            instruction->arg1 = strdup(buffer);
            instruction->op = "="; //strdup(expr->expr.operator);
            instruction->arg2 = NULL;
            if (isVariableInSystem(instruction->arg1) == -1) {
                // printf("CREATING TEMP VAR\n");
                int temp = getNextAvailableTempVar(tempVars);
                tempRegisterData[temp].variableType = "word";
                instruction->result = createTempVar();
                for (int i = 0; i < 10; i++) {
                    if (strcmp(variablesInSystem[i].name, instruction->result) == 0) {
                        variablesInSystem[i].variableType = instruction->arg1;
                        // printf("Allocated register: %s\n", variablesInSystem[i].name);
                        // printf("Variable type: %s\n", variablesInSystem[i].variableType);
                        lastArgument = NULL;
                    }
                }
            } else {
                return NULL;
            }
            break;
        }

        case NodeType_SimpleID: {
            // printf("ID GENERATION\n");       
            // printf("Generating TAC for simple ID\n");
            instruction->arg1 = strdup(expr->simpleID.name);
            instruction->op = strdup("assign");
            instruction->result = createTempVar();
            break;
        }

        // Add cases for other expression types...

        default:
            // printf("Unknown GENREATION Type\n");
            free(instruction);
            return NULL;
    }
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForPrint(ASTNode* expr, ASTNode* varName) {
    // Depending on your AST structure, generate the appropriate TAC
    // If the TAC is generated successfully, append it to the global TAC list
    // Return the generated TAC, so that it can be used by the caller, e.g. for printing
    if (!expr) return NULL;

    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    // printf("Generating TAC for print statement %s\n", varName);
    // printf("Generating TAC for print expression %s\n", expr->simpleID.name);

    if(strcmp(varName, "write") == 0 || strcmp(varName, "print") == 0) {
        // printf("\n\n\n------------------Generating TAC for print statement------------------\n\n\n");
        // printf("\n\n\n------------------FOUND: %s------------------\n\n\n", varName);
        // if (expr->type == NodeType_SimpleID) {
        //     printf("\n\n\n------------------FOUND: SIMPLEID------------------\n\n\n");
        // } else if (expr->type == NodeType_SimpleExpr) {
        //     printf("\n\n\n------------------FOUND: SIMPLEEXPR------------------\n\n\n");        
        // } else if (expr->type == NodeType_Expr) {
        //     printf("\n\n\n------------------FOUND: EXPR------------------\n\n\n");        
        // } else {
        //     printf("\n\n\n------------------FOUND: SOMETHING ELSE------------------\n\n\n");
        // }
        instruction->arg1 = strdup(varName);
        if (expr->type == NodeType_SimpleID) {
            // printf("\n\n\n------------------FOUND: SIMPLEID------------------\n\n\n");
            instruction->arg2 = strdup(expr->simpleID.name);
        } else if (expr->type == NodeType_SimpleExpr) {
            // printf("\n\n\n------------------FOUND: SIMPLEEXPR------------------\n\n\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->simpleExpr.number);
            instruction->arg2 = strdup(buffer);
        } else if (expr->type == NodeType_Expr) {
            if (varDeclHold == NULL) {
                printf("\033[1;34mVarDeclHold IS NULL\033[0m\n");
            }
            printf("%s", varDeclHold);
            if (findAllocatedRegister(varDeclHold) != -1) {
                printf("\033[1;34mVarDeclHold FOUND\033[0m\n");
                lastArgument = dataHolding[findAllocatedRegister(varDeclHold)].name;
            }
            instruction->arg2 = lastArgument;
            // printf("\n\n\n------------------FOUND: EXPR------------------\n\n\n");
            // exit(0);        
        } else {
            printf("\n\n\n------------------FOUND: SOMETHING ELSE------------------\n\n\n");
        }
        instruction->op = strdup(""); //strdup(expr->expr.operator);
    } else{
        // printf("\n\n\n------------------FOUND: %s------------------\n\n\n", varName);
        free(instruction);
        return NULL;
    }

    printTAC(instruction);
    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
// Function to create a new temporary variable for TAC
char* createTempVar() {
    static int count = 0;
    char* tempVar = malloc(10); // Enough space for "t" + number
    if (!tempVar) return NULL;
    count = allocateNextAvailableTempVar(tempVars);
    // printf("\033[1;31mAllocated register: t%d\033[0m\n", count);
    sprintf(tempVar, "t%d", count++);
    return tempVar;
}

char* createOperand(ASTNode* node) {
    // Depending on your AST structure, return the appropriate string
    // representation of the operand. For example, if the operand is a simple
    // expression or an identifier, return its string representation.
    // This function needs to be implemented based on your AST structure.
    if (!node) return NULL;

    switch (node->type) {
        case NodeType_SimpleExpr: {
            char* buffer = malloc(20);
            snprintf(buffer, 20, "%d", node->simpleExpr.number);
            return buffer;
        }

        case NodeType_SimpleID: {
            return strdup(node->simpleID.name);
        }

        case NodeType_Expr: {
            return createTempVar();
        }

        // Add cases for other operand types...

        default:
            return NULL;
    }
}

void printTAC(TAC* tac) {
    if (!tac) return;

    // Print the TAC instruction with non-null fields
    if(tac->result != NULL)
        printf("%s = ", tac->result);
    if(tac->arg1 != NULL)
        printf("%s ", tac->arg1);
    if(tac->arg2 != NULL && tac->op != NULL)
        printf("%s ", tac->op);
    if(tac->arg2 != NULL)
        printf("%s ", tac->arg2);
    printf("\n");
}

void printFullTAC(TAC* tac) {
    if (!tac) return;
    while (tac != NULL) {
        if (strcmp(tac->op,"=") == 0) {
            printf("%s = %s\n", tac->result, tac->arg1);
        } 
        else {
            if(tac->result != NULL)
                printf("%s = ", tac->result);
            if(tac->arg1 != NULL)
                printf("%s ", tac->arg1);
            if(tac->op != NULL)
                printf("%s ", tac->op);
            if(tac->arg2 != NULL)
                printf("%s ", tac->arg2);
            printf("\n");
    }
        tac = tac->next;
    }   
}

// Print the TAC list to a file
// This function is provided for reference, you can modify it as needed

void printTACToFile(const char* filename, TAC* tac) {
    FILE* file = fopen(filename , "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }   
    TAC* current = tac;
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
    printf("TAC written to %s\n", filename);
}


// Temporary variable allocation and deallocation functions //

void initializeTempVars() {
    for (int i = 0; i < 20; i++) {
        tempVars[i] = 0;
    }
}

int allocateNextAvailableTempVar(int tempVars[]) {
   // implement the temp var allocation logic
   // use the tempVars array to keep track of allocated temp vars

    // search for the next available temp var
    for (int i = 0; i < 20; i++) {
        if (tempVars[i] == 0) {
            tempVars[i] = 1;
            return i;
        }
    }
    return -1; // No available temp var
}

int getNextAvailableTempVar(int tempVars[]) {
   // implement the temp var allocation logic
   // use the tempVars array to keep track of allocated temp vars

    // search for the next available temp var
    for (int i = 0; i < 20; i++) {
        if (tempVars[i] == 0) {
            return i;
        }
    }
    return -1; // No available temp var
}

void deallocateTempVar(int tempVars[], int index) {
    // implement the temp var deallocation logic
    // use the tempVars array to keep track of allocated temp vars
    if (index >= 0 && index < 20) {
        tempVars[index] = 0;
    }
}   

void appendTAC(TAC** head, TAC* newInstruction) {
    if (!*head) {
        *head = newInstruction;
    } else {
        TAC* current = *head;
        while (current->next != NULL) {
            // printf("Current Instruction: %s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
            current = current->next;
        }
        current->next = newInstruction;
    }
}
