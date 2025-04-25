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
  YYSYMBOL_PLUS = 29,                      /* PLUS  */
  YYSYMBOL_MINUS = 30,                     /* MINUS  */
  YYSYMBOL_MUL = 31,                       /* MUL  */
  YYSYMBOL_DIV = 32,                       /* DIV  */
  YYSYMBOL_POW = 33,                       /* POW  */
  YYSYMBOL_FAC = 34,                       /* FAC  */
  YYSYMBOL_FIB = 35,                       /* FIB  */
  YYSYMBOL_WRITE = 36,                     /* WRITE  */
  YYSYMBOL_PRINT = 37,                     /* PRINT  */
  YYSYMBOL_IF = 38,                        /* IF  */
  YYSYMBOL_ELSE = 39,                      /* ELSE  */
  YYSYMBOL_RETURN = 40,                    /* RETURN  */
  YYSYMBOL_WHILE = 41,                     /* WHILE  */
  YYSYMBOL_INT = 42,                       /* INT  */
  YYSYMBOL_FLOAT = 43,                     /* FLOAT  */
  YYSYMBOL_MULT = 44,                      /* MULT  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_Program = 46,                   /* Program  */
  YYSYMBOL_MainFunc = 47,                  /* MainFunc  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_Body = 49,                      /* Body  */
  YYSYMBOL_FuncDeclList = 50,              /* FuncDeclList  */
  YYSYMBOL_FuncDecl = 51,                  /* FuncDecl  */
  YYSYMBOL_52_2 = 52,                      /* $@2  */
  YYSYMBOL_FuncCall = 53,                  /* FuncCall  */
  YYSYMBOL_ParamList = 54,                 /* ParamList  */
  YYSYMBOL_ParamDecl = 55,                 /* ParamDecl  */
  YYSYMBOL_VarDeclList = 56,               /* VarDeclList  */
  YYSYMBOL_VarDecl = 57,                   /* VarDecl  */
  YYSYMBOL_StmtList = 58,                  /* StmtList  */
  YYSYMBOL_Stmt = 59,                      /* Stmt  */
  YYSYMBOL_ExprList = 60,                  /* ExprList  */
  YYSYMBOL_Expr = 61,                      /* Expr  */
  YYSYMBOL_Array_Decl = 62,                /* Array_Decl  */
  YYSYMBOL_Array = 63,                     /* Array  */
  YYSYMBOL_BinOp = 64                      /* BinOp  */
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
#define YYLAST   695

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  191

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   116,   116,   124,   127,   127,   136,   142,   147,   148,
     155,   160,   160,   197,   202,   212,   213,   219,   225,   230,
     253,   258,   259,   271,   276,   303,   329,   340,   349,   353,
     357,   361,   366,   367,   375,   384,   394,   397,   406,   410,
     418,   422,   430,   438,   442,   450,   454,   462,   466,   467,
     469,   470,   471,   472,   473,   474,   476,   480,   484,   488,
     492,   496,   500,   504,   508,   512,   517,   518,   519,   520,
     522,   528,   536,   548,   553,   559,   570,   582,   591,   598,
     605,   611,   617,   623,   628,   639,   664,   689,   695,   701,
     707,   713,   719,   724,   729,   734,   739,   744,   749,   755
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
  "PLUS", "MINUS", "MUL", "DIV", "POW", "FAC", "FIB", "WRITE", "PRINT",
  "IF", "ELSE", "RETURN", "WHILE", "INT", "FLOAT", "MULT", "$accept",
  "Program", "MainFunc", "$@1", "Body", "FuncDeclList", "FuncDecl", "$@2",
  "FuncCall", "ParamList", "ParamDecl", "VarDeclList", "VarDecl",
  "StmtList", "Stmt", "ExprList", "Expr", "Array_Decl", "Array", "BinOp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-133)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-76)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      65,    40,     8,    17,    10,    71,    16,  -133,    20,  -133,
      31,  -133,  -133,    39,    32,  -133,     3,    46,    52,    54,
      53,    55,    64,  -133,    66,     3,    67,    12,  -133,    12,
       4,    14,    63,   293,   237,   -15,    69,    38,  -133,  -133,
    -133,    41,   197,   645,    75,   657,    99,    61,  -133,   293,
      91,   112,  -133,  -133,   100,  -133,   108,  -133,   669,   669,
     109,   681,  -133,  -133,   102,  -133,  -133,  -133,  -133,   669,
     111,   101,  -133,   669,   152,   669,   669,   453,   669,  -133,
    -133,   669,   669,   104,   669,   193,   110,   381,   105,   113,
     106,   231,   474,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,   669,  -133,   495,
    -133,   416,   516,  -133,   437,   532,   115,   107,   610,  -133,
    -133,   669,  -133,  -133,  -133,   114,   669,    70,   134,   117,
     669,   135,   140,   669,  -133,   143,   148,  -133,  -133,   553,
    -133,   331,   574,  -133,   337,   595,  -133,   669,  -133,   126,
     149,   151,  -133,   153,   155,   156,   158,  -133,   275,  -133,
     343,  -133,   121,   129,   159,    -7,  -133,   178,   180,   183,
     349,   161,   186,  -133,  -133,   281,  -133,   195,   187,   387,
    -133,   198,  -133,   287,  -133,   199,  -133,  -133,   218,  -133,
    -133
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
      72,     0,     0,     0,     0,     0,     0,     0,     6,     0,
       0,    23,    22,    26,     0,     5,     0,    24,     0,     0,
       0,     0,    83,    80,    77,    78,    79,    81,    82,     0,
       0,     0,    77,     0,     0,     0,     0,     0,     0,    36,
      33,     0,     0,     0,     0,     0,     0,     0,     0,    77,
       0,     0,     0,    99,    39,    94,    95,    96,    97,    98,
      87,    88,    89,    90,    91,    92,    93,     0,    42,     0,
      44,     0,     0,    71,     0,     0,     0,    84,     0,    25,
      14,     0,    86,    35,    34,    43,     0,     0,    47,     0,
       0,     0,     0,     0,    37,     0,     0,    74,    41,     0,
      46,     0,     0,    70,     0,     0,    27,     0,    76,     0,
       0,     0,    66,     0,     0,     0,     0,    48,     0,    68,
       0,    85,     0,    54,     0,    56,    67,     0,     0,     0,
       0,    50,     0,    69,    49,     0,    64,     0,     0,     0,
      55,    62,    60,     0,    59,     0,    53,    52,    58,    57,
      51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,  -133,  -133,   185,   232,  -133,  -133,   175,   216,
    -133,   208,  -133,   194,  -132,   -80,   -42,  -133,   202,   -55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     9,    17,    32,     4,     5,    14,    47,    20,
      21,    33,    34,    48,    49,    86,    87,    35,    50,   107
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    74,   116,    77,    18,    53,    19,   -31,    54,   150,
     171,     6,   153,    30,     8,    31,    85,     7,   -15,    91,
     -21,    -7,    37,    38,    12,    13,   165,    92,   167,   -21,
     168,   109,   172,   111,   112,   -10,   114,   126,   177,   115,
      -3,   137,   118,   181,   -10,    15,    16,   185,   -21,   -21,
     -21,   188,   -21,   -21,   126,    59,    56,   126,    57,    60,
      22,    58,    23,   126,    61,   127,     1,   155,    24,    -8,
       2,    93,    10,   -75,   -20,    -8,     2,    25,   -75,    26,
      39,    79,    27,    29,   139,   -75,    55,   -75,   142,    75,
     -75,   145,   -75,   -75,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   -75,   -75,   -75,   -75,
     -75,   -75,    93,    78,    81,   -31,    82,    83,    88,   -40,
      60,   108,    40,   117,   122,   120,   123,    59,   -40,    41,
     136,    94,   135,   141,   138,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   -40,   -40,   -40,
     -40,   -40,   -40,    93,   140,   143,   144,    42,    43,    44,
     -45,    45,    46,   146,   147,   156,   157,   158,   169,   -45,
     159,   160,   110,   161,   162,   170,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   -45,   -45,
     -45,   -45,   -45,   -45,    93,   173,   -29,   174,    62,   175,
     178,   -29,   179,   183,    63,    64,    65,    66,    67,    68,
     -29,    69,   182,   119,    36,   186,   189,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   -29,
     -29,   -29,    93,   -29,   -29,   190,    90,    11,    51,   -38,
      31,    28,    52,    80,    71,   -21,     0,     0,   -38,     0,
       0,   124,     0,     0,   -21,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   -38,   -38,   -38,
     -38,   -38,   -38,   -21,   -21,   -21,    40,   -21,   -21,     0,
       0,     0,    40,    41,     0,     0,     0,     0,    40,    41,
       0,     0,   163,     0,    40,    41,     0,     0,   180,     0,
       0,    41,     0,     0,   187,     0,     0,     0,     0,     0,
     -32,    42,    43,    44,   164,    45,    46,    42,    43,    44,
     -65,    45,    46,    42,    43,    44,   -61,    45,    46,    42,
      43,    44,    40,    45,    46,     0,     0,     0,    40,    41,
       0,     0,     0,     0,    40,    41,     0,     0,   149,     0,
      40,    41,     0,     0,   152,     0,     0,    41,     0,     0,
     166,     0,     0,     0,     0,     0,   176,    42,    43,    44,
       0,    45,    46,    42,    43,    44,     0,    45,    46,    42,
      43,    44,    93,    45,    46,    42,    43,    44,    40,    45,
      46,     0,     0,     0,     0,    41,   -73,     0,   -73,     0,
       0,     0,     0,   121,   184,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,    93,     0,     0,
       0,     0,     0,    42,    43,    44,     0,    45,    46,     0,
       0,   129,     0,     0,     0,     0,     0,     0,    93,   130,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   132,     0,    93,     0,     0,     0,     0,     0,
     133,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   113,     0,    93,     0,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   125,
       0,     0,     0,     0,     0,     0,    93,     0,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     128,     0,     0,     0,     0,     0,     0,    93,     0,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   131,     0,    93,     0,     0,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   134,     0,    93,     0,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   148,     0,
       0,     0,     0,     0,     0,    93,     0,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   151,
       0,     0,     0,     0,     0,     0,    93,     0,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     154,    93,     0,     0,     0,     0,     0,     0,     0,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,     0,     0,     0,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,    62,     0,     0,     0,
       0,     0,    63,    72,    65,    66,    67,    68,    62,    73,
       0,     0,     0,     0,    63,    72,    65,    66,    67,    68,
      62,    76,     0,     0,     0,     0,    63,    72,    65,    66,
      67,    68,    62,    84,     0,     0,     0,     0,    63,    89,
      65,    66,    67,    68,     0,    84
};

static const yytype_int16 yycheck[] =
{
      42,    43,    82,    45,     1,    20,     3,     3,    23,   141,
      17,     3,   144,     1,     4,     3,    58,     0,    15,    61,
       8,    17,     8,     9,     8,     5,   158,    69,   160,    17,
     162,    73,    39,    75,    76,     4,    78,    92,   170,    81,
       0,   121,    84,   175,     4,     6,    14,   179,    36,    37,
      38,   183,    40,    41,   109,    14,    18,   112,    20,    18,
      14,    23,     8,   118,    23,   107,     1,   147,    15,     4,
       5,     1,     1,     3,    22,     4,     5,    22,     8,    15,
      17,    20,    16,    16,   126,    15,    17,    17,   130,    14,
      20,   133,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,     1,    14,    23,     3,    16,     9,     9,     8,
      18,    20,     1,    19,    19,    15,    20,    14,    17,     8,
      23,    20,    17,    16,    20,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,     1,    20,    20,    16,    36,    37,    38,
       8,    40,    41,    20,    16,    39,    17,    16,    39,    17,
      17,    16,    20,    17,    16,    16,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,     1,    17,     3,    17,     1,    16,
      39,     8,    16,    16,     7,     8,     9,    10,    11,    12,
      17,    14,    17,    20,    29,    17,    17,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,     1,    40,    41,    17,    61,     5,     1,     8,
       3,    25,    34,    49,    42,     8,    -1,    -1,    17,    -1,
      -1,    20,    -1,    -1,    17,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    36,    37,    38,     1,    40,    41,    -1,
      -1,    -1,     1,     8,    -1,    -1,    -1,    -1,     1,     8,
      -1,    -1,    17,    -1,     1,     8,    -1,    -1,    17,    -1,
      -1,     8,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,
      17,    36,    37,    38,    39,    40,    41,    36,    37,    38,
      39,    40,    41,    36,    37,    38,    39,    40,    41,    36,
      37,    38,     1,    40,    41,    -1,    -1,    -1,     1,     8,
      -1,    -1,    -1,    -1,     1,     8,    -1,    -1,    17,    -1,
       1,     8,    -1,    -1,    17,    -1,    -1,     8,    -1,    -1,
      17,    -1,    -1,    -1,    -1,    -1,    17,    36,    37,    38,
      -1,    40,    41,    36,    37,    38,    -1,    40,    41,    36,
      37,    38,     1,    40,    41,    36,    37,    38,     1,    40,
      41,    -1,    -1,    -1,    -1,     8,    15,    -1,    17,    -1,
      -1,    -1,    -1,    22,    17,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,     1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,     1,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    15,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    20,    -1,     1,    -1,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    15,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      15,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    15,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    20,    -1,     1,    -1,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    15,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    15,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      15,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     1,    -1,    -1,    -1,
      -1,    -1,     7,     8,     9,    10,    11,    12,     1,    14,
      -1,    -1,    -1,    -1,     7,     8,     9,    10,    11,    12,
       1,    14,    -1,    -1,    -1,    -1,     7,     8,     9,    10,
      11,    12,     1,    14,    -1,    -1,    -1,    -1,     7,     8,
       9,    10,    11,    12,    -1,    14
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     5,    46,    50,    51,     3,     0,     4,    47,
       1,    50,     8,     5,    52,     6,    14,    48,     1,     3,
      54,    55,    14,     8,    15,    22,    15,    16,    54,    16,
       1,     3,    49,    56,    57,    62,    49,     8,     9,    17,
       1,     8,    36,    37,    38,    40,    41,    53,    58,    59,
      63,     1,    56,    20,    23,    17,    18,    20,    23,    14,
      18,    23,     1,     7,     8,     9,    10,    11,    12,    14,
      61,    63,     8,    14,    61,    14,    14,    61,    14,    20,
      58,    23,    16,     9,    14,    61,    60,    61,     9,     8,
      53,    61,    61,     1,    20,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    64,    20,    61,
      20,    61,    61,    20,    61,    61,    60,    19,    61,    20,
      15,    22,    19,    20,    20,    15,    64,    61,    15,    15,
      23,    15,    15,    23,    20,    17,    23,    60,    20,    61,
      20,    16,    61,    20,    16,    61,    20,    16,    15,    17,
      59,    15,    17,    59,    15,    60,    39,    17,    16,    17,
      16,    17,    16,    17,    39,    59,    17,    59,    59,    39,
      16,    17,    39,    17,    17,    16,    17,    59,    39,    16,
      17,    59,    17,    16,    17,    59,    17,    17,    59,    17,
      17
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    46,    48,    47,    49,    49,    50,    50,
      50,    52,    51,    51,    53,    54,    54,    54,    54,    55,
      55,    56,    56,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    58,    58,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    62,    62,    63,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     0,     9,     2,     1,     0,     2,
       1,     0,    10,     1,     4,     0,     1,     3,     1,     2,
       1,     0,     2,     1,     3,     5,     2,     6,     2,     4,
       2,     1,     0,     2,     4,     4,     2,     4,     3,     3,
       2,     5,     3,     4,     3,     2,     5,     4,     7,    10,
       9,    13,    12,    12,     8,    11,     8,    12,    12,    11,
      11,    11,    11,     7,    10,    10,     6,     8,     7,     9,
       5,     3,     1,     1,     3,     3,     5,     1,     1,     1,
       1,     1,     1,     1,     5,     9,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
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
#line 96 "parser.y"
         { fprintf(yyoutput, "%s", ((*yyvaluep).string)); }
#line 997 "parser.tab.c"
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
#line 116 "parser.y"
                                  { 
							printf("The PARSER has started\n"); 
							printf("\nMAIN FUNCTION\n");
							root = malloc(sizeof(ASTNode));
							root->type = NodeType_Program;
							root->program.mainFunc = (yyvsp[0].ast);
							root->program.funcDeclList = (yyvsp[-1].ast);
							}
#line 1394 "parser.tab.c"
    break;

  case 3: /* Program: error  */
#line 124 "parser.y"
                { printf("PARSER: Syntax error on line %d\n", yylineno); exit(0); }
#line 1400 "parser.tab.c"
    break;

  case 4: /* $@1: %empty  */
#line 127 "parser.y"
                              {
		scope = "Global";
	}
#line 1408 "parser.tab.c"
    break;

  case 5: /* MainFunc: VOID FUNC_DECL MAIN $@1 LPAR RPAR LBRA Body RBRA  */
#line 129 "parser.y"
                                  { 
		printf("PARSER: Recognized main() function declaration\n"); 
		(yyval.ast) = createNode(NodeType_Main);
		(yyval.ast)->mainFunc.funcName = strdup((yyvsp[-6].string));
		(yyval.ast)->mainFunc.body = (yyvsp[-1].ast);
	}
#line 1419 "parser.tab.c"
    break;

  case 6: /* Body: VarDeclList StmtList  */
#line 136 "parser.y"
                           {
		printf("PARSER: Recognized function body\n"); 
		(yyval.ast) = createNode(NodeType_Body);
		(yyval.ast)->body.varDeclList = (yyvsp[-1].ast);
		(yyval.ast)->body.stmtList = (yyvsp[0].ast);
	}
#line 1430 "parser.tab.c"
    break;

  case 7: /* Body: error  */
#line 142 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid BODY syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1439 "parser.tab.c"
    break;

  case 8: /* FuncDeclList: %empty  */
#line 147 "parser.y"
               {/* No functions declared */ }
#line 1445 "parser.tab.c"
    break;

  case 9: /* FuncDeclList: FuncDecl FuncDeclList  */
#line 148 "parser.y"
                                { 
		printf("PARSER: Recognized function declaration list\n"); 
		(yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_FuncDeclList;
		(yyval.ast)->funcDeclList.funcDecl = (yyvsp[-1].ast);
		(yyval.ast)->funcDeclList.funcDeclList = (yyvsp[0].ast);
		}
#line 1457 "parser.tab.c"
    break;

  case 10: /* FuncDeclList: error  */
#line 155 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid FUNC DECL LIST syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1466 "parser.tab.c"
    break;

  case 11: /* $@2: %empty  */
#line 160 "parser.y"
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
#line 1484 "parser.tab.c"
    break;

  case 12: /* FuncDecl: FUNC_DECL TYPE ID $@2 LPAR ParamList RPAR LBRA Body RBRA  */
#line 172 "parser.y"
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
#line 1514 "parser.tab.c"
    break;

  case 13: /* FuncDecl: error  */
#line 197 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid FUNC DECL syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1523 "parser.tab.c"
    break;

  case 14: /* FuncCall: ID LPAR ExprList RPAR  */
#line 202 "parser.y"
                                {
	printf("PARSER: Recognized func call\n");
	printf("\n******************************************\n\n");
	//TODO: 
	(yyval.ast) = malloc(sizeof(ASTNode));
	(yyval.ast)->type = NodeType_FuncCall;
	(yyval.ast)->funcCall.funcName = strdup((yyvsp[-3].string));
	(yyval.ast)->funcCall.exprList = (yyvsp[-1].ast);
}
#line 1537 "parser.tab.c"
    break;

  case 15: /* ParamList: %empty  */
#line 212 "parser.y"
            {/*empty, i.e. it is possible not to have any parameter*/}
#line 1543 "parser.tab.c"
    break;

  case 16: /* ParamList: ParamDecl  */
#line 213 "parser.y"
                    {printf("One parameter\n");
		// Create AST node for VarDeclList
		(yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_ParamDeclList;
		(yyval.ast)->paramDeclList.paramDecl = (yyvsp[0].ast);
	}
#line 1554 "parser.tab.c"
    break;

  case 17: /* ParamList: ParamDecl COMMA ParamList  */
#line 219 "parser.y"
                                    { printf("PARSER: Recognized parameter list\n"); 
		(yyval.ast) = malloc(sizeof(ASTNode));
		(yyval.ast)->type = NodeType_ParamDeclList;
		(yyval.ast)->paramDeclList.paramDecl = (yyvsp[-2].ast);
		(yyval.ast)->paramDeclList.paramDeclList = (yyvsp[0].ast);
	}
#line 1565 "parser.tab.c"
    break;

  case 18: /* ParamList: error  */
#line 225 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid PARAM LIST syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1574 "parser.tab.c"
    break;

  case 19: /* ParamDecl: TYPE ID  */
#line 230 "parser.y"
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
#line 1602 "parser.tab.c"
    break;

  case 20: /* ParamDecl: error  */
#line 253 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid PARAM DECL syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1611 "parser.tab.c"
    break;

  case 21: /* VarDeclList: %empty  */
#line 258 "parser.y"
              {/*empty, i.e. it is possible not to declare a variable*/}
#line 1617 "parser.tab.c"
    break;

  case 22: /* VarDeclList: VarDecl VarDeclList  */
#line 259 "parser.y"
                              {  printf("PARSER: Recognized variable declaration list\n"); 

							// Create AST node for VarDeclList
							(yyval.ast) = malloc(sizeof(ASTNode));
							(yyval.ast)->type = NodeType_VarDeclList;
							(yyval.ast)->varDeclList.varDecl = (yyvsp[-1].ast);
							(yyval.ast)->varDeclList.varDeclList = (yyvsp[0].ast);
				
							// Set other fields as necessary

							
							}
#line 1634 "parser.tab.c"
    break;

  case 23: /* VarDeclList: error  */
#line 271 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nBase Error: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1643 "parser.tab.c"
    break;

  case 24: /* VarDecl: TYPE ID SEMICOLON  */
#line 276 "parser.y"
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
#line 1675 "parser.tab.c"
    break;

  case 25: /* VarDecl: TYPE ID EQ Expr SEMICOLON  */
#line 303 "parser.y"
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
#line 1706 "parser.tab.c"
    break;

  case 26: /* VarDecl: Array_Decl SEMICOLON  */
#line 329 "parser.y"
                                       { 
			// E.G. int myList[10];
				printf("PARSER: Recognized array declaration: %s\n", (yyvsp[-1].ast)->arrDecl.array->array.arrName);

				// Just pass the already created ASTNode along
				(yyval.ast) = (yyvsp[-1].ast);

				// Add to symbol table using data from the inner array node
				addSymbol(symTab, (yyvsp[-1].ast)->arrDecl.array->array.arrName, (yyvsp[-1].ast)->arrDecl.varType, "Arr", (yyvsp[-1].ast)->arrDecl.array->array.arrIndex, scope);
				printSymbolTable(symTab);
			}
#line 1722 "parser.tab.c"
    break;

  case 27: /* VarDecl: Array_Decl EQ LBRA ExprList RBRA SEMICOLON  */
#line 340 "parser.y"
                                                             {
			printf("PARSER: Recognized array declaration with initialization: %s\n", (yyvsp[-5].ast)->arrDecl.array->array.arrName);
			// Set the exprList in the array declaration
			(yyvsp[-5].ast)->arrDecl.exprList = (yyvsp[-2].ast);
			(yyval.ast) = (yyvsp[-5].ast);
			// Add to symbol table
			addSymbol(symTab, (yyvsp[-5].ast)->arrDecl.array->array.arrName, (yyvsp[-5].ast)->arrDecl.varType, "Arr", (yyvsp[-5].ast)->arrDecl.array->array.arrIndex, scope);
			printSymbolTable(symTab);
		}
#line 1736 "parser.tab.c"
    break;

  case 28: /* VarDecl: TYPE ID  */
#line 349 "parser.y"
                          {
                  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after declaring variable: %s on line %d\n\n\n---------------------------\n\n\n", (yyvsp[0].string), yylineno-1);
				  exit(0);
             }
#line 1745 "parser.tab.c"
    break;

  case 29: /* VarDecl: TYPE ID EQ Expr  */
#line 353 "parser.y"
                                  {
                  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after declaring variable: %s on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-2].string), yylineno-1);
				  exit(0);
             }
#line 1754 "parser.tab.c"
    break;

  case 30: /* VarDecl: TYPE NUMBER  */
#line 357 "parser.y"
                              {
                  printf ("\n\n\n---------------------------\n\n\nCannot use number as a variable name for: '%s %d' on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-1].string), (yyvsp[0].number), yylineno);
				  exit(0);
             }
#line 1763 "parser.tab.c"
    break;

  case 31: /* VarDecl: error  */
#line 361 "parser.y"
                        { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 1772 "parser.tab.c"
    break;

  case 32: /* StmtList: %empty  */
#line 366 "parser.y"
           {/*empty, i.e. it is possible not to have any statement*/}
#line 1778 "parser.tab.c"
    break;

  case 33: /* StmtList: Stmt StmtList  */
#line 367 "parser.y"
                        { printf("PARSER: Recognized statement list\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_StmtList;
						(yyval.ast)->stmtList.stmt = (yyvsp[-1].ast);
						(yyval.ast)->stmtList.stmtList = (yyvsp[0].ast);
						// Set other fields as necessary
					}
#line 1790 "parser.tab.c"
    break;

  case 34: /* Stmt: ID EQ Expr SEMICOLON  */
#line 375 "parser.y"
                           { /* code TBD */
								printf("PARSER: Recognized assignment statement\n");
			 					printf("\n******************************************\n\n");
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_AssignStmt;
								(yyval.ast)->assignStmt.varName = strdup((yyvsp[-3].string));
								(yyval.ast)->assignStmt.operator = (yyvsp[-2].operator);
								(yyval.ast)->assignStmt.expr = (yyvsp[-1].ast);
 	}
#line 1804 "parser.tab.c"
    break;

  case 35: /* Stmt: ID EQ FuncCall SEMICOLON  */
#line 384 "parser.y"
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
#line 1819 "parser.tab.c"
    break;

  case 36: /* Stmt: FuncCall SEMICOLON  */
#line 394 "parser.y"
                             { /* code TBD */
			printf("PARSER: Recognized func call\n");
 	}
#line 1827 "parser.tab.c"
    break;

  case 37: /* Stmt: Array EQ Expr SEMICOLON  */
#line 397 "parser.y"
                                  { /* code TBD */
			printf("PARSER: Recognized array assignment statement\n");
			printf("\n******************************************\n\n");
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_ArrDeclAssign;
			(yyval.ast)->arrAssignStmt.operator = (yyvsp[-2].operator);
			(yyval.ast)->arrAssignStmt.array = (yyvsp[-3].ast);
			(yyval.ast)->arrAssignStmt.expr = (yyvsp[-1].ast);
 	}
#line 1841 "parser.tab.c"
    break;

  case 38: /* Stmt: ID EQ Expr  */
#line 406 "parser.y"
                     {
		      printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s %s on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-2].string),(yyvsp[-1].operator),(yyvsp[0].ast), yylineno-1);
			  exit(0);
			}
#line 1850 "parser.tab.c"
    break;

  case 39: /* Stmt: WRITE Expr SEMICOLON  */
#line 410 "parser.y"
                               { 
								printf("PARSER: Recognized write statement -> write %s;\n", (yyvsp[-1].ast)); 
								printf("\n******************************************\n\n"); 
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_PrintStmt;
								(yyval.ast)->printStmt.varName = strdup((yyvsp[-2].string));
								(yyval.ast)->printStmt.expr = (yyvsp[-1].ast);
						}
#line 1863 "parser.tab.c"
    break;

  case 40: /* Stmt: WRITE Expr  */
#line 418 "parser.y"
                     {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-1].string),(yyvsp[0].ast), yylineno-1);
			  exit(0);
			}
#line 1872 "parser.tab.c"
    break;

  case 41: /* Stmt: WRITE LPAR Expr RPAR SEMICOLON  */
#line 422 "parser.y"
                                         { 
			printf("PARSER: Recognized write statement -> write(%s);\n", (yyvsp[-2].ast)); 
			printf("\n******************************************\n\n"); 
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_PrintStmt;
			(yyval.ast)->printStmt.varName = strdup((yyvsp[-4].string));
			(yyval.ast)->printStmt.expr = (yyvsp[-2].ast);
		}
#line 1885 "parser.tab.c"
    break;

  case 42: /* Stmt: WRITE Array SEMICOLON  */
#line 430 "parser.y"
                                { 
			printf("PARSER: Recognized write array statement -> write %s;\n", (yyvsp[-1].ast)); 
			printf("\n******************************************\n\n"); 
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_ArrPrintStmt;
			(yyval.ast)->arrPrintStmt.varName = strdup((yyvsp[-2].string));
			(yyval.ast)->arrPrintStmt.array = (yyvsp[-1].ast);
		}
#line 1898 "parser.tab.c"
    break;

  case 43: /* Stmt: WRITE LPAR Expr RPAR  */
#line 438 "parser.y"
                               {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-3].string),(yyvsp[-1].ast), yylineno-1);
			  exit(0);
			}
#line 1907 "parser.tab.c"
    break;

  case 44: /* Stmt: PRINT Expr SEMICOLON  */
#line 442 "parser.y"
                               { 
								printf("PARSER: Recognized print statement -> print %s;\n", (yyvsp[-1].ast)); 
								printf("\n******************************************\n\n"); 
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_PrintStmt;
								(yyval.ast)->printStmt.varName = strdup((yyvsp[-2].string));
								(yyval.ast)->printStmt.expr = (yyvsp[-1].ast);
						}
#line 1920 "parser.tab.c"
    break;

  case 45: /* Stmt: PRINT Expr  */
#line 450 "parser.y"
                     {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s %s on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-1].string),(yyvsp[0].ast), yylineno-1);
			  exit(0);
			}
#line 1929 "parser.tab.c"
    break;

  case 46: /* Stmt: PRINT LPAR Expr RPAR SEMICOLON  */
#line 454 "parser.y"
                                         { 
								printf("PARSER: Recognized print statement -> print(%s);\n", (yyvsp[-2].ast)); 
								printf("\n******************************************\n\n"); 
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_PrintStmt;
								(yyval.ast)->printStmt.varName = strdup((yyvsp[-4].string));
								(yyval.ast)->printStmt.expr = (yyvsp[-2].ast);
						}
#line 1942 "parser.tab.c"
    break;

  case 47: /* Stmt: PRINT LPAR Expr RPAR  */
#line 462 "parser.y"
                               {
			  printf ("\n\n\n---------------------------\n\n\nMissing semicolon after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-3].string),(yyvsp[-1].ast), yylineno-1);
			  exit(0);
			}
#line 1951 "parser.tab.c"
    break;

  case 48: /* Stmt: IF LPAR Expr RPAR LBRA Stmt RBRA  */
#line 466 "parser.y"
                                           { printf("PARSER: Recognized if statement\n"); printf("\n******************************************\n\n"); }
#line 1957 "parser.tab.c"
    break;

  case 49: /* Stmt: IF LPAR Expr RPAR LBRA RBRA ELSE LBRA Stmt RBRA  */
#line 467 "parser.y"
                                                          { printf("PARSER: Recognized if-else statement\n"); printf("\n******************************************\n\n"); }
#line 1963 "parser.tab.c"
    break;

  case 50: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA  */
#line 469 "parser.y"
                                                   { printf("PARSER: Recognized if statement\n"); printf("\n******************************************\n\n"); }
#line 1969 "parser.tab.c"
    break;

  case 51: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA ELSE LBRA Stmt RBRA  */
#line 470 "parser.y"
                                                                       { printf("PARSER: Recognized if-else statement\n"); printf("\n******************************************\n\n"); }
#line 1975 "parser.tab.c"
    break;

  case 52: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA ELSE LBRA RBRA  */
#line 471 "parser.y"
                                                                  { printf("PARSER: Recognized if-else statement\n"); printf("\n******************************************\n\n"); }
#line 1981 "parser.tab.c"
    break;

  case 53: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA RBRA ELSE LBRA Stmt RBRA  */
#line 472 "parser.y"
                                                                  { printf("PARSER: Recognized if-else statement\n"); printf("\n******************************************\n\n"); }
#line 1987 "parser.tab.c"
    break;

  case 54: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA RBRA  */
#line 473 "parser.y"
                                              { printf("PARSER: Recognized if statement\n"); printf("\n******************************************\n\n"); }
#line 1993 "parser.tab.c"
    break;

  case 55: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA RBRA ELSE LBRA RBRA  */
#line 474 "parser.y"
                                                             { printf("PARSER: Recognized if-else statement\n"); printf("\n******************************************\n\n"); }
#line 1999 "parser.tab.c"
    break;

  case 56: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt  */
#line 476 "parser.y"
                                              { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-7].string),(yyvsp[-5].ast), brackStart);
			  exit(0); 
			}
#line 2008 "parser.tab.c"
    break;

  case 57: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt ELSE LBRA Stmt RBRA  */
#line 480 "parser.y"
                                                                  { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-11].string),(yyvsp[-9].ast), brackStart);
			  exit(0);
	 		}
#line 2017 "parser.tab.c"
    break;

  case 58: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA ELSE LBRA Stmt  */
#line 484 "parser.y"
                                                                  { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-11].string),(yyvsp[-9].ast), brackStart);
			  exit(0);
	 		}
#line 2026 "parser.tab.c"
    break;

  case 59: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt ELSE LBRA RBRA  */
#line 488 "parser.y"
                                                             { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-10].string),(yyvsp[-8].ast), brackStart);
			  exit(0);
	 		}
#line 2035 "parser.tab.c"
    break;

  case 60: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA ELSE LBRA Stmt RBRA  */
#line 492 "parser.y"
                                                             { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-10].string),(yyvsp[-8].ast), brackStart);
			  exit(0);
	 		}
#line 2044 "parser.tab.c"
    break;

  case 61: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA Stmt RBRA ELSE LBRA  */
#line 496 "parser.y"
                                                             { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-10].string),(yyvsp[-8].ast), brackStart);
			  exit(0);
	 		}
#line 2053 "parser.tab.c"
    break;

  case 62: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA RBRA ELSE LBRA Stmt  */
#line 500 "parser.y"
                                                             { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-10].string),(yyvsp[-8].ast), brackStart);
			  exit(0);
	 		}
#line 2062 "parser.tab.c"
    break;

  case 63: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA  */
#line 504 "parser.y"
                                         { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-6].string),(yyvsp[-4].ast), brackStart);
			  exit(0);
	 		}
#line 2071 "parser.tab.c"
    break;

  case 64: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA ELSE LBRA RBRA  */
#line 508 "parser.y"
                                                        { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-9].string),(yyvsp[-7].ast), brackStart);
			  exit(0);
	 		}
#line 2080 "parser.tab.c"
    break;

  case 65: /* Stmt: IF LPAR Expr EQ Expr RPAR LBRA RBRA ELSE LBRA  */
#line 512 "parser.y"
                                                        { 
			  printf ("\n\n\n---------------------------\n\n\nMissing closing bracket after: %s(%s) on line %d\n\n\n---------------------------\n\n\n", (yyvsp[-9].string),(yyvsp[-7].ast), brackStart);
			  exit(0);
	 		}
#line 2089 "parser.tab.c"
    break;

  case 66: /* Stmt: WHILE LPAR Expr RPAR LBRA RBRA  */
#line 517 "parser.y"
                                         { printf("PARSER: Recognized while statement\n"); printf("\n******************************************\n\n"); }
#line 2095 "parser.tab.c"
    break;

  case 67: /* Stmt: WHILE LPAR Expr EQ Expr RPAR LBRA RBRA  */
#line 518 "parser.y"
                                                 { printf("PARSER: Recognized while statement\n"); printf("\n******************************************\n\n"); }
#line 2101 "parser.tab.c"
    break;

  case 68: /* Stmt: WHILE LPAR Expr RPAR LBRA Stmt RBRA  */
#line 519 "parser.y"
                                              { printf("PARSER: Recognized while statement\n"); printf("\n******************************************\n\n"); }
#line 2107 "parser.tab.c"
    break;

  case 69: /* Stmt: WHILE LPAR Expr EQ Expr RPAR LBRA Stmt RBRA  */
#line 520 "parser.y"
                                                      { printf("PARSER: Recognized while statement\n"); printf("\n******************************************\n\n"); }
#line 2113 "parser.tab.c"
    break;

  case 70: /* Stmt: RETURN LPAR Expr RPAR SEMICOLON  */
#line 522 "parser.y"
                                          { printf("PARSER: Recognized return statement"); 
			printf("\n******************************************\n\n"); 
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_ReturnStmt;
			(yyval.ast)->returnStmt.varName = strdup((yyvsp[-4].string));
			(yyval.ast)->returnStmt.expr = (yyvsp[-2].ast); }
#line 2124 "parser.tab.c"
    break;

  case 71: /* Stmt: RETURN Expr SEMICOLON  */
#line 528 "parser.y"
                                { 
								printf("PARSER: Recognized return statement"); 
								printf("\n******************************************\n\n"); 
								(yyval.ast) = malloc(sizeof(ASTNode));
								(yyval.ast)->type = NodeType_ReturnStmt;
								(yyval.ast)->returnStmt.varName = strdup((yyvsp[-2].string));
								(yyval.ast)->returnStmt.expr = (yyvsp[-1].ast); 
								}
#line 2137 "parser.tab.c"
    break;

  case 72: /* Stmt: error  */
#line 536 "parser.y"
            { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 2146 "parser.tab.c"
    break;

  case 73: /* ExprList: Expr  */
#line 548 "parser.y"
               {
    (yyval.ast) = createNode(NodeType_ExprList);
    (yyval.ast)->exprList.expr = (yyvsp[0].ast);
    (yyval.ast)->exprList.next = NULL;
	}
#line 2156 "parser.tab.c"
    break;

  case 74: /* ExprList: Expr COMMA ExprList  */
#line 553 "parser.y"
                              {
    (yyval.ast) = createNode(NodeType_ExprList);
    (yyval.ast)->exprList.expr = (yyvsp[-2].ast);
    (yyval.ast)->exprList.next = (yyvsp[0].ast);
	}
#line 2166 "parser.tab.c"
    break;

  case 75: /* Expr: Expr BinOp Expr  */
#line 559 "parser.y"
                      { printf("PARSER: Recognized expression\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_Expr;
						(yyval.ast)->expr.left = (yyvsp[-2].ast);
						(yyval.ast)->expr.right = (yyvsp[0].ast);
						(yyval.ast)->expr.operator = (yyvsp[-1].ast)->binOp.operator;
						// TODO: Fix double initialization of 8+3
						printf("--%s %c %s--\n", (yyvsp[-2].ast), (yyvsp[-1].ast)->binOp.operator, (yyvsp[0].ast));
						
						// Set other fields as necessary
					  }
#line 2182 "parser.tab.c"
    break;

  case 76: /* Expr: LPAR Expr BinOp Expr RPAR  */
#line 570 "parser.y"
                                    { printf("PARSER: Recognized expression\n");
						(yyval.ast) = malloc(sizeof(ASTNode));
						(yyval.ast)->type = NodeType_Expr;
						(yyval.ast)->expr.left = (yyvsp[-3].ast);
						(yyval.ast)->expr.right = (yyvsp[-1].ast);
						(yyval.ast)->expr.operator = (yyvsp[-2].ast)->binOp.operator;
						// TODO: Fix double initialization of 8+3
						printf("--%s %c %s--\n", (yyvsp[-3].ast), (yyvsp[-2].ast)->binOp.operator, (yyvsp[-1].ast));
						
						// Set other fields as necessary
					  }
#line 2198 "parser.tab.c"
    break;

  case 77: /* Expr: ID  */
#line 582 "parser.y"
             { printf("ASSIGNMENT statement \n"); 
			if (lookupSymbol(symTab, (yyvsp[0].string)) == NULL) {
                printf("\n\n\n---------------------------\n\n\nSemantic error: Variable %s on line %d has not been declared\n\n\n---------------------------\n\n\n", (yyvsp[0].string), yylineno);
                exit(0);
            }
			(yyval.ast) = malloc(sizeof(ASTNode));
			(yyval.ast)->type = NodeType_SimpleID;
			(yyval.ast)->simpleID.name = (yyvsp[0].string);
		}
#line 2212 "parser.tab.c"
    break;

  case 78: /* Expr: NUMBER  */
#line 591 "parser.y"
                 { 
				// printf("\n\n %d \n\n", $1);
				printf("PARSER: Recognized number\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_SimpleExpr;
				(yyval.ast)->simpleExpr.number = (yyvsp[0].number);
			 }
#line 2224 "parser.tab.c"
    break;

  case 79: /* Expr: DECIMAL_NUMBER  */
#line 598 "parser.y"
                         { 
				// printf("\n\n %f \n\n", $1);
				printf("PARSER: Recognized float number\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_SimpleDecimal;
				(yyval.ast)->simpleDecimal.number = (yyvsp[0].float_number);
			 }
#line 2236 "parser.tab.c"
    break;

  case 80: /* Expr: BOOL  */
#line 605 "parser.y"
               { 
				printf("PARSER: Recognized boolean\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_SimpleString;
				(yyval.ast)->simpleString.name = (yyvsp[0].string);
			 }
#line 2247 "parser.tab.c"
    break;

  case 81: /* Expr: STR  */
#line 611 "parser.y"
                {
				printf("PARSER: Recognized string\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_SimpleString;
				(yyval.ast)->simpleString.name = (yyvsp[0].string);
			}
#line 2258 "parser.tab.c"
    break;

  case 82: /* Expr: CHR  */
#line 617 "parser.y"
                {
				printf("PARSER: Recognized char\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_SimpleID;
				(yyval.ast)->simpleID.name = (yyvsp[0].string);
			}
#line 2269 "parser.tab.c"
    break;

  case 83: /* Expr: error  */
#line 623 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 2278 "parser.tab.c"
    break;

  case 84: /* Array_Decl: TYPE ID LBLO NUMBER RBLO  */
#line 628 "parser.y"
                                     { printf("PARSER: Recognized array\n");
		(yyval.ast) = createNode(NodeType_ArrDecl);
		(yyval.ast)->arrDecl.varType = strdup((yyvsp[-4].string));

		ASTNode* arrayNode = createNode(NodeType_Array);
		arrayNode->array.arrName = strdup((yyvsp[-3].string));
		arrayNode->array.arrIndex = (yyvsp[-1].number);

		(yyval.ast)->arrDecl.array = arrayNode;
		(yyval.ast)->arrDecl.exprList = NULL;  // No initialization list
	}
#line 2294 "parser.tab.c"
    break;

  case 85: /* Array_Decl: TYPE ID LBLO NUMBER RBLO EQ LBRA ExprList RBRA  */
#line 639 "parser.y"
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
#line 2322 "parser.tab.c"
    break;

  case 86: /* Array: ID LBLO NUMBER RBLO  */
#line 664 "parser.y"
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
#line 2351 "parser.tab.c"
    break;

  case 87: /* BinOp: PLUS  */
#line 689 "parser.y"
            {
				printf("PARSER: Recognized binary operator PLUS\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[0].operator);
            }
#line 2362 "parser.tab.c"
    break;

  case 88: /* BinOp: MINUS  */
#line 695 "parser.y"
                {
				printf("PARSER: Recognized binary operator MINUS\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[0].operator);
			}
#line 2373 "parser.tab.c"
    break;

  case 89: /* BinOp: MUL  */
#line 701 "parser.y"
                {
				printf("PARSER: Recognized binary operator MUL\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[0].operator);
			}
#line 2384 "parser.tab.c"
    break;

  case 90: /* BinOp: DIV  */
#line 707 "parser.y"
                {
				printf("PARSER: Recognized binary operator DIV\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[0].operator);
			}
#line 2395 "parser.tab.c"
    break;

  case 91: /* BinOp: POW  */
#line 713 "parser.y"
                {
				printf("PARSER: Recognized binary operator POW\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[0].operator);
			}
#line 2406 "parser.tab.c"
    break;

  case 92: /* BinOp: FAC  */
#line 719 "parser.y"
                {
			    /* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator FAC\n");
			}
#line 2416 "parser.tab.c"
    break;

  case 93: /* BinOp: FIB  */
#line 724 "parser.y"
                {
			  	/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator FIB\n");
			}
#line 2426 "parser.tab.c"
    break;

  case 94: /* BinOp: PEQ  */
#line 729 "parser.y"
                {
			    /* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator PEQ\n");
			}
#line 2436 "parser.tab.c"
    break;

  case 95: /* BinOp: SEQ  */
#line 734 "parser.y"
                {
				/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator SEQ\n");
			}
#line 2446 "parser.tab.c"
    break;

  case 96: /* BinOp: MEQ  */
#line 739 "parser.y"
                {
				/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator MEQ\n");
			}
#line 2456 "parser.tab.c"
    break;

  case 97: /* BinOp: DEQ  */
#line 744 "parser.y"
                {
				/* This is not an operator */
				/* Move this to Expr */
				printf("PARSER: Recognized binary operator DEQ\n");
			}
#line 2466 "parser.tab.c"
    break;

  case 98: /* BinOp: DUP  */
#line 749 "parser.y"
                {
				printf("PARSER: Recognized binary operator DUP\n");
				(yyval.ast) = malloc(sizeof(ASTNode));
				(yyval.ast)->type = NodeType_BinOp;
				(yyval.ast)->binOp.operator = *(yyvsp[0].operator);
			}
#line 2477 "parser.tab.c"
    break;

  case 99: /* BinOp: error  */
#line 755 "parser.y"
                { 
          printf("\n\n\n---------------------------\n\n\nError: Invalid syntax, statement not recognized at %s on line %d char %d\n\n\n---------------------------\n\n\n", yytext, yylineno, chars);
          exit(0);
      }
#line 2486 "parser.tab.c"
    break;


#line 2490 "parser.tab.c"

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

#line 760 "parser.y"


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
		generateMIPS(tacHead);
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
