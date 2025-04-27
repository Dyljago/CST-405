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

DataRegister returnRegisters[10] = {
    {"", ""}, {"", ""}, {"", ""}, {"", ""},
    {"", ""}, {"", ""}, {"", ""}, {"", ""},
    {"", ""}, {"", ""}
};

char* varDeclHold;
int pullNextVariable;
int arrayIndex = 0;
int redeclare = 0;
char* lastArgument;
int returnNext = 0;

// TODO: expr + expr error in mips generation (e.g. 4 + x + 5 + 3 -> t5 = 4 + x, t5 = 5 + 3 but should be t5 = 5 + t5 -> t5 = 3 + t5)

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
        // printf("\t\t%s == %s\n", variableName, dataHolding[i].variableType);
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
            semanticAnalysis(node->program.funcDeclList, symTab);
            semanticAnalysis(node->program.mainFunc, symTab);
            break;
        case NodeType_Main:
            // printf("Performing semantic analysis on main\n");
            generateTACForMain(node->mainFunc.funcName);
            semanticAnalysis(node->mainFunc.body, symTab);
            break;
        case NodeType_FuncDeclList:
            // printf("Performing semantic analysis on main\n");
            semanticAnalysis(node->funcDeclList.funcDecl, symTab);
            semanticAnalysis(node->funcDeclList.funcDeclList, symTab);
            break;
        case NodeType_FuncDecl:
            // printf("Performing semantic analysis on %s\n", node->funcDecl.funcName);
            generateTACForFunc(node->funcDecl.funcName, node->funcDecl.returnType, node->funcDecl.paramList);
            semanticAnalysis(node->funcDecl.paramList, symTab);
            // for (int i = 0; i < 10; i++) {
            //     printf("DATAHOLDING%s: %s\n", dataHolding[i].name, dataHolding[i].variableType);
            // }
            semanticAnalysis(node->funcDecl.body, symTab);
            break;
        case NodeType_FuncCall:
            // printf("Performing semantic analysis on %s\n", node->funcCall.funcName);
            generateTACForFuncCall(node->funcCall.funcName, node->funcCall.exprList);
            semanticAnalysis(node->funcCall.exprList, symTab);
            break;
        case NodeType_FuncCallAssign:
            // printf("Performing semantic analysis on %s\n", node->funcAssignStmt.varName);
            generateTACForFuncAssign(node->funcAssignStmt.varName, node->funcAssignStmt.funcCall);
            // semanticAnalysis(node->funcAssignStmt.funcCall, symTab);
            break;
        case NodeType_ParamDeclList:
            semanticAnalysis(node->paramDeclList.paramDecl, symTab);
            semanticAnalysis(node->paramDeclList.paramDeclList, symTab);
            break;
        case NodeType_ParamDecl:
            generateTACForParam(node->paramDecl.paramName);
            break;
        case NodeType_WhileStmt:
            printf("Performing semantic analysis on while\n");
            generateTACForWhile(node->whileStatement.expr);
            // semanticAnalysis(node->ifStatement.expr, symTab);
            semanticAnalysis(node->whileStatement.body, symTab);
            generateTACForEndLoop();
            break;
        case NodeType_IfStmt:
            // printf("Performing semantic analysis on body\n");
            generateTACForIf(node->ifStatement.expr);
            // semanticAnalysis(node->ifStatement.expr, symTab);
            semanticAnalysis(node->ifStatement.body, symTab);
            generateTACForEnd();
            semanticAnalysis(node->ifStatement.elseIfStatement, symTab);
            semanticAnalysis(node->ifStatement.elseStatement, symTab);
            break;
        case NodeType_ElseIfStmt:
            // printf("Performing semantic analysis on body\n");
            generateTACForElseIf(node->elseIfStatement.expr);
            // semanticAnalysis(node->elseIfStatement.expr, symTab);
            semanticAnalysis(node->elseIfStatement.body, symTab);
            generateTACForEnd();
            semanticAnalysis(node->elseIfStatement.elseIfStatement, symTab);
            break;
        case NodeType_ElseStmt:
            // printf("Performing semantic analysis on body\n");
            generateTACForElse();
            semanticAnalysis(node->elseStatement.body, symTab);
            generateTACForEnd();
            break;
        case NodeType_Body:
            // printf("Performing semantic analysis on body\n");
            semanticAnalysis(node->body.varDeclList, symTab);
            semanticAnalysis(node->body.stmtList, symTab);
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
            semanticAnalysis(node->assignStmt.expr, symTab);
            break; 
        case NodeType_PrintStmt:
            printf("");
            // printf("\n\n\n\n\n----------------------Performing semantic analysis on other statement----------------------\n\n\n\n\n");
            // printf("Print statement type: %s\n", node->printStmt.varName);
            redeclare = 1;

            // printf("\033[1;34mBEFORE Generating TAC for print statement\033[0m\n");
            semanticAnalysis(node->printStmt.expr, symTab);
            TAC* tac = generateTACForPrint(node->printStmt.expr, node->printStmt.varName);
            // printf("\033[1;34mAFTER Generating TAC for print statement\033[0m\n");
            // Process or store the generated TAC
            // printTAC(tac);
            break;
        case NodeType_ReturnStmt:
            printf("");
            returnNext = 1;
            semanticAnalysis(node->returnStmt.expr, symTab);
            generateTACForReturn(node->returnStmt.expr, node->returnStmt.varName);
            break;
        case NodeType_Expr:
            // printf("\n\n\nEXPR Type\n\n\n");
            // printf("EXPR Operator: %c\n", node->expr.operator);
            pullNextVariable = 0;
            if (redeclare == 1) {
                if (node->expr.left->type == NodeType_SimpleID || node->expr.right->type == NodeType_SimpleID) {
                    // printf("\033[1;35mSIMPLE ID\033[0m\n");
                    if (node->expr.left->type == NodeType_SimpleID) {
                        // printf("\033[1;34mVarDeclHold ADD %s\033[0m\n", node->expr.left->simpleID.name);
                        varDeclHold = node->expr.left->simpleID.name;   
                    } else {
                        // printf("\033[1;34mVarDeclHold ADD %s\033[0m\n", node->expr.right->simpleID.name);
                        varDeclHold = node->expr.right->simpleID.name;
                    }
                    redeclare = 0;
                } else if (node->expr.left->type == NodeType_SimpleExpr && node->expr.right != NULL) {
                    // printf("\033[1;35mSIMPLE EXPR\033[0m\n");
                    char buffer[20];
                    snprintf(buffer, 20, "%d", node->expr.left->simpleExpr.number);
                    // printf("\033[1;34mVarDeclHold ADD %s\033[0m\n", buffer);
                    varDeclHold = buffer;
                    redeclare = 0;
                }
            } else if (returnNext == 1) {
                if (node->expr.left->type == NodeType_SimpleID || node->expr.right->type == NodeType_SimpleID) {
                    if (node->expr.left->type == NodeType_SimpleID) {
                        returnRegisters[getNextAvailableReturnValue(returnRegisters)].variableType = node->expr.left->simpleID.name;   
                    } else {
                        returnRegisters[getNextAvailableReturnValue(returnRegisters)].variableType = node->expr.right->simpleID.name;
                    }
                    returnNext = 0;
                } else if (node->expr.left->type == NodeType_SimpleExpr && node->expr.right != NULL) {
                    char buffer[20];
                    snprintf(buffer, 20, "%d", node->expr.left->simpleExpr.number);
                    returnRegisters[getNextAvailableReturnValue(returnRegisters)].variableType = buffer;
                    returnNext = 0;
                }
            }
            semanticAnalysis(node->expr.left, symTab);
            semanticAnalysis(node->expr.right, symTab);
            break;
        case NodeType_BinOp:
            // printf("\n\n\nBinOP Type\n\n\n");
            // Check for declaration of variables
            if (lookupSymbol(symTab, node->binOp.left->varDecl.varName) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->varDecl.varName);
                exit(0);
            }
            if (lookupSymbol(symTab, node->binOp.right->varDecl.varName) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->varDecl.varName);
                exit(0);
            }
            semanticAnalysis(node->binOp.left, symTab);
            break;
        case NodeType_SimpleID:
            // printf("\n\n\nSimple ID Type\n\n\n");
            // Check for declaration of variable
            // if (redeclare == 1) {
            //     printf("\033[1;34mVarDeclHold ADD %s\033[0m\n", node->simpleID.name);
            //     varDeclHold = node->simpleID.name;
            //     // lastArgument = node->simpleID.name;
            //     redeclare = 0;
            // }
            if (lookupSymbol(symTab, node->simpleID.name) == NULL) {
                fprintf(stderr, "\n\n\n---------------------------\n\n\nSemantic error: Variable %s has not been declared\n\n\n---------------------------\n\n\n", node->simpleID.name);
                exit(0);
            }
        case NodeType_SimpleString:
            // printf("\n\n\nSimple String Type\n\n\n");
            // semanticAnalysis(node->assignStmt.expr, symTab);
        case NodeType_SimpleExpr:
            // no checks necessary for number
        case NodeType_SimpleDecimal:
            // no checks necessary for number
        // ... handle other node types ...
        // In the semanticAnalysis function
        case NodeType_ArrDecl:
            // Check for array declaration
            // printf("\033[1;34mArray declaration type: %s\033[0m\n", node->arrDecl.varType);
            semanticAnalysis(node->arrDecl.array, symTab);
            semanticAnalysis(node->arrDecl.exprList, symTab);
            break;

        case NodeType_Array:
            // Handle array access
            // printf("\033[1;34mArray access: %s[%d]\033[0m\n", node->array.arrName, node->array.arrIndex);
            // if (lookupSymbol(symTab, node->array.arrName) == NULL) {
            //     fprintf(stderr, "Semantic error: Array %s has not been declared\n", node->array.arrName);
            //     exit(0);
            // }
            break;

        case NodeType_ArrDeclAssign:
            // Handle array assignment
            if (node->arrAssignStmt.array && node->arrAssignStmt.array->type == NodeType_Array) {
                varDeclHold = node->arrAssignStmt.array->array.arrName;
                char indexStr[20];
                snprintf(indexStr, 20, "[%d]", node->arrAssignStmt.array->array.arrIndex);
                strcat(varDeclHold, indexStr);
                
                pullNextVariable = 1;
                if (findAllocatedRegister(varDeclHold) != -1) {
                    lastArgument = dataHolding[findAllocatedRegister(varDeclHold)].name;
                }
            }
            semanticAnalysis(node->arrAssignStmt.array, symTab);
            semanticAnalysis(node->arrAssignStmt.expr, symTab);
            
            // Generate TAC for array assignment
            TAC* tac2 = generateTACForArrayAssignment(node->arrAssignStmt.array, node->arrAssignStmt.expr);
            break;

        case NodeType_ArrPrintStmt:
            // Handle array print
            redeclare = 1;
            semanticAnalysis(node->arrPrintStmt.array, symTab);
            TAC* tac3 = generateTACForArrayPrint(node->arrPrintStmt.array, node->arrPrintStmt.varName);
            break;

        default:
            // fprintf(stderr, "Unknown Nodes Type\n");
    }

       // ... other code ...

    if (node->type == NodeType_Expr || node->type == NodeType_SimpleExpr || node->type == NodeType_SimpleString || node->type == NodeType_SimpleDecimal) {
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
        // } else if (node->type == NodeType_SimpleExpr) {
        //     printf("Simple expression num: %d\n", node->simpleExpr.number);
        // } else {
        //     printf("Simple string: %s\n", node->simpleString.name);
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
                    if (isNumber(varDeclHold) == 0) {  
                        dataHolding[i].variableType = varDeclHold;   
                    }
                    
                    // printf("\033[1;36mallocated register: %s with type %s\033[0m\n", dataHolding[i].name, dataHolding[i].variableType);
                    // printf("\033[1;36mAllocated register: %s\033[0m\n", dataHolding[i].name);
                    // printf("\033[1;36mVariable type: %s\033[0m\n", dataHolding[i].variableType);
                    // printf("\033[1;36m%s -> %s\033[0m\n", varDeclHold, lastArgument);
                }
            }
            pullNextVariable = 0;
        } 
        else {
            if (pullNextVariable == 1) {
                for (int i = 0; i < 10; i++) {
                    if (strcmp(dataHolding[i].name, tac->result) == 0) {
                        dataHolding[i].variableType = varDeclHold;
                        // printf("\033[1;36mAllocated register: %s with type %s\033[0m\n", dataHolding[i].name, dataHolding[i].variableType);
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
            } else if (expr->expr.right->type == NodeType_SimpleDecimal) {
                // printf("SIMPLE EXPR EREJRJES");
                snprintf(leftBuffer, 20, "%f", expr->expr.right->simpleDecimal.number);
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
            } else if (expr->expr.right->type == NodeType_SimpleDecimal) {
                // printf("SIMPLE EXPR EREJRJES");
                snprintf(rightBuffer, 20, "%f", expr->expr.right->simpleDecimal.number);
            } 
            // else {
            //     printf("NOTHING EREJRJES");
            // }

            // printf("\n\n\n%s %c %s\nEREOROROORE\n\n", leftBuffer, expr->expr.operator, rightBuffer);
            
            if (expr->expr.left->type == NodeType_SimpleExpr || expr->expr.right->type == NodeType_SimpleDecimal) {
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
                    for (int i = 0; i < 10; i++) {
                        printf("%s: %s\n", dataHolding[i].name, dataHolding[i].variableType);
                    }
                    // printf("%s NOT IN SYSTEM\n", leftBuffer);
                    instruction->arg1 = createOperand(expr->expr.left);
                } else {
                    instruction->arg1 = dataHolding[dataInSystem(leftBuffer)].name;
                }
            } else {
                // printf("\033[1;36mLEFT BUFFER IS NULL\033[0m\n");
                instruction->arg1 = lastArgument;
            }

            if (expr->expr.right->type == NodeType_SimpleExpr || expr->expr.right->type == NodeType_SimpleDecimal) {
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
            if (strcmp(expr->expr.operator, "+") == 0) {
                instruction->op = strdup("+");
            } else if (strcmp(expr->expr.operator, "-") == 0) {
                instruction->op = strdup("-");
            } else if (strcmp(expr->expr.operator, "*") == 0) {
                instruction->op = strdup("*");
            } else if (strcmp(expr->expr.operator, "/") == 0) {
                instruction->op = strdup("/");
            } else if (strcmp(expr->expr.operator, "==") == 0) {
                instruction->op = strdup("==");
            } else if (strcmp(expr->expr.operator, ">") == 0) {
                instruction->op = strdup(">");
            } else if (strcmp(expr->expr.operator, "<") == 0) {
                instruction->op = strdup("<");
            } else if (strcmp(expr->expr.operator, ">=") == 0) {
                instruction->op = strdup(">=");
            } else if (strcmp(expr->expr.operator, "<=") == 0) {
                instruction->op = strdup("<=");
            } else if (strcmp(expr->expr.operator, "!=") == 0) {
                instruction->op = strdup("!=");
            } else {
                printf("Invalid operator (%s)\n", expr->expr.operator);
            }
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
                // printf("Variable already allocated\n");
                instruction->result = variablesInSystem[isVariableInSystem(instruction->arg1)].name;
                // return NULL;
            }
            break;
        }

        case NodeType_SimpleString: {
            // printf("SIMPLE String GENERATION\n");
            instruction->arg1 = expr->simpleString.name;
            instruction->op = "="; //strdup(expr->expr.operator);
            instruction->arg2 = NULL;
            if (isVariableInSystem(instruction->arg1) == -1) {
                // printf("CREATING TEMP VAR\n");
                int temp = getNextAvailableTempVar(tempVars);
                tempRegisterData[temp].variableType = "asciiz";
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
                // printf("Variable already allocated\n");
                instruction->result = variablesInSystem[isVariableInSystem(instruction->arg1)].name;
                // return NULL;
            }
            break;
        }

        case NodeType_SimpleDecimal: {
            // printf("SIMPLE DECIMAL GENERATION\n");
            // printf("\033[1;32mThis is green text\033[0m\n");
            // printf("Generating TAC for simple expression\n");
            char buffer[20];
            snprintf(buffer, 20, "%f", expr->simpleDecimal.number);
            instruction->arg1 = strdup(buffer);
            instruction->op = "="; //strdup(expr->expr.operator);
            instruction->arg2 = NULL;
            if (isVariableInSystem(instruction->arg1) == -1) {
                // printf("CREATING TEMP VAR\n");
                int temp = getNextAvailableTempVar(tempVars);
                tempRegisterData[temp].variableType = "float";
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
                // printf("Variable already allocated\n");
                instruction->result = variablesInSystem[isVariableInSystem(instruction->arg1)].name;
                // return NULL;
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
TAC* generateTACForParam(char* paramName) {
    // printf("GENERATING PARAM\n");
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    // printf("STILL GENERATION\n");

    instruction->arg1 = paramName;
    instruction->op = strdup("=");
    instruction->result = createTempVar();
    for (int i = 0; i < 10; i++) {
        if (strcmp(dataHolding[i].name, instruction->result) == 0) {
            dataHolding[i].variableType = instruction->arg1;
        }
    }
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForWhile(ASTNode* expr) {
    printf("GENERATING While\n");
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    char* leftArg = NULL;
    char* rightArg = NULL;

    // Handle based on expr's type
    if (expr->type == NodeType_SimpleID) {
        printf("Func Name: SimpleID\n");
        leftArg = expr->simpleID.name;
    } else if (expr->type == NodeType_SimpleExpr) {
        printf("Func Name: SimpleExpr\n");
        char buffer[20];
        snprintf(buffer, 20, "%d", expr->simpleExpr.number);
        leftArg =  strdup(buffer);
    } else if (expr->type == NodeType_Expr) {
        // This is likely where expr.left lives
        if (expr->expr.left && expr->expr.left->type == NodeType_SimpleID) {
            printf("Func Name: Complex SimpleID\n");
            leftArg = expr->expr.left->simpleID.name;
        } else if (expr->expr.left && expr->expr.left->type == NodeType_SimpleExpr) {
            printf("Func Name: Complex SimpleExpr\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->expr.left->simpleExpr.number);
            leftArg = strdup(buffer);
        } else if (expr->expr.left && expr->expr.left->type == NodeType_SimpleString) {
            printf("Func Name: Complex SimpleString\n");
            leftArg = expr->expr.left->simpleString.name;
        } else {
            printf("Unknown left expr type\n");
        }
        // This is likely where expr.right lives
        if (expr->expr.right && expr->expr.right->type == NodeType_SimpleID) {
            printf("Func Name: Complex SimpleID\n");
            rightArg = expr->expr.right->simpleID.name;
        } else if (expr->expr.right && expr->expr.right->type == NodeType_SimpleExpr) {
            printf("Func Name: Complex SimpleExpr\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->expr.right->simpleExpr.number);
            rightArg = strdup(buffer);
        } else if (expr->expr.right && expr->expr.right->type == NodeType_SimpleString) {
            printf("Func Name: Complex SimpleString\n");
            rightArg = expr->expr.right->simpleString.name;
        } else {
            printf("Unknown right expr type %s\n");
        }
    } else {
        printf("Unknown expr type: %d\n", expr->type);
    }

    if (expr->expr.left->type == NodeType_SimpleExpr || expr->expr.right->type == NodeType_SimpleDecimal) {
        // printf("EXPR GOOD");
        if (isVariableInSystem(leftArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", leftBuffer);
            leftArg = createOperand(expr->expr.left);
        } else {
            leftArg = variablesInSystem[isVariableInSystem(leftArg)].name;
        }
    } else if (expr->expr.left->type == NodeType_SimpleID) {
        // printf("ID GOOD");
        if (dataInSystem(leftArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", leftBuffer);
            leftArg = createOperand(expr->expr.left);
        } else {
            leftArg = dataHolding[dataInSystem(leftArg)].name;
        }
    }

    if (expr->expr.right->type == NodeType_SimpleExpr || expr->expr.right->type == NodeType_SimpleDecimal) {
        // printf("EXPR GOOD");    
        if (isVariableInSystem(rightArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", rightBuffer);
            rightArg = createOperand(expr->expr.right);
        } else {
            rightArg = variablesInSystem[isVariableInSystem(rightArg)].name;
        }
    } else if (expr->expr.right->type == NodeType_SimpleID) {
        // printf("ID GOOD");
        if (dataInSystem(rightArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", rightBuffer);
            rightArg = createOperand(expr->expr.right);
        } else {
            rightArg = dataHolding[dataInSystem(rightArg)].name;
        }
    }

    instruction->arg2 = rightArg;
    instruction->arg1 = leftArg;
    instruction->op = expr->expr.operator;
    instruction->result = "while";
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForIf(ASTNode* expr) {
    printf("GENERATING If\n");
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    char* leftArg = NULL;
    char* rightArg = NULL;

    // Handle based on expr's type
    if (expr->type == NodeType_SimpleID) {
        printf("Func Name: SimpleID\n");
        leftArg = expr->simpleID.name;
    } else if (expr->type == NodeType_SimpleExpr) {
        printf("Func Name: SimpleExpr\n");
        char buffer[20];
        snprintf(buffer, 20, "%d", expr->simpleExpr.number);
        leftArg =  strdup(buffer);
    } else if (expr->type == NodeType_Expr) {
        // This is likely where expr.left lives
        if (expr->expr.left && expr->expr.left->type == NodeType_SimpleID) {
            printf("Func Name: Complex SimpleID\n");
            leftArg = expr->expr.left->simpleID.name;
        } else if (expr->expr.left && expr->expr.left->type == NodeType_SimpleExpr) {
            printf("Func Name: Complex SimpleExpr\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->expr.left->simpleExpr.number);
            leftArg = strdup(buffer);
        } else if (expr->expr.left && expr->expr.left->type == NodeType_SimpleString) {
            printf("Func Name: Complex SimpleString\n");
            leftArg = expr->expr.left->simpleString.name;
        } else {
            printf("Unknown left expr type\n");
        }
        // This is likely where expr.right lives
        if (expr->expr.right && expr->expr.right->type == NodeType_SimpleID) {
            printf("Func Name: Complex SimpleID\n");
            rightArg = expr->expr.right->simpleID.name;
        } else if (expr->expr.right && expr->expr.right->type == NodeType_SimpleExpr) {
            printf("Func Name: Complex SimpleExpr\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->expr.right->simpleExpr.number);
            rightArg = strdup(buffer);
        } else if (expr->expr.right && expr->expr.right->type == NodeType_SimpleString) {
            printf("Func Name: Complex SimpleString\n");
            rightArg = expr->expr.right->simpleString.name;
        } else {
            printf("Unknown right expr type %s\n");
        }
    } else {
        printf("Unknown expr type: %d\n", expr->type);
    }

    if (expr->expr.left->type == NodeType_SimpleExpr || expr->expr.right->type == NodeType_SimpleDecimal) {
        // printf("EXPR GOOD");
        if (isVariableInSystem(leftArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", leftBuffer);
            leftArg = createOperand(expr->expr.left);
        } else {
            leftArg = variablesInSystem[isVariableInSystem(leftArg)].name;
        }
    } else if (expr->expr.left->type == NodeType_SimpleID) {
        // printf("ID GOOD");
        if (dataInSystem(leftArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", leftBuffer);
            leftArg = createOperand(expr->expr.left);
        } else {
            leftArg = dataHolding[dataInSystem(leftArg)].name;
        }
    }

    if (expr->expr.right->type == NodeType_SimpleExpr || expr->expr.right->type == NodeType_SimpleDecimal) {
        // printf("EXPR GOOD");    
        if (isVariableInSystem(rightArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", rightBuffer);
            rightArg = createOperand(expr->expr.right);
        } else {
            rightArg = variablesInSystem[isVariableInSystem(rightArg)].name;
        }
    } else if (expr->expr.right->type == NodeType_SimpleID) {
        // printf("ID GOOD");
        if (dataInSystem(rightArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", rightBuffer);
            rightArg = createOperand(expr->expr.right);
        } else {
            rightArg = dataHolding[dataInSystem(rightArg)].name;
        }
    }

    instruction->arg2 = rightArg;
    instruction->arg1 = leftArg;
    instruction->op = expr->expr.operator;
    instruction->result = "if";
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForElseIf(ASTNode* expr) {
    printf("GENERATING Else if\n");
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    char* leftArg = NULL;
    char* rightArg = NULL;

    // Handle based on expr's type
    if (expr->type == NodeType_SimpleID) {
        printf("Func Name: SimpleID\n");
        leftArg = expr->simpleID.name;
    } else if (expr->type == NodeType_SimpleExpr) {
        printf("Func Name: SimpleExpr\n");
        char buffer[20];
        snprintf(buffer, 20, "%d", expr->simpleExpr.number);
        leftArg =  strdup(buffer);
    } else if (expr->type == NodeType_Expr) {
        // This is likely where expr.left lives
        if (expr->expr.left && expr->expr.left->type == NodeType_SimpleID) {
            printf("Func Name: Complex SimpleID\n");
            leftArg = expr->expr.left->simpleID.name;
        } else if (expr->expr.left && expr->expr.left->type == NodeType_SimpleExpr) {
            printf("Func Name: Complex SimpleExpr\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->expr.left->simpleExpr.number);
            leftArg = strdup(buffer);
        } else if (expr->expr.left && expr->expr.left->type == NodeType_SimpleString) {
            printf("Func Name: Complex SimpleString\n");
            leftArg = expr->expr.left->simpleString.name;
        } else {
            printf("Unknown left expr type\n");
        }
        // This is likely where expr.right lives
        if (expr->expr.right && expr->expr.right->type == NodeType_SimpleID) {
            printf("Func Name: Complex SimpleID\n");
            rightArg = expr->expr.right->simpleID.name;
        } else if (expr->expr.right && expr->expr.right->type == NodeType_SimpleExpr) {
            printf("Func Name: Complex SimpleExpr\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->expr.right->simpleExpr.number);
            rightArg = strdup(buffer);
        } else if (expr->expr.right && expr->expr.right->type == NodeType_SimpleString) {
            printf("Func Name: Complex SimpleString\n");
            rightArg = expr->expr.right->simpleString.name;
        } else {
            printf("Unknown right expr type %s\n");
        }
    } else {
        printf("Unknown expr type: %d\n", expr->type);
    }

    if (expr->expr.left->type == NodeType_SimpleExpr || expr->expr.right->type == NodeType_SimpleDecimal) {
        // printf("EXPR GOOD");
        if (isVariableInSystem(leftArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", leftBuffer);
            leftArg = createOperand(expr->expr.left);
        } else {
            leftArg = variablesInSystem[isVariableInSystem(leftArg)].name;
        }
    } else if (expr->expr.left->type == NodeType_SimpleID) {
        // printf("ID GOOD");
        if (dataInSystem(leftArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", leftBuffer);
            leftArg = createOperand(expr->expr.left);
        } else {
            leftArg = dataHolding[dataInSystem(leftArg)].name;
        }
    }

    if (expr->expr.right->type == NodeType_SimpleExpr || expr->expr.right->type == NodeType_SimpleDecimal) {
        // printf("EXPR GOOD");    
        if (isVariableInSystem(rightArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", rightBuffer);
            rightArg = createOperand(expr->expr.right);
        } else {
            rightArg = variablesInSystem[isVariableInSystem(rightArg)].name;
        }
    } else if (expr->expr.right->type == NodeType_SimpleID) {
        // printf("ID GOOD");
        if (dataInSystem(rightArg) == -1) {
            // printf("%s NOT IN SYSTEM\n", rightBuffer);
            rightArg = createOperand(expr->expr.right);
        } else {
            rightArg = dataHolding[dataInSystem(rightArg)].name;
        }
    }

    instruction->arg2 = rightArg;
    instruction->arg1 = leftArg;
    instruction->op = expr->expr.operator;
    instruction->result = "else if";
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForElse() {
    printf("GENERATING Else\n");
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    instruction->arg2 = NULL;
    instruction->arg1 = NULL;
    instruction->op = strdup("");
    instruction->result = "else";
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForEnd() {
    printf("GENERATING End\n");
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    instruction->arg2 = NULL;
    instruction->arg1 = NULL;
    instruction->op = strdup("");
    instruction->result = "end";
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForEndLoop() {
    printf("GENERATING End loop\n");
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    instruction->arg2 = NULL;
    instruction->arg1 = NULL;
    instruction->op = strdup("");
    instruction->result = "end_loop";
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForFunc(char* funcName, char* returnType, ASTNode* paramList) {
    printf("GENERATING Func\n");
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;
    char* paramListStr = generateParamList(paramList);

    instruction->arg2 = returnType;
    instruction->arg1 = paramListStr;
    instruction->op = strdup(" -> ");
    instruction->result = funcName;
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForFuncCall(char* funcName, ASTNode* exprList) {
    printf("GENERATING Func\n");
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;
    // char* paramListStr = generateParamList(exprList);

    char* paramListStr = malloc(256);
    paramListStr[0] = '\0';

    ASTNode* exprListTraverse = exprList;

    while (exprListTraverse) {
        ASTNode* expr = exprListTraverse->exprList.expr;

        if (!expr) {
            printf("Null expr\n");
            break;
        }

        // Handle based on expr's type
        if (expr->type == NodeType_SimpleID) {
            printf("Func Name: SimpleID\n");
            strcat(paramListStr, expr->simpleID.name);
        } else if (expr->type == NodeType_SimpleExpr) {
            printf("Func Name: SimpleExpr\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->simpleExpr.number);
            strcat(paramListStr, strdup(buffer));
        } else if (expr->type == NodeType_Expr) {
            // This is likely where expr.left lives
            if (expr->expr.left && expr->expr.left->type == NodeType_SimpleID) {
                printf("Func Name: Complex SimpleID\n");
                strcat(paramListStr, expr->expr.left->simpleID.name);
            } else if (expr->expr.left && expr->expr.left->type == NodeType_SimpleExpr) {
                printf("Func Name: Complex SimpleExpr\n");
                strcat(paramListStr, expr->expr.left->simpleExpr.number);
            } else {
                printf("Unknown left expr type\n");
            }
        } else {
            printf("Unknown expr type: %d\n", expr->type);
        }

        // Only add comma if there's another node
        if (exprListTraverse->exprList.next) {
            strcat(paramListStr, ", ");
        }

        exprListTraverse = exprListTraverse->exprList.next;
    }

    instruction->arg2 = paramListStr;
    instruction->arg1 = "";
    instruction->result = funcName;
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForFuncAssign(char* varName, ASTNode* funcCall) {
    printf("GENERATING Func Assign\n");
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    // generateTACForFuncCall(funcCall->funcCall.funcName, funcCall->funcCall.exprList);

    char* paramListStr = malloc(256);
    paramListStr[0] = '\0';

    ASTNode* exprListTraverse = funcCall->funcCall.exprList;

    while (exprListTraverse) {
        ASTNode* expr = exprListTraverse->exprList.expr;

        if (!expr) {
            printf("Null expr\n");
            break;
        }

        // Handle based on expr's type
        if (expr->type == NodeType_SimpleID) {
            printf("Func Name: SimpleID\n");
            strcat(paramListStr, expr->simpleID.name);
        } else if (expr->type == NodeType_SimpleExpr) {
            printf("Func Name: SimpleExpr\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->simpleExpr.number);
            strcat(paramListStr, strdup(buffer));
        } else if (expr->type == NodeType_Expr) {
            // This is likely where expr.left lives
            if (expr->expr.left && expr->expr.left->type == NodeType_SimpleID) {
                printf("Func Name: Complex SimpleID\n");
                strcat(paramListStr, expr->expr.left->simpleID.name);
            } else if (expr->expr.left && expr->expr.left->type == NodeType_SimpleExpr) {
                printf("Func Name: Complex SimpleExpr\n");
                strcat(paramListStr, expr->expr.left->simpleExpr.number);
            } else {
                printf("Unknown left expr type\n");
            }
        } else {
            printf("Unknown expr type: %d\n", expr->type);
        }

        // Only add comma if there's another node
        if (exprListTraverse->exprList.next) {
            strcat(paramListStr, ", ");
        }

        exprListTraverse = exprListTraverse->exprList.next;
    }
    // printf("Param List: %s\n", paramListStr);

    instruction->arg2 = paramListStr;
    instruction->op = strdup(" -> ");
    instruction->arg1 = funcCall->funcCall.funcName;
    instruction->result = varName;
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
char* generateParamList(ASTNode* paramList) {
    if (!paramList) return NULL;

    char* paramListStr = (char*)malloc(100);
    if (!paramListStr) return NULL;

    while (paramList->paramDeclList.paramDecl != NULL) {
        // strcat(paramListStr, paramList->paramDeclList.paramDecl->paramDecl.paramType);
        // strcat(paramListStr, " ");
        strcat(paramListStr, paramList->paramDeclList.paramDecl->paramDecl.paramName);
        if (paramList->paramDeclList.paramDeclList == NULL) break;
        strcat(paramListStr, ", ");
        paramList = paramList->paramDeclList.paramDeclList;
    }
    // printf("PARAM LIST: %s\n", paramListStr);
    if (strcmp(paramListStr, "") == 0) {
        return "EMPTY";
    }
    return paramListStr;
}
TAC* generateTACForReturn(ASTNode* expr, ASTNode* varName) {
    // Depending on your AST structure, generate the appropriate TAC
    // If the TAC is generated successfully, append it to the global TAC list
    // Return the generated TAC, so that it can be used by the caller, e.g. for printing
    if (!expr) return NULL;

    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    // printf("Generating TAC for print statement %s\n", varName);
    // printf("Generating TAC for print expression %s\n", expr->simpleID.name);

    if(strcmp(varName, "return") == 0) {
        instruction->arg1 = strdup(varName);
        if (expr->type == NodeType_SimpleID) {
            if (dataInSystem(expr->simpleID.name) != -1) {
                instruction->arg2 = dataHolding[dataInSystem(expr->simpleID.name)].name;
            } else {
                instruction->arg2 = strdup(expr->simpleID.name);
            }
        } else if (expr->type == NodeType_SimpleExpr) {
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->simpleExpr.number);
            instruction->arg2 = strdup(buffer);
        }  else if (expr->type == NodeType_SimpleDecimal) {
            char buffer[20];
            snprintf(buffer, 20, "%f", expr->simpleDecimal.number);
            instruction->arg2 = strdup(buffer);
        } else if (expr->type == NodeType_Expr) {
            if (findAllocatedRegister(varDeclHold) != -1) {
                lastArgument = dataHolding[findAllocatedRegister(varDeclHold)].name;
            }
            instruction->arg2 = lastArgument;       
        } else if (expr->type == NodeType_SimpleString) {
            if (dataInSystem(expr->simpleString.name) != -1) {
                instruction->arg2 = dataHolding[dataInSystem(expr->simpleString.name)].name;
            } else {
                instruction->arg2 = strdup(expr->simpleString.name);
            }
        } else if (expr->type == NodeType_Array) {
            char elementName[50];
            snprintf(elementName, 50, "%s[%d]", expr->array.arrName, expr->array.arrIndex);
            
            if (dataInSystem(elementName) != -1) {
                instruction->arg2 = dataHolding[dataInSystem(elementName)].name;
            } else {
                // Generate array access TAC and use its result
                TAC* accessTAC = generateTACForArrayAccess(expr);
                instruction->arg2 = accessTAC->result;
            }
        } else {
            printf("\n\n\n------------------FOUND: SOMETHING ELSE------------------\n\n\n");
        }
        instruction->op = strdup(""); //strdup(expr->expr.operator);
    } else{
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
        //     printf("\n\n\n------------------FOUND: SIMPLEID %s------------------\n\n\n", expr->simpleID.name);
        // } else if (expr->type == NodeType_SimpleExpr) {
        //     printf("\n\n\n------------------FOUND: SIMPLEEXPR------------------\n\n\n");        
        // } else if (expr->type == NodeType_Expr) {
        //     printf("\n\n\n------------------FOUND: EXPR------------------\n\n\n");        
        // } else {
        //     printf("\n\n\n------------------FOUND: SOMETHING ELSE------------------\n\n\n");
        // }
        instruction->arg1 = strdup(varName);
        if (expr->type == NodeType_SimpleID) {
            // printf("\n\n\n------------------FOUND: SIMPLEID2 %s------------------\n\n\n", expr->simpleID.name);
            if (dataInSystem(expr->simpleID.name) != -1) {
                // printf("\n\n\n------------------FOUND: SIMPLEID2 %s------------------\n\n\n", expr->simpleID.name);
                instruction->arg2 = dataHolding[dataInSystem(expr->simpleID.name)].name;
            } else {
                // printf("\n\n\n------------------NOT FOUND: SIMPLEID2 %s------------------\n\n\n", expr->simpleID.name);
                instruction->arg2 = strdup(expr->simpleID.name);
            }
        } else if (expr->type == NodeType_SimpleExpr) {
            // printf("\n\n\n------------------FOUND: SIMPLEEXPR------------------\n\n\n");
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->simpleExpr.number);
            instruction->arg2 = strdup(buffer);
        }  else if (expr->type == NodeType_SimpleDecimal) {
            // printf("\n\n\n------------------FOUND: SIMPLEEXPR------------------\n\n\n");
            char buffer[20];
            snprintf(buffer, 20, "%f", expr->simpleDecimal.number);
            instruction->arg2 = strdup(buffer);
        } else if (expr->type == NodeType_Expr) {
            // if (varDeclHold == NULL) {
            //     printf("\033[1;34mVarDeclHold IS NULL\033[0m\n");
            // }
            // printf("%s", varDeclHold);
            if (findAllocatedRegister(varDeclHold) != -1) {
                // printf("\033[1;34mVarDeclHold FOUND %s\033[0m\n", varDeclHold);
                lastArgument = dataHolding[findAllocatedRegister(varDeclHold)].name;
            }
            instruction->arg2 = lastArgument;
            // printf("\n\n\n------------------FOUND: EXPR------------------\n\n\n");
            // exit(0);        
        } else if (expr->type == NodeType_SimpleString) {
            if (dataInSystem(expr->simpleString.name) != -1) {
                instruction->arg2 = dataHolding[dataInSystem(expr->simpleString.name)].name;
            } else {
                instruction->arg2 = strdup(expr->simpleString.name);
            }
        } else if (expr->type == NodeType_Array) {
            char elementName[50];
            snprintf(elementName, 50, "%s[%d]", expr->array.arrName, expr->array.arrIndex);
            
            if (dataInSystem(elementName) != -1) {
                instruction->arg2 = dataHolding[dataInSystem(elementName)].name;
            } else {
                // Generate array access TAC and use its result
                TAC* accessTAC = generateTACForArrayAccess(expr);
                instruction->arg2 = accessTAC->result;
            }
        } else {
            printf("\n\n\n------------------FOUND: SOMETHING ELSE------------------\n\n\n");
        }
        instruction->op = strdup(""); //strdup(expr->expr.operator);
    } else{
        // printf("\n\n\n------------------FOUND: %s------------------\n\n\n", varName);
        free(instruction);
        return NULL;
    }

    // printf("\033[1;34mGenerating TAC for print statement %s\033[0m\n", varName);
    printTAC(instruction);
    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForMain(char* funcName) {
    printf("GENERATING Func\n");
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    instruction->op = "";
    instruction->result = funcName;
    printTAC(instruction);

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
TAC* generateTACForArrayAccess(ASTNode* arrayNode) {
    if (!arrayNode || arrayNode->type != NodeType_Array) return NULL;
    char elementName[50];
    snprintf(elementName, 50, "%s[%d]", arrayNode->array.arrName, arrayNode->array.arrIndex);

    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    // Generate code to calculate array index and access
    char* arrayName = elementName;
    int arrayIndex = arrayNode->array.arrIndex;
    
    // Create a string representation of the index
    char indexStr[20];
    snprintf(indexStr, 20, "%d", arrayIndex);
    
    // Generate array access instruction
    instruction->op = strdup("=");
    instruction->arg1 = strdup(arrayName);
    instruction->arg2 = NULL;
    instruction->result = createTempVar();
    
    instruction->next = NULL;
    appendTAC(&tacHead, instruction);
    return instruction;
}

TAC* generateTACForArrayAssignment(ASTNode* arrayNode, ASTNode* exprNode) {
    if (!arrayNode || arrayNode->type != NodeType_Array || !exprNode) return NULL;

    // First generate TAC for the expression
    TAC* exprTAC = generateTACForExpr(exprNode);
    
    // Then generate TAC for the array assignment
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;
    
    char* arrayName = arrayNode->array.arrName;
    int arrayIndex = arrayNode->array.arrIndex;
    
    // Create a string representation of the index
    char indexStr[20];
    snprintf(indexStr, 20, "%d", arrayIndex);

    // printf("\033[1;34mGenerating TAC for array assignment %s[%d] = %s\033[0m\n", arrayName, arrayIndex, exprTAC->result);
    
    // Generate array assignment instruction
    instruction->op = strdup("=");
    instruction->result = strdup(arrayName);
    instruction->arg2 = NULL;
    instruction->arg1 = exprTAC->result;
    
    instruction->next = NULL;
    appendTAC(&tacHead, instruction);
    return instruction;
}

TAC* generateTACForArrayPrint(ASTNode* arrayNode, char* printStmt) {
    if (!arrayNode || arrayNode->type != NodeType_Array) return NULL;

    // First generate TAC for the array access
    TAC* accessTAC = generateTACForArrayAccess(arrayNode);
    
    // Then generate TAC for the print statement
    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;
    
    instruction->op = strdup("");
    instruction->arg1 = strdup(printStmt);
    instruction->arg2 = accessTAC->result;
    instruction->result = NULL;
    
    instruction->next = NULL;
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

        case NodeType_SimpleDecimal: {
            char* buffer = malloc(20);
            snprintf(buffer, 20, "%f", node->simpleDecimal.number);
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
        printf("\n--- CURRENT INSTRUCTION %s = %s %s %s ---\n", current->result, current->arg1, current->op, current->arg2);
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

int getNextAvailableReturnValue() {
   // implement the temp var allocation logic
   // use the tempVars array to keep track of allocated temp vars

    // search for the next available temp var
    for (int i = 0; i < 10; i++) {
        if (returnRegisters[i].variableType == "") {
            return i;
        }
    }
    return -1; // No available temp var
}

int getNextAvailableReturnName() {
   // implement the temp var allocation logic
   // use the tempVars array to keep track of allocated temp vars

    // search for the next available temp var
    for (int i = 0; i < 10; i++) {
        if (returnRegisters[i].name == "") {
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
