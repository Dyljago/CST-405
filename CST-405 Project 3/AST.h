#ifndef AST_H
#define AST_H

// Include standard libraries as needed, e.g., stdlib 
// for memory management functions
#include <stdlib.h>
#include <stdio.h>

// NodeType enum to differentiate between different 
// kinds of AST nodes
typedef enum { 
    NodeType_Program,
    NodeType_Body,
    NodeType_Main,
    NodeType_ParamDecl,
    NodeType_ParamDeclList,
    NodeType_FuncDeclList,
    NodeType_FuncDecl,
    NodeType_FuncCall,
    NodeType_FuncCallAssign,
    NodeType_VarDeclList, 
    NodeType_VarDecl,
    NodeType_ArrDecl,
    NodeType_VarDeclAssign, 
    NodeType_ArrDeclAssign, 
    NodeType_SimpleExpr,
    NodeType_SimpleDecimal,
    NodeType_SimpleID,
    NodeType_SimpleString,
    NodeType_Expr, 
    NodeType_Array,
    NodeType_StmtList,
    NodeType_AssignStmt,
    NodeType_PrintStmt,
    NodeType_ReturnStmt,
    NodeType_ArrPrintStmt,
    NodeType_BinOp, 
    NodeType_ExprList,
} NodeType;

// Structure for AST nodes
typedef struct ASTNode {
    NodeType type;
    union {
        struct{
            struct ASTNode* funcDeclList;
            struct ASTNode* mainFunc;
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
            struct ASTNode* paramList;
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

        struct{
            struct ASTNode* varDeclList;
            struct ASTNode* stmtList;
        } body;

        struct {
            struct ASTNode* paramDecl;
            struct ASTNode* paramDeclList;
        } paramDeclList;

        struct {
            char* paramType;
            char* paramName;
        } paramDecl;

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
            char* varType;
            char* varName;
            struct ASTNode* varAssign;
        } varDeclAssign;

        struct {
            char* operator; // e.g., '='
            struct ASTNode* expr;
            struct ASTNode* array;
        } arrAssignStmt;

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
            // Expression-specific fields
            char operator;  // Example for an operator field
            struct ASTNode* left;  // Left operand
            struct ASTNode* right; // Right operand
        } expr;

        struct {
            char* arrName;
            int arrIndex;
        } array;

        struct {
            // StatementList-specific fields
            struct ASTNode* stmt;
            struct ASTNode*  stmtList; 
            // Example for linking statements in a list
        } stmtList;

        struct {
            char* operator; // e.g., '='
            char* varName;
            struct ASTNode* expr;
        } assignStmt;

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

// Function prototypes for AST handling
ASTNode* createNode(NodeType type);
void freeAST(ASTNode* node);
void traverseAST(ASTNode* node, int level);

#endif // AST_H
