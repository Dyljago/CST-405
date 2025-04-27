/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


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


#line 105 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TYPE = 3,                       /* TYPE  */
  YYSYMBOL_VOID = 4,                       /* VOID  */
  YYSYMBOL_FUNC_DECL = 5,                  /* FUNC_DECL  */
  YYSYMBOL_MAIN = 6,                       /* MAIN  */
  YYSYMBOL_BOOL = 7,                       /* BOOL  */
  YYSYMBOL_ID = 8,                         /* ID  */
  YYSYMBOL_NUMBER = 9,                     /* NUMBER  */
  YYSYMBOL_DECIMAL_NUMBER = 10,            /* DECIMAL_NUMBER  */
  YYSYMBOL_STR = 11,                       /* STR  */
  YYSYMBOL_CHR = 12,                       /* CHR  */
  YYSYMBOL_END = 13,                       /* END  */
  YYSYMBOL_LPAR = 14,                      /* LPAR  */
  YYSYMBOL_RPAR = 15,                      /* RPAR  */
  YYSYMBOL_LBRA = 16,                      /* LBRA  */
  YYSYMBOL_RBRA = 17,                      /* RBRA  */
  YYSYMBOL_LBLO = 18,                      /* LBLO  */
  YYSYMBOL_RBLO = 19,                      /* RBLO  */
  YYSYMBOL_SEMICOLON = 20,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 21,                     /* COLON  */
  YYSYMBOL_COMMA = 22,                     /* COMMA  */
  YYSYMBOL_EQ = 23,                        /* EQ  */
  YYSYMBOL_PEQ = 24,                       /* PEQ  */
  YYSYMBOL_SEQ = 25,                       /* SEQ  */
  YYSYMBOL_MEQ = 26,                       /* MEQ  */
  YYSYMBOL_DEQ = 27,                       /* DEQ  */
  YYSYMBOL_DUP = 28,                       /* DUP  */
  YYSYMBOL_NUP = 29,                       /* NUP  */
  YYSYMBOL_LT = 30,                        /* LT  */
  YYSYMBOL_LTE = 31,                       /* LTE  */
  YYSYMBOL_GT = 32,                        /* GT  */
  YYSYMBOL_GTE = 33,                       /* GTE  */
  YYSYMBOL_PLUS = 34,                      /* PLUS  */
  YYSYMBOL_MINUS = 35,                     /* MINUS  */
  YYSYMBOL_MUL = 36,                       /* MUL  */
  YYSYMBOL_DIV = 37,                       /* DIV  */
  YYSYMBOL_POW = 38,                       /* POW  */
  YYSYMBOL_FAC = 39,                       /* FAC  */
  YYSYMBOL_FIB = 40,                       /* FIB  */
  YYSYMBOL_WRITE = 41,                     /* WRITE  */
  YYSYMBOL_PRINT = 42,                     /* PRINT  */
  YYSYMBOL_IF = 43,                        /* IF  */
  YYSYMBOL_ELSEIF = 44,                    /* ELSEIF  */
  YYSYMBOL_ELSE = 45,                      /* ELSE  */
  YYSYMBOL_RETURN = 46,                    /* RETURN  */
  YYSYMBOL_WHILE = 47,                     /* WHILE  */
  YYSYMBOL_INT = 48,                       /* INT  */
  YYSYMBOL_FLOAT = 49,                     /* FLOAT  */
  YYSYMBOL_MULT = 50,                      /* MULT  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_Program = 52,                   /* Program  */
  YYSYMBOL_MainFunc = 53,                  /* MainFunc  */
  YYSYMBOL_54_1 = 54,                      /* $@1  */
  YYSYMBOL_Body = 55,                      /* Body  */
  YYSYMBOL_FuncDeclList = 56,              /* FuncDeclList  */
  YYSYMBOL_FuncDecl = 57,                  /* FuncDecl  */
  YYSYMBOL_58_2 = 58,                      /* $@2  */
  YYSYMBOL_FuncCall = 59,                  /* FuncCall  */
  YYSYMBOL_ParamList = 60,                 /* ParamList  */
  YYSYMBOL_ParamDecl = 61,                 /* ParamDecl  */
  YYSYMBOL_VarDeclList = 62,               /* VarDeclList  */
  YYSYMBOL_VarDecl = 63,                   /* VarDecl  */
  YYSYMBOL_StmtList = 64,                  /* StmtList  */
  YYSYMBOL_Stmt = 65,                      /* Stmt  */
  YYSYMBOL_WhileStatement = 66,            /* WhileStatement  */
  YYSYMBOL_IfStatements = 67,              /* IfStatements  */
  YYSYMBOL_ElseIfStatements = 68,          /* ElseIfStatements  */
  YYSYMBOL_ElseStatement = 69,             /* ElseStatement  */
  YYSYMBOL_ExprList = 70,                  /* ExprList  */
  YYSYMBOL_Expr = 71,                      /* Expr  */
  YYSYMBOL_Array_Decl = 72,                /* Array_Decl  */
  YYSYMBOL_Array = 73,                     /* Array  */
  YYSYMBOL_BinOp = 74                      /* BinOp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   843

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  196

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   122,   122,   130,   133,   133,   142,   148,   153,   154,
     161,   166,   166,   203,   208,   218,   219,   225,   231,   236,
     259,   264,   265,   277,   282,   309,   335,   346,   355,   359,
     363,   367,   372,   373,   381,   390,   400,   403,   412,   416,
     424,   428,   436,   444,   448,   456,   460,   468,   472,   473,
     474,   478,   482,   486,   490,   494,   498,   502,   506,   510,
     516,   522,   530,   535,   544,   554,   564,   574,   585,   592,
     600,   605,   610,   616,   627,   639,   648,   655,   662,   668,
     674,   680,   685,   696,   721,   746,   752,   758,   764,   770,
     776,   781,   786,   791,   796,   801,   806,   812,   818,   824,
     830,   836,   842
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TYPE", "VOID",
  "FUNC_DECL", "MAIN", "BOOL", "ID", "NUMBER", "DECIMAL_NUMBER", "STR",
  "CHR", "END", "LPAR", "RPAR", "LBRA", "RBRA", "LBLO", "RBLO",
  "SEMICOLON", "COLON", "COMMA", "EQ", "PEQ", "SEQ", "MEQ", "DEQ", "DUP",
  "NUP", "LT", "LTE", "GT", "GTE", "PLUS", "MINUS", "MUL", "DIV", "POW",
  "FAC", "FIB", "WRITE", "PRINT", "IF", "ELSEIF", "ELSE", "RETURN",
  "WHILE", "INT", "FLOAT", "MULT", "$accept", "Program", "MainFunc", "$@1",
  "Body", "FuncDeclList", "FuncDecl", "$@2", "FuncCall", "ParamList",
  "ParamDecl", "VarDeclList", "VarDecl", "StmtList", "Stmt",
  "WhileStatement", "IfStatements", "ElseIfStatements", "ElseStatement",
  "ExprList", "Expr", "Array_Decl", "Array", "BinOp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-148)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-74)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      78,   135,     4,     9,    25,   121,    30,  -148,    36,  -148,
      40,  -148,  -148,   111,    49,  -148,    10,   110,    42,   119,
     123,   115,   125,  -148,   126,    10,   128,     7,  -148,     7,
       3,    19,   129,   345,    15,    -6,   130,    57,  -148,  -148,
    -148,    37,    58,    77,   134,   122,   137,   132,  -148,   345,
    -148,  -148,   131,   146,  -148,  -148,   139,  -148,   144,  -148,
     189,   189,   147,   232,  -148,  -148,   140,  -148,  -148,  -148,
    -148,   189,   185,   143,  -148,   189,   228,   189,   189,   485,
     189,  -148,  -148,   189,   189,   141,   189,    73,   176,   424,
     173,   180,   175,   271,   525,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,   189,  -148,   565,  -148,   464,   605,
    -148,   645,   666,   187,   183,   803,  -148,  -148,   189,  -148,
    -148,  -148,   188,   189,   142,   214,   191,   189,   215,   221,
    -148,   218,   231,  -148,  -148,   706,  -148,     7,   746,  -148,
       7,  -148,   189,  -148,   233,   235,   259,   260,    50,   314,
    -148,  -148,   264,   265,   204,  -148,   237,   267,   -12,   189,
       7,  -148,   268,   381,   240,   270,   786,   263,   322,  -148,
     272,   274,   389,   276,  -148,  -148,  -148,   332,  -148,   277,
       7,  -148,  -148,   302,   243,  -148
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    13,     0,     0,     0,     0,     0,     1,     0,     2,
      13,     9,    11,     0,     0,     4,     0,     0,    18,     0,
       0,    16,     0,    19,     0,     0,     0,     0,    17,     0,
      23,     0,     0,     0,     0,     0,     0,    28,    30,    12,
      62,     0,     0,     0,     0,     0,     0,     0,     6,     0,
      49,    48,     0,    23,    22,    26,     0,     5,     0,    24,
       0,     0,     0,     0,    81,    78,    75,    76,    77,    79,
      80,     0,     0,     0,    75,     0,     0,     0,     0,     0,
       0,    36,    33,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     0,     0,     0,   102,    39,    92,    93,    94,
      95,    96,    97,   100,   101,    98,    99,    85,    86,    87,
      88,    89,    90,    91,     0,    42,     0,    44,     0,     0,
      61,     0,     0,     0,    82,     0,    25,    14,     0,    84,
      35,    34,    43,     0,     0,    47,     0,     0,     0,     0,
      37,     0,     0,    72,    41,     0,    46,     0,     0,    60,
       0,    27,     0,    74,     0,     0,     0,     0,    64,     0,
      63,    83,     0,     0,    66,    65,     0,     0,    50,     0,
       0,    67,     0,     0,     0,     0,     0,     0,     0,    58,
       0,     0,     0,     0,    70,    56,    54,     0,    53,     0,
       0,    52,    51,     0,    68,    69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -148,  -148,  -148,  -148,   -29,   288,  -148,  -148,   257,   296,
    -148,   290,  -148,   278,  -147,  -148,  -148,   138,   161,   -81,
     -41,  -148,   284,   -73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     9,    17,    32,     4,     5,    14,    47,    20,
      21,    33,    34,    48,    49,    50,    51,   164,   165,    88,
      89,    35,    52,   114
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,    72,    76,   123,    79,   174,   -31,     6,    30,     7,
      31,    18,   168,    19,    55,   -21,    53,    56,    31,    87,
      -7,   133,    93,   -21,   -21,   -15,   180,    37,    38,     8,
      94,   185,   -21,   175,   116,   189,   118,   119,    12,   121,
     191,    13,   122,   133,   -10,   125,   133,   143,   -21,   -21,
     -21,    61,   133,   -21,   -21,    62,   -21,   -21,   -21,    64,
      63,   -21,   -21,    16,   -20,    65,    66,    67,    68,    69,
      70,   157,    71,   134,    95,    58,   -29,    59,    64,     1,
      60,   -29,    -8,     2,    65,    74,    67,    68,    69,    70,
     -29,    75,   145,   126,   162,   163,   148,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   -29,   -29,   -29,    15,   154,   -29,
     -29,   156,    10,    64,    22,    -8,     2,    23,   176,    65,
      74,    67,    68,    69,    70,    -3,    78,    25,    24,   -10,
      26,   177,    27,    95,    29,   -73,    39,    57,    77,   -31,
     -73,    80,    81,    85,    83,    84,    90,   -73,    62,   -73,
     124,   193,   -73,   115,   -73,   -73,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   -73,   -73,   -73,    95,   -73,   -73,   -73,
      64,   127,   129,   -40,    61,   130,    65,    74,    67,    68,
      69,    70,   -40,    86,   141,    96,   142,   147,   144,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   -40,   -40,   -40,    95,
     -40,   -40,   -40,    64,   146,   149,   -45,   150,   151,    65,
      91,    67,    68,    69,    70,   -45,    86,   152,   117,   163,
     158,   159,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   -45,
     -45,   -45,    95,   -45,   -45,   -45,   160,   161,   169,   -38,
     184,   170,   172,   173,   178,   181,   182,   162,   -38,   186,
     187,   131,   190,    11,   192,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   -38,   -38,   -38,    40,   -38,   -38,   -38,   194,
      92,    28,    41,    40,    54,   171,    73,    82,     0,     0,
      41,   166,   195,    40,     0,     0,     0,     0,     0,   -59,
      41,     0,     0,     0,     0,     0,    40,     0,     0,   -55,
       0,     0,     0,    41,     0,    42,    43,    44,     0,   167,
      45,    46,   -32,    42,    43,    44,     0,   -59,    45,    46,
       0,     0,     0,    42,    43,    44,     0,   -55,    45,    46,
       0,     0,    40,     0,     0,     0,    42,    43,    44,    41,
      40,    45,    46,     0,     0,     0,     0,    41,   179,     0,
       0,     0,     0,     0,     0,     0,   188,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    43,    44,    95,     0,    45,    46,     0,
      42,    43,    44,     0,     0,    45,    46,     0,     0,   -71,
       0,   -71,     0,     0,     0,     0,   128,     0,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    95,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   136,
       0,     0,     0,     0,     0,     0,    95,   137,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   120,     0,     0,     0,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     132,     0,     0,     0,     0,     0,     0,     0,     0,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,     0,     0,     0,     0,     0,     0,     0,     0,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     138,     0,     0,     0,     0,     0,     0,     0,     0,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     139,     0,     0,     0,     0,     0,     0,    95,     0,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   140,     0,     0,     0,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   153,     0,     0,     0,     0,     0,     0,     0,     0,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   155,     0,     0,     0,     0,     0,     0,     0,     0,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   183,     0,     0,    95,     0,     0,     0,     0,     0,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113
};

static const yytype_int16 yycheck[] =
{
      29,    42,    43,    84,    45,    17,     3,     3,     1,     0,
       3,     1,   159,     3,    20,     8,     1,    23,     3,    60,
      17,    94,    63,     8,    17,    15,   173,     8,     9,     4,
      71,   178,    17,    45,    75,   182,    77,    78,     8,    80,
     187,     5,    83,   116,     4,    86,   119,   128,    41,    42,
      43,    14,   125,    46,    47,    18,    41,    42,    43,     1,
      23,    46,    47,    14,    22,     7,     8,     9,    10,    11,
      12,   152,    14,   114,     1,    18,     3,    20,     1,     1,
      23,     8,     4,     5,     7,     8,     9,    10,    11,    12,
      17,    14,   133,    20,    44,    45,   137,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,     6,   147,    46,
      47,   150,     1,     1,    14,     4,     5,     8,   169,     7,
       8,     9,    10,    11,    12,     0,    14,    22,    15,     4,
      15,   170,    16,     1,    16,     3,    17,    17,    14,     3,
       8,    14,    20,     9,    23,    16,     9,    15,    18,    17,
      19,   190,    20,    20,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,     1,    45,    46,    47,
       1,    15,    19,     8,    14,    20,     7,     8,     9,    10,
      11,    12,    17,    14,    17,    20,    23,    16,    20,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,     1,
      45,    46,    47,     1,    20,    20,     8,    16,    20,     7,
       8,     9,    10,    11,    12,    17,    14,    16,    20,    45,
      17,    16,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,     1,    45,    46,    47,    17,    17,    14,     8,
      17,    16,    45,    16,    16,    45,    16,    44,    17,    17,
      16,    20,    16,     5,    17,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,     1,    45,    46,    47,    17,
      63,    25,     8,     1,    34,   164,    42,    49,    -1,    -1,
       8,    17,   194,     1,    -1,    -1,    -1,    -1,    -1,    17,
       8,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    17,
      -1,    -1,    -1,     8,    -1,    41,    42,    43,    -1,    45,
      46,    47,    17,    41,    42,    43,    -1,    45,    46,    47,
      -1,    -1,    -1,    41,    42,    43,    -1,    45,    46,    47,
      -1,    -1,     1,    -1,    -1,    -1,    41,    42,    43,     8,
       1,    46,    47,    -1,    -1,    -1,    -1,     8,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,     1,    -1,    46,    47,    -1,
      41,    42,    43,    -1,    -1,    46,    47,    -1,    -1,    15,
      -1,    17,    -1,    -1,    -1,    -1,    22,    -1,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    20,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    20,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     5,    52,    56,    57,     3,     0,     4,    53,
       1,    56,     8,     5,    58,     6,    14,    54,     1,     3,
      60,    61,    14,     8,    15,    22,    15,    16,    60,    16,
       1,     3,    55,    62,    63,    72,    55,     8,     9,    17,
       1,     8,    41,    42,    43,    46,    47,    59,    64,    65,
      66,    67,    73,     1,    62,    20,    23,    17,    18,    20,
      23,    14,    18,    23,     1,     7,     8,     9,    10,    11,
      12,    14,    71,    73,     8,    14,    71,    14,    14,    71,
      14,    20,    64,    23,    16,     9,    14,    71,    70,    71,
       9,     8,    59,    71,    71,     1,    20,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    74,    20,    71,    20,    71,    71,
      20,    71,    71,    70,    19,    71,    20,    15,    22,    19,
      20,    20,    15,    74,    71,    15,    15,    23,    15,    15,
      20,    17,    23,    70,    20,    71,    20,    16,    71,    20,
      16,    20,    16,    15,    55,    15,    55,    70,    17,    16,
      17,    17,    44,    45,    68,    69,    17,    45,    65,    14,
      16,    69,    45,    16,    17,    45,    71,    55,    16,    17,
      65,    45,    16,    15,    17,    65,    17,    16,    17,    65,
      16,    65,    17,    55,    17,    68
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    52,    54,    53,    55,    55,    56,    56,
      56,    58,    57,    57,    59,    60,    60,    60,    60,    61,
      61,    62,    62,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    64,    64,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    66,    67,    67,    67,    67,    68,    68,
      69,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    72,    73,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     0,     9,     2,     1,     0,     2,
       1,     0,    10,     1,     4,     0,     1,     3,     1,     2,
       1,     0,     2,     1,     3,     5,     2,     6,     2,     4,
       2,     1,     0,     2,     4,     4,     2,     4,     3,     3,
       2,     5,     3,     4,     3,     2,     5,     4,     1,     1,
       8,    12,    12,    11,    11,    11,    11,     7,    10,    10,
       5,     3,     1,     7,     7,     8,     8,     9,     7,     8,
       4,     1,     3,     3,     5,     1,     1,     1,     1,     1,
       1,     1,     5,     9,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_ID: /* ID  */
#line 102 "parser.y"
         { fprintf(yyoutput, "%s", ((*yyvaluep).string)); }
#line 1045 "parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: FuncDeclList MainFunc  */
#line 122 "parser.y"
                                  { 
							printf("The PARSER has started\n"); 
							printf("\nMAIN FUNCTION\n");
							root = malloc(sizeof(ASTNode));
							root->type = NodeType_Program;
							root->program.mainFunc = (yyvsp[0].ast);
							root->program.funcDeclList = (yyvsp[-1].ast);
							}
#line 1442 "parser.tab.c"
    break;

  case 3: /* Program: error  */
#line 130 "parser.y"
                { printf("PARSER: Syntax error on line %d\n", yylineno); exit(0); }
#line 1448 "parser.tab.c"
    break;

  case 4: /* $@1: %empty  */
#line 133 "parser.y"
                              {
		scope = "Global";
	}
#line 1456 "parser.tab.c"
    break;

  case 5: /* MainFunc: VOID FUNC_DECL MAIN $@1 LPAR RPAR LBRA Body RBRA  */
#line 135 "parser.y"
                                  { 
		printf("PARSER: Recognized main() function declaration\n"); 
		(yyval.ast) = createNode(NodeType_Main);
		(yyval.ast)->mainFunc.funcName = strdup((yyvsp[-6].string));
		(yyval.ast)->mainFunc.body = (yyvsp[-1].ast);
	}
#line 1467 "parser.tab.c"
    break;

  case 6: /* Body: VarDeclList StmtList  */
#line 142 "parser.y"
                           {
		printf("PARSER: Recognized function body\n"); 
		(yyval.ast) = createNode(NodeType_Body);
		(yyval.ast)->body.varDeclList = (yyvsp[-1].ast);
		(yyval.ast)->body.stmtList = (yyvsp[0].ast);
	}
#line 1478 "parser.tab.c"
    break;

  case 7: /* Body: error  */
#line 148 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid BODY syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1487 "parser.tab.c"
    break;

  case 8: /* FuncDeclList: %empty  */
#line 153 "parser.y"
               {/* No functions declared */ }
#line 1493 "parser.tab.c"
    break;

  case 9: /* FuncDeclList: FuncDecl FuncDeclList  */
#line 154 "parser.y"
                                { 
		printf("PARSER: Recognized function declaration list\n"); 
		(yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_FuncDeclList;
		(yyval.ast)->funcDeclList.funcDecl = (yyvsp[-1].ast);
		(yyval.ast)->funcDeclList.funcDeclList = (yyvsp[0].ast);
		}
#line 1505 "parser.tab.c"
    break;

  case 10: /* FuncDeclList: error  */
#line 161 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid FUNC DECL LIST syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1514 "parser.tab.c"
    break;

  case 11: /* $@2: %empty  */
#line 166 "parser.y"
                            {
        printf("PARSER: Beginning function declaration for %s\n", (yyvsp[0].string));
        /* Set the scope immediately when we see the function name */
        scope = strdup((yyvsp[0].string));
        
        /* Check if function already exists */
        symbol = lookupSymbol(symTab, (yyvsp[0].string));
        if (symbol != NULL) {
            printf("\n\n\n---------------------------\n\n\nPARSER: Function %s at line %d has already been declared - COMPILATION HALTED\n\n\n---------------------------\n\n\n", (yyvsp[0].string), yylineno);
            exit(0);
        }
        /* We'll add the function to symbol table after we know parameter count */
	}
#line 1532 "parser.tab.c"
    break;

  case 12: /* FuncDecl: FUNC_DECL TYPE ID $@2 LPAR ParamList RPAR LBRA Body RBRA  */
#line 178 "parser.y"
                                            { 
		 printf("PARSER: Completed function declaration\n");
        
        /* Count parameters - this was moved after parsing them */
        ASTNode* traverse = (yyvsp[-4].ast);
        int paramSize = 0;
        while (traverse && traverse->paramDeclList.paramDecl != NULL) {
            paramSize++;
            traverse = traverse->paramDeclList.paramDeclList;
        }
        printf("PARAM Size: %d\n", paramSize);
        
        /* Now add the function to symbol table with correct param count */
        addSymbol(symTab, (yyvsp[-7].string), (yyvsp[-8].string), "Func", paramSize, "Global");
        printSymbolTable(symTab);
        printf("\n******************************************\n\n");
        
        /* Create the AST node */
        (yyval.ast) = malloc(sizeof(ASTNode));
        (yyval.ast)->type = NodeType_FuncDecl;
        (yyval.ast)->funcDecl.funcName = (yyvsp[-7].string);
        (yyval.ast)->funcDecl.returnType = (yyvsp[-8].string);
        (yyval.ast)->funcDecl.body = (yyvsp[-1].ast);
        (yyval.ast)->funcDecl.paramList = (yyvsp[-4].ast);
	}
#line 1562 "parser.tab.c"
    break;

  case 13: /* FuncDecl: error  */
#line 203 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid FUNC DECL syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1571 "parser.tab.c"
    break;

  case 14: /* FuncCall: ID LPAR ExprList RPAR  */
#line 208 "parser.y"
                                {
	printf("PARSER: Recognized func call\n");
	printf("\n******************************************\n\n");
	//TODO: 
	(yyval.ast) = malloc(sizeof(ASTNode));
	(yyval.ast)->type = NodeType_FuncCall;
	(yyval.ast)->funcCall.funcName = strdup((yyvsp[-3].string));
	(yyval.ast)->funcCall.exprList = (yyvsp[-1].ast);
}
#line 1585 "parser.tab.c"
    break;

  case 15: /* ParamList: %empty  */
#line 218 "parser.y"
            {/*empty, i.e. it is possible not to have any parameter*/}
#line 1591 "parser.tab.c"
    break;

  case 16: /* ParamList: ParamDecl  */
#line 219 "parser.y"
                    {printf("One parameter\n");
		// Create AST node for VarDeclList
		(yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_ParamDeclList;
		(yyval.ast)->paramDeclList.paramDecl = (yyvsp[0].ast);
	}
#line 1602 "parser.tab.c"
    break;

  case 17: /* ParamList: ParamDecl COMMA ParamList  */
#line 225 "parser.y"
                                    { printf("PARSER: Recognized parameter list\n"); 
		(yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_ParamDeclList;
		(yyval.ast)->paramDeclList.paramDecl = (yyvsp[-2].ast);
		(yyval.ast)->paramDeclList.paramDeclList = (yyvsp[0].ast);
	}
#line 1613 "parser.tab.c"
    break;

  case 18: /* ParamList: error  */
#line 231 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid PARAM LIST syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1622 "parser.tab.c"
    break;

  case 19: /* ParamDecl: TYPE ID  */
#line 236 "parser.y"
                   { 
			printf("PARSER: Printing symbol table\n");
			printSymbolTable(symTab);

			/* Add variabe to symbol table
			Check if its already in there and add if not */

			symbol = lookupSymbol(symTab, (yyvsp[0].string));

			if (symbol != NULL) {
				printf("\n\n\n---------------------------\n\n\nPARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n\n\n---------------------------\n\n\n", (yyvsp[0].string), yylineno);
				exit(0);
			} else {
				addSymbol(symTab, (yyvsp[0].string), (yyvsp[-1].string), "Var", 0, scope);
				printSymbolTable(symTab);
				printf("\n******************************************\n\n");
			}
			printf("PARSER: Recognized parameter declaration\n"); 
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_ParamDecl;
			(yyval.ast)->paramDecl.paramName = (yyvsp[0].string);
			(yyval.ast)->paramDecl.paramType = (yyvsp[-1].string);
		}
#line 1650 "parser.tab.c"
    break;

  case 20: /* ParamDecl: error  */
#line 259 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid PARAM DECL syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1659 "parser.tab.c"
    break;

  case 21: /* VarDeclList: %empty  */
#line 264 "parser.y"
              {/*empty, i.e. it is possible not to declare a variable*/}
#line 1665 "parser.tab.c"
    break;

  case 22: /* VarDeclList: VarDecl VarDeclList  */
#line 265 "parser.y"
                              {  printf("PARSER: Recognized variable declaration list\n"); 

							// Create AST node for VarDeclList
							(yyval.ast) = malloc(sizeof(ASTNode));
							(yyval.ast)->type = NodeType_VarDeclList;
							(yyval.ast)->varDeclList.varDecl = (yyvsp[-1].ast);
							(yyval.ast)->varDeclList.varDeclList = (yyvsp[0].ast);
				
							// Set other fields as necessary

							
							}
#line 1682 "parser.tab.c"
    break;

  case 23: /* VarDeclList: error  */
#line 277 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nBase Error: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1691 "parser.tab.c"
    break;

  case 24: /* VarDecl: TYPE ID SEMICOLON  */
#line 282 "parser.y"
                           { printf("\nPARSER: Recognized variable declaration: %s\n", (yyvsp[-1].string));

								printf("PARSER: Printing symbol table\n");
								printSymbolTable(symTab);

								/* Add variabe to symbol table
								Check if its already in there and add if not */

								symbol = lookupSymbol(symTab, (yyvsp[-1].string));

								if (symbol != NULL) {
									printf("\n\n\n---------------------------\n\n\nPARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n\n\n---------------------------\n\n\n", (yyvsp[-1].string), yylineno);
									exit(0);
								} else {
									addSymbol(symTab, (yyvsp[-1].string), (yyvsp[-2].string), "Var", 0, scope);
									printSymbolTable(symTab);
									printf("\n******************************************\n\n");
								}

								// Create AST Node for VarDecl
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_VarDecl;
								(yyval.ast)->varDecl.varType = strdup((yyvsp[-2].string));
								(yyval.ast)->varDecl.varName = strdup((yyvsp[-1].string));
								// Set other fields as necessary

							 }
#line 1723 "parser.tab.c"
    break;

  case 25: /* VarDecl: TYPE ID EQ Expr SEMICOLON  */
#line 309 "parser.y"
                                            { printf("PARSER: Recognized variable declaration: %s\n", (yyvsp[-3].string));
								printf("PARSER: Printing symbol table\n");
								printSymbolTable(symTab);

								/* Add variabe to symbol table
								Check if its already in there and add if not */

								symbol = lookupSymbol(symTab, (yyvsp[-3].string));

								if (symbol != NULL) {
									printf("PARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n", (yyvsp[-3].string), yylineno);
									exit(0);
								} else {
									addSymbol(symTab, (yyvsp[-3].string), (yyvsp[-4].string), "Var", 0, scope);
									printSymbolTable(symTab);
									printf("\n******************************************\n\n");
								}

								// Create AST Node for VarDecl
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_VarDeclAssign;
								(yyval.ast)->varDeclAssign.varType = strdup((yyvsp[-4].string));
								(yyval.ast)->varDeclAssign.varName = strdup((yyvsp[-3].string));
								(yyval.ast)->varDeclAssign.varAssign = (yyvsp[-1].ast);
								// Set other fields as necessary
			}
#line 1754 "parser.tab.c"
    break;

  case 26: /* VarDecl: Array_Decl SEMICOLON  */
#line 335 "parser.y"
                                       { 
			// E.G. int myList[10];
				printf("PARSER: Recognized array declaration: %s\n", (yyvsp[-1].ast)->arrDecl.array->array.arrName);

				// Just pass the already created ASTNode along
				(yyval.ast) = (yyvsp[-1].ast);

				// Add to symbol table using data from the inner array node
				addSymbol(symTab, (yyvsp[-1].ast)->arrDecl.array->array.arrName, (yyvsp[-1].ast)->arrDecl.varType, "Arr", (yyvsp[-1].ast)->arrDecl.array->array.arrIndex, scope);
				printSymbolTable(symTab);
			}
#line 1770 "parser.tab.c"
    break;

  case 27: /* VarDecl: Array_Decl EQ LBRA ExprList RBRA SEMICOLON  */
#line 346 "parser.y"
                                                             {
			printf("PARSER: Recognized array declaration with initialization: %s\n", (yyvsp[-5].ast)->arrDecl.array->array.arrName);
			// Set the exprList in the array declaration
			(yyvsp[-5].ast)->arrDecl.exprList = (yyvsp[-2].ast);
			(yyval.ast) = (yyvsp[-5].ast);
			// Add to symbol table
			addSymbol(symTab, (yyvsp[-5].ast)->arrDecl.array->array.arrName, (yyvsp[-5].ast)->arrDecl.varType, "Arr", (yyvsp[-5].ast)->arrDecl.array->array.arrIndex, scope);
			printSymbolTable(symTab);
		}
#line 1784 "parser.tab.c"
    break;

  case 28: /* VarDecl: TYPE ID  */
#line 355 "parser.y"
                          {
                  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after declaring variable: %s on line %d\n\n\n---------------------------\n\n\n", (yyvsp[0].string), yylineno-1);
				  exit(0);
             }
#line 1793 "parser.tab.c"
    break;

  case 29: /* VarDecl: TYPE ID EQ Expr  */
#line 359 "parser.y"
                                  {
                  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after declaring variable: %s on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-2].string), yylineno-1);
				  exit(0);
             }
#line 1802 "parser.tab.c"
    break;

  case 30: /* VarDecl: TYPE NUMBER  */
#line 363 "parser.y"
                              {
                  printf ("\n\n\n---------------------------\n\n\nCannot use number as a variable name for: '%s %d' on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-1].string), (yyvsp[0].number), yylineno);
				  exit(0);
             }
#line 1811 "parser.tab.c"
    break;

  case 31: /* VarDecl: error  */
#line 367 "parser.y"
                        { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1820 "parser.tab.c"
    break;

  case 32: /* StmtList: %empty  */
#line 372 "parser.y"
           {/*empty, i.e. it is possible not to have any statement*/}
#line 1826 "parser.tab.c"
    break;

  case 33: /* StmtList: Stmt StmtList  */
#line 373 "parser.y"
                        { printf("PARSER: Recognized statement list\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_StmtList;
						(yyval.ast)->stmtList.stmt = (yyvsp[-1].ast);
						(yyval.ast)->stmtList.stmtList = (yyvsp[0].ast);
						// Set other fields as necessary
					}
#line 1838 "parser.tab.c"
    break;

  case 34: /* Stmt: ID EQ Expr SEMICOLON  */
#line 381 "parser.y"
                           { /* code TBD */
								printf("PARSER: Recognized assignment statement\n");
			 					printf("\n******************************************\n\n");
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_AssignStmt;
								(yyval.ast)->assignStmt.varName = strdup((yyvsp[-3].string));
								(yyval.ast)->assignStmt.operator = (yyvsp[-2].operator);
								(yyval.ast)->assignStmt.expr = (yyvsp[-1].ast);
 	}
#line 1852 "parser.tab.c"
    break;

  case 35: /* Stmt: ID EQ FuncCall SEMICOLON  */
#line 390 "parser.y"
                                   { /* code TBD */
			printf("PARSER: Recognized func assign\n");
			printf("\n******************************************\n\n");
			//TODO: 
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_FuncCallAssign;
			(yyval.ast)->funcAssignStmt.varName = strdup((yyvsp[-3].string));
			(yyval.ast)->funcAssignStmt.funcCall = (yyvsp[-1].ast);
			(yyval.ast)->funcAssignStmt.operator = (yyvsp[-2].operator);
 	}
#line 1867 "parser.tab.c"
    break;

  case 36: /* Stmt: FuncCall SEMICOLON  */
#line 400 "parser.y"
                             { /* code TBD */
			printf("PARSER: Recognized func call\n");
 	}
#line 1875 "parser.tab.c"
    break;

  case 37: /* Stmt: Array EQ Expr SEMICOLON  */
#line 403 "parser.y"
                                  { /* code TBD */
			printf("PARSER: Recognized array assignment statement\n");
			printf("\n******************************************\n\n");
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_ArrDeclAssign;
			(yyval.ast)->arrAssignStmt.operator = (yyvsp[-2].operator);
			(yyval.ast)->arrAssignStmt.array = (yyvsp[-3].ast);
			(yyval.ast)->arrAssignStmt.expr = (yyvsp[-1].ast);
 	}
#line 1889 "parser.tab.c"
    break;

  case 38: /* Stmt: ID EQ Expr  */
#line 412 "parser.y"
                     {
		      printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s %s on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-2].string),(yyvsp[-1].operator),(yyvsp[0].ast), yylineno-1);
			  exit(0);
			}
#line 1898 "parser.tab.c"
    break;

  case 39: /* Stmt: WRITE Expr SEMICOLON  */
#line 416 "parser.y"
                               { 
								printf("PARSER: Recognized write statement -> write %s;\n", (yyvsp[-1].ast)); 
								printf("\n******************************************\n\n"); 
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_PrintStmt;
								(yyval.ast)->printStmt.varName = strdup((yyvsp[-2].string));
								(yyval.ast)->printStmt.expr = (yyvsp[-1].ast);
						}
#line 1911 "parser.tab.c"
    break;

  case 40: /* Stmt: WRITE Expr  */
#line 424 "parser.y"
                     {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-1].string),(yyvsp[0].ast), yylineno-1);
			  exit(0);
			}
#line 1920 "parser.tab.c"
    break;

  case 41: /* Stmt: WRITE LPAR Expr RPAR SEMICOLON  */
#line 428 "parser.y"
                                         { 
			printf("PARSER: Recognized write statement -> write(%s);\n", (yyvsp[-2].ast)); 
			printf("\n******************************************\n\n"); 
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_PrintStmt;
			(yyval.ast)->printStmt.varName = strdup((yyvsp[-4].string));
			(yyval.ast)->printStmt.expr = (yyvsp[-2].ast);
		}
#line 1933 "parser.tab.c"
    break;

  case 42: /* Stmt: WRITE Array SEMICOLON  */
#line 436 "parser.y"
                                { 
			printf("PARSER: Recognized write array statement -> write %s;\n", (yyvsp[-1].ast)); 
			printf("\n******************************************\n\n"); 
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_ArrPrintStmt;
			(yyval.ast)->arrPrintStmt.varName = strdup((yyvsp[-2].string));
			(yyval.ast)->arrPrintStmt.array = (yyvsp[-1].ast);
		}
#line 1946 "parser.tab.c"
    break;

  case 43: /* Stmt: WRITE LPAR Expr RPAR  */
#line 444 "parser.y"
                               {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-3].string),(yyvsp[-1].ast), yylineno-1);
			  exit(0);
			}
#line 1955 "parser.tab.c"
    break;

  case 44: /* Stmt: PRINT Expr SEMICOLON  */
#line 448 "parser.y"
                               { 
								printf("PARSER: Recognized print statement -> print %s;\n", (yyvsp[-1].ast)); 
								printf("\n******************************************\n\n"); 
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_PrintStmt;
								(yyval.ast)->printStmt.varName = strdup((yyvsp[-2].string));
								(yyval.ast)->printStmt.expr = (yyvsp[-1].ast);
						}
#line 1968 "parser.tab.c"
    break;

  case 45: /* Stmt: PRINT Expr  */
#line 456 "parser.y"
                     {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-1].string),(yyvsp[0].ast), yylineno-1);
			  exit(0);
			}
#line 1977 "parser.tab.c"
    break;

  case 46: /* Stmt: PRINT LPAR Expr RPAR SEMICOLON  */
#line 460 "parser.y"
                                         { 
								printf("PARSER: Recognized print statement -> print(%s);\n", (yyvsp[-2].ast)); 
								printf("\n******************************************\n\n"); 
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_PrintStmt;
								(yyval.ast)->printStmt.varName = strdup((yyvsp[-4].string));
								(yyval.ast)->printStmt.expr = (yyvsp[-2].ast);
						}
#line 1990 "parser.tab.c"
    break;

  case 47: /* Stmt: PRINT LPAR Expr RPAR  */
#line 468 "parser.y"
                               {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-3].string),(yyvsp[-1].ast), yylineno-1);
			  exit(0);
			}
#line 1999 "parser.tab.c"
    break;

  case 48: /* Stmt: IfStatements  */
#line 472 "parser.y"
                       {}
#line 2005 "parser.tab.c"
    break;

  case 49: /* Stmt: WhileStatement  */
#line 473 "parser.y"
                         {}
#line 2011 "parser.tab.c"
    break;

  case 50: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt  */
#line 474 "parser.y"
                                              { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-7].string),(yyvsp[-5].ast), brackStart);
			  exit(0); 
			}
#line 2020 "parser.tab.c"
    break;

  case 51: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt ELSE LBRA Stmt RBRA  */
#line 478 "parser.y"
                                                                  { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-11].string),(yyvsp[-9].ast), brackStart);
			  exit(0);
	 		}
#line 2029 "parser.tab.c"
    break;

  case 52: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA ELSE LBRA Stmt  */
#line 482 "parser.y"
                                                                  { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-11].string),(yyvsp[-9].ast), brackStart);
			  exit(0);
	 		}
#line 2038 "parser.tab.c"
    break;

  case 53: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt ELSE LBRA RBRA  */
#line 486 "parser.y"
                                                             { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-10].string),(yyvsp[-8].ast), brackStart);
			  exit(0);
	 		}
#line 2047 "parser.tab.c"
    break;

  case 54: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA ELSE LBRA Stmt RBRA  */
#line 490 "parser.y"
                                                             { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-10].string),(yyvsp[-8].ast), brackStart);
			  exit(0);
	 		}
#line 2056 "parser.tab.c"
    break;

  case 55: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA ELSE LBRA  */
#line 494 "parser.y"
                                                             { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-10].string),(yyvsp[-8].ast), brackStart);
			  exit(0);
	 		}
#line 2065 "parser.tab.c"
    break;

  case 56: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA RBRA ELSE LBRA Stmt  */
#line 498 "parser.y"
                                                             { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-10].string),(yyvsp[-8].ast), brackStart);
			  exit(0);
	 		}
#line 2074 "parser.tab.c"
    break;

  case 57: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA  */
#line 502 "parser.y"
                                         { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-6].string),(yyvsp[-4].ast), brackStart);
			  exit(0);
	 		}
#line 2083 "parser.tab.c"
    break;

  case 58: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA ELSE LBRA RBRA  */
#line 506 "parser.y"
                                                        { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-9].string),(yyvsp[-7].ast), brackStart);
			  exit(0);
	 		}
#line 2092 "parser.tab.c"
    break;

  case 59: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA RBRA ELSE LBRA  */
#line 510 "parser.y"
                                                        { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-9].string),(yyvsp[-7].ast), brackStart);
			  exit(0);
	 		}
#line 2101 "parser.tab.c"
    break;

  case 60: /* Stmt: RETURN LPAR Expr RPAR SEMICOLON  */
#line 516 "parser.y"
                                          { printf("PARSER: Recognized return statement"); 
			printf("\n******************************************\n\n"); 
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_ReturnStmt;
			(yyval.ast)->returnStmt.varName = strdup((yyvsp[-4].string));
			(yyval.ast)->returnStmt.expr = (yyvsp[-2].ast); }
#line 2112 "parser.tab.c"
    break;

  case 61: /* Stmt: RETURN Expr SEMICOLON  */
#line 522 "parser.y"
                                { 
								printf("PARSER: Recognized return statement"); 
								printf("\n******************************************\n\n"); 
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_ReturnStmt;
								(yyval.ast)->returnStmt.varName = strdup((yyvsp[-2].string));
								(yyval.ast)->returnStmt.expr = (yyvsp[-1].ast); 
								}
#line 2125 "parser.tab.c"
    break;

  case 62: /* Stmt: error  */
#line 530 "parser.y"
            { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 2134 "parser.tab.c"
    break;

  case 63: /* WhileStatement: WHILE LPAR Expr RPAR LBRA Body RBRA  */
#line 535 "parser.y"
                                                    {
	printf("PARSER: Recognized while statement\n"); 
	printf("\n******************************************\n\n"); 
	(yyval.ast) = malloc(sizeof(ASTNode));
	(yyval.ast)->type = NodeType_WhileStmt;
	(yyval.ast)->whileStatement.expr = (yyvsp[-4].ast);
	(yyval.ast)->whileStatement.body = (yyvsp[-1].ast);
}
#line 2147 "parser.tab.c"
    break;

  case 64: /* IfStatements: IF LPAR Expr RPAR LBRA Body RBRA  */
#line 544 "parser.y"
                                               { 
		printf("PARSER: Recognized if statement\n"); 
		printf("\n******************************************\n\n"); 
		(yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_IfStmt;
		(yyval.ast)->ifStatement.expr = (yyvsp[-4].ast);
		(yyval.ast)->ifStatement.body = (yyvsp[-1].ast);
		(yyval.ast)->ifStatement.elseIfStatement = NULL;
		(yyval.ast)->ifStatement.elseStatement = NULL;
	}
#line 2162 "parser.tab.c"
    break;

  case 65: /* IfStatements: IF LPAR Expr RPAR LBRA Body RBRA ElseStatement  */
#line 554 "parser.y"
                                                         { 
		printf("PARSER: Recognized if-else statement\n"); 
		printf("\n******************************************\n\n"); 
		(yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_IfStmt;
		(yyval.ast)->ifStatement.expr = (yyvsp[-5].ast);
		(yyval.ast)->ifStatement.body = (yyvsp[-2].ast);
		(yyval.ast)->ifStatement.elseIfStatement = NULL;
		(yyval.ast)->ifStatement.elseStatement = (yyvsp[0].ast);
	}
#line 2177 "parser.tab.c"
    break;

  case 66: /* IfStatements: IF LPAR Expr RPAR LBRA Body RBRA ElseIfStatements  */
#line 564 "parser.y"
                                                            { 
		printf("PARSER: Recognized if-else_if statement\n"); 
		printf("\n******************************************\n\n"); 
		(yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_IfStmt;
		(yyval.ast)->ifStatement.expr = (yyvsp[-5].ast);
		(yyval.ast)->ifStatement.body = (yyvsp[-2].ast);
		(yyval.ast)->ifStatement.elseIfStatement = (yyvsp[0].ast);
		(yyval.ast)->ifStatement.elseStatement = NULL;
	}
#line 2192 "parser.tab.c"
    break;

  case 67: /* IfStatements: IF LPAR Expr RPAR LBRA Body RBRA ElseIfStatements ElseStatement  */
#line 574 "parser.y"
                                                                          { 
		printf("PARSER: Recognized if-else_if-else statement\n"); 
		printf("\n******************************************\n\n"); 
		(yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_IfStmt;
		(yyval.ast)->ifStatement.expr = (yyvsp[-6].ast);
		(yyval.ast)->ifStatement.body = (yyvsp[-3].ast);
		(yyval.ast)->ifStatement.elseIfStatement = (yyvsp[-1].ast);
		(yyval.ast)->ifStatement.elseStatement = (yyvsp[0].ast);
	}
#line 2207 "parser.tab.c"
    break;

  case 68: /* ElseIfStatements: ELSEIF LPAR Expr RPAR LBRA Body RBRA  */
#line 585 "parser.y"
                                                       {
        (yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_ElseIfStmt;
		(yyval.ast)->ifStatement.expr = (yyvsp[-4].ast);
		(yyval.ast)->ifStatement.body = (yyvsp[-1].ast);
		(yyval.ast)->ifStatement.elseIfStatement = NULL;
	}
#line 2219 "parser.tab.c"
    break;

  case 69: /* ElseIfStatements: ELSEIF LPAR Expr RPAR LBRA Body RBRA ElseIfStatements  */
#line 592 "parser.y"
                                                                {
	     (yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_ElseIfStmt;
		(yyval.ast)->ifStatement.expr = (yyvsp[-5].ast);
		(yyval.ast)->ifStatement.body = (yyvsp[-2].ast);
		(yyval.ast)->ifStatement.elseIfStatement = (yyvsp[0].ast);
	}
#line 2231 "parser.tab.c"
    break;

  case 70: /* ElseStatement: ELSE LBRA Body RBRA  */
#line 600 "parser.y"
                                   {
	(yyval.ast) = createNode(NodeType_ElseStmt);
    (yyval.ast)->elseStatement.body = (yyvsp[-1].ast);
}
#line 2240 "parser.tab.c"
    break;

  case 71: /* ExprList: Expr  */
#line 605 "parser.y"
               {
    (yyval.ast) = createNode(NodeType_ExprList);
    (yyval.ast)->exprList.expr = (yyvsp[0].ast);
    (yyval.ast)->exprList.next = NULL;
	}
#line 2250 "parser.tab.c"
    break;

  case 72: /* ExprList: Expr COMMA ExprList  */
#line 610 "parser.y"
                              {
    (yyval.ast) = createNode(NodeType_ExprList);
    (yyval.ast)->exprList.expr = (yyvsp[-2].ast);
    (yyval.ast)->exprList.next = (yyvsp[0].ast);
	}
#line 2260 "parser.tab.c"
    break;

  case 73: /* Expr: Expr BinOp Expr  */
#line 616 "parser.y"
                      { printf("PARSER: Recognized expression\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_Expr;
						(yyval.ast)->expr.left = (yyvsp[-2].ast);
						(yyval.ast)->expr.right = (yyvsp[0].ast);
						(yyval.ast)->expr.operator = (yyvsp[-1].ast)->binOp.operator;
						// TODO: Fix double initialization of 8+3
						// printf("--%s %c %s--\n", $1, $2->binOp.operator, $3);
						
						// Set other fields as necessary
					  }
#line 2276 "parser.tab.c"
    break;

  case 74: /* Expr: LPAR Expr BinOp Expr RPAR  */
#line 627 "parser.y"
                                    { printf("PARSER: Recognized expression\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_Expr;
						(yyval.ast)->expr.left = (yyvsp[-3].ast);
						(yyval.ast)->expr.right = (yyvsp[-1].ast);
						(yyval.ast)->expr.operator = (yyvsp[-2].ast)->binOp.operator;
						// TODO: Fix double initialization of 8+3
						// printf("--%s %c %s--\n", $2, $3->binOp.operator, $4);
						
						// Set other fields as necessary
					  }
#line 2292 "parser.tab.c"
    break;

  case 75: /* Expr: ID  */
#line 639 "parser.y"
             { printf("ASSIGNMENT statement \n"); 
			if (lookupSymbol(symTab, (yyvsp[0].string)) == NULL) {
                printf("\n\n\n---------------------------\n\n\nSemantic error: Variable %s on line %d has not been declared\n\n\n---------------------------\n\n\n", (yyvsp[0].string), yylineno);
                exit(0);
            }
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_SimpleID;
			(yyval.ast)->simpleID.name = (yyvsp[0].string);
		}
#line 2306 "parser.tab.c"
    break;

  case 76: /* Expr: NUMBER  */
#line 648 "parser.y"
                 { 
				// printf("\n\n %d \n\n", $1);
				printf("PARSER: Recognized number\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_SimpleExpr;
				(yyval.ast)->simpleExpr.number = (yyvsp[0].number);
			 }
#line 2318 "parser.tab.c"
    break;

  case 77: /* Expr: DECIMAL_NUMBER  */
#line 655 "parser.y"
                         { 
				// printf("\n\n %f \n\n", $1);
				printf("PARSER: Recognized float number\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_SimpleDecimal;
				(yyval.ast)->simpleDecimal.number = (yyvsp[0].float_number);
			 }
#line 2330 "parser.tab.c"
    break;

  case 78: /* Expr: BOOL  */
#line 662 "parser.y"
               { 
				printf("PARSER: Recognized boolean\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_SimpleString;
				(yyval.ast)->simpleString.name = (yyvsp[0].string);
			 }
#line 2341 "parser.tab.c"
    break;

  case 79: /* Expr: STR  */
#line 668 "parser.y"
                {
				printf("PARSER: Recognized string\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_SimpleString;
				(yyval.ast)->simpleString.name = (yyvsp[0].string);
			}
#line 2352 "parser.tab.c"
    break;

  case 80: /* Expr: CHR  */
#line 674 "parser.y"
                {
				printf("PARSER: Recognized char\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_SimpleID;
				(yyval.ast)->simpleID.name = (yyvsp[0].string);
			}
#line 2363 "parser.tab.c"
    break;

  case 81: /* Expr: error  */
#line 680 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 2372 "parser.tab.c"
    break;

  case 82: /* Array_Decl: TYPE ID LBLO NUMBER RBLO  */
#line 685 "parser.y"
                                     { printf("PARSER: Recognized array\n");
		(yyval.ast) = createNode(NodeType_ArrDecl);
		(yyval.ast)->arrDecl.varType = strdup((yyvsp[-4].string));

		ASTNode* arrayNode = createNode(NodeType_Array);
		arrayNode->array.arrName = strdup((yyvsp[-3].string));
		arrayNode->array.arrIndex = (yyvsp[-1].number);

		(yyval.ast)->arrDecl.array = arrayNode;
		(yyval.ast)->arrDecl.exprList = NULL;  // No initialization list
	}
#line 2388 "parser.tab.c"
    break;

  case 83: /* Array_Decl: TYPE ID LBLO NUMBER RBLO EQ LBRA ExprList RBRA  */
#line 696 "parser.y"
                                                         { 
		printf("PARSER: Recognized array declaration with initialization\n");
		(yyval.ast) = createNode(NodeType_ArrDecl);
		(yyval.ast)->arrDecl.varType = strdup((yyvsp[-8].string));
		ASTNode* arrayNode = createNode(NodeType_Array);
		arrayNode->array.arrName = strdup((yyvsp[-7].string));
		arrayNode->array.arrIndex = (yyvsp[-5].number);
		(yyval.ast)->arrDecl.array = arrayNode;
		(yyval.ast)->arrDecl.exprList = (yyvsp[-1].ast); // Set the initialization list
		
		// Check if the array size matches the expression list size
		int count = 0;
		ASTNode* current = (yyvsp[-1].ast);
		while (current != NULL) {
			count++;
			current = current->exprList.next;
		}
		
		if (count > (yyvsp[-5].number)) {
			printf("\n\n\n---------------------------\n\n\nError: Too many initializers for array '%s' of size %d on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-7].string), (yyvsp[-5].number), yylineno);
			exit(0);
		} 
	}
#line 2416 "parser.tab.c"
    break;

  case 84: /* Array: ID LBLO NUMBER RBLO  */
#line 721 "parser.y"
                           {
    // Check if the array exists in the symbol table
    Symbol* sym = lookupSymbol(symTab, (yyvsp[-3].string));
    if (sym == NULL) {
        printf("\n\n\n---------------------------\n\n\nSemantic error: Array '%s' on line %d has not been declared\n\n\n---------------------------\n\n\n", (yyvsp[-3].string), yylineno);
        exit(0);
    }
    
    // Check if the symbol is actually an array
    if (strcmp(sym->kind, "Arr") != 0) {
        printf("\n\n\n---------------------------\n\n\nSemantic error: '%s' is not an array on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-3].string), yylineno);
        exit(0);
    }
    
    // Check array bounds
    if ((yyvsp[-1].number) >= sym->size) {
        printf("\n\n\n---------------------------\n\n\nSemantic error: Array index %d out of bounds for array '%s' of size %d on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-1].number), (yyvsp[-3].string), sym->size, yylineno);
        exit(0);
    }
    
    (yyval.ast) = createNode(NodeType_Array);
    (yyval.ast)->array.arrName = strdup((yyvsp[-3].string));
    (yyval.ast)->array.arrIndex = (yyvsp[-1].number);
	}
#line 2445 "parser.tab.c"
    break;

  case 85: /* BinOp: PLUS  */
#line 746 "parser.y"
            {
				printf("PARSER: Recognized binary operator PLUS\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = (yyvsp[0].operator);
            }
#line 2456 "parser.tab.c"
    break;

  case 86: /* BinOp: MINUS  */
#line 752 "parser.y"
                {
				printf("PARSER: Recognized binary operator MINUS\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = (yyvsp[0].operator);
			}
#line 2467 "parser.tab.c"
    break;

  case 87: /* BinOp: MUL  */
#line 758 "parser.y"
                {
				printf("PARSER: Recognized binary operator MUL\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = (yyvsp[0].operator);
			}
#line 2478 "parser.tab.c"
    break;

  case 88: /* BinOp: DIV  */
#line 764 "parser.y"
                {
				printf("PARSER: Recognized binary operator DIV\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = (yyvsp[0].operator);
			}
#line 2489 "parser.tab.c"
    break;

  case 89: /* BinOp: POW  */
#line 770 "parser.y"
                {
				printf("PARSER: Recognized binary operator POW\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = (yyvsp[0].operator);
			}
#line 2500 "parser.tab.c"
    break;

  case 90: /* BinOp: FAC  */
#line 776 "parser.y"
                {
			    /* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator FAC\n");
			}
#line 2510 "parser.tab.c"
    break;

  case 91: /* BinOp: FIB  */
#line 781 "parser.y"
                {
			  	/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator FIB\n");
			}
#line 2520 "parser.tab.c"
    break;

  case 92: /* BinOp: PEQ  */
#line 786 "parser.y"
                {
			    /* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator PEQ\n");
			}
#line 2530 "parser.tab.c"
    break;

  case 93: /* BinOp: SEQ  */
#line 791 "parser.y"
                {
				/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator SEQ\n");
			}
#line 2540 "parser.tab.c"
    break;

  case 94: /* BinOp: MEQ  */
#line 796 "parser.y"
                {
				/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator MEQ\n");
			}
#line 2550 "parser.tab.c"
    break;

  case 95: /* BinOp: DEQ  */
#line 801 "parser.y"
                {
				/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator DEQ\n");
			}
#line 2560 "parser.tab.c"
    break;

  case 96: /* BinOp: DUP  */
#line 806 "parser.y"
                {
				printf("PARSER: Recognized boolean operator DUP\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = (yyvsp[0].operator);
			}
#line 2571 "parser.tab.c"
    break;

  case 97: /* BinOp: NUP  */
#line 812 "parser.y"
                {
				printf("PARSER: Recognized boolean operator NUP\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = (yyvsp[0].operator);
			}
#line 2582 "parser.tab.c"
    break;

  case 98: /* BinOp: GT  */
#line 818 "parser.y"
                {
				printf("PARSER: Recognized boolean operator GT\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = (yyvsp[0].operator);
			}
#line 2593 "parser.tab.c"
    break;

  case 99: /* BinOp: GTE  */
#line 824 "parser.y"
                {
				printf("PARSER: Recognized boolean operator GTE\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = (yyvsp[0].operator);
			}
#line 2604 "parser.tab.c"
    break;

  case 100: /* BinOp: LT  */
#line 830 "parser.y"
                {
				printf("PARSER: Recognized boolean operator GT\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = (yyvsp[0].operator);
			}
#line 2615 "parser.tab.c"
    break;

  case 101: /* BinOp: LTE  */
#line 836 "parser.y"
                {
				printf("PARSER: Recognized boolean operator LTE\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = (yyvsp[0].operator);
			}
#line 2626 "parser.tab.c"
    break;

  case 102: /* BinOp: error  */
#line 842 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 2635 "parser.tab.c"
    break;


#line 2639 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 847 "parser.y"


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
