/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TYPE = 258,                    /* TYPE  */
    VOID = 259,                    /* VOID  */
    FUNC_DECL = 260,               /* FUNC_DECL  */
    MAIN = 261,                    /* MAIN  */
    BOOL = 262,                    /* BOOL  */
    ID = 263,                      /* ID  */
    NUMBER = 264,                  /* NUMBER  */
    DECIMAL_NUMBER = 265,          /* DECIMAL_NUMBER  */
    STR = 266,                     /* STR  */
    CHR = 267,                     /* CHR  */
    END = 268,                     /* END  */
    LPAR = 269,                    /* LPAR  */
    RPAR = 270,                    /* RPAR  */
    LBRA = 271,                    /* LBRA  */
    RBRA = 272,                    /* RBRA  */
    LBLO = 273,                    /* LBLO  */
    RBLO = 274,                    /* RBLO  */
    SEMICOLON = 275,               /* SEMICOLON  */
    COLON = 276,                   /* COLON  */
    COMMA = 277,                   /* COMMA  */
    EQ = 278,                      /* EQ  */
    PEQ = 279,                     /* PEQ  */
    SEQ = 280,                     /* SEQ  */
    MEQ = 281,                     /* MEQ  */
    DEQ = 282,                     /* DEQ  */
    DUP = 283,                     /* DUP  */
    NUP = 284,                     /* NUP  */
    LT = 285,                      /* LT  */
    LTE = 286,                     /* LTE  */
    GT = 287,                      /* GT  */
    GTE = 288,                     /* GTE  */
    PLUS = 289,                    /* PLUS  */
    MINUS = 290,                   /* MINUS  */
    MUL = 291,                     /* MUL  */
    DIV = 292,                     /* DIV  */
    POW = 293,                     /* POW  */
    FAC = 294,                     /* FAC  */
    FIB = 295,                     /* FIB  */
    WRITE = 296,                   /* WRITE  */
    PRINT = 297,                   /* PRINT  */
    IF = 298,                      /* IF  */
    ELSEIF = 299,                  /* ELSEIF  */
    ELSE = 300,                    /* ELSE  */
    RETURN = 301,                  /* RETURN  */
    WHILE = 302,                   /* WHILE  */
    INT = 303,                     /* INT  */
    FLOAT = 304,                   /* FLOAT  */
    MULT = 305                     /* MULT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 35 "parser.y"

	int number;
	float float_number;
	char character;
	char* string;
	char* operator;
	struct ASTNode* ast;

#line 123 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
