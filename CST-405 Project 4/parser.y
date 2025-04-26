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

char* scope = "Global";

%}

%union {
	int number;
	float float_number;
	char character;
	char* string;
	char* operator;
	struct ASTNode* ast;
}

// Base Grammar
%token <string> TYPE
%token <string> VOID
%token <string> FUNC_DECL
%token <string> MAIN
%token <string> BOOL
%token <string> ID
%token <number> NUMBER
%token <float_number> DECIMAL_NUMBER
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
%token <operator> NUP
%token <operator> LT
%token <operator> LTE
%token <operator> GT
%token <operator> GTE
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
%token <string> ELSEIF
%token <string> ELSE
%token <string> RETURN
%token <string> WHILE
%token <string> INT
%token <string> FLOAT

%left PLUS MINUS
%left MULT DIV

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <ast> Program VarDecl VarDeclList Stmt StmtList Expr FuncDecl FuncCall ParamList ParamDecl IfStatements ElseIfStatements ElseStatement MainFunc FuncDeclList Body Array Array_Decl BinOp ExprList
%start Program

%%

/*
VarDeclList StmtList    { printf("The PARSER has started\n"); 
									root = malloc(sizeof(ASTNode));
									root->type = NodeType_Program;
									root->program.varDeclList = $1;
									root->program.stmtList = $2;
									// Set other fields as necessary
									// TODO: ADD IN PROGRAM SCOPE STUFF
									// TODO: MAKE RECURSIVE SO ORDER DOESNT MATTER IN THIS (WILL NEED TO ADJUST AST.H)
								}
	| 
*/

Program: FuncDeclList MainFunc    { 
							printf("The PARSER has started\n"); 
							printf("\nMAIN FUNCTION\n");
							root = malloc(sizeof(ASTNode));
							root->type = NodeType_Program;
							root->program.mainFunc = $2;
							root->program.funcDeclList = $1;
							}
	| error { printf("PARSER: Syntax error on line %d\n", yylineno); exit(0); }
;

MainFunc: VOID FUNC_DECL MAIN {
		scope = "Global";
	}LPAR RPAR LBRA Body RBRA { 
		printf("PARSER: Recognized main() function declaration\n"); 
		$$ = createNode(NodeType_Main);
		$$->mainFunc.funcName = strdup($3);
		$$->mainFunc.body = $8;
	};

Body: VarDeclList StmtList {
		printf("PARSER: Recognized function body\n"); 
		$$ = createNode(NodeType_Body);
		$$->body.varDeclList = $1;
		$$->body.stmtList = $2;
	}
	| error { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid BODY syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      };

FuncDeclList:  {/* No functions declared */ }
	| FuncDecl FuncDeclList { 
		printf("PARSER: Recognized function declaration list\n"); 
		$$ = malloc(sizeof(ASTNode));
		$$->type = NodeType_FuncDeclList;
		$$->funcDeclList.funcDecl = $1;
		$$->funcDeclList.funcDeclList = $2;
		}
	| error { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid FUNC DECL LIST syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      };

FuncDecl: FUNC_DECL TYPE ID {
        printf("PARSER: Beginning function declaration for %s\n", $3);
        /* Set the scope immediately when we see the function name */
        scope = strdup($3);
        
        /* Check if function already exists */
        symbol = lookupSymbol(symTab, $3);
        if (symbol != NULL) {
            printf("\n\n\n---------------------------\n\n\nPARSER: Function %s at line %d has already been declared - COMPILATION HALTED\n\n\n---------------------------\n\n\n", $3, yylineno);
            exit(0);
        }
        /* We'll add the function to symbol table after we know parameter count */
	}LPAR ParamList RPAR LBRA Body RBRA { 
		 printf("PARSER: Completed function declaration\n");
        
        /* Count parameters - this was moved after parsing them */
        ASTNode* traverse = $6;
        int paramSize = 0;
        while (traverse && traverse->paramDeclList.paramDecl != NULL) {
            paramSize++;
            traverse = traverse->paramDeclList.paramDeclList;
        }
        printf("PARAM Size: %d\n", paramSize);
        
        /* Now add the function to symbol table with correct param count */
        addSymbol(symTab, $3, $2, "Func", paramSize, "Global");
        printSymbolTable(symTab);
        printf("\n******************************************\n\n");
        
        /* Create the AST node */
        $$ = malloc(sizeof(ASTNode));
        $$->type = NodeType_FuncDecl;
        $$->funcDecl.funcName = $3;
        $$->funcDecl.returnType = $2;
        $$->funcDecl.body = $9;
        $$->funcDecl.paramList = $6;
	}
	| error { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid FUNC DECL syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      };

FuncCall: ID LPAR ExprList RPAR {
	printf("PARSER: Recognized func call\n");
	printf("\n******************************************\n\n");
	//TODO: 
	$$ = malloc(sizeof(ASTNode));
	$$->type = NodeType_FuncCall;
	$$->funcCall.funcName = strdup($1);
	$$->funcCall.exprList = $3;
};

ParamList:  {/*empty, i.e. it is possible not to have any parameter*/}
	| ParamDecl {printf("One parameter\n");
		// Create AST node for VarDeclList
		$$ = malloc(sizeof(ASTNode));
		$$->type = NodeType_ParamDeclList;
		$$->paramDeclList.paramDecl = $1;
	}
	| ParamDecl COMMA ParamList { printf("PARSER: Recognized parameter list\n"); 
		$$ = malloc(sizeof(ASTNode));
		$$->type = NodeType_ParamDeclList;
		$$->paramDeclList.paramDecl = $1;
		$$->paramDeclList.paramDeclList = $3;
	}
	| error { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid PARAM LIST syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      };

ParamDecl: TYPE ID { 
			printf("PARSER: Printing symbol table\n");
			printSymbolTable(symTab);

			/* Add variabe to symbol table
			Check if its already in there and add if not */

			symbol = lookupSymbol(symTab, $2);

			if (symbol != NULL) {
				printf("\n\n\n---------------------------\n\n\nPARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n\n\n---------------------------\n\n\n", $2, yylineno);
				exit(0);
			} else {
				addSymbol(symTab, $2, $1, "Var", 0, scope);
				printSymbolTable(symTab);
				printf("\n******************************************\n\n");
			}
			printf("PARSER: Recognized parameter declaration\n"); 
			$$ = malloc(sizeof(ASTNode));
			$$->type = NodeType_ParamDecl;
			$$->paramDecl.paramName = $2;
			$$->paramDecl.paramType = $1;
		}
	| error { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid PARAM DECL syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      };

VarDeclList:  {/*empty, i.e. it is possible not to declare a variable*/}
	| VarDecl VarDeclList {  printf("PARSER: Recognized variable declaration list\n"); 

							// Create AST node for VarDeclList
							$$ = malloc(sizeof(ASTNode));
							$$->type = NodeType_VarDeclList;
							$$->varDeclList.varDecl = $1;
							$$->varDeclList.varDeclList = $2;
				
							// Set other fields as necessary

							
							}
	| error { 
          printf("\n\n\n---------------------------\n\n\nBase Error: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      };

VarDecl: TYPE ID SEMICOLON { printf("\nPARSER: Recognized variable declaration: %s\n", $2);

								printf("PARSER: Printing symbol table\n");
								printSymbolTable(symTab);

								/* Add variabe to symbol table
								Check if its already in there and add if not */

								symbol = lookupSymbol(symTab, $2);

								if (symbol != NULL) {
									printf("\n\n\n---------------------------\n\n\nPARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n\n\n---------------------------\n\n\n", $2, yylineno);
									exit(0);
								} else {
									addSymbol(symTab, $2, $1, "Var", 0, scope);
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
									addSymbol(symTab, $2, $1, "Var", 0, scope);
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
		| Array_Decl SEMICOLON { 
			// E.G. int myList[10];
				printf("PARSER: Recognized array declaration: %s\n", $1->arrDecl.array->array.arrName);

				// Just pass the already created ASTNode along
				$$ = $1;

				// Add to symbol table using data from the inner array node
				addSymbol(symTab, $1->arrDecl.array->array.arrName, $1->arrDecl.varType, "Arr", $1->arrDecl.array->array.arrIndex, scope);
				printSymbolTable(symTab);
			}
		| Array_Decl EQ LBRA ExprList RBRA SEMICOLON {
			printf("PARSER: Recognized array declaration with initialization: %s\n", $1->arrDecl.array->array.arrName);
			// Set the exprList in the array declaration
			$1->arrDecl.exprList = $4;
			$$ = $1;
			// Add to symbol table
			addSymbol(symTab, $1->arrDecl.array->array.arrName, $1->arrDecl.varType, "Arr", $1->arrDecl.array->array.arrIndex, scope);
			printSymbolTable(symTab);
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
		| error { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      };

StmtList:  {/*empty, i.e. it is possible not to have any statement*/}
	| Stmt StmtList { printf("PARSER: Recognized statement list\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_StmtList;
						$$->stmtList.stmt = $1;
						$$->stmtList.stmtList = $2;
						// Set other fields as necessary
					};

Stmt: ID EQ Expr SEMICOLON { /* code TBD */
								printf("PARSER: Recognized assignment statement\n");
			 					printf("\n******************************************\n\n");
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_AssignStmt;
								$$->assignStmt.varName = strdup($1);
								$$->assignStmt.operator = $2;
								$$->assignStmt.expr = $3;
 	}
	| ID EQ FuncCall SEMICOLON { /* code TBD */
			printf("PARSER: Recognized func assign\n");
			printf("\n******************************************\n\n");
			//TODO: 
			$$ = malloc(sizeof(ASTNode));
			$$->type = NodeType_FuncCallAssign;
			$$->funcAssignStmt.varName = strdup($1);
			$$->funcAssignStmt.funcCall = $3;
			$$->funcAssignStmt.operator = $2;
 	}
	| FuncCall SEMICOLON { /* code TBD */
			printf("PARSER: Recognized func call\n");
 	}
	| Array EQ Expr SEMICOLON { /* code TBD */
			printf("PARSER: Recognized array assignment statement\n");
			printf("\n******************************************\n\n");
			$$ = malloc(sizeof(ASTNode));
			$$->type = NodeType_ArrDeclAssign;
			$$->arrAssignStmt.operator = $2;
			$$->arrAssignStmt.array = $1;
			$$->arrAssignStmt.expr = $3;
 	}
	| ID EQ Expr {
		      printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s %s on line %d\n\n\n---------------------------\n\n\n", $1,$2,$3, yylineno-1);
			  exit(0);
			}
	| WRITE Expr SEMICOLON { 
								printf("PARSER: Recognized write statement -> write %s;\n", $2); 
								printf("\n******************************************\n\n"); 
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_PrintStmt;
								$$->printStmt.varName = strdup($1);
								$$->printStmt.expr = $2;
						}
	| WRITE Expr {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s on line %d\n\n\n---------------------------\n\n\n", $1,$2, yylineno-1);
			  exit(0);
			}
	| WRITE LPAR Expr RPAR SEMICOLON { 
			printf("PARSER: Recognized write statement -> write(%s);\n", $3); 
			printf("\n******************************************\n\n"); 
			$$ = malloc(sizeof(ASTNode));
			$$->type = NodeType_PrintStmt;
			$$->printStmt.varName = strdup($1);
			$$->printStmt.expr = $3;
		}
	| WRITE Array SEMICOLON { 
			printf("PARSER: Recognized write array statement -> write %s;\n", $2); 
			printf("\n******************************************\n\n"); 
			$$ = malloc(sizeof(ASTNode));
			$$->type = NodeType_ArrPrintStmt;
			$$->arrPrintStmt.varName = strdup($1);
			$$->arrPrintStmt.array = $2;
		}
	| WRITE LPAR Expr RPAR {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, yylineno-1);
			  exit(0);
			}
	| PRINT Expr SEMICOLON { 
								printf("PARSER: Recognized print statement -> print %s;\n", $2); 
								printf("\n******************************************\n\n"); 
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_PrintStmt;
								$$->printStmt.varName = strdup($1);
								$$->printStmt.expr = $2;
						}
	| PRINT Expr {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s on line %d\n\n\n---------------------------\n\n\n", $1,$2, yylineno-1);
			  exit(0);
			}
	| PRINT LPAR Expr RPAR SEMICOLON { 
								printf("PARSER: Recognized print statement -> print(%s);\n", $3); 
								printf("\n******************************************\n\n"); 
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_PrintStmt;
								$$->printStmt.varName = strdup($1);
								$$->printStmt.expr = $3;
						}
	| PRINT LPAR Expr RPAR {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", $1,$3, yylineno-1);
			  exit(0);
			}
	| IfStatements {}
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
	
	| RETURN LPAR Expr RPAR SEMICOLON { printf("PARSER: Recognized return statement"); 
			printf("\n******************************************\n\n"); 
			$$ = malloc(sizeof(ASTNode));
			$$->type = NodeType_ReturnStmt;
			$$->returnStmt.varName = strdup($1);
			$$->returnStmt.expr = $3; }
	| RETURN Expr SEMICOLON { 
								printf("PARSER: Recognized return statement"); 
								printf("\n******************************************\n\n"); 
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_ReturnStmt;
								$$->returnStmt.varName = strdup($1);
								$$->returnStmt.expr = $2; 
								}
    | error { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      };

/* FuncDecl: FUNC_DECL TYPE ID LPAR{
	scope = strdup($3);
} 
ParamList RPar LBRA Body RBRA {

} */

IfStatements: IF LPAR Expr RPAR LBRA Body RBRA { 
		printf("PARSER: Recognized if statement\n"); 
		printf("\n******************************************\n\n"); 
		$$ = malloc(sizeof(ASTNode));
		$$->type = NodeType_IfStmt;
		$$->ifStatement.expr = $3;
		$$->ifStatement.body = $6;
		$$->ifStatement.elseIfStatement = NULL;
		$$->ifStatement.elseStatement = NULL;
	}
	| IF LPAR Expr RPAR LBRA Body RBRA ElseStatement { 
		printf("PARSER: Recognized if-else statement\n"); 
		printf("\n******************************************\n\n"); 
		$$ = malloc(sizeof(ASTNode));
		$$->type = NodeType_IfStmt;
		$$->ifStatement.expr = $3;
		$$->ifStatement.body = $6;
		$$->ifStatement.elseIfStatement = NULL;
		$$->ifStatement.elseStatement = $8;
	}
	| IF LPAR Expr RPAR LBRA Body RBRA ElseIfStatements { 
		printf("PARSER: Recognized if-else_if statement\n"); 
		printf("\n******************************************\n\n"); 
		$$ = malloc(sizeof(ASTNode));
		$$->type = NodeType_IfStmt;
		$$->ifStatement.expr = $3;
		$$->ifStatement.body = $6;
		$$->ifStatement.elseIfStatement = $8;
		$$->ifStatement.elseStatement = NULL;
	}
	| IF LPAR Expr RPAR LBRA Body RBRA ElseIfStatements ElseStatement { 
		printf("PARSER: Recognized if-else_if-else statement\n"); 
		printf("\n******************************************\n\n"); 
		$$ = malloc(sizeof(ASTNode));
		$$->type = NodeType_IfStmt;
		$$->ifStatement.expr = $3;
		$$->ifStatement.body = $6;
		$$->ifStatement.elseIfStatement = $8;
		$$->ifStatement.elseStatement = $9;
	};

ElseIfStatements: ELSEIF LPAR Expr RPAR LBRA Body RBRA {
        $$ = malloc(sizeof(ASTNode));
		$$->type = NodeType_ElseIfStmt;
		$$->ifStatement.expr = $3;
		$$->ifStatement.body = $6;
		$$->ifStatement.elseIfStatement = NULL;
	}
	| ELSEIF LPAR Expr RPAR LBRA Body RBRA ElseIfStatements {
	     $$ = malloc(sizeof(ASTNode));
		$$->type = NodeType_ElseIfStmt;
		$$->ifStatement.expr = $3;
		$$->ifStatement.body = $6;
		$$->ifStatement.elseIfStatement = $8;
	};

ElseStatement: ELSE LBRA Body RBRA {
	$$ = createNode(NodeType_ElseStmt);
    $$->elseStatement.body = $3;
}

ExprList: Expr {
    $$ = createNode(NodeType_ExprList);
    $$->exprList.expr = $1;
    $$->exprList.next = NULL;
	}
	| Expr COMMA ExprList {
    $$ = createNode(NodeType_ExprList);
    $$->exprList.expr = $1;
    $$->exprList.next = $3;
	};

Expr: Expr BinOp Expr { printf("PARSER: Recognized expression\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_Expr;
						$$->expr.left = $1;
						$$->expr.right = $3;
						$$->expr.operator = $2->binOp.operator;
						// TODO: Fix double initialization of 8+3
						// printf("--%s %c %s--\n", $1, $2->binOp.operator, $3);
						
						// Set other fields as necessary
					  }
	| LPAR Expr BinOp Expr RPAR { printf("PARSER: Recognized expression\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_Expr;
						$$->expr.left = $2;
						$$->expr.right = $4;
						$$->expr.operator = $3->binOp.operator;
						// TODO: Fix double initialization of 8+3
						// printf("--%s %c %s--\n", $2, $3->binOp.operator, $4);
						
						// Set other fields as necessary
					  }
 					
	| ID { printf("ASSIGNMENT statement \n"); 
			if (lookupSymbol(symTab, $1) == NULL) {
                printf("\n\n\n---------------------------\n\n\nSemantic error: Variable %s on line %d has not been declared\n\n\n---------------------------\n\n\n", $1, yylineno);
                exit(0);
            }
			$$ = malloc(sizeof(ASTNode));
			$$->type = NodeType_SimpleID;
			$$->simpleID.name = $1;
		}
	| NUMBER { 
				// printf("\n\n %d \n\n", $1);
				printf("PARSER: Recognized number\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_SimpleExpr;
				$$->simpleExpr.number = $1;
			 }
	| DECIMAL_NUMBER { 
				// printf("\n\n %f \n\n", $1);
				printf("PARSER: Recognized float number\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_SimpleDecimal;
				$$->simpleDecimal.number = $1;
			 }
	| BOOL { 
				printf("PARSER: Recognized boolean\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_SimpleString;
				$$->simpleString.name = $1;
			 }
	| STR 	{
				printf("PARSER: Recognized string\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_SimpleString;
				$$->simpleString.name = $1;
			}
	| CHR 	{
				printf("PARSER: Recognized char\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_SimpleID;
				$$->simpleID.name = $1;
			}
	| error { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      };

Array_Decl: TYPE ID LBLO NUMBER RBLO { printf("PARSER: Recognized array\n");
		$$ = createNode(NodeType_ArrDecl);
		$$->arrDecl.varType = strdup($1);

		ASTNode* arrayNode = createNode(NodeType_Array);
		arrayNode->array.arrName = strdup($2);
		arrayNode->array.arrIndex = $4;

		$$->arrDecl.array = arrayNode;
		$$->arrDecl.exprList = NULL;  // No initialization list
	}
	| TYPE ID LBLO NUMBER RBLO EQ LBRA ExprList RBRA { 
		printf("PARSER: Recognized array declaration with initialization\n");
		$$ = createNode(NodeType_ArrDecl);
		$$->arrDecl.varType = strdup($1);
		ASTNode* arrayNode = createNode(NodeType_Array);
		arrayNode->array.arrName = strdup($2);
		arrayNode->array.arrIndex = $4;
		$$->arrDecl.array = arrayNode;
		$$->arrDecl.exprList = $8; // Set the initialization list
		
		// Check if the array size matches the expression list size
		int count = 0;
		ASTNode* current = $8;
		while (current != NULL) {
			count++;
			current = current->exprList.next;
		}
		
		if (count > $4) {
			printf("\n\n\n---------------------------\n\n\nError: Too many initializers for array '%s' of size %d on line %d\n\n\n---------------------------\n\n\n", $2, $4, yylineno);
			exit(0);
		} 
	};

/* Update the Array rule for better error handling */
Array: ID LBLO NUMBER RBLO {
    // Check if the array exists in the symbol table
    Symbol* sym = lookupSymbol(symTab, $1);
    if (sym == NULL) {
        printf("\n\n\n---------------------------\n\n\nSemantic error: Array '%s' on line %d has not been declared\n\n\n---------------------------\n\n\n", $1, yylineno);
        exit(0);
    }
    
    // Check if the symbol is actually an array
    if (strcmp(sym->kind, "Arr") != 0) {
        printf("\n\n\n---------------------------\n\n\nSemantic error: '%s' is not an array on line %d\n\n\n---------------------------\n\n\n", $1, yylineno);
        exit(0);
    }
    
    // Check array bounds
    if ($3 >= sym->size) {
        printf("\n\n\n---------------------------\n\n\nSemantic error: Array index %d out of bounds for array '%s' of size %d on line %d\n\n\n---------------------------\n\n\n", $3, $1, sym->size, yylineno);
        exit(0);
    }
    
    $$ = createNode(NodeType_Array);
    $$->array.arrName = strdup($1);
    $$->array.arrIndex = $3;
	};

BinOp: PLUS {
				printf("PARSER: Recognized binary operator PLUS\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = $1;
            }
	| MINUS {
				printf("PARSER: Recognized binary operator MINUS\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = $1;
			}
	| MUL	{
				printf("PARSER: Recognized binary operator MUL\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = $1;
			}
	| DIV	{
				printf("PARSER: Recognized binary operator DIV\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = $1;
			}
	| POW	{
				printf("PARSER: Recognized binary operator POW\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = $1;
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
				printf("PARSER: Recognized boolean operator DUP\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = $1;
			}
	| NUP	{
				printf("PARSER: Recognized boolean operator NUP\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = $1;
			}
	| GT	{
				printf("PARSER: Recognized boolean operator GT\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = $1;
			}
	| GTE	{
				printf("PARSER: Recognized boolean operator GTE\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = $1;
			}
	| LT	{
				printf("PARSER: Recognized boolean operator GT\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = $1;
			}
	| LTE	{
				printf("PARSER: Recognized boolean operator LTE\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_BinOp;
				$$->binOp.operator = $1;
			}
	| error { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      };

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
		/* initCodeGenerator("output.s", 1);
		/* generateMIPS(tacHead);
		finalizeCodeGenerator("output.s"); */ 
		initCodeGenerator("optimizedOutput.s", 0);
		generateMIPS(optimizedTacHead);
		finalizeCodeGenerator("optimizedOutput.s");

        freeAST(root);
		freeSymbolTable(symTab);
    } else {
        /* fprintf(stderr, "Parsing failed\n"); */
    	 fprintf(stderr, "Parsing failed around line %d.\n", yylineno);
    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
	//fprintf(stderr, "Parse error: %s\n", s);
	/* exit(1); */
}