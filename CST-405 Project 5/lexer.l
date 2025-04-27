%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()
#include "parser.tab.h"

int words = 0;
int chars = 0;
int lines = 0;
int brackStart = 0;

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
/* Strings? */
STR 		"\""
CHR			"\'"
/* Parenthesis, Brackets, etc */
LPAR		"("
RPAR		")"
LBRA		"{"
RBRA		"}"
LBLO		"["
RBLO		"]"
/* Keywords */
VOIDKW		"void"
INTKW		"int"
FLOATKW		"float"
STRINGKW	"string"
CHARKW		"char"
BOOLKW		"bool"
WRITEKW		"write"
PRINTKW		"print"
IFKW		"if"
ELSEIFKW	"else if"
ELSEKW		"else"
WHILEKW		"while"
RETURNKW	"return"
TRUEKW		"true"
FALSEKW		"false"
FUNCKW		"func"
MAINKW		"main"
/* Mathmatical Operators */
MUL			"*"
DIV			"/"
ADD			"+"
SUB			"-"
EQU			"="
PEQ			"+="
SEQ			"-="
MEQ			"*="
DEQ			"/="
DUP			"=="
NUP			"!="
LTE			"<="
LeT			"<"
GTE			">="
GeT			">"
POW			"^"
FAC			"!"
FIB			"fib"
/* Punctuation */
COLON		":"
SEMICOLON	";"
COMMA		","
/* APOST		"'"
QUOTEMARK	"\"" */
/* CONVERTERS int(), float(), etc */

%option yylineno

/* Add three keywords */

%%
{COMMBLOCK}   			{
							int ended = 0;
							int lineStart = yylineno;
							int lineEnd = 10;
							int c;
							char commentBuffer[1024];  
							int index = 0;
							while((c = input()) != 0) {
								if(c == '*') {
									if((c = input()) == '/') {
										ended = 1;
										break;
									} else
										if (index < sizeof(commentBuffer) - 1) {
											commentBuffer[index++] = c;
										}
								}
								if (index < sizeof(commentBuffer) - 1) {
									commentBuffer[index++] = c;
								}
							}
							lineEnd = yylineno;
							commentBuffer[index] = '\0';  
							if (ended == 1) {
								printf("/* %s */ : COMMENT BLOCK\n", commentBuffer);
								printf("\n******************************************\n\n");
							} else {
								printf("\n\n\n---------------------------\n\n\n/* %s : COMMENT NEVER CLOSED AT LINES %d - %d\n\n\n---------------------------\n\n\n", commentBuffer, lineStart, lineEnd);
								exit(0);
							}
						}

{COMM} 		{
				lines++;
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
				printf("\n******************************************\n\n");
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

{BOOLKW}	{words++; chars += strlen(yytext);
			  printf("%s : TYPE\n", yytext);
			  yylval.string = strdup(yytext); 
			  return TYPE;
			}

{TRUEKW}	{words++; chars += strlen(yytext);
			  printf("%s : BOOL\n", yytext);
			  yylval.string = strdup(yytext); 
			  return BOOL;
			}

{FALSEKW}	{words++; chars += strlen(yytext);
			  printf("%s : BOOL\n", yytext);
			  yylval.string = strdup(yytext); 
			  return BOOL;
			}

{STRINGKW}	{words++; chars += strlen(yytext);
			  printf("%s : TYPE\n", yytext);
			  yylval.string = strdup(yytext); 
			  return TYPE;
			}

{VOIDKW}	{words++; chars += strlen(yytext);
			  printf("%s : VOID\n", yytext);
			  yylval.string = strdup(yytext); 
			  return VOID;
			}

{FUNCKW}	{words++; chars += strlen(yytext);
			  printf("%s : FUNC\n", yytext);
			  yylval.string = strdup(yytext); 
			  return FUNC_DECL;
			}

{MAINKW}	{words++; chars += strlen(yytext);
			  printf("%s : MAIN\n", yytext);
			  yylval.string = strdup(yytext); 
			  return MAIN;
			}

{CHARKW}	{words++; chars += strlen(yytext);
			  printf("%s : TYPE\n", yytext);
			  yylval.string = strdup(yytext); 
			  return TYPE;
			}

{IFKW}		{words++; chars += strlen(yytext);
			  printf("%s : KEYWORD\n", yytext);
			  yylval.string = strdup(yytext); 
			  return IF;
			}

{ELSEIFKW}	{words++; chars += strlen(yytext);
			  printf("%s : KEYWORD\n", yytext);
			  yylval.string = strdup(yytext); 
			  return ELSEIF;
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
			  if (strchr(yytext, '.') != NULL) {
				// printf("\n\n\nDECIMAL\n\n\n");
			  	yylval.float_number = atof(strdup(yytext)); 
			  	return DECIMAL_NUMBER;
              } else {
				// printf("\n\n\INTEGER\n\n\n");
			  	yylval.number = atoi(strdup(yytext)); 
			  	return NUMBER;
              }
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
			  brackStart = lines + 1;
		      printf("%s : Left Bracket\n", yytext);
		      yylval.string = strdup(yytext); 
		      return LBRA;
			}

{RBRA}		{chars++;
			  brackStart = 0;
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

{STR}		{
				int ended = 0;
				int lineStart = yylineno;
				int lineEnd = 10;
				int c;
				int lastChar;
				char stringBuffer[1024];  
				int index = 0;
				stringBuffer[index++] = '"';
				while((c = input()) != 0) {
					//printf("Character read: %c (ASCII: %d)\n", c, c); // Print the character and its ASCII value
					chars++;
					if(lastChar != '\\') {
						if(c == '"') {
							chars++;
							ended = 1;
							break;
						} else
							if (index < sizeof(stringBuffer) - 1) {
								stringBuffer[index++] = c;
							}
					} else {
							if (index < sizeof(stringBuffer) - 1) {
								stringBuffer[index++] = c;
							}
					}
					lastChar = c;
				}
				lineEnd = yylineno;
				stringBuffer[index++] = '"';
				stringBuffer[index] = '\0';  
				if (ended == 1) {
					printf("%s: STRING\n", stringBuffer);
					yylval.string = strdup(stringBuffer); 
					return STR;
				} else {
					printf("\n\n\n---------------------------\n\n\n/* %s : STRING NEVER CLOSED AT LINES %d - %d\n\n\n---------------------------\n\n\n", stringBuffer, lineStart, lineEnd);
					exit(0);
				}
			}

{CHR}		{
				int ended = 0;
				int lineStart = yylineno;
				int lineEnd = 10;
				int c;
				int lastChar;
				char charBuffer[1024];  
				int index = 0;
				charBuffer[index++] = '\'';
				while((c = input()) != 0) {
					//printf("Character read: %c (ASCII: %d)\n", c, c); // Print the character and its ASCII value
					chars++;
					if(lastChar != '\\') {
						if(c == '\'') {
							chars++;
							ended = 1;
							break;
						} else
							if (index < sizeof(charBuffer) - 1) {
								charBuffer[index++] = c;
							}
					} else {
							if (index < sizeof(charBuffer) - 1) {
								charBuffer[index++] = c;
							}
					}
					lastChar = c;
				}
				lineEnd = yylineno;
				charBuffer[index++] = '\'';
				charBuffer[index] = '\0';  
				if (ended == 1) {
					printf("%s: CHAR\n", charBuffer);
					yylval.string = strdup(charBuffer); 
					return CHR;
				} else {
					printf("\n\n\n---------------------------\n\n\n/* %s : CHAR NEVER CLOSED AT LINES %d - %d\n\n\n---------------------------\n\n\n", charBuffer, lineStart, lineEnd);
					exit(0);
				}
			}
		
{EQU}		{chars++;
			  printf("%s : EQ\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return EQ;
			}

{PEQ}		{chars++;
			  printf("%s : PLUS EQ\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return PEQ;
			}

{SEQ}		{chars++;
			  printf("%s : SUB EQ\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return SEQ;
			}

{MEQ}		{chars++;
			  printf("%s : MULT EQ\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return MEQ;
			}

{DEQ}		{chars++;
			  printf("%s : DIV EQ\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return DEQ;
			}

{DUP}		{chars++;
			  printf("%s : DUP\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return DUP;
			}

{NUP}		{chars++;
			  printf("%s : NUP\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return NUP;
			}

{GeT}		{chars++;
			  printf("%s : GT\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return GT;
			}

{GTE}		{chars++;
			  printf("%s : GTE\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return GTE;
			}

{LeT}		{chars++;
			  printf("%s : LT\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return LT;
			}

{LTE}		{chars++;
			  printf("%s : LTE\n", yytext);
			  yylval.operator = strdup(yytext); 
			  return LTE;
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

{FIB}		{chars++;
			  printf("%s : FIBONACCI\n", yytext);
			  yylval.operator = strdup(yytext); 
		 	  return FIB;
			}

[\n]	{lines++; chars=0;}
[ \t]	{chars++;}
.		{chars++;
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
		}
		

%%