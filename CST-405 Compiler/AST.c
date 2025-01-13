#include "AST.h"
int indentValue = 2;

void printIndent(int level) {
    for (int i = 0; i < level-1; i++) {
        printf("--");
    }
}


void traverseAST(ASTNode* node, int level) {
    if (!node) {
        printf ("Nothing to traverse\n");
        return;
    }

    printIndent(level);
    //printf("Traversing node of type %d\n", node->type);
    
    // Traverse the node based on its type
    // Switch statement is used to determine the type of the node
}

void freeAST(ASTNode* node) {
    if (!node) return;

    //printf("Freeing node of type %d\n", node->type);

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
  
        // Add more cases as necessary for other node types

    return newNode;
}