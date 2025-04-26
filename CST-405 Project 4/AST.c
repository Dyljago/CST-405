#include "AST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int indentValue = 2;

void printIndent(int level) {
    // printf("Indent level: %d\n", level);
    for (int i = 0; i < level-1; i++) {
        printf("--");
    }
}


void traverseAST(ASTNode* node, int level) {
    if (!node) {
        // printIndent(level);
        // printf ("Nothing to traverse\n");
        return;
    }

    // printIndent(level);
    // printf("Traversing node of type %d\n", node->type);
    // const char *NodeTypeNames[] = {
    //     "Program",
    //     "VarDeclList",
    //     "VarDecl",
    //     "VarDeclAssign",
    //     "SimpleExpr",
    //     "SimpleID",
    //     "Expr",
    //     "StmtList",
    //     "AssignStmt",
    //     "PrintStmt",
    //     "BinOp"
    // };

    // printf("Traversing node of type %s\n", NodeTypeNames[node->type]);
    switch (node->type) {
    typedef struct ASTNode {
        int type; // Add the "type" field
        union {
            struct {
                struct ASTNode* mainFunc;
                struct ASTNode* funcDeclList;
            } program;
            struct{
                struct ASTNode* body;
                char* funcName;
            } mainFunc;
            struct {
                struct ASTNode* funcDecl;
                struct ASTNode* funcDeclList;
            } funcDeclList;
            struct{
                struct ASTNode* body;
                char* funcName;
                char* paramList;
                char* returnType;
            } funcDecl;
            struct{
                char* funcName;
                struct ASTNode* exprList;
            } funcCall;
            struct {
                char* operator; // e.g., '='
                char* varName;
                struct ASTNode* funcCall;
            } funcAssignStmt;
            struct {
                struct ASTNode* paramDecl;
                struct ASTNode* paramDeclList;
            } paramDeclList;
            struct {
                char* paramType;
                char* paramName;
            } paramDecl;
            struct {
                struct ASTNode* expr;
                struct ASTNode* body;
                struct ASTNode* elseIfStatement;
                struct ASTNode* elseStmt;
            } ifStatement;
            struct {
                struct ASTNode* expr;
                struct ASTNode* body;
                struct ASTNode* elseIfStatement;
            } elseIfStatement;
            struct {
                struct ASTNode* body;
            } elseStatement;
            struct {
                struct ASTNode* varDeclList;
                struct ASTNode* stmtList;
            } body;
            struct {
                struct ASTNode* varDecl;
                struct ASTNode* varDeclList;
            } varDeclList;
            struct {
                char* varType;
                char* varName;
            } varDecl;
            struct {
                char* varType;
                struct ASTNode* array;
                struct ASTNode* exprList;
            } arrDecl;
            struct {
                struct ASTNode* expr;
                struct ASTNode* next;
            } exprList;
            struct {
                int number;
            } simpleExpr;
            struct {
                float number;
            } simpleDecimal;
            struct {
                char* name;
            } simpleID;
            struct {
                char* name;
            } simpleString;
            struct {
                char* operator;
                struct ASTNode* left;
                struct ASTNode* right;
            } expr;
            struct {
                char* arrName;
                int arrIndex;
            } array;
            struct {
                struct ASTNode* stmt;
                struct ASTNode* stmtList;
            } stmtList;
            struct {
                char* varName;
                char* operator;
                struct ASTNode* expr;
            } assignStmt;
            struct {
                char* operator; // e.g., '='
                struct ASTNode* expr;
                struct ASTNode* arrDecl;
            } arrAssignStmt;
            struct {
                char* varName;
                struct ASTNode* expr;
            } printStmt;
            struct {
                char* varName;
                struct ASTNode* expr;
            } returnStmt;
            struct {
                char* varName;
                struct ASTNode* array;
            } arrPrintStmt;
            struct {
                char operator;
                struct ASTNode* left;
                struct ASTNode* right;
            } binOp;
        };
    } ASTNode;
        case NodeType_Program:
            printIndent(level);
            printf("Program\n");
            traverseAST(node->program.funcDeclList, level + 2);
            traverseAST(node->program.mainFunc, level + 2);
            break;
        case NodeType_Body:
            printIndent(level);
            printf("Body\n");
            if (node->body.varDeclList) {
                traverseAST(node->body.varDeclList, level+1);
            }
            if (node->body.stmtList) {
                traverseAST(node->body.stmtList, level+1);
            }
            break;
        case NodeType_Main:
            printIndent(level);
            printf("Main Func\n");
            traverseAST(node->mainFunc.body, level+1);
            break;
        case NodeType_FuncDeclList:
            printIndent(level);
            printf("FuncDeclList\n");
            traverseAST(node->funcDeclList.funcDecl, level + 1);
            traverseAST(node->funcDeclList.funcDeclList, level);
            break;
        case NodeType_FuncDecl:
            printIndent(level);
            printf("%s Func\n", node->funcDecl.funcName);
            traverseAST(node->funcDecl.body, level+1);
            break;
        case NodeType_FuncCall:
            printIndent(level);
            printf("%s Func\n", node->funcCall.funcName);
            traverseAST(node->funcCall.exprList, level+1);
            break;
        case NodeType_FuncCallAssign:
            printIndent(level);
            printf("Stmt: %s = \n", node->funcAssignStmt.varName);
            traverseAST(node->funcAssignStmt.funcCall, level+1);
            break;
        case NodeType_ParamDeclList:
            printIndent(level);
            printf("ParamDeclList\n");
            // printf("ParamDecl: %s %s\n", node->varDeclList.varDecl->varDecl.varType, node->varDeclList.varDecl->varDecl.varName);
            traverseAST(node->paramDeclList.paramDecl, level + 1);
            traverseAST(node->paramDeclList.paramDeclList, level);
            break;
        case NodeType_ParamDecl:
            printIndent(level);
            printf("ParamDecl: %s %s\n", node->paramDecl.paramType, node->paramDecl.paramName);
            break;
        case NodeType_VarDeclList:
            printIndent(level);
            printf("VarDeclList\n");
            if (node->varDeclList.varDecl != NULL) {
                printf("VarDecl: %s %s\n", node->varDeclList.varDecl->varDecl.varType, node->varDeclList.varDecl->varDecl.varName);
            }
            traverseAST(node->varDeclList.varDecl, level + 1);
            traverseAST(node->varDeclList.varDeclList, level);
            break;
        case NodeType_VarDecl:
            printIndent(level);
            printf("VarDecl: %s %s\n", node->varDecl.varType, node->varDecl.varName);
            break;
        case NodeType_ArrDecl:
            printIndent(level);
            printf("ArrDecl: %s\n", node->arrDecl.varType);
            traverseAST(node->arrDecl.array, level + 1);
            if (node->arrDecl.exprList != NULL) {
                printIndent(level);
                printf("Initialization values:\n");
                traverseAST(node->arrDecl.exprList, level + 1);
            }
            break;
        case NodeType_ExprList:
            traverseAST(node->exprList.expr, level);
            if (node->exprList.next != NULL) {
                traverseAST(node->exprList.next, level);
            }
            break;
        case NodeType_IfStmt:
            printIndent(level);
            printf("If Statement: \n");
            traverseAST(node->ifStatement.expr, level);
            traverseAST(node->ifStatement.body, level + 1);
            if (node->ifStatement.elseIfStatement != NULL) {
                traverseAST(node->ifStatement.elseIfStatement, level + 1);
            }
            if (node->ifStatement.elseStatement != NULL) {
                traverseAST(node->ifStatement.elseStatement, level + 1);
            }
            break;
        case NodeType_ElseIfStmt:
            printIndent(level);
            printf("Else If Statement: \n");
            traverseAST(node->elseIfStatement.expr, level);
            traverseAST(node->elseIfStatement.body, level + 1);
            if (node->elseIfStatement.elseIfStatement != NULL) {
                traverseAST(node->elseIfStatement.elseIfStatement, level + 1);
            }
            break;
        case NodeType_ElseStmt:
            printIndent(level);
            printf("Else Statement: \n");
            traverseAST(node->elseStatement.body, level+1);
            break;
        case NodeType_SimpleExpr:
            printIndent(level);
            //printf("SimpleExpr: %d\n", node->simpleExpr.number);
            printf("%d\n", node->simpleExpr.number);
            break;
        case NodeType_SimpleDecimal:
            printIndent(level);
            printf("%f\n", node->simpleDecimal.number);
            break;
        case NodeType_SimpleID:
            printIndent(level);
            //printf("SimpleID: %d\n", node->simpleID.name);
            printf("%s\n", node->simpleID.name);
            break;
        case NodeType_SimpleString:
            printIndent(level);
            //printf("SimpleString: %d\n", node->simpleString.name);
            printf("%s\n", node->simpleString.name);
            break;
        case NodeType_Expr:
            printIndent(level);
            printf("Expr: %s\n", node->expr.operator);
            traverseAST(node->expr.left, level + 1);
            traverseAST(node->expr.right, level + 1);
            break;
        case NodeType_Array:
            printIndent(level);
            printf("Array: %s[%d]\n", node->array.arrName, node->array.arrIndex);
            break;
        case NodeType_StmtList:
            // printIndent(level);
            traverseAST(node->stmtList.stmt, level);
            traverseAST(node->stmtList.stmtList, level);
            break;
        case NodeType_AssignStmt:
            printIndent(level);
            printf("Stmt: %s = \n", node->assignStmt.varName);
            traverseAST(node->assignStmt.expr, level + 1);
            break;
        case NodeType_ArrDeclAssign:
            printIndent(level);
            printf("Array Assign Stmt: %s \n", node->arrAssignStmt.operator);
            traverseAST(node->arrAssignStmt.array, level + 1);
            traverseAST(node->arrAssignStmt.expr, level + 1);
            break;
        case NodeType_PrintStmt:
            printIndent(level);
            printf("Stmt: %s \n", node->printStmt.varName);
            traverseAST(node->printStmt.expr, level + 1);
            break;
        case NodeType_ReturnStmt:
            printIndent(level);
            printf("Stmt: %s \n", node->returnStmt.varName);
            traverseAST(node->returnStmt.expr, level + 1);
            break;
        case NodeType_ArrPrintStmt:
            printIndent(level);
            printf("Stmt: %s \n", node->arrPrintStmt.varName);
            traverseAST(node->arrPrintStmt.array, level + 1);
            break;
        case NodeType_BinOp:
            printIndent(level);
            printf("BinOp: %s\n", node->binOp.operator);
            traverseAST(node->binOp.left, level + 1);
            traverseAST(node->binOp.right, level + 1);
            break;
        default:
            printf("Unknown node type: %d\n", node->type);
            break;
    }
}

void freeAST(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NodeType_Program:
            free(node->program.mainFunc);
            break;
        case NodeType_Body:
            free(node->body.varDeclList);
            free(node->body.stmtList);
            break;
        case NodeType_Main:
            free(node->mainFunc.body);
            break;
        case NodeType_FuncDecl:
            free(node->funcDecl.body);
            // free(node->funcDecl.funcName);
            free(node->funcDecl.paramList);
            // free(node->funcDecl.returnType);
            break;
        case NodeType_FuncCall:
            // free(node->funcCall.funcName);
            free(node->funcCall.exprList);
            break;
        case NodeType_FuncCallAssign:
            // free(node->funcCall.funcName);
            free(node->funcAssignStmt.funcCall);
            break;
        case NodeType_FuncDeclList:
            free(node->funcDeclList.funcDecl);
            free(node->funcDeclList.funcDeclList);
            break;
        case NodeType_ParamDecl:
            // free(node->paramDecl.paramName);
            // free(node->paramDecl.paramType);
            break;
        case NodeType_ParamDeclList:
            free(node->paramDeclList.paramDecl);
            free(node->paramDeclList.paramDeclList);
            break;
        case NodeType_VarDeclList:
            free(node->varDeclList.varDecl);
            free(node->varDeclList.varDeclList);
            break;
        case NodeType_VarDecl:
            free(node->varDecl.varType);
            free(node->varDecl.varName);
            break;
        case NodeType_ArrDecl:
            free(node->arrDecl.varType);
            free(node->arrDecl.array);
            freeAST(node->arrDecl.exprList);
            //free(node->arrDecl.arrSize);
            break;
        case NodeType_SimpleExpr:
            //free((node->simpleExpr));
            break;
        case NodeType_SimpleDecimal:
            //free((node->simpleExpr));
            break;
        case NodeType_SimpleID:
            //free((node->simpleID));
            break;
        case NodeType_SimpleString:
            //free((node->simpleString));
            break;
        case NodeType_Expr:
            free(node->expr.left);
            free(node->expr.right);
            //free(node->expr.operator);
            break;
        case NodeType_Array:
            free(node->array.arrName);
            // free(node->array.arrIndex);
            break;
        case NodeType_ExprList:
            freeAST(node->exprList.expr);
            freeAST(node->exprList.next);
            break;
        case NodeType_IfStmt:
            freeAST(node->ifStatement.expr);
            freeAST(node->ifStatement.body);
            freeAST(node->ifStatement.elseIfStatement);
            freeAST(node->ifStatement.elseStatement);
            break;
        case NodeType_ElseIfStmt:
            freeAST(node->elseIfStatement.expr);
            freeAST(node->elseIfStatement.body);
            freeAST(node->elseIfStatement.elseIfStatement);
            break;
        case NodeType_ElseStmt:
            freeAST(node->elseStatement.body);
            break;
        case NodeType_StmtList:
            free(node->stmtList.stmt);
            free(node->stmtList.stmtList);
            break;
        case NodeType_AssignStmt:
            free(node->assignStmt.varName);
            free(node->assignStmt.operator);
            free(node->assignStmt.expr);
            break;
        case NodeType_ArrDeclAssign:
            free(node->arrAssignStmt.expr);
            free(node->arrAssignStmt.operator);
            free(node->arrAssignStmt.array);
            break;
        case NodeType_PrintStmt:
            free(node->printStmt.varName);
            free(node->printStmt.expr);
            break;
        case NodeType_ReturnStmt:
            free(node->returnStmt.varName);
            free(node->returnStmt.expr);
            break;
        case NodeType_BinOp:
            free(node->binOp.left);
            free(node->binOp.right);
            //free(node->binOp.operator);
            break;
    }

    free(node);
}

ASTNode* createNode(NodeType type) {
    ASTNode* newNode = (ASTNode*)malloc(sizeof(ASTNode));
    if (newNode == NULL) {
        // Handle memory allocation failure if needed
        return NULL;
    }

    newNode->type = type;

    // Initialize the node based on its type
    switch (type) {
        case NodeType_Program:
            newNode->program.mainFunc = NULL;
            break;
        case NodeType_Body:
            newNode->body.varDeclList = NULL;
            newNode->body.stmtList = NULL;
            break;
        case NodeType_Main:
            newNode->mainFunc.body = NULL;
            newNode->mainFunc.funcName = '\0';
            break;
        case NodeType_FuncDecl:
            newNode->funcDecl.body = NULL;
            newNode->funcDecl.funcName = '\0';
            newNode->funcDecl.paramList = NULL;
            newNode->funcDecl.returnType = '\0';
            break;
        case NodeType_FuncCall:
            newNode->funcCall.exprList = NULL;
            newNode->funcCall.funcName = '\0';
            break;
        case NodeType_FuncCallAssign:
            newNode->funcAssignStmt.funcCall = NULL;
            newNode->funcAssignStmt.varName = '\0';
            newNode->funcAssignStmt.operator = '\0';
            break;
        case NodeType_FuncDeclList:
            newNode->funcDeclList.funcDecl = NULL;
            newNode->funcDeclList.funcDeclList = NULL;
            break;
        case NodeType_ParamDecl:
            newNode->paramDecl.paramName = '\0';
            newNode->paramDecl.paramType = '\0';
            break;
        case NodeType_ParamDeclList:
            newNode->paramDeclList.paramDecl = NULL;
            newNode->paramDeclList.paramDeclList = NULL;
            break;
        case NodeType_VarDeclList:
            newNode->varDeclList.varDecl = NULL;
            newNode->varDeclList.varDeclList = NULL;
            break;
        case NodeType_VarDecl:
            newNode->varDecl.varType = NULL;
            newNode->varDecl.varName = NULL;
            break;
        case NodeType_ArrDecl:
            newNode->arrDecl.varType = NULL;
            newNode->arrDecl.array = NULL;
            newNode->arrDecl.exprList = NULL;
            break;
        case NodeType_SimpleExpr:
            // Initialize the number to NULL
            newNode->simpleExpr.number = '\0';
            break;
        case NodeType_SimpleDecimal:
            // Initialize the number to NULL
            newNode->simpleDecimal.number = '\0';
            break;
        case NodeType_SimpleID:
            //newNode->simpleID.name = NULL;
            break;
        case NodeType_SimpleString:
            //newNode->simpleString.name = NULL;
            break;
        case NodeType_Expr:
            newNode->expr.operator = '\0';  // Placeholder value
            newNode->expr.left = NULL;
            newNode->expr.right = NULL;
            break;
        case NodeType_Array:
            newNode->array.arrIndex = '\0';  // Placeholder value
            newNode->array.arrName = NULL;
            break;
        case NodeType_ExprList:
            newNode->exprList.expr = NULL;  // Example initialization
            newNode->exprList.next = NULL;
            break;
        case NodeType_IfStmt:
            newNode->ifStatement.expr = NULL;
            newNode->ifStatement.body = NULL;
            newNode->ifStatement.elseIfStatement = NULL;
            newNode->ifStatement.elseStatement = NULL;
            break;
        case NodeType_ElseIfStmt:
            newNode->elseIfStatement.expr = NULL;
            newNode->elseIfStatement.body = NULL;
            newNode->elseIfStatement.elseIfStatement = NULL;
            break;
        case NodeType_ElseStmt:
            newNode->elseStatement.body = NULL;
            break;
        case NodeType_StmtList:
            newNode->stmtList.stmt = NULL;  // Example initialization
            newNode->stmtList.stmtList = NULL;
            break;
        case NodeType_AssignStmt:
            newNode->assignStmt.operator = NULL;  // Example initialization
            newNode->assignStmt.varName = NULL;
            newNode->assignStmt.expr = NULL;
            break;
        case NodeType_ArrDeclAssign:
            newNode->arrAssignStmt.operator = NULL;  // Example initialization
            newNode->arrAssignStmt.expr = NULL;
            newNode->arrAssignStmt.array = NULL;
            break;
        case NodeType_PrintStmt:
            newNode->printStmt.varName = NULL;
            newNode->printStmt.expr = NULL;
            break;
        case NodeType_ReturnStmt:
            newNode->returnStmt.varName = NULL;
            newNode->returnStmt.expr = NULL;
            break;
        case NodeType_BinOp:
            newNode->binOp.operator = '\0';  // Placeholder value
            newNode->binOp.left = NULL;
            newNode->binOp.right = NULL;
            break;
        // Add more cases as necessary for other node types
    }

    return newNode;
}