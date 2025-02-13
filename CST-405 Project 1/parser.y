%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "symbolTable.h"
#include "semantic.h"
#include "codeGenerator.h"
#include "optimizer.h"

#define TABLE_SIZE 100

extern int yylex();   // Declare yylex, the lexer function
extern int yyparse(); // Declare yyparse, the parser function
extern FILE* yyin;    // Declare yyin, the file pointer for the input file
extern int yylineno;  // Declare yylineno, the line number counter
extern TAC* tacHead;  // Declare the head of the linked list of TAC entries

void yyerror(const char* s);

ASTNode* root = NULL; 
SymbolTable* symTab = NULL;
Symbol* symbol = NULL;

%}

%union {
	int number;
	char character;
	char* string;
	char* operator;
	struct ASTNode* ast;
}

// Base Grammar
%token <string> TYPE
%token <string> ID
%token <number> NUMBER
// Parenthesis, Brackets, etc
%token <char> LPAR
%token <char> RPAR
%token <char> LBRA
%token <char> RBRA
%token <char> LBLO
%token <char> RBLO
// Punctuation
%token <char> SEMICOLON
%token <char> COLON
%token <char> COMMA
%token <char> APOST
%token <char> QUOTEMARK
// Math
%token <operator> EQ
%token <operator> PLUS
%token <operator> MINUS
%token <operator> MUL
%token <operator> DIV
%token <operator> POW
%token <operator> FAC
// Keywords
%token <string> WRITE
%token <string> PRINT
%token <string> IF
%token <string> ELSE
%token <string> RETURN
%token <string> WHILE
%token <string> INT
%token <string> FLOAT

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <ast> Program VarDecl VarDeclList Stmt StmtList Expr BinOp
%start Program

%%

Program: VarDeclList StmtList    { printf("The PARSER has started\n"); 
									
								}

;

VarDeclList:  {/*empty, i.e. it is possible not to declare a variable*/}
	| VarDecl VarDeclList {  printf("PARSER: Recognized variable declaration list\n"); 

							// Create AST node for VarDeclList
							

							
							}
;

VarDecl: TYPE ID SEMICOLON { printf("PARSER: Recognized variable declaration: %s\n", $2);

								printf("PARSER: Printing symbol table\n");
								printSymbolTable(symTab);

							 }
		| TYPE ID EQ NUMBER SEMICOLON { printf("PARSER: Recognized variable declaration: %s\n", $2);
								printf("PARSER: Printing symbol table\n");
								printSymbolTable(symTab);

			}
		| TYPE ID {
				  /* Add line and character number */
                  printf ("Missing semicolon after declaring variable: %s\n", $2);
             }

StmtList:  {/*empty, i.e. it is possible not to have any statement*/}
	| Stmt StmtList { printf("PARSER: Recognized statement list\n");
						
					}
;

Stmt: ID EQ Expr SEMICOLON { /* code TBD */
								printf("PARSER: Recognized assignment statement\n");
 	}
	| TYPE ID EQ NUMBER SEMICOLON { printf("PARSER: Recognized assignment statement\n");}
	| TYPE ID EQ ID SEMICOLON { printf("PARSER: Recognized assignment statement\n");}
	| WRITE Expr SEMICOLON { printf("PARSER: Recognized write statement\n"); }
	| WRITE LPAR Expr RPAR SEMICOLON { printf("PARSER: Recognized write statement\n"); }
	| PRINT Expr SEMICOLON { printf("PARSER: Recognized print statement\n"); }
	| PRINT LPAR Expr RPAR SEMICOLON { printf("PARSER: Recognized print statement\n"); }
	| IF LPAR Expr RPAR LBRA RBRA { printf("PARSER: Recognized if statement\n"); }
	| IF LPAR Expr RPAR LBRA RBRA ELSE LBRA RBRA { printf("PARSER: Recognized if-else statement\n"); }
	| IF LPAR Expr EQ Expr RPAR LBRA RBRA { printf("PARSER: Recognized if statement\n"); }
	| IF LPAR Expr EQ Expr RPAR LBRA RBRA ELSE LBRA RBRA { printf("PARSER: Recognized if-else statement\n"); }
	| WHILE LPAR Expr RPAR LBRA RBRA { printf("PARSER: Recognized while statement\n"); }
	| WHILE LPAR Expr EQ Expr RPAR LBRA RBRA { printf("PARSER: Recognized while statement\n"); }
	| RETURN LPAR Expr RPAR SEMICOLON { printf("PARSER: Recognized return statement\n"); }
	| RETURN Expr SEMICOLON { printf("PARSER: Recognized return statement\n"); }
;

Expr: Expr BinOp Expr { printf("PARSER: Recognized expression\n");
						
						
						// Set other fields as necessary
					  }
 					
	| ID { printf("ASSIGNMENT statement \n"); 
				
		}
	| NUMBER { 
				printf("PARSER: Recognized number\n");
			 }
;

BinOp: PLUS {
				printf("PARSER: Recognized binary operator PLUS\n");
            }
	| MINUS {
				printf("PARSER: Recognized binary operator MINUS\n");
			}
	| MUL	{
				printf("PARSER: Recognized binary operator MUL\n");
			}
	| DIV	{
				printf("PARSER: Recognized binary operator DIV\n");
			}
	| POW	{
				printf("PARSER: Recognized binary operator POW\n");
			}
	| FAC	{
				printf("PARSER: Recognized binary operator FAC\n");
			}
;

%%

int main() {
    // Initialize file or input source
    yyin = fopen("testProg.cmm", "r");

	// Initialize symbol table
	symTab = createSymbolTable(TABLE_SIZE);
    if (symTab == NULL) {
        // Handle error
        return EXIT_FAILURE;
    }
	symbol = malloc(sizeof(Symbol));
	initializeTempVars();

    // Start parsing
    if (yyparse() == 0) {
        // Successfully parsed
		printf("Parsing successful!\n");
        traverseAST(root, 0);
		// Print symbol table for debugging
		printSymbolTable(symTab);
		// Semantic analysis
		printf("\n=== SEMANTIC ANALYSIS ===\n\n");
		semanticAnalysis(root, symTab);
		printf("\n=== TAC GENERATION ===\n");
		printTACToFile("TAC.ir", tacHead);

		// Code optimization
		printf("\n=== CODE OPTIMIZATION ===\n");
		// Traverse the linked list of TAC entries and optimize
		// But - you MIGHT need to traverse the AST again to optimize

		optimizeTAC(&tacHead);
		printOptimizedTAC("TACOptimized.ir", tacHead);

		// Code generation
		printf("\n=== CODE GENERATION ===\n");
		initCodeGenerator("output.s");
		generateMIPS(tacHead);
		finalizeCodeGenerator("output.s");

        freeAST(root);
		freeSymbolTable(symTab);
    } else {
        fprintf(stderr, "Parsing failed\n");
    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}