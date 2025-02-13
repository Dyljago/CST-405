%{

// Shift reduce parser with 1 look ahead

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
extern int chars;
extern TAC* tacHead;  // Declare the head of the linked list of TAC entries
extern char* yytext; // The problematic token
extern int brackStart;

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
%token <string> STR
%token <string> CHR
%token <string> END
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
/* %token <char> APOST */
/* %token <char> QUOTEMARK */
// Math
%token <operator> EQ
%token <operator> PEQ
%token <operator> SEQ
%token <operator> MEQ
%token <operator> DEQ
%token <operator> DUP
%token <operator> PLUS
%token <operator> MINUS
%token <operator> MUL
%token <operator> DIV
%token <operator> POW
%token <operator> FAC
%token <operator> FIB
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
									root = malloc(sizeof(ASTNode));
									root->type = NodeType_Program;
									root->program.varDeclList = $1;
									root->program.stmtList = $2;
									// Set other fields as necessary
								}

;

VarDeclList:  {/*empty, i.e. it is possible not to declare a variable*/}
	| VarDecl VarDeclList {  printf("PARSER: Recognized variable declaration list\n"); 

							// Create AST node for VarDeclList
							$$ = malloc(sizeof(ASTNode));
							$$->type = NodeType_VarDeclList;
							$$->varDeclList.varDecl = $1;
							$$->varDeclList.varDeclList = $2;
				
							// Set other fields as necessary

							
							}
;

VarDecl: TYPE ID SEMICOLON { printf("\nPARSER: Recognized variable declaration: %s\n", $2);

								printf("PARSER: Printing symbol table\n");
								printSymbolTable(symTab);

								/* Add variabe to symbol table
								Check if its already in there and add if not */

								/* TODO: CHECK IF ITS THERE*/

								symbol = lookupSymbol(symTab, $2);

								if (symbol != NULL) {
									printf("\n\n\n---------------------------\n\n\nPARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n\n\n---------------------------\n\n\n", $2, yylineno);
									exit(0);
								} else {
									addSymbol(symTab, $2, $1);
									printSymbolTable(symTab);
									printf("\n******************************************\n\n");
								}

								// Create AST Node for VarDecl
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_VarDecl;
								$$->varDecl.varType = strdup($1);
								$$->varDecl.varName = strdup($2);
								// Set other fields as necessary

							 }
		| TYPE ID EQ Expr SEMICOLON { printf("PARSER: Recognized variable declaration: %s\n", $2);
								printf("PARSER: Printing symbol table\n");
								printSymbolTable(symTab);

								/* Add variabe to symbol table
								Check if its already in there and add if not */

								symbol = lookupSymbol(symTab, $2);

								if (symbol != NULL) {
									printf("PARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n", $2, yylineno);
									exit(0);
								} else {
									addSymbol(symTab, $2, $1);
									printSymbolTable(symTab);
									printf("\n******************************************\n\n");
								}

								// Create AST Node for VarDecl
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_VarDeclAssign;
								$$->varDeclAssign.varType = strdup($1);
								$$->varDeclAssign.varName = strdup($2);
								$$->varDeclAssign.varAssign = $4;
								// Set other fields as necessary
			}
		| TYPE ID {
                  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after declaring variable: %s on line %d\n\n\n---------------------------\n\n\n", $2, yylineno-1);
				  exit(0);
             }
		| TYPE ID EQ Expr {
                  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after declaring variable: %s on line %d\n\n\n---------------------------\n\n\n", $2, yylineno-1);
				  exit(0);
             }
		| TYPE NUMBER {
                  printf ("\n\n\n---------------------------\n\n\nCannot use number as a variable name for: '%s %d' on line %d\n\n\n---------------------------\n\n\n", $1, $2, yylineno);
				  exit(0);
             }
;

StmtList:  {/*empty, i.e. it is possible not to have any statement*/}
	| Stmt StmtList { printf("PARSER: Recognized statement list\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_StmtList;
						$$->stmtList.stmt = $1;
						$$->stmtList.stmtList = $2;
						// Set other fields as necessary
					}
;

Stmt: ID EQ Expr SEMICOLON { /* code TBD */
								printf("PARSER: Recognized assignment statement\n");
			 					printf("\n******************************************\n\n");
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_AssignStmt;
								$$->assignStmt.varName = strdup($1);
								$$->assignStmt.operator = $2;
								$$->assignStmt.expr = $3;
 	}
	| ID EQ Expr {
		      printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s %s on line %d\n\n\n---------------------------\n\n\n", $1,$2,$3, yylineno-1);
			  exit(0);
			}
	| WRITE Expr SEMICOLON { 
								printf("PARSER: Recognized write statement -> write %s;\n", $2); 
								printf("\n******************************************\n\n"); 
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_OtherStmt;
								$$->otherStmt.varName = strdup($1);
								$$->otherStmt.expr = $2;
						}
	| WRITE Expr {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s on line %d\n\n\n---------------------------\n\n\n", $1,$2, yylineno-1);
			  exit(0);
			}
	| WRITE LPAR Expr RPAR SEMICOLON { 
			printf("PARSER: Recognized write statement -> write(%s);\n", $3); 
			printf("\n******************************************\n\n"); 
			$$ = malloc(sizeof(ASTNode));
			$$->type = NodeType_OtherStmt;
			$$->otherStmt.varName = strdup($1);
			$$->otherStmt.expr = $3;
		}
	| WRITE LPAR Expr RPAR {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, yylineno-1);
			  exit(0);
			}
	| PRINT Expr SEMICOLON { printf("PARSER: Recognized print statement -> print %s;\n", $2); printf("\n******************************************\n\n"); }
	| PRINT Expr {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s on line %d\n\n\n---------------------------\n\n\n", $1,$2, yylineno-1);
			  exit(0);
			}
	| PRINT LPAR Expr RPAR SEMICOLON { printf("PARSER: Recognized print statement -> print(%s);\n", $3); printf("\n******************************************\n\n"); }
	| PRINT LPAR Expr RPAR {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, yylineno-1);
			  exit(0);
			}
	| IF LPAR Expr RPAR LBRA Stmt RBRA { printf("PARSER: Recognized if statement\n"); printf("\n******************************************\n\n"); }
	| IF LPAR Expr RPAR LBRA RBRA ELSE LBRA Stmt RBRA { printf("PARSER: Recognized if-else statement\n"); printf("\n******************************************\n\n"); }
	
	| IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA { printf("PARSER: Recognized if statement\n"); printf("\n******************************************\n\n"); }
	| IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA ELSE LBRA Stmt RBRA { printf("PARSER: Recognized if-else statement\n"); printf("\n******************************************\n\n"); }
	| IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA ELSE LBRA RBRA { printf("PARSER: Recognized if-else statement\n"); printf("\n******************************************\n\n"); }
	| IF LPAR Expr EQ Expr RPAR LBRA RBRA ELSE LBRA Stmt RBRA { printf("PARSER: Recognized if-else statement\n"); printf("\n******************************************\n\n"); }
	| IF LPAR Expr EQ Expr RPAR LBRA RBRA { printf("PARSER: Recognized if statement\n"); printf("\n******************************************\n\n"); }
	| IF LPAR Expr EQ Expr RPAR LBRA RBRA ELSE LBRA RBRA { printf("PARSER: Recognized if-else statement\n"); printf("\n******************************************\n\n"); }
	
	| IF LPAR Expr EQ Expr RPAR LBRA Stmt { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, brackStart);
			  exit(0); 
			}
	| IF LPAR Expr EQ Expr RPAR LBRA Stmt ELSE LBRA Stmt RBRA { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, brackStart);
			  exit(0);
	 		}
	| IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA ELSE LBRA Stmt { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, brackStart);
			  exit(0);
	 		}
	| IF LPAR Expr EQ Expr RPAR LBRA Stmt ELSE LBRA RBRA { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, brackStart);
			  exit(0);
	 		}
	| IF LPAR Expr EQ Expr RPAR LBRA ELSE LBRA Stmt RBRA { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, brackStart);
			  exit(0);
	 		}
	| IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA ELSE LBRA { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, brackStart);
			  exit(0);
	 		}
	| IF LPAR Expr EQ Expr RPAR LBRA RBRA ELSE LBRA Stmt { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, brackStart);
			  exit(0);
	 		}
	| IF LPAR Expr EQ Expr RPAR LBRA { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, brackStart);
			  exit(0);
	 		}
	| IF LPAR Expr EQ Expr RPAR LBRA ELSE LBRA RBRA { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, brackStart);
			  exit(0);
	 		}
	| IF LPAR Expr EQ Expr RPAR LBRA RBRA ELSE LBRA { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, brackStart);
			  exit(0);
	 		}

	| WHILE LPAR Expr RPAR LBRA RBRA { printf("PARSER: Recognized while statement\n"); printf("\n******************************************\n\n"); }
	| WHILE LPAR Expr EQ Expr RPAR LBRA RBRA { printf("PARSER: Recognized while statement\n"); printf("\n******************************************\n\n"); }
	| WHILE LPAR Expr RPAR LBRA Stmt RBRA { printf("PARSER: Recognized while statement\n"); printf("\n******************************************\n\n"); }
	| WHILE LPAR Expr EQ Expr RPAR LBRA Stmt RBRA { printf("PARSER: Recognized while statement\n"); printf("\n******************************************\n\n"); }
	
	| RETURN LPAR Expr RPAR SEMICOLON { printf("PARSER: Recognized return statement -> return(%s);\n", $3); printf("\n******************************************\n\n"); }
	| RETURN Expr SEMICOLON { printf("PARSER: Recognized return statement -> return %s;\n", $2); printf("\n******************************************\n\n"); }
    | error { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
;

Expr: Expr BinOp Expr { printf("PARSER: Recognized expression\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_Expr;
						$$->expr.left = $1;
						$$->expr.right = $3;
						$$->expr.operator = $2->binOp.operator;
						
						// Set other fields as necessary
					  }
 					
	| ID { printf("ASSIGNMENT statement \n"); 
			$$ = malloc(sizeof(ASTNode));
			$$->type = NodeType_SimpleID;
			$$->simpleID.name = $1;
		}
	| NUMBER { 
				printf("PARSER: Recognized number\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_SimpleExpr;
				$$->simpleExpr.number = $1;
			 }
	| STR 	{
				printf("PARSER: Recognized string\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_SimpleID;
				$$->simpleID.name = $1;
			}
	| CHR 	{
				printf("PARSER: Recognized char\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_SimpleID;
				$$->simpleID.name = $1;
			}
;

BinOp: PLUS {
				printf("PARSER: Recognized binary operator PLUS\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = *$1;
            }
	| MINUS {
				printf("PARSER: Recognized binary operator MINUS\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = *$1;
			}
	| MUL	{
				printf("PARSER: Recognized binary operator MUL\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = *$1;
			}
	| DIV	{
				printf("PARSER: Recognized binary operator DIV\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = *$1;
			}
	| POW	{
				printf("PARSER: Recognized binary operator POW\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = *$1;
			}
	| FAC	{
			    /* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator FAC\n");
			}
	| FIB	{
			  	/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator FIB\n");
			}
	| PEQ	{
			    /* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator PEQ\n");
			}
	| SEQ	{
				/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator SEQ\n");
			}
	| MEQ	{
				/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator MEQ\n");
			}
	| DEQ	{
				/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator DEQ\n");
			}
	| DUP	{
				printf("PARSER: Recognized binary operator DUP\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = *$1;
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

		TAC* optimizedTacHead = optimizeTAC(&tacHead);
		/* printOptimizedTAC("TACOptimized.ir", tacHead); */

		// Code generation
		printf("\n=== CODE GENERATION ===\n");
		initCodeGenerator("output.s", 1);
		generateMIPS(tacHead);
		finalizeCodeGenerator("output.s");
		initCodeGenerator("optimizedOutput.s", 0);
		generateMIPS(optimizedTacHead);
		finalizeCodeGenerator("optimizedOutput.s");

        freeAST(root);
		freeSymbolTable(symTab);
    } else {
        fprintf(stderr, "Parsing failed\n");
    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
	//fprintf(stderr, "Parse error: %s\n", s);
	/* exit(1); */
}