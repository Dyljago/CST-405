%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()
#include "parser.tab.h"

int words = 0;
int chars = 0;
int lines = 0;

%}

/* Base Grammar */
letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
delim       [ \t\n]
NUMBER      {digit}+(\.{digit}+)?(E[+\-]?(digit)+)?
ws          {delim}+
/* Comments */
COMMBLOCK	"/\*"
COMM		"/\/"
/* Parenthesis, Brackets, etc */
LPAR		"("
RPAR		")"
LBRA		"{"
RBRA		"}"
LBLO		"["
RBLO		"]"
/* Keywords */
INTKW		"int"
FLOATKW		"float"
WRITEKW		"write"
PRINTKW		"print"
IFKW		"if"
ELSEKW		"else"
WHILEKW		"while"
RETURNKW	"return"
/* Mathmatical Operators */
MUL			"*"
DIV			"/"
ADD			"+"
SUB			"-"
EQU			"="
POW			"^"
FAC			"!"
/* Punctuation */
COLON		":"
SEMICOLON	";"
COMMA		","
APOST		"'"
QUOTEMARK	"""

%option yylineno

/* Add three keywords */

%%
{COMMBLOCK}   			{
							int c;
							char commentBuffer[1024];  
							int index = 0;
							while((c = input()) != 0) {
								if(c == '*') {
									if((c = input()) == '/')
										break;
									else
										if (index < sizeof(commentBuffer) - 1) {
											commentBuffer[index++] = c;
										}
								}
								if (index < sizeof(commentBuffer) - 1) {
									commentBuffer[index++] = c;
								}
							}
							commentBuffer[index] = '\0';  
							printf("/* %s */ : COMMENT BLOCK\n", commentBuffer);
						}

{COMM} 		{
				int c;
				char commentBuffer[1024];  
				int index = 0;

				
				while ((c = input()) != '\n' && c != EOF) {
					if (index < sizeof(commentBuffer) - 1) {
						commentBuffer[index++] = c;
					}
				}

				commentBuffer[index] = '\0';  

				printf("//%s : COMMENT\n", commentBuffer);
			}


{INTKW}		{words++; chars += strlen(yytext);
			  printf("%s : TYPE\n", yytext);
			  yylval.string = strdup(yytext); 
			  return TYPE;
			}

{FLOATKW}	{words++; chars += strlen(yytext);
			  printf("%s : TYPE\n", yytext);
			  yylval.string = strdup(yytext); 
			  return TYPE;
			}

{IFKW}		{words++; chars += strlen(yytext);
			  printf("%s : KEYWORD\n", yytext);
			  yylval.string = strdup(yytext); 
			  return IF;
			}

{ELSEKW}	{words++; chars += strlen(yytext);
			  printf("%s : KEYWORD\n", yytext);
			  yylval.string = strdup(yytext); 
			  return ELSE;
			}

{WHILEKW}	{words++; chars += strlen(yytext);
			  printf("%s : KEYWORD\n", yytext);
			  yylval.string = strdup(yytext); 
			  return WHILE;
			}

{RETURNKW}	{words++; chars += strlen(yytext);
			  printf("%s : KEYWORD\n", yytext);
			  yylval.string = strdup(yytext); 
			  return RETURN;
			}

{WRITEKW}	{words++; chars += strlen(yytext);
			  printf("%s : KEYWORD\n", yytext);
			  yylval.string = strdup(yytext); 
			  return WRITE;
			}

{PRINTKW}	{words++; chars += strlen(yytext);
			  printf("%s : KEYWORD\n", yytext);
			  yylval.string = strdup(yytext); 
			  return PRINT;
			}

{ID}		{words++; chars += strlen(yytext);
			  printf("%s : IDENTIFIER\n",yytext);
			  yylval.string = strdup(yytext); 
			  return ID;
			}
			
{NUMBER}	{words++; chars += strlen(yytext);
			  printf("%s : NUMBER\n",yytext);
			  yylval.number = atoi(strdup(yytext)); 
			  return NUMBER;
			}
			
{SEMICOLON}	{chars++;
		      printf("%s : SEMICOLON\n", yytext);
		      yylval.string = strdup(yytext); 
		      return SEMICOLON;
			}

{COLON}		{chars++;
		      printf("%s : COLON\n", yytext);
		      yylval.string = strdup(yytext); 
		      return COLON;
			}

{COMMA}		{chars++;
		      printf("%s : COMMA\n", yytext);
		      yylval.string = strdup(yytext); 
		      return COMMA;
			}

{LPAR}		{chars++;
		      printf("%s : Left Parenthesis\n", yytext);
		      yylval.string = strdup(yytext); 
		      return LPAR;
			}

{RPAR}		{chars++;
		      printf("%s : Right Parenthesis\n", yytext);
		      yylval.string = strdup(yytext); 
		      return RPAR;
			}

{LBRA}		{chars++;
		      printf("%s : Left Bracket\n", yytext);
		      yylval.string = strdup(yytext); 
		      return LBRA;
			}

{RBRA}		{chars++;
		      printf("%s : Right Bracket\n", yytext);
		      yylval.string = strdup(yytext); 
		      return RBRA;
			}

{LBLO}		{chars++;
		      printf("%s : Left Block\n", yytext);
		      yylval.string = strdup(yytext); 
		      return LBLO;
			}

{RBLO}		{chars++;
		      printf("%s : Right Block\n", yytext);
		      yylval.string = strdup(yytext); 
		      return RBLO;
			}

{APOST} {chars++;
		      printf("%s : APOSTROPHE\n", yytext);
		      yylval.string = strdup(yytext); 
		      return APOST;
			}

"\""	{chars++;
		      printf("%s : QUOTATION MARK\n", yytext);
		      yylval.string = strdup(yytext); 
		      return QUOTEMARK;
			}
		
{EQU}		{chars++;
			  printf("%s : EQ\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return EQ;
			}

{ADD}		{chars++;
			  printf("%s : PLUS\n", yytext);
			  yylval.operator = strdup(yytext); 
		 	  return PLUS;
			}

{SUB}		{chars++;
			  printf("%s : MINUS\n", yytext);
			  yylval.operator = strdup(yytext); 
		 	  return MINUS;
			}

{MUL}		{chars++;
			  printf("%s : MULTIPLICATION\n", yytext);
			  yylval.operator = strdup(yytext); 
		 	  return MUL;
			}

{DIV}		{chars++;
			  printf("%s : DIVISION\n", yytext);
			  yylval.operator = strdup(yytext); 
		 	  return DIV;
			}

{POW}		{chars++;
			  printf("%s : POWER OF\n", yytext);
			  yylval.operator = strdup(yytext); 
		 	  return POW;
			}

{FAC}		{chars++;
			  printf("%s : FACTORIAL\n", yytext);
			  yylval.operator = strdup(yytext); 
		 	  return FAC;
			}

[\n]	{lines++; chars=0;yylineno++;}
[ \t]	{chars++;}
.		{chars++;
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
		}
		

%%