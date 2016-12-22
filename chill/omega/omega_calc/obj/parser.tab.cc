/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 15 "../src/parser.yy"

//#define YYDEBUG 1
#include <basic/Dynamic_Array.h>
#include <basic/Iterator.h>
#include <omega_calc/AST.h>
#include <omega/hull.h>
#include <omega/closure.h>
#include <omega/reach.h>
#include <string>
#include <iostream>
#include <fstream>
#include "parser.tab.hh"
#include <omega_calc/myflex.h>
//#include <stdio.h>

#if defined __USE_POSIX
#include <unistd.h>
#elif defined  __WIN32
#include <io.h>
#endif


#ifndef WIN32
#include <sys/time.h>
#include <sys/resource.h>
#endif
#if !defined(OMIT_GETRUSAGE)
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#endif

#if !defined(OMIT_GETRUSAGE)
#ifdef __sparc__
extern "C" int getrusage (int, struct rusage*);
#endif


  

struct rusage start_time;
bool anyTimingDone = false;

void start_clock( void ) {
  getrusage(RUSAGE_SELF, &start_time);
}

int clock_diff( void ) {
  struct rusage current_time;
  getrusage(RUSAGE_SELF, &current_time);
  return (current_time.ru_utime.tv_sec -start_time.ru_utime.tv_sec)*1000000 + (current_time.ru_utime.tv_usec-start_time.ru_utime.tv_usec);
}
#endif


#ifdef BUILD_CODEGEN  
#include <code_gen/codegen.h>
#endif

extern myFlexLexer mylexer;
#define yylex mylexer.yylex

  


int omega_calc_debug = 0;

extern bool is_interactive;
extern const char *PROMPT_STRING;
bool simplify = true;
using namespace omega;

extern std::string err_msg;

bool need_coef;

namespace {
  int redundant_conj_level = 2;  // default maximum 2
  int redundant_constr_level = 4;  // default maximum 4
}

std::map<std::string, Relation *> relationMap;
int argCount = 0;
int tuplePos = 0;
Argument_Tuple currentTuple = Input_Tuple;

Relation LexForward(int n);
reachable_information *reachable_info;

void yyerror(const std::string &s);
void flushScanBuffer();



/* Line 268 of yacc.c  */
#line 166 "parser.tab.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VAR = 258,
     INT = 259,
     COEF = 260,
     STRING = 261,
     OPEN_BRACE = 262,
     CLOSE_BRACE = 263,
     SYMBOLIC = 264,
     NO_SIMPLIFY = 265,
     OR = 266,
     AND = 267,
     NOT = 268,
     ST = 269,
     APPROX = 270,
     IS_ASSIGNED = 271,
     FORALL = 272,
     EXISTS = 273,
     DOMAIN = 274,
     RANGE = 275,
     DIFFERENCE = 276,
     DIFFERENCE_TO_RELATION = 277,
     GIST = 278,
     GIVEN = 279,
     HULL = 280,
     WITHIN = 281,
     MAXIMIZE = 282,
     MINIMIZE = 283,
     AFFINE_HULL = 284,
     VENN = 285,
     CONVEX_COMBINATION = 286,
     POSITIVE_COMBINATION = 287,
     LINEAR_COMBINATION = 288,
     AFFINE_COMBINATION = 289,
     CONVEX_HULL = 290,
     CONIC_HULL = 291,
     LINEAR_HULL = 292,
     QUICK_HULL = 293,
     PAIRWISE_CHECK = 294,
     CONVEX_CHECK = 295,
     CONVEX_REPRESENTATION = 296,
     RECT_HULL = 297,
     SIMPLE_HULL = 298,
     DECOUPLED_CONVEX_HULL = 299,
     MAXIMIZE_RANGE = 300,
     MINIMIZE_RANGE = 301,
     MAXIMIZE_DOMAIN = 302,
     MINIMIZE_DOMAIN = 303,
     LEQ = 304,
     GEQ = 305,
     NEQ = 306,
     GOES_TO = 307,
     COMPOSE = 308,
     JOIN = 309,
     INVERSE = 310,
     COMPLEMENT = 311,
     IN = 312,
     CARRIED_BY = 313,
     TIME = 314,
     TIMECLOSURE = 315,
     UNION = 316,
     INTERSECTION = 317,
     VERTICAL_BAR = 318,
     SUCH_THAT = 319,
     SUBSET = 320,
     CODEGEN = 321,
     DECOUPLED_FARKAS = 322,
     FARKAS = 323,
     MAKE_UPPER_BOUND = 324,
     MAKE_LOWER_BOUND = 325,
     REL_OP = 326,
     RESTRICT_DOMAIN = 327,
     RESTRICT_RANGE = 328,
     SUPERSETOF = 329,
     SUBSETOF = 330,
     SAMPLE = 331,
     SYM_SAMPLE = 332,
     PROJECT_AWAY_SYMBOLS = 333,
     PROJECT_ON_SYMBOLS = 334,
     REACHABLE_FROM = 335,
     REACHABLE_OF = 336,
     ASSERT_UNSAT = 337,
     PARSE_EXPRESSION = 338,
     PARSE_FORMULA = 339,
     PARSE_RELATION = 340,
     p1 = 341,
     p2 = 342,
     p3 = 343,
     p4 = 344,
     p5 = 345,
     p6 = 346,
     p7 = 347,
     p8 = 348,
     p9 = 349,
     p10 = 350
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 109 "../src/parser.yy"

  int INT_VALUE;
  omega::coef_t COEF_VALUE;
  Rel_Op REL_OPERATOR;
  char *VAR_NAME;
  std::set<char *> *VAR_LIST;
  Exp *EXP;
  std::set<Exp *> *EXP_LIST;
  AST *ASTP;
  omega::Argument_Tuple ARGUMENT_TUPLE;
  AST_constraints *ASTCP;
  Declaration_Site *DECLARATION_SITE;
  omega::Relation *RELATION;
  tupleDescriptor *TUPLE_DESCRIPTOR;
  std::pair<std::vector<omega::Relation>, std::vector<omega::Relation> > *REL_TUPLE_PAIR;
  omega::Dynamic_Array1<omega::Relation> * RELATION_ARRAY_1D;
  std::string *STRING_VALUE;



/* Line 293 of yacc.c  */
#line 318 "parser.tab.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 330 "parser.tab.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   750

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  108
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  159
/* YYNRULES -- Number of states.  */
#define YYNSTATES  309

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   350

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      99,   104,    90,    86,   102,    87,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   103,   101,
       2,     2,     2,     2,    91,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   106,     2,   107,   105,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    88,    89,    92,    93,    94,    95,    96,    97,    98,
     100
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     9,    11,    14,    17,    21,
      26,    29,    33,    37,    42,    47,    53,    56,    57,    60,
      66,    70,    74,    76,    77,    82,    84,    88,    91,    94,
      99,   103,   107,   110,   113,   116,   119,   122,   125,   128,
     131,   134,   137,   140,   143,   146,   149,   152,   157,   160,
     163,   166,   169,   172,   175,   178,   181,   184,   187,   190,
     193,   196,   199,   202,   205,   210,   213,   216,   219,   222,
     227,   232,   236,   240,   244,   248,   252,   256,   260,   264,
     268,   271,   274,   277,   280,   283,   286,   288,   291,   292,
     293,   300,   303,   305,   308,   309,   311,   313,   315,   316,
     321,   322,   324,   328,   330,   332,   334,   338,   344,   348,
     350,   352,   354,   358,   362,   364,   369,   371,   375,   379,
     381,   385,   388,   394,   400,   403,   406,   408,   410,   412,
     415,   418,   420,   422,   426,   428,   432,   436,   438,   439,
     445,   449,   453,   455,   457,   460,   462,   465,   469,   473,
     477,   481,   487,   491,   495,   497,   501,   507,   515,   521
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     109,     0,    -1,    -1,    -1,   109,   110,   111,    -1,   101,
      -1,    10,   101,    -1,     1,   101,    -1,     9,   128,   101,
      -1,     3,    16,   114,   101,    -1,   114,   101,    -1,    59,
     114,   101,    -1,    60,   114,   101,    -1,   114,    65,   114,
     101,    -1,    66,   113,   112,   101,    -1,    66,     4,   113,
     112,   101,    -1,   142,   101,    -1,    -1,    24,   114,    -1,
     113,   102,   114,   103,   114,    -1,   113,   102,   114,    -1,
     114,   103,   114,    -1,   114,    -1,    -1,     7,   115,   116,
       8,    -1,     3,    -1,    99,   114,   104,    -1,   114,    86,
      -1,   114,    90,    -1,   114,    86,    26,   114,    -1,   114,
     105,    91,    -1,   114,   105,    86,    -1,    46,   114,    -1,
      45,   114,    -1,    48,   114,    -1,    47,   114,    -1,    27,
     114,    -1,    28,   114,    -1,    68,   114,    -1,    67,   114,
      -1,   114,    91,    -1,    78,   114,    -1,    79,   114,    -1,
      21,   114,    -1,    22,   114,    -1,    19,   114,    -1,    30,
     114,    -1,    30,   114,    24,   114,    -1,    35,   114,    -1,
      44,   114,    -1,    32,   114,    -1,    33,   114,    -1,    34,
     114,    -1,    31,   114,    -1,    39,   114,    -1,    40,   114,
      -1,    41,   114,    -1,    29,   114,    -1,    36,   114,    -1,
      37,   114,    -1,    38,   114,    -1,    42,   114,    -1,    43,
     114,    -1,    25,   114,    -1,    25,   114,    24,   114,    -1,
      15,   114,    -1,    20,   114,    -1,    55,   114,    -1,    56,
     114,    -1,    23,   114,    24,   114,    -1,   114,    99,   114,
     104,    -1,   114,    53,   114,    -1,   114,    58,     4,    -1,
     114,    54,   114,    -1,   114,    73,   114,    -1,   114,    72,
     114,    -1,   114,    62,   114,    -1,   114,    87,   114,    -1,
     114,    61,   114,    -1,   114,    90,   114,    -1,    74,   114,
      -1,    75,   114,    -1,    69,   114,    -1,    70,   114,    -1,
      76,   114,    -1,    77,   114,    -1,   143,    -1,    82,   114,
      -1,    -1,    -1,   121,    52,   117,   121,   118,   119,    -1,
     121,   119,    -1,   130,    -1,   120,   130,    -1,    -1,   103,
      -1,    63,    -1,    64,    -1,    -1,   122,   106,   123,   107,
      -1,    -1,   124,    -1,   123,   102,   124,    -1,     3,    -1,
      90,    -1,   141,    -1,   141,   103,   141,    -1,   141,   103,
     141,   103,     5,    -1,   125,   102,     3,    -1,     3,    -1,
     125,    -1,   126,    -1,   106,   126,   107,    -1,   128,   102,
     129,    -1,   129,    -1,     3,    99,     4,   104,    -1,     3,
      -1,   130,    12,   130,    -1,   130,    11,   130,    -1,   137,
      -1,    99,   130,   104,    -1,    13,   130,    -1,   131,   127,
     132,   130,   135,    -1,   133,   127,   134,   130,   135,    -1,
      99,    18,    -1,    18,    99,    -1,   103,    -1,    63,    -1,
      64,    -1,    99,    17,    -1,    17,    99,    -1,   103,    -1,
     104,    -1,   141,   102,   136,    -1,   141,    -1,   136,    71,
     136,    -1,   136,    71,   137,    -1,     3,    -1,    -1,     3,
      99,   139,   140,   104,    -1,    99,   141,   104,    -1,   140,
     102,     3,    -1,     3,    -1,     5,    -1,     5,   138,    -1,
     138,    -1,    87,   141,    -1,   141,    86,   141,    -1,   141,
      87,   141,    -1,   141,    90,   141,    -1,    80,   144,   146,
      -1,    81,     3,    57,   144,   146,    -1,    99,   145,   104,
      -1,   145,   102,     3,    -1,     3,    -1,     7,   147,     8,
      -1,   147,   102,     3,   103,   114,    -1,   147,   102,     3,
      52,     3,   103,   114,    -1,     3,    52,     3,   103,   114,
      -1,     3,   103,   114,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   203,   203,   204,   204,   208,   209,   212,   222,   223,
     240,   249,   326,   412,   428,   451,   474,   493,   494,   497,
     513,   527,   544,   561,   561,   569,   579,   580,   593,   607,
     622,   635,   648,   664,   680,   696,   712,   728,   744,   757,
     770,   783,   796,   809,   822,   835,   848,   861,   876,   889,
     902,   915,   928,   941,   954,   967,   980,   993,  1006,  1019,
    1032,  1045,  1058,  1071,  1084,  1099,  1112,  1125,  1138,  1151,
    1166,  1181,  1196,  1210,  1225,  1240,  1255,  1270,  1285,  1300,
    1315,  1328,  1341,  1354,  1367,  1380,  1393,  1394,  1404,  1405,
    1404,  1438,  1459,  1468,  1469,  1472,  1473,  1474,  1477,  1477,
    1482,  1483,  1484,  1487,  1506,  1507,  1511,  1515,  1521,  1522,
    1525,  1533,  1534,  1537,  1538,  1541,  1542,  1548,  1549,  1550,
    1551,  1552,  1553,  1554,  1557,  1558,  1561,  1562,  1563,  1566,
    1567,  1570,  1573,  1576,  1577,  1580,  1581,  1584,  1594,  1594,
    1608,  1611,  1627,  1645,  1646,  1647,  1648,  1649,  1650,  1651,
    1663,  1669,  1687,  1695,  1699,  1707,  1751,  1765,  1790,  1815
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VAR", "INT", "COEF", "STRING",
  "OPEN_BRACE", "CLOSE_BRACE", "SYMBOLIC", "NO_SIMPLIFY", "OR", "AND",
  "NOT", "ST", "APPROX", "IS_ASSIGNED", "FORALL", "EXISTS", "DOMAIN",
  "RANGE", "DIFFERENCE", "DIFFERENCE_TO_RELATION", "GIST", "GIVEN", "HULL",
  "WITHIN", "MAXIMIZE", "MINIMIZE", "AFFINE_HULL", "VENN",
  "CONVEX_COMBINATION", "POSITIVE_COMBINATION", "LINEAR_COMBINATION",
  "AFFINE_COMBINATION", "CONVEX_HULL", "CONIC_HULL", "LINEAR_HULL",
  "QUICK_HULL", "PAIRWISE_CHECK", "CONVEX_CHECK", "CONVEX_REPRESENTATION",
  "RECT_HULL", "SIMPLE_HULL", "DECOUPLED_CONVEX_HULL", "MAXIMIZE_RANGE",
  "MINIMIZE_RANGE", "MAXIMIZE_DOMAIN", "MINIMIZE_DOMAIN", "LEQ", "GEQ",
  "NEQ", "GOES_TO", "COMPOSE", "JOIN", "INVERSE", "COMPLEMENT", "IN",
  "CARRIED_BY", "TIME", "TIMECLOSURE", "UNION", "INTERSECTION",
  "VERTICAL_BAR", "SUCH_THAT", "SUBSET", "CODEGEN", "DECOUPLED_FARKAS",
  "FARKAS", "MAKE_UPPER_BOUND", "MAKE_LOWER_BOUND", "REL_OP",
  "RESTRICT_DOMAIN", "RESTRICT_RANGE", "SUPERSETOF", "SUBSETOF", "SAMPLE",
  "SYM_SAMPLE", "PROJECT_AWAY_SYMBOLS", "PROJECT_ON_SYMBOLS",
  "REACHABLE_FROM", "REACHABLE_OF", "ASSERT_UNSAT", "PARSE_EXPRESSION",
  "PARSE_FORMULA", "PARSE_RELATION", "'+'", "'-'", "p1", "p2", "'*'",
  "'@'", "p3", "p4", "p5", "p6", "p7", "p8", "p9", "'('", "p10", "';'",
  "','", "':'", "')'", "'^'", "'['", "']'", "$accept", "inputSequence",
  "$@1", "inputItem", "context", "relPairList", "relation", "$@2",
  "builtRelation", "$@3", "$@4", "optionalFormula", "formula_sep",
  "tupleDeclaration", "$@5", "optionalTupleVarList", "tupleVar", "varList",
  "varDecl", "varDeclOptBrackets", "globVarList", "globVar", "formula",
  "start_exists", "exists_sep", "start_forall", "forall_sep", "end_quant",
  "expList", "constraintChain", "simpleExp", "$@6", "argumentList", "exp",
  "reachable", "reachable_of", "nodeNameList", "realNodeNameList",
  "nodeSpecificationList", "realNodeSpecificationList", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,    43,    45,   341,   342,
      42,    64,   343,   344,   345,   346,   347,   348,   349,    40,
     350,    59,    44,    58,    41,    94,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   108,   109,   110,   109,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   112,   112,   113,
     113,   113,   113,   115,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   117,   118,
     116,   116,   116,   119,   119,   120,   120,   120,   122,   121,
     123,   123,   123,   124,   124,   124,   124,   124,   125,   125,
     126,   127,   127,   128,   128,   129,   129,   130,   130,   130,
     130,   130,   130,   130,   131,   131,   132,   132,   132,   133,
     133,   134,   135,   136,   136,   137,   137,   138,   139,   138,
     138,   140,   140,   141,   141,   141,   141,   141,   141,   141,
     142,   143,   144,   145,   145,   146,   147,   147,   147,   147
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     3,     1,     2,     2,     3,     4,
       2,     3,     3,     4,     4,     5,     2,     0,     2,     5,
       3,     3,     1,     0,     4,     1,     3,     2,     2,     4,
       3,     3,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     4,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     4,     2,     2,     2,     2,     4,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     2,     2,     1,     2,     0,     0,
       6,     2,     1,     2,     0,     1,     1,     1,     0,     4,
       0,     1,     3,     1,     1,     1,     3,     5,     3,     1,
       1,     1,     3,     3,     1,     4,     1,     3,     3,     1,
       3,     2,     5,     5,     2,     2,     1,     1,     1,     2,
       2,     1,     1,     3,     1,     3,     3,     1,     0,     5,
       3,     3,     1,     1,     2,     1,     2,     3,     3,     3,
       3,     5,     3,     3,     1,     3,     5,     7,     5,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     3,     1,     0,     0,    25,    23,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     4,     0,
       0,    86,     7,     0,    98,   116,     0,   114,     6,    25,
      65,    45,    66,    43,    44,     0,    63,    36,    37,    57,
      46,    53,    50,    51,    52,    48,    58,    59,    60,    54,
      55,    56,    61,    62,    49,    33,    32,    35,    34,    67,
      68,     0,     0,     0,    17,    22,    39,    38,    82,    83,
      80,    81,    84,    85,    41,    42,     0,     0,     0,    87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
       0,    28,    40,     0,    10,     0,    16,     0,   137,   143,
       0,     0,     0,     0,     0,     0,    94,     0,    92,     0,
       0,     0,   119,   145,   134,     0,     8,     0,     0,     0,
       0,    11,    12,    17,     0,     0,     0,     0,   154,     0,
       0,   150,     0,    26,    71,    73,    72,    78,    76,     0,
      75,    74,     0,    77,    79,     0,    31,    30,     9,   138,
       0,   144,   121,   130,   125,   146,   129,   124,     0,   134,
      24,    88,    96,    97,    95,    91,     0,   100,     0,     0,
     109,     0,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,   113,    69,    64,    47,     0,    18,    20,    14,
      21,     0,   152,     0,     0,     0,    13,    29,    70,     0,
       0,   120,   140,    98,    93,   137,   104,     0,   101,   105,
     118,   117,     0,     0,   127,   128,   126,     0,   131,     0,
     135,   136,   147,   148,   149,   133,   115,    15,     0,   153,
       0,     0,   155,     0,   151,   142,     0,    89,     0,    99,
       0,   112,   108,     0,     0,    19,     0,   159,     0,     0,
     139,    94,   102,   106,   132,   122,   123,     0,     0,     0,
     141,    90,     0,   158,     0,   156,   107,     0,   157
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     3,    58,   166,   104,   105,    64,   145,   243,
     291,   205,   206,   146,   147,   247,   248,   212,   213,   214,
      66,    67,   148,   149,   257,   150,   259,   295,   151,   152,
     153,   239,   276,   154,    60,    61,   117,   169,   171,   234
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -158
static const yytype_int16 yypact[] =
{
    -158,    73,  -158,   168,   -99,    72,  -158,    88,     4,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   278,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,    10,   134,   359,   359,  -158,  -158,   358,
      48,  -158,  -158,   359,    67,    53,    -7,  -158,  -158,  -158,
     -16,   -16,   -16,   -16,   -16,   389,    15,   -16,   -16,   -16,
      30,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   411,   442,   359,    34,   464,   -16,   -16,   -16,   -16,
     167,   167,   -16,   -16,   -16,   -16,   160,   158,   111,   632,
     499,   359,   359,   166,   359,   359,   359,   359,   359,   150,
     359,   359,  -158,   359,  -158,   -30,  -158,   520,    82,     2,
      67,    86,    87,    59,    93,   186,   189,   112,   161,    -2,
      -2,   146,  -158,  -158,   193,   215,  -158,    88,   359,   359,
     359,  -158,  -158,    34,   359,   359,   121,   359,  -158,    11,
     223,  -158,    10,  -158,   -16,   -16,  -158,   167,    54,   555,
     645,   645,   359,    54,    54,   576,  -158,  -158,  -158,  -158,
      59,  -158,  -158,  -158,  -158,  -158,    86,    87,    63,   169,
    -158,  -158,  -158,  -158,  -158,  -158,    67,    52,    67,    67,
    -158,   227,   129,  -158,    23,   130,    59,    59,    59,    59,
      59,   128,  -158,   -16,   -16,   -16,   153,   632,   597,  -158,
     632,   248,  -158,    14,    43,   158,  -158,   -16,  -158,   259,
     174,  -158,  -158,  -158,   161,   -31,  -158,    -5,  -158,    13,
     251,  -158,   163,   271,  -158,  -158,  -158,    67,  -158,    67,
     146,  -158,   185,   185,  -158,  -158,  -158,  -158,   359,  -158,
     273,   359,  -158,   274,  -158,  -158,    46,  -158,    52,  -158,
      59,  -158,  -158,    70,    70,   632,   181,   632,    38,   283,
    -158,    29,  -158,    57,  -158,  -158,  -158,   359,   284,   359,
    -158,  -158,   285,   632,   188,   632,  -158,   359,   632
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -158,  -158,  -158,  -158,   125,   199,    -3,  -158,  -158,  -158,
    -158,    36,  -158,    85,  -158,  -158,    51,  -158,    78,   180,
    -158,   175,   -75,  -158,  -158,  -158,  -158,    47,  -157,   119,
     197,  -158,  -158,  -140,  -158,  -158,   165,  -158,   103,  -158
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -104
static const yytype_int16 yytable[] =
{
      59,   210,    62,   195,   199,   138,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   159,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     240,   272,   119,   120,   160,   245,   186,   139,   164,   260,
     137,   187,   138,   265,   139,   192,   270,   249,   189,   198,
     138,  -103,   139,     2,   208,   209,  -103,   262,   263,   264,
     140,   208,   209,   133,   141,   142,   254,   255,    63,   135,
     298,    65,   202,   203,   156,   157,   138,   278,   139,   217,
     218,   190,   279,   219,   211,    68,   140,   121,   122,   116,
     196,   197,   123,   231,   133,   232,   280,   271,   174,   175,
     135,   177,   178,   179,   180,   181,   256,   183,   184,   133,
     185,   244,   204,   250,   251,   135,   165,   118,   249,   143,
     293,   299,   246,   217,   218,   273,   143,   219,   289,   136,
     290,   190,   155,   133,   143,   223,   224,   225,   190,   135,
     302,   227,   228,   168,   230,   170,   144,   241,   172,     4,
     176,     5,   208,   209,   294,     6,   182,     7,     8,   237,
     143,   189,   283,     9,   284,   193,   194,    10,    11,    12,
      13,    14,   144,    15,   200,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,   216,   207,   221,
     121,   122,   229,    38,    39,   123,   233,    40,    41,   125,
     210,   253,   266,   258,    42,    43,    44,    45,    46,   127,
     128,   201,    47,    48,    49,    50,    51,    52,    53,    54,
      55,   269,   202,   203,   267,   217,   218,   131,   132,   219,
     217,   218,   275,   209,   219,   285,   133,    56,   287,    57,
     281,   220,   135,   242,   282,   219,   286,   288,   242,   217,
     218,    69,   103,   219,   297,     6,   300,   304,   226,   252,
     306,   307,   204,     9,   303,   220,   305,    10,    11,    12,
      13,    14,   163,    15,   308,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,   301,   277,   292,
     215,   296,   222,    38,    39,   261,   191,   235,   274,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,     0,
       0,     0,    47,    48,    49,    50,    51,    52,     0,    54,
      55,     0,    69,     0,     0,     0,     6,     0,     0,     0,
       0,     0,     0,     0,     9,     0,     0,    56,    10,    11,
      12,    13,    14,     0,    15,     0,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,     0,     0,
       0,   121,   122,   158,    38,    39,   123,     0,     0,   124,
     125,     0,     0,   126,     0,     0,    43,    44,    45,    46,
     127,   128,     0,    47,    48,    49,    50,    51,    52,     0,
      54,    55,   121,   122,   129,   130,     0,   123,   131,   132,
     124,   125,     0,     0,     0,     0,     0,   133,    56,   134,
       0,   127,   128,   135,   121,   122,     0,     0,     0,   123,
       0,     0,   124,   125,     0,   129,   130,     0,     0,   131,
     132,     0,     0,   127,   128,     0,     0,     0,   133,     0,
       0,     0,     0,     0,   135,   121,   122,   129,   130,     0,
     123,   131,   132,   124,   125,     0,     0,     0,     0,     0,
     133,     0,   161,     0,   127,   128,   135,   121,   122,     0,
       0,     0,   123,     0,     0,   124,   125,     0,   129,   130,
       0,     0,   131,   132,     0,     0,   127,   128,     0,     0,
       0,   133,     0,   162,     0,     0,     0,   135,     0,     0,
     129,   130,   121,   122,   131,   132,     0,   123,     0,     0,
     124,   125,     0,   133,     0,     0,     0,   167,     0,   135,
       0,   127,   128,   121,   122,     0,     0,     0,   123,     0,
       0,   124,   125,     0,     0,   129,   130,     0,     0,   131,
     132,     0,   127,   128,     0,     0,     0,     0,   133,     0,
       0,     0,     0,   173,   135,     0,   129,   130,   121,   122,
     131,   132,     0,   123,     0,     0,   124,   125,     0,   133,
       0,   188,     0,     0,     0,   135,     0,   127,   128,   121,
     122,     0,     0,     0,   123,     0,     0,   124,   125,     0,
       0,   129,   130,     0,     0,   131,   132,     0,   127,   128,
     121,   122,     0,     0,   133,   123,   236,     0,   124,   125,
     135,     0,   129,   130,     0,     0,   131,   132,     0,   127,
     128,     0,     0,     0,     0,   133,     0,     0,     0,     0,
     238,   135,     0,   129,   130,   121,   122,   131,   132,     0,
     123,     0,     0,   124,   125,     0,   133,     0,   121,   122,
     268,     0,   135,   123,   127,   128,     0,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,   130,
       0,     0,   131,   132,     0,     0,     0,     0,     0,     0,
       0,   133,     0,     0,     0,   131,   132,   135,     0,     0,
       0,     0,     0,     0,   133,     0,     0,     0,     0,     0,
     135
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-158))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       3,     3,   101,   143,   144,     3,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    24,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
     190,     8,    55,    56,    24,     3,    86,     5,    24,   216,
      63,    91,     3,   220,     5,   140,    52,   207,    99,   144,
       3,   102,     5,     0,    11,    12,   107,   217,   218,   219,
      13,    11,    12,    99,    17,    18,    63,    64,    16,   105,
      52,     3,    63,    64,   101,   102,     3,   102,     5,    86,
      87,    99,   107,    90,   106,   101,    13,    53,    54,    99,
      17,    18,    58,   102,    99,   104,   103,   103,   121,   122,
     105,   124,   125,   126,   127,   128,   103,   130,   131,    99,
     133,   206,   103,   208,   209,   105,   102,     3,   278,    87,
     280,   103,    90,    86,    87,   102,    87,    90,   102,   101,
     104,    99,    99,    99,    87,   158,   159,   160,    99,   105,
     103,   164,   165,     3,   167,     7,    99,   104,    57,     1,
       4,     3,    11,    12,   104,     7,    26,     9,    10,   182,
      87,    99,   257,    15,   259,    99,    99,    19,    20,    21,
      22,    23,    99,    25,     8,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    71,   106,     4,
      53,    54,   101,    55,    56,    58,     3,    59,    60,    62,
       3,   102,   104,   103,    66,    67,    68,    69,    70,    72,
      73,    52,    74,    75,    76,    77,    78,    79,    80,    81,
      82,     3,    63,    64,   101,    86,    87,    90,    91,    90,
      86,    87,     3,    12,    90,   268,    99,    99,   271,   101,
     107,   102,   105,   104,     3,    90,     3,     3,   104,    86,
      87,     3,     4,    90,   103,     7,     3,     3,   163,   211,
       5,   103,   103,    15,   297,   102,   299,    19,    20,    21,
      22,    23,   103,    25,   307,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,   291,   243,   278,
     150,   284,   157,    55,    56,   216,   139,   172,   235,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    -1,    81,
      82,    -1,     3,    -1,    -1,    -1,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    -1,    -1,    99,    19,    20,
      21,    22,    23,    -1,    25,    -1,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    53,    54,    24,    55,    56,    58,    -1,    -1,    61,
      62,    -1,    -1,    65,    -1,    -1,    67,    68,    69,    70,
      72,    73,    -1,    74,    75,    76,    77,    78,    79,    -1,
      81,    82,    53,    54,    86,    87,    -1,    58,    90,    91,
      61,    62,    -1,    -1,    -1,    -1,    -1,    99,    99,   101,
      -1,    72,    73,   105,    53,    54,    -1,    -1,    -1,    58,
      -1,    -1,    61,    62,    -1,    86,    87,    -1,    -1,    90,
      91,    -1,    -1,    72,    73,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    -1,    -1,   105,    53,    54,    86,    87,    -1,
      58,    90,    91,    61,    62,    -1,    -1,    -1,    -1,    -1,
      99,    -1,   101,    -1,    72,    73,   105,    53,    54,    -1,
      -1,    -1,    58,    -1,    -1,    61,    62,    -1,    86,    87,
      -1,    -1,    90,    91,    -1,    -1,    72,    73,    -1,    -1,
      -1,    99,    -1,   101,    -1,    -1,    -1,   105,    -1,    -1,
      86,    87,    53,    54,    90,    91,    -1,    58,    -1,    -1,
      61,    62,    -1,    99,    -1,    -1,    -1,   103,    -1,   105,
      -1,    72,    73,    53,    54,    -1,    -1,    -1,    58,    -1,
      -1,    61,    62,    -1,    -1,    86,    87,    -1,    -1,    90,
      91,    -1,    72,    73,    -1,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    -1,   104,   105,    -1,    86,    87,    53,    54,
      90,    91,    -1,    58,    -1,    -1,    61,    62,    -1,    99,
      -1,   101,    -1,    -1,    -1,   105,    -1,    72,    73,    53,
      54,    -1,    -1,    -1,    58,    -1,    -1,    61,    62,    -1,
      -1,    86,    87,    -1,    -1,    90,    91,    -1,    72,    73,
      53,    54,    -1,    -1,    99,    58,   101,    -1,    61,    62,
     105,    -1,    86,    87,    -1,    -1,    90,    91,    -1,    72,
      73,    -1,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,
     104,   105,    -1,    86,    87,    53,    54,    90,    91,    -1,
      58,    -1,    -1,    61,    62,    -1,    99,    -1,    53,    54,
     103,    -1,   105,    58,    72,    73,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      -1,    -1,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    99,    -1,    -1,    -1,    90,    91,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,
     105
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   109,     0,   110,     1,     3,     7,     9,    10,    15,
      19,    20,    21,    22,    23,    25,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    55,    56,
      59,    60,    66,    67,    68,    69,    70,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    99,   101,   111,   114,
     142,   143,   101,    16,   115,     3,   128,   129,   101,     3,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,     4,   113,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,    99,   144,     3,   114,
     114,    53,    54,    58,    61,    62,    65,    72,    73,    86,
      87,    90,    91,    99,   101,   105,   101,   114,     3,     5,
      13,    17,    18,    87,    99,   116,   121,   122,   130,   131,
     133,   136,   137,   138,   141,    99,   101,   102,    24,    24,
      24,   101,   101,   113,    24,   102,   112,   103,     3,   145,
       7,   146,    57,   104,   114,   114,     4,   114,   114,   114,
     114,   114,    26,   114,   114,   114,    86,    91,   101,    99,
      99,   138,   130,    99,    99,   141,    17,    18,   130,   141,
       8,    52,    63,    64,   103,   119,   120,   106,    11,    12,
       3,   106,   125,   126,   127,   127,    71,    86,    87,    90,
     102,     4,   129,   114,   114,   114,   112,   114,   114,   101,
     114,   102,   104,     3,   147,   144,   101,   114,   104,   139,
     141,   104,   104,   117,   130,     3,    90,   123,   124,   141,
     130,   130,   126,   102,    63,    64,   103,   132,   103,   134,
     136,   137,   141,   141,   141,   136,   104,   101,   103,     3,
      52,   103,     8,   102,   146,     3,   140,   121,   102,   107,
     103,   107,     3,   130,   130,   114,     3,   114,     3,   102,
     104,   118,   124,   141,   104,   135,   135,   103,    52,   103,
       3,   119,   103,   114,     3,   114,     5,   103,   114
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* "VAR" */

/* Line 1391 of yacc.c  */
#line 171 "../src/parser.yy"
	{delete [](yyvaluep->VAR_NAME);};

/* Line 1391 of yacc.c  */
#line 1649 "parser.tab.cc"
	break;
      case 6: /* "STRING" */

/* Line 1391 of yacc.c  */
#line 172 "../src/parser.yy"
	{delete (yyvaluep->STRING_VALUE);};

/* Line 1391 of yacc.c  */
#line 1658 "parser.tab.cc"
	break;
      case 112: /* "context" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->RELATION);};

/* Line 1391 of yacc.c  */
#line 1667 "parser.tab.cc"
	break;
      case 113: /* "relPairList" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->REL_TUPLE_PAIR);};

/* Line 1391 of yacc.c  */
#line 1676 "parser.tab.cc"
	break;
      case 114: /* "relation" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->RELATION);};

/* Line 1391 of yacc.c  */
#line 1685 "parser.tab.cc"
	break;
      case 116: /* "builtRelation" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->RELATION);};

/* Line 1391 of yacc.c  */
#line 1694 "parser.tab.cc"
	break;
      case 119: /* "optionalFormula" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->ASTP);};

/* Line 1391 of yacc.c  */
#line 1703 "parser.tab.cc"
	break;
      case 121: /* "tupleDeclaration" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->TUPLE_DESCRIPTOR);};

/* Line 1391 of yacc.c  */
#line 1712 "parser.tab.cc"
	break;
      case 125: /* "varList" */

/* Line 1391 of yacc.c  */
#line 180 "../src/parser.yy"
	{
  for (std::set<char *>::iterator i = (yyvaluep->VAR_LIST)->begin(); i != (yyvaluep->VAR_LIST)->end(); i++)
    delete []*i;
  delete (yyvaluep->VAR_LIST);
 };

/* Line 1391 of yacc.c  */
#line 1725 "parser.tab.cc"
	break;
      case 126: /* "varDecl" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->DECLARATION_SITE);};

/* Line 1391 of yacc.c  */
#line 1734 "parser.tab.cc"
	break;
      case 127: /* "varDeclOptBrackets" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->DECLARATION_SITE);};

/* Line 1391 of yacc.c  */
#line 1743 "parser.tab.cc"
	break;
      case 130: /* "formula" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->ASTP);};

/* Line 1391 of yacc.c  */
#line 1752 "parser.tab.cc"
	break;
      case 136: /* "expList" */

/* Line 1391 of yacc.c  */
#line 175 "../src/parser.yy"
	{
  for (std::set<Exp *>::iterator i = (yyvaluep->EXP_LIST)->begin(); i != (yyvaluep->EXP_LIST)->end(); i++)
    delete *i;
  delete (yyvaluep->EXP_LIST);
 };

/* Line 1391 of yacc.c  */
#line 1765 "parser.tab.cc"
	break;
      case 137: /* "constraintChain" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->ASTCP);};

/* Line 1391 of yacc.c  */
#line 1774 "parser.tab.cc"
	break;
      case 138: /* "simpleExp" */

/* Line 1391 of yacc.c  */
#line 174 "../src/parser.yy"
	{delete (yyvaluep->EXP);};

/* Line 1391 of yacc.c  */
#line 1783 "parser.tab.cc"
	break;
      case 141: /* "exp" */

/* Line 1391 of yacc.c  */
#line 174 "../src/parser.yy"
	{delete (yyvaluep->EXP);};

/* Line 1391 of yacc.c  */
#line 1792 "parser.tab.cc"
	break;
      case 142: /* "reachable" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->RELATION_ARRAY_1D);};

/* Line 1391 of yacc.c  */
#line 1801 "parser.tab.cc"
	break;
      case 143: /* "reachable_of" */

/* Line 1391 of yacc.c  */
#line 173 "../src/parser.yy"
	{delete (yyvaluep->RELATION);};

/* Line 1391 of yacc.c  */
#line 1810 "parser.tab.cc"
	break;

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1806 of yacc.c  */
#line 204 "../src/parser.yy"
    { assert( current_Declaration_Site == globalDecls);}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 209 "../src/parser.yy"
    {
             simplify = false; 
          }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 212 "../src/parser.yy"
    {
            flushScanBuffer();
            std::cout << err_msg;
            err_msg.clear();
            current_Declaration_Site = globalDecls;
            need_coef = false;
            std::cout << "...skipping to statement end..." << std::endl;
            delete relationDecl;
            relationDecl = NULL;
          }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 222 "../src/parser.yy"
    {flushScanBuffer();}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 223 "../src/parser.yy"
    {
            flushScanBuffer();
            try {
              if(simplify)
              (yyvsp[(3) - (4)].RELATION)->simplify(redundant_conj_level, redundant_constr_level);
              else
              (yyvsp[(3) - (4)].RELATION)->simplify();
              Relation *r = relationMap[std::string((yyvsp[(1) - (4)].VAR_NAME))];
              if (r != NULL) delete r;
              relationMap[std::string((yyvsp[(1) - (4)].VAR_NAME))] = (yyvsp[(3) - (4)].RELATION);
            }
             catch(const std::exception &e){
                  std::cout << e.what() << std::endl; 
             } 
           
            delete [](yyvsp[(1) - (4)].VAR_NAME);
          }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 240 "../src/parser.yy"
    {
            flushScanBuffer();
            if(simplify)
            (yyvsp[(1) - (2)].RELATION)->simplify(redundant_conj_level, redundant_constr_level);
            else
            (yyvsp[(1) - (2)].RELATION)->simplify();
            (yyvsp[(1) - (2)].RELATION)->print_with_subs(stdout); 
            delete (yyvsp[(1) - (2)].RELATION);
          }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 249 "../src/parser.yy"
    {
#if defined(OMIT_GETRUSAGE)
            printf("'time' requires getrusage, but the omega calclator was compiled with OMIT_GETRUSAGE set!\n");
#else
            flushScanBuffer();
            printf("\n");
            int t;
            Relation R;
            bool SKIP_FULL_CHECK = getenv("OC_TIMING_SKIP_FULL_CHECK");
            ((yyvsp[(2) - (3)].RELATION))->and_with_GEQ();
            start_clock();
            for (t=1;t<=100;t++) {
              R = *(yyvsp[(2) - (3)].RELATION);
              R.finalize();
            }
            int copyTime = clock_diff();
            start_clock();
            for (t=1;t<=100;t++) {
              R = *(yyvsp[(2) - (3)].RELATION);
              R.finalize();
              R.simplify();  /* default simplification effort */
            }
            int simplifyTime = clock_diff() -copyTime;
            Relation R2;
            if (!SKIP_FULL_CHECK) {
              start_clock();
              for (t=1;t<=100;t++) {
                R2 = *(yyvsp[(2) - (3)].RELATION);
                R2.finalize();
                R2.simplify(2,4); /* maximal simplification effort */
              }
            }
            int excessiveTime = clock_diff() - copyTime;
            printf("Times (in microseconds): \n");
            printf("%5d us to copy original set of constraints\n",copyTime/100);
            printf("%5d us to do the default amount of simplification, obtaining: \n\t", simplifyTime/100);
            R.print_with_subs(stdout); 
            printf("\n"); 
            if (!SKIP_FULL_CHECK) {
              printf("%5d us to do the maximum (i.e., excessive) amount of simplification, obtaining: \n\t", excessiveTime/100);
              R2.print_with_subs(stdout); 
              printf("\n");
            }
            if (!anyTimingDone) {
              bool warn = false;
#ifndef SPEED 
              warn =true;
#endif
#ifndef NDEBUG
              warn = true;
#endif
              if (warn) {
                printf("WARNING: The Omega calculator was compiled with options that force\n");
                printf("it to perform additional consistency and error checks\n");
                printf("that may slow it down substantially\n");
                printf("\n");
              }
              printf("NOTE: These times relect the time of the current _implementation_\n");
              printf("of our algorithms. Performance bugs do exist. If you intend to publish or \n");
              printf("report on the performance on the Omega test, we respectfully but strongly \n");
              printf("request that send your test cases to us to allow us to determine if the \n");
              printf("times are appropriate, and if the way you are using the Omega library to \n"); 
              printf("solve your problem is the most effective way.\n");
              printf("\n");

              printf("Also, please be aware that over the past two years, we have focused our \n");
              printf("efforts on the expressive power of the Omega library, sometimes at the\n");
              printf("expensive of raw speed. Our original implementation of the Omega test\n");
              printf("was substantially faster on the limited domain it handled.\n");
              printf("\n");
              printf("  Thanks, \n");
              printf("  the Omega Team \n");
            }
            anyTimingDone = true;
            delete (yyvsp[(2) - (3)].RELATION);
#endif
          }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 326 "../src/parser.yy"
    {
#if defined(OMIT_GETRUSAGE)
            printf("'timeclosure' requires getrusage, but the omega calclator was compiled with OMIT_GETRUSAGE set!\n");
#else
            flushScanBuffer();
            try {
              int t;
              Relation R;
              ((yyvsp[(2) - (3)].RELATION))->and_with_GEQ();
              start_clock();
              for (t=1;t<=100;t++) {
                R = *(yyvsp[(2) - (3)].RELATION);
                R.finalize();
              }
              int copyTime = clock_diff();
              start_clock();
              for (t=1;t<=100;t++) {
                R = *(yyvsp[(2) - (3)].RELATION);
                R.finalize();
                R.simplify();
              }
              int simplifyTime = clock_diff() -copyTime;
              Relation Rclosed;
              start_clock();
              for (t=1;t<=100;t++) {
                Rclosed = *(yyvsp[(2) - (3)].RELATION);
                Rclosed.finalize();
                Rclosed = TransitiveClosure(Rclosed, 1,Relation::Null());
              }
              int closureTime = clock_diff() - copyTime;
              Relation R2;
              start_clock();
              for (t=1;t<=100;t++) {
                R2 = *(yyvsp[(2) - (3)].RELATION);
                R2.finalize();
                R2.simplify(2,4);
              }
              int excessiveTime = clock_diff() - copyTime;
              printf("Times (in microseconds): \n");
              printf("%5d us to copy original set of constraints\n",copyTime/100);
              printf("%5d us to do the default amount of simplification, obtaining: \n\t", simplifyTime/100);
              R.print_with_subs(stdout); 
              printf("\n"); 
              printf("%5d us to do the maximum (i.e., excessive) amount of simplification, obtaining: \n\t", excessiveTime/100);
              R2.print_with_subs(stdout); 
              printf("%5d us to do the transitive closure, obtaining: \n\t", closureTime/100);
              Rclosed.print_with_subs(stdout);
              printf("\n");
              if (!anyTimingDone) {
                bool warn = false;
#ifndef SPEED 
                warn =true;
#endif
#ifndef NDEBUG
                warn = true;
#endif
                if (warn) {
                  printf("WARNING: The Omega calculator was compiled with options that force\n");
                  printf("it to perform additional consistency and error checks\n");
                  printf("that may slow it down substantially\n");
                  printf("\n");
                }
                printf("NOTE: These times relect the time of the current _implementation_\n");
                printf("of our algorithms. Performance bugs do exist. If you intend to publish or \n");
                printf("report on the performance on the Omega test, we respectfully but strongly \n");
                printf("request that send your test cases to us to allow us to determine if the \n");
                printf("times are appropriate, and if the way you are using the Omega library to \n"); 
                printf("solve your problem is the most effective way.\n");
                printf("\n");
              
                printf("Also, please be aware that over the past two years, we have focused our \n");
                printf("efforts on the expressive power of the Omega library, sometimes at the\n");
                printf("expensive of raw speed. Our original implementation of the Omega test\n");
                printf("was substantially faster on the limited domain it handled.\n");
                printf("\n");
                printf("  Thanks, \n");
                printf("  the Omega Team \n");
              }
              anyTimingDone = true;
            }
            catch (const std::exception &e) {
              std::cout << e.what() << std::endl;
            }
            delete (yyvsp[(2) - (3)].RELATION);
#endif
          }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 412 "../src/parser.yy"
    {
            flushScanBuffer();
            try {
              if (Must_Be_Subset(copy(*(yyvsp[(1) - (4)].RELATION)), copy(*(yyvsp[(3) - (4)].RELATION))))
                std::cout << "True" << std::endl;
              else if (Might_Be_Subset(copy(*(yyvsp[(1) - (4)].RELATION)), copy(*(yyvsp[(3) - (4)].RELATION))))
                std::cout << "Possible" << std::endl;
              else
                std::cout << "False" << std::endl;
            }
            catch (const std::exception &e) {
              std::cout << e.what() << std::endl;
            }
            delete (yyvsp[(1) - (4)].RELATION);
            delete (yyvsp[(3) - (4)].RELATION);
          }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 428 "../src/parser.yy"
    {
            flushScanBuffer();
#ifdef BUILD_CODEGEN
            try {
              CodeGen cg((yyvsp[(2) - (4)].REL_TUPLE_PAIR)->first, (yyvsp[(2) - (4)].REL_TUPLE_PAIR)->second, *(yyvsp[(3) - (4)].RELATION));
              CG_result *cgr = cg.buildAST();
              if (cgr != NULL) {
                std::string s = cgr->printString();
                std::cout << s << std::endl;
                delete cgr;
              }
              else
                std::cout << "/* empty */" << std::endl;
            }
            catch (const std::exception &e) {
              std::cout << e.what() << std::endl;
            }
#else
            std::cout << "CodeGen package not built" << std::endl;
#endif
            delete (yyvsp[(3) - (4)].RELATION);
            delete (yyvsp[(2) - (4)].REL_TUPLE_PAIR);
          }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 451 "../src/parser.yy"
    {
            flushScanBuffer();
#ifdef BUILD_CODEGEN
            try {
              CodeGen cg((yyvsp[(3) - (5)].REL_TUPLE_PAIR)->first, (yyvsp[(3) - (5)].REL_TUPLE_PAIR)->second, *(yyvsp[(4) - (5)].RELATION));
              CG_result *cgr = cg.buildAST((yyvsp[(2) - (5)].INT_VALUE));
              if (cgr != NULL) {
                std::string s = cgr->printString();
                std::cout << s << std::endl;
                delete cgr;
              }
              else
                std::cout << "/* empty */" << std::endl;
            }
            catch (const std::exception &e) {
              std::cout << e.what() << std::endl;
            }
#else
            std::cout << "CodeGen package not built" << std::endl;
#endif
            delete (yyvsp[(4) - (5)].RELATION);
            delete (yyvsp[(3) - (5)].REL_TUPLE_PAIR);
          }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 474 "../src/parser.yy"
    {
            flushScanBuffer();
            Dynamic_Array1<Relation> &final = *(yyvsp[(1) - (2)].RELATION_ARRAY_1D);
            bool any_sat = false;
            int i,n_nodes = reachable_info->node_names.size();
            for(i = 1; i <= n_nodes; i++)
              if(final[i].is_upper_bound_satisfiable()) {
                any_sat = true;
                std::cout << "Node " << reachable_info->node_names[i] << ": ";
                final[i].print_with_subs(stdout);
              }
            if(!any_sat)
              std::cout << "No nodes reachable.\n";
            delete (yyvsp[(1) - (2)].RELATION_ARRAY_1D);
            delete reachable_info;
          }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 493 "../src/parser.yy"
    {(yyval.RELATION) = new Relation(); *(yyval.RELATION) = Relation::Null();}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 494 "../src/parser.yy"
    {(yyval.RELATION) = (yyvsp[(2) - (2)].RELATION); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 497 "../src/parser.yy"
    {
              try {
                (yyvsp[(1) - (5)].REL_TUPLE_PAIR)->first.push_back(*(yyvsp[(3) - (5)].RELATION));
                (yyvsp[(1) - (5)].REL_TUPLE_PAIR)->second.push_back(*(yyvsp[(5) - (5)].RELATION));
              }
              catch (const std::exception &e) {
                delete (yyvsp[(1) - (5)].REL_TUPLE_PAIR);
                delete (yyvsp[(3) - (5)].RELATION);
                delete (yyvsp[(5) - (5)].RELATION);
                yyerror(e.what());
                YYERROR;
              }
              delete (yyvsp[(3) - (5)].RELATION);
              delete (yyvsp[(5) - (5)].RELATION);
              (yyval.REL_TUPLE_PAIR) = (yyvsp[(1) - (5)].REL_TUPLE_PAIR);
            }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 513 "../src/parser.yy"
    {
              try {
                (yyvsp[(1) - (3)].REL_TUPLE_PAIR)->first.push_back(Identity((yyvsp[(3) - (3)].RELATION)->n_set()));
                (yyvsp[(1) - (3)].REL_TUPLE_PAIR)->second.push_back(*(yyvsp[(3) - (3)].RELATION));
              }
              catch (const std::exception &e) {
                delete (yyvsp[(1) - (3)].REL_TUPLE_PAIR);
                delete (yyvsp[(3) - (3)].RELATION);
                yyerror(e.what());
                YYERROR;
              }
              delete (yyvsp[(3) - (3)].RELATION);
              (yyval.REL_TUPLE_PAIR) = (yyvsp[(1) - (3)].REL_TUPLE_PAIR);
            }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 527 "../src/parser.yy"
    {
              std::pair<std::vector<Relation>, std::vector<Relation> > *rtp = new std::pair<std::vector<Relation>, std::vector<Relation> >();
              try {
                rtp->first.push_back(*(yyvsp[(1) - (3)].RELATION));
                rtp->second.push_back(*(yyvsp[(3) - (3)].RELATION));
              }
              catch (const std::exception &e) {
                delete rtp;
                delete (yyvsp[(1) - (3)].RELATION);
                delete (yyvsp[(3) - (3)].RELATION);
                yyerror(e.what());
                YYERROR;
              }
              delete (yyvsp[(1) - (3)].RELATION);
              delete (yyvsp[(3) - (3)].RELATION);
              (yyval.REL_TUPLE_PAIR) = rtp;
            }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 544 "../src/parser.yy"
    {
              std::pair<std::vector<Relation>, std::vector<Relation> > *rtp = new std::pair<std::vector<Relation>, std::vector<Relation> >();
              try {
                rtp->first.push_back(Identity((yyvsp[(1) - (1)].RELATION)->n_set()));
                rtp->second.push_back(*(yyvsp[(1) - (1)].RELATION));
              }
              catch (const std::exception &e) {
                delete rtp;
                delete (yyvsp[(1) - (1)].RELATION);
                yyerror(e.what());
                YYERROR;
              }
              delete (yyvsp[(1) - (1)].RELATION);
              (yyval.REL_TUPLE_PAIR) = rtp;
            }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 561 "../src/parser.yy"
    {need_coef = true; relationDecl = new Declaration_Site();}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 562 "../src/parser.yy"
    {
           need_coef = false;
           (yyval.RELATION) = (yyvsp[(3) - (4)].RELATION); 
           current_Declaration_Site = globalDecls;
           delete relationDecl;
           relationDecl = NULL;
         }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 569 "../src/parser.yy"
    {
           Relation *r = relationMap[std::string((yyvsp[(1) - (1)].VAR_NAME))];
           if (r == NULL) {
             yyerror(std::string("relation ") + to_string((yyvsp[(1) - (1)].VAR_NAME)) + std::string(" not declared"));
             delete [](yyvsp[(1) - (1)].VAR_NAME);
             YYERROR;
           }
           (yyval.RELATION) = new Relation(*r);
           delete [](yyvsp[(1) - (1)].VAR_NAME);
         }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 579 "../src/parser.yy"
    {(yyval.RELATION) = (yyvsp[(2) - (3)].RELATION);}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 580 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = TransitiveClosure(*(yyvsp[(1) - (2)].RELATION), 1, Relation::Null());
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (2)].RELATION);
         }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 593 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             int vars = (yyvsp[(1) - (2)].RELATION)->n_inp();
             *(yyval.RELATION) = Union(Identity(vars), TransitiveClosure(*(yyvsp[(1) - (2)].RELATION), 1, Relation::Null()));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }           
           delete (yyvsp[(1) - (2)].RELATION);
         }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 607 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION)= TransitiveClosure(*(yyvsp[(1) - (4)].RELATION), 1, *(yyvsp[(4) - (4)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (4)].RELATION);
             delete (yyvsp[(4) - (4)].RELATION);
             yyerror(e.what());
             YYERROR;
           }           
           delete (yyvsp[(1) - (4)].RELATION);
           delete (yyvsp[(4) - (4)].RELATION);
         }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 622 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = ApproxClosure(*(yyvsp[(1) - (3)].RELATION)); 
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (3)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (3)].RELATION);
         }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 635 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = calculateTransitiveClosure(*(yyvsp[(1) - (3)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (3)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (3)].RELATION);
         }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 648 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             Relation o(*(yyvsp[(2) - (2)].RELATION));
             Relation r(*(yyvsp[(2) - (2)].RELATION));
             r = Join(r,LexForward((yyvsp[(2) - (2)].RELATION)->n_out()));
             *(yyval.RELATION) = Difference(o,r);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }           
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 664 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             Relation o(*(yyvsp[(2) - (2)].RELATION));
             Relation r(*(yyvsp[(2) - (2)].RELATION));
             r = Join(r,Inverse(LexForward((yyvsp[(2) - (2)].RELATION)->n_out())));
             *(yyval.RELATION) = Difference(o,r);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 680 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             Relation o(*(yyvsp[(2) - (2)].RELATION));
             Relation r(*(yyvsp[(2) - (2)].RELATION));
             r = Join(LexForward((yyvsp[(2) - (2)].RELATION)->n_inp()),r);
             *(yyval.RELATION) = Difference(o,r);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 696 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             Relation o(*(yyvsp[(2) - (2)].RELATION));
             Relation r(*(yyvsp[(2) - (2)].RELATION));
             r = Join(Inverse(LexForward((yyvsp[(2) - (2)].RELATION)->n_inp())),r);
             *(yyval.RELATION) = Difference(o,r);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 712 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             Relation c(*(yyvsp[(2) - (2)].RELATION));
             Relation r(*(yyvsp[(2) - (2)].RELATION));
             *(yyval.RELATION) = Cross_Product(Relation(*(yyvsp[(2) - (2)].RELATION)),c);
             *(yyval.RELATION) = Difference(r,Domain(Intersection(*(yyval.RELATION),LexForward((yyval.RELATION)->n_inp()))));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 728 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             Relation c(*(yyvsp[(2) - (2)].RELATION));
             Relation r(*(yyvsp[(2) - (2)].RELATION));
             *(yyval.RELATION) = Cross_Product(Relation(*(yyvsp[(2) - (2)].RELATION)),c);
             *(yyval.RELATION) = Difference(r,Range(Intersection(*(yyval.RELATION),LexForward((yyval.RELATION)->n_inp()))));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);       
         }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 744 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Farkas(*(yyvsp[(2) - (2)].RELATION), Basic_Farkas);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 757 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Farkas(*(yyvsp[(2) - (2)].RELATION), Decoupled_Farkas);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 770 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = ConicClosure(*(yyvsp[(1) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }             
           delete (yyvsp[(1) - (2)].RELATION);
         }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 783 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Project_Sym(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 796 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Project_On_Sym(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 809 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Deltas(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 822 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = DeltasToRelation(*(yyvsp[(2) - (2)].RELATION),(yyvsp[(2) - (2)].RELATION)->n_set(),(yyvsp[(2) - (2)].RELATION)->n_set());
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 835 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Domain(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 848 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = VennDiagramForm(*(yyvsp[(2) - (2)].RELATION),Relation::True(*(yyvsp[(2) - (2)].RELATION)));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 861 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = VennDiagramForm(*(yyvsp[(2) - (4)].RELATION),*(yyvsp[(4) - (4)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (4)].RELATION);
             delete (yyvsp[(4) - (4)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (4)].RELATION);
           delete (yyvsp[(4) - (4)].RELATION);
         }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 876 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = ConvexHull(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 889 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = DecoupledConvexHull(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 902 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Farkas(*(yyvsp[(2) - (2)].RELATION),Positive_Combination_Farkas);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 915 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Farkas(*(yyvsp[(2) - (2)].RELATION),Linear_Combination_Farkas);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 928 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Farkas(*(yyvsp[(2) - (2)].RELATION),Affine_Combination_Farkas);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 941 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Farkas(*(yyvsp[(2) - (2)].RELATION),Convex_Combination_Farkas);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }           
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 954 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = CheckForConvexRepresentation(CheckForConvexPairs(*(yyvsp[(2) - (2)].RELATION)));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 967 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = CheckForConvexRepresentation(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 980 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = ConvexRepresentation(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 993 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = AffineHull(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 1006 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = ConicHull(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 1019 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = LinearHull(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 1032 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = QuickHull(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 1045 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = RectHull(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 1058 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = SimpleHull(*(yyvsp[(2) - (2)].RELATION), true, true);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 1071 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Hull(*(yyvsp[(2) - (2)].RELATION),true,1,Relation::Null());
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 1084 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Hull(*(yyvsp[(2) - (4)].RELATION),true,1,*(yyvsp[(4) - (4)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (4)].RELATION);
             delete (yyvsp[(4) - (4)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (4)].RELATION);
           delete (yyvsp[(4) - (4)].RELATION);
         }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 1099 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Approximate(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 1112 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Range(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 1125 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Inverse(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 1138 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Complement(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 1151 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Gist(*(yyvsp[(2) - (4)].RELATION),*(yyvsp[(4) - (4)].RELATION),1);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (4)].RELATION);
             delete (yyvsp[(4) - (4)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (4)].RELATION);
           delete (yyvsp[(4) - (4)].RELATION);
         }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 1166 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Composition(*(yyvsp[(1) - (4)].RELATION),*(yyvsp[(3) - (4)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (4)].RELATION);
             delete (yyvsp[(3) - (4)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (4)].RELATION);
           delete (yyvsp[(3) - (4)].RELATION);
         }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 1181 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Composition(*(yyvsp[(1) - (3)].RELATION),*(yyvsp[(3) - (3)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (3)].RELATION);
             delete (yyvsp[(3) - (3)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (3)].RELATION);
           delete (yyvsp[(3) - (3)].RELATION);
         }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 1196 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = After(*(yyvsp[(1) - (3)].RELATION),(yyvsp[(3) - (3)].INT_VALUE),(yyvsp[(3) - (3)].INT_VALUE));
             (*(yyval.RELATION)).prefix_print(stdout);
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (3)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (3)].RELATION);
         }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 1210 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Composition(*(yyvsp[(3) - (3)].RELATION),*(yyvsp[(1) - (3)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (3)].RELATION);
             delete (yyvsp[(3) - (3)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (3)].RELATION);
           delete (yyvsp[(3) - (3)].RELATION);
         }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 1225 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Restrict_Range(*(yyvsp[(1) - (3)].RELATION),*(yyvsp[(3) - (3)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (3)].RELATION);
             delete (yyvsp[(3) - (3)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (3)].RELATION);
           delete (yyvsp[(3) - (3)].RELATION);
         }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 1240 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Restrict_Domain(*(yyvsp[(1) - (3)].RELATION),*(yyvsp[(3) - (3)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (3)].RELATION);
             delete (yyvsp[(3) - (3)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (3)].RELATION);
           delete (yyvsp[(3) - (3)].RELATION);
         }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 1255 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Intersection(*(yyvsp[(1) - (3)].RELATION),*(yyvsp[(3) - (3)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (3)].RELATION);
             delete (yyvsp[(3) - (3)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (3)].RELATION);
           delete (yyvsp[(3) - (3)].RELATION);
         }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1270 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Difference(*(yyvsp[(1) - (3)].RELATION),*(yyvsp[(3) - (3)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (3)].RELATION);
             delete (yyvsp[(3) - (3)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (3)].RELATION);
           delete (yyvsp[(3) - (3)].RELATION);
         }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 1285 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Union(*(yyvsp[(1) - (3)].RELATION),*(yyvsp[(3) - (3)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (3)].RELATION);
             delete (yyvsp[(3) - (3)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (3)].RELATION);
           delete (yyvsp[(3) - (3)].RELATION);
         }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1300 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Cross_Product(*(yyvsp[(1) - (3)].RELATION),*(yyvsp[(3) - (3)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(1) - (3)].RELATION);
             delete (yyvsp[(3) - (3)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(1) - (3)].RELATION);
           delete (yyvsp[(3) - (3)].RELATION);
         }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1315 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Union(*(yyvsp[(2) - (2)].RELATION), Relation::Unknown(*(yyvsp[(2) - (2)].RELATION)));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1328 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Intersection(*(yyvsp[(2) - (2)].RELATION), Relation::Unknown(*(yyvsp[(2) - (2)].RELATION)));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1341 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Upper_Bound(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1354 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Lower_Bound(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1367 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Sample_Solution(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1380 "../src/parser.yy"
    {
           (yyval.RELATION) = new Relation();
           try {
             *(yyval.RELATION) = Symbolic_Solution(*(yyvsp[(2) - (2)].RELATION));
           }
           catch (const std::exception &e) {
             delete (yyval.RELATION);
             delete (yyvsp[(2) - (2)].RELATION);
             yyerror(e.what());
             YYERROR;
           }
           delete (yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1393 "../src/parser.yy"
    { (yyval.RELATION) = (yyvsp[(1) - (1)].RELATION); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1394 "../src/parser.yy"
    {
           if (((yyvsp[(2) - (2)].RELATION))->is_satisfiable()) {
             fprintf(stderr,"assert_unsatisfiable failed on ");
             ((yyvsp[(2) - (2)].RELATION))->print_with_subs(stderr);
             exit(1);
           }
           (yyval.RELATION)=(yyvsp[(2) - (2)].RELATION);
         }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1404 "../src/parser.yy"
    {currentTuple = Output_Tuple;}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1405 "../src/parser.yy"
    {currentTuple = Input_Tuple;}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1405 "../src/parser.yy"
    {
                 Relation * r = new Relation((yyvsp[(1) - (6)].TUPLE_DESCRIPTOR)->size,(yyvsp[(4) - (6)].TUPLE_DESCRIPTOR)->size);
                 resetGlobals();
                 F_And *f = r->add_and();
                 for(int i = 1; i <= (yyvsp[(1) - (6)].TUPLE_DESCRIPTOR)->size; i++) {
                   (yyvsp[(1) - (6)].TUPLE_DESCRIPTOR)->vars[i-1]->vid = r->input_var(i);
                   if (!(yyvsp[(1) - (6)].TUPLE_DESCRIPTOR)->vars[i-1]->anonymous) 
                     r->name_input_var(i, (yyvsp[(1) - (6)].TUPLE_DESCRIPTOR)->vars[i-1]->stripped_name);
                 }
                 for(int i = 1; i <= (yyvsp[(4) - (6)].TUPLE_DESCRIPTOR)->size; i++) {
                   (yyvsp[(4) - (6)].TUPLE_DESCRIPTOR)->vars[i-1]->vid = r->output_var(i);
                   if (!(yyvsp[(4) - (6)].TUPLE_DESCRIPTOR)->vars[i-1]->anonymous) 
                     r->name_output_var(i, (yyvsp[(4) - (6)].TUPLE_DESCRIPTOR)->vars[i-1]->stripped_name);
                 }
                 r->setup_names();
                 for (std::set<Exp *>::iterator i = (yyvsp[(1) - (6)].TUPLE_DESCRIPTOR)->eq_constraints.begin(); i != (yyvsp[(1) - (6)].TUPLE_DESCRIPTOR)->eq_constraints.end(); i++)
                   install_eq(f, *i, 0);
                 for (std::set<Exp *>::iterator i = (yyvsp[(1) - (6)].TUPLE_DESCRIPTOR)->geq_constraints.begin(); i != (yyvsp[(1) - (6)].TUPLE_DESCRIPTOR)->geq_constraints.end(); i++)
                   install_geq(f, *i, 0);
                 for (std::set<strideConstraint *>::iterator i = (yyvsp[(1) - (6)].TUPLE_DESCRIPTOR)->stride_constraints.begin(); i != (yyvsp[(1) - (6)].TUPLE_DESCRIPTOR)->stride_constraints.end(); i++)
                   install_stride(f, *i);
                 for (std::set<Exp *>::iterator i = (yyvsp[(4) - (6)].TUPLE_DESCRIPTOR)->eq_constraints.begin(); i != (yyvsp[(4) - (6)].TUPLE_DESCRIPTOR)->eq_constraints.end(); i++)
                   install_eq(f, *i, 0);
                 for (std::set<Exp *>::iterator i = (yyvsp[(4) - (6)].TUPLE_DESCRIPTOR)->geq_constraints.begin(); i != (yyvsp[(4) - (6)].TUPLE_DESCRIPTOR)->geq_constraints.end(); i++)
                   install_geq(f, *i, 0);
                 for (std::set<strideConstraint *>::iterator i = (yyvsp[(4) - (6)].TUPLE_DESCRIPTOR)->stride_constraints.begin(); i != (yyvsp[(4) - (6)].TUPLE_DESCRIPTOR)->stride_constraints.end(); i++)
                   install_stride(f, *i);
                 if ((yyvsp[(6) - (6)].ASTP)) (yyvsp[(6) - (6)].ASTP)->install(f);
                 delete (yyvsp[(1) - (6)].TUPLE_DESCRIPTOR);
                 delete (yyvsp[(4) - (6)].TUPLE_DESCRIPTOR);
                 delete (yyvsp[(6) - (6)].ASTP);
                 (yyval.RELATION) = r;
               }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1438 "../src/parser.yy"
    {
                 Relation * r = new Relation((yyvsp[(1) - (2)].TUPLE_DESCRIPTOR)->size);
                 resetGlobals();
                 F_And *f = r->add_and();
                 for(int i = 1; i <= (yyvsp[(1) - (2)].TUPLE_DESCRIPTOR)->size; i++) {
                   (yyvsp[(1) - (2)].TUPLE_DESCRIPTOR)->vars[i-1]->vid = r->set_var(i);
                   if (!(yyvsp[(1) - (2)].TUPLE_DESCRIPTOR)->vars[i-1]->anonymous) 
                     r->name_set_var(i, (yyvsp[(1) - (2)].TUPLE_DESCRIPTOR)->vars[i-1]->stripped_name);
                 }
                 r->setup_names();
                 for (std::set<Exp *>::iterator i = (yyvsp[(1) - (2)].TUPLE_DESCRIPTOR)->eq_constraints.begin(); i != (yyvsp[(1) - (2)].TUPLE_DESCRIPTOR)->eq_constraints.end(); i++)
                   install_eq(f, *i, 0);
                 for (std::set<Exp *>::iterator i = (yyvsp[(1) - (2)].TUPLE_DESCRIPTOR)->geq_constraints.begin(); i != (yyvsp[(1) - (2)].TUPLE_DESCRIPTOR)->geq_constraints.end(); i++)
                   install_geq(f, *i, 0);
                 for (std::set<strideConstraint *>::iterator i = (yyvsp[(1) - (2)].TUPLE_DESCRIPTOR)->stride_constraints.begin(); i != (yyvsp[(1) - (2)].TUPLE_DESCRIPTOR)->stride_constraints.end(); i++)
                   install_stride(f, *i);
                 if ((yyvsp[(2) - (2)].ASTP)) (yyvsp[(2) - (2)].ASTP)->install(f);
                 delete (yyvsp[(1) - (2)].TUPLE_DESCRIPTOR);
                 delete (yyvsp[(2) - (2)].ASTP);
                 (yyval.RELATION) = r;
               }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1459 "../src/parser.yy"
    {
                 Relation * r = new Relation(0,0);
                 F_And *f = r->add_and();
                 (yyvsp[(1) - (1)].ASTP)->install(f);
                 delete (yyvsp[(1) - (1)].ASTP);
                 (yyval.RELATION) = r;
               }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1468 "../src/parser.yy"
    {(yyval.ASTP) = (yyvsp[(2) - (2)].ASTP);}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1469 "../src/parser.yy"
    {(yyval.ASTP) = 0;}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1477 "../src/parser.yy"
    {currentTupleDescriptor = new tupleDescriptor; tuplePos = 1;}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1479 "../src/parser.yy"
    {(yyval.TUPLE_DESCRIPTOR) = currentTupleDescriptor; tuplePos = 0;}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1487 "../src/parser.yy"
    {
           Declaration_Site *ds = defined((yyvsp[(1) - (1)].VAR_NAME));
           if (!ds)
             currentTupleDescriptor->extend((yyvsp[(1) - (1)].VAR_NAME),currentTuple,tuplePos);
           else {
             Variable_Ref *v = lookupScalar((yyvsp[(1) - (1)].VAR_NAME));
             if (v == NULL) {
               yyerror(std::string("cannot find declaration for variable ") + to_string((yyvsp[(1) - (1)].VAR_NAME)));
               delete [](yyvsp[(1) - (1)].VAR_NAME);
               YYERROR;
             }
             if (ds != globalDecls)
               currentTupleDescriptor->extend((yyvsp[(1) - (1)].VAR_NAME), new Exp(v));
             else
               currentTupleDescriptor->extend(new Exp(v));
           }
           tuplePos++;
           delete [](yyvsp[(1) - (1)].VAR_NAME);
         }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1506 "../src/parser.yy"
    {currentTupleDescriptor->extend(); tuplePos++;}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1507 "../src/parser.yy"
    {
             currentTupleDescriptor->extend((yyvsp[(1) - (1)].EXP));
             tuplePos++;
         }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1511 "../src/parser.yy"
    {
             currentTupleDescriptor->extend((yyvsp[(1) - (3)].EXP),(yyvsp[(3) - (3)].EXP));
             tuplePos++;
         }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1515 "../src/parser.yy"
    {
             currentTupleDescriptor->extend((yyvsp[(1) - (5)].EXP),(yyvsp[(3) - (5)].EXP),(yyvsp[(5) - (5)].COEF_VALUE));
             tuplePos++;
         }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1521 "../src/parser.yy"
    {(yyval.VAR_LIST) = (yyvsp[(1) - (3)].VAR_LIST); (yyval.VAR_LIST)->insert((yyvsp[(3) - (3)].VAR_NAME)); (yyvsp[(3) - (3)].VAR_NAME) = NULL;}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1522 "../src/parser.yy"
    {(yyval.VAR_LIST) = new std::set<char *>(); (yyval.VAR_LIST)->insert((yyvsp[(1) - (1)].VAR_NAME)); (yyvsp[(1) - (1)].VAR_NAME) = NULL;}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1525 "../src/parser.yy"
    {
          (yyval.DECLARATION_SITE) = current_Declaration_Site = new Declaration_Site((yyvsp[(1) - (1)].VAR_LIST));
          for (std::set<char *>::iterator i = (yyvsp[(1) - (1)].VAR_LIST)->begin(); i != (yyvsp[(1) - (1)].VAR_LIST)->end(); i++)
            delete [](*i);
          delete (yyvsp[(1) - (1)].VAR_LIST);
        }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1533 "../src/parser.yy"
    {(yyval.DECLARATION_SITE) = (yyvsp[(1) - (1)].DECLARATION_SITE);}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1534 "../src/parser.yy"
    {(yyval.DECLARATION_SITE) = (yyvsp[(2) - (3)].DECLARATION_SITE);}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1541 "../src/parser.yy"
    {globalDecls->extend_both_tuples((yyvsp[(1) - (4)].VAR_NAME), (yyvsp[(3) - (4)].INT_VALUE)); delete [](yyvsp[(1) - (4)].VAR_NAME);}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1542 "../src/parser.yy"
    {
          globalDecls->extend((yyvsp[(1) - (1)].VAR_NAME));
          delete [](yyvsp[(1) - (1)].VAR_NAME);
        }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1548 "../src/parser.yy"
    {(yyval.ASTP) = new AST_And((yyvsp[(1) - (3)].ASTP),(yyvsp[(3) - (3)].ASTP));}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1549 "../src/parser.yy"
    {(yyval.ASTP) = new AST_Or((yyvsp[(1) - (3)].ASTP),(yyvsp[(3) - (3)].ASTP));}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1550 "../src/parser.yy"
    {(yyval.ASTP) = (yyvsp[(1) - (1)].ASTCP);}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1551 "../src/parser.yy"
    {(yyval.ASTP) = (yyvsp[(2) - (3)].ASTP);}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1552 "../src/parser.yy"
    {(yyval.ASTP) = new AST_Not((yyvsp[(2) - (2)].ASTP));}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1553 "../src/parser.yy"
    {(yyval.ASTP) = new AST_exists((yyvsp[(2) - (5)].DECLARATION_SITE),(yyvsp[(4) - (5)].ASTP));}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1554 "../src/parser.yy"
    {(yyval.ASTP) = new AST_forall((yyvsp[(2) - (5)].DECLARATION_SITE),(yyvsp[(4) - (5)].ASTP));}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1573 "../src/parser.yy"
    {popScope();}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1576 "../src/parser.yy"
    {(yyval.EXP_LIST) = (yyvsp[(3) - (3)].EXP_LIST); (yyval.EXP_LIST)->insert((yyvsp[(1) - (3)].EXP));}
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1577 "../src/parser.yy"
    {(yyval.EXP_LIST) = new std::set<Exp *>(); (yyval.EXP_LIST)->insert((yyvsp[(1) - (1)].EXP));}
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1580 "../src/parser.yy"
    {(yyval.ASTCP) = new AST_constraints((yyvsp[(1) - (3)].EXP_LIST),(yyvsp[(2) - (3)].REL_OPERATOR),(yyvsp[(3) - (3)].EXP_LIST));}
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1581 "../src/parser.yy"
    {(yyval.ASTCP) = new AST_constraints((yyvsp[(1) - (3)].EXP_LIST),(yyvsp[(2) - (3)].REL_OPERATOR),(yyvsp[(3) - (3)].ASTCP));}
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1584 "../src/parser.yy"
    {
            Variable_Ref *v = lookupScalar((yyvsp[(1) - (1)].VAR_NAME));
            if (v == NULL) {
              yyerror(std::string("cannot find declaration for variable ") + to_string((yyvsp[(1) - (1)].VAR_NAME)));
              delete [](yyvsp[(1) - (1)].VAR_NAME);
              YYERROR;
            }
            (yyval.EXP) = new Exp(v);
            delete [](yyvsp[(1) - (1)].VAR_NAME);
          }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1594 "../src/parser.yy"
    {argCount = 1;}
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1594 "../src/parser.yy"
    {
            Variable_Ref *v;
            if ((yyvsp[(4) - (5)].ARGUMENT_TUPLE) == Input_Tuple)
              v = functionOfInput[(yyvsp[(1) - (5)].VAR_NAME)];
            else
              v = functionOfOutput[(yyvsp[(1) - (5)].VAR_NAME)];
            if (v == NULL) {
              yyerror(std::string("Function ") + to_string((yyvsp[(1) - (5)].VAR_NAME)) + std::string(" not declared"));
              delete [](yyvsp[(1) - (5)].VAR_NAME);
              YYERROR;
            }
            (yyval.EXP) = new Exp(v);
            delete [](yyvsp[(1) - (5)].VAR_NAME);
          }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1608 "../src/parser.yy"
    { (yyval.EXP) = (yyvsp[(2) - (3)].EXP); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1611 "../src/parser.yy"
    {
               Variable_Ref *v = lookupScalar((yyvsp[(3) - (3)].VAR_NAME));
               if (v == NULL) {
                 yyerror(std::string("cannot find declaration for variable ") + to_string((yyvsp[(1) - (3)].ARGUMENT_TUPLE)));
                 delete [](yyvsp[(3) - (3)].VAR_NAME);
                 YYERROR;
               }
               if (v->pos != argCount || v->of != (yyvsp[(1) - (3)].ARGUMENT_TUPLE) || (v->of != Input_Tuple && v->of != Output_Tuple)) {
                 yyerror("arguments to function must be prefix of input or output tuple");
                 delete [](yyvsp[(3) - (3)].VAR_NAME);
                 YYERROR;
               }
               (yyval.ARGUMENT_TUPLE) = v->of;
               argCount++;
               delete [](yyvsp[(3) - (3)].VAR_NAME);
             }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1627 "../src/parser.yy"
    {
               Variable_Ref *v = lookupScalar((yyvsp[(1) - (1)].VAR_NAME));
               if (v == NULL) {
                 yyerror(std::string("cannot find declaration for variable ") + to_string((yyvsp[(1) - (1)].VAR_NAME)));
                 delete [](yyvsp[(1) - (1)].VAR_NAME);
                 YYERROR;
               }
               if (v->pos != argCount || (v->of != Input_Tuple && v->of != Output_Tuple)) {
                 yyerror("arguments to function must be prefix of input or output tuple");
                 delete [](yyvsp[(1) - (1)].VAR_NAME);
                 YYERROR;
               }
               (yyval.ARGUMENT_TUPLE) = v->of;
               argCount++;
               delete [](yyvsp[(1) - (1)].VAR_NAME);
             }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1645 "../src/parser.yy"
    {(yyval.EXP) = new Exp((yyvsp[(1) - (1)].COEF_VALUE));}
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 1646 "../src/parser.yy"
    {(yyval.EXP) = multiply((yyvsp[(1) - (2)].COEF_VALUE),(yyvsp[(2) - (2)].EXP));}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1647 "../src/parser.yy"
    {(yyval.EXP) = (yyvsp[(1) - (1)].EXP); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 1648 "../src/parser.yy"
    {(yyval.EXP) = negate((yyvsp[(2) - (2)].EXP));}
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 1649 "../src/parser.yy"
    {(yyval.EXP) = add((yyvsp[(1) - (3)].EXP),(yyvsp[(3) - (3)].EXP));}
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1650 "../src/parser.yy"
    {(yyval.EXP) = subtract((yyvsp[(1) - (3)].EXP),(yyvsp[(3) - (3)].EXP));}
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1651 "../src/parser.yy"
    {
      try {
        (yyval.EXP) = multiply((yyvsp[(1) - (3)].EXP),(yyvsp[(3) - (3)].EXP));
      }
      catch (const std::exception &e) {
        yyerror(e.what());
        YYERROR;
      }
    }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 1663 "../src/parser.yy"
    {
            Dynamic_Array1<Relation> *final = Reachable_Nodes(reachable_info);
            (yyval.RELATION_ARRAY_1D) = final;
          }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 1669 "../src/parser.yy"
    {
               Dynamic_Array1<Relation> *final = Reachable_Nodes(reachable_info);
               int index = reachable_info->node_names.index(std::string((yyvsp[(2) - (5)].VAR_NAME)));
               if (index == 0) {
                 yyerror(std::string("no such node ") + to_string((yyvsp[(2) - (5)].VAR_NAME)));
                 delete [](yyvsp[(2) - (5)].VAR_NAME);
                 delete final;
                 delete reachable_info;
                 YYERROR;
               }
               (yyval.RELATION) = new Relation; 
               *(yyval.RELATION) = (*final)[index];
               delete final;
               delete reachable_info;
               delete [](yyvsp[(2) - (5)].VAR_NAME);
             }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 1687 "../src/parser.yy"
    {
               int sz = reachable_info->node_names.size();
               reachable_info->node_arity.reallocate(sz);
               reachable_info->transitions.resize(sz+1,sz+1);
               reachable_info->start_nodes.resize(sz+1);
             }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1695 "../src/parser.yy"
    {
                   reachable_info->node_names.append(std::string((yyvsp[(3) - (3)].VAR_NAME)));
                   delete [](yyvsp[(3) - (3)].VAR_NAME);
                 }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 1699 "../src/parser.yy"
    {
                   reachable_info = new reachable_information;
                   reachable_info->node_names.append(std::string((yyvsp[(1) - (1)].VAR_NAME)));
                   delete [](yyvsp[(1) - (1)].VAR_NAME);
                 }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1707 "../src/parser.yy"
    {  
                        int i,j;
                        int n_nodes = reachable_info->node_names.size();
                        Tuple<int> &arity = reachable_info->node_arity;
                        Dynamic_Array2<Relation> &transitions = reachable_info->transitions;

                        /* fixup unspecified transitions to be false */
                        /* find arity */
                        for(i = 1; i <= n_nodes; i++) arity[i] = -1;
                        for(i = 1; i <= n_nodes; i++)
                          for(j = 1; j <= n_nodes; j++)
                            if(! transitions[i][j].is_null()) {
                              int in_arity = transitions[i][j].n_inp();
                              int out_arity = transitions[i][j].n_out();
                              if(arity[i] < 0) arity[i] = in_arity;
                              if(arity[j] < 0) arity[j] = out_arity;
                              if(in_arity != arity[i] || out_arity != arity[j]) {
                                yyerror(std::string("arity mismatch in node transition: ") + to_string(reachable_info->node_names[i]) + std::string(" -> ") + to_string(reachable_info->node_names[j]));
                                delete reachable_info;
                                YYERROR;
                              }
                            }
                        for(i = 1; i <= n_nodes; i++) 
                          if(arity[i] < 0) arity[i] = 0;
                        /* Fill in false relations */
                        for(i = 1; i <= n_nodes; i++)
                          for(j = 1; j <= n_nodes; j++)
                            if(transitions[i][j].is_null())
                              transitions[i][j] = Relation::False(arity[i],arity[j]);

                        /* fixup unused start node positions */
                        Dynamic_Array1<Relation> &nodes = reachable_info->start_nodes;
                        for(i = 1; i <= n_nodes; i++) 
                          if(nodes[i].is_null()) 
                            nodes[i] = Relation::False(arity[i]);
                          else
                            if(nodes[i].n_set() != arity[i]){
                              yyerror(std::string("arity mismatch in start node ") + to_string(reachable_info->node_names[i]));
                              delete reachable_info;
                              YYERROR;
                            }
                   }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 1751 "../src/parser.yy"
    {
                            int n_nodes = reachable_info->node_names.size();
                            int index = reachable_info->node_names.index((yyvsp[(3) - (5)].VAR_NAME));
                            if (!(index > 0 && index <= n_nodes)) {
                              yyerror(std::string("no such node ")+to_string((yyvsp[(3) - (5)].VAR_NAME)));
                              delete (yyvsp[(5) - (5)].RELATION);
                              delete [](yyvsp[(3) - (5)].VAR_NAME);
                              delete reachable_info;
                              YYERROR;
                            }
                            reachable_info->start_nodes[index] = *(yyvsp[(5) - (5)].RELATION);
                            delete (yyvsp[(5) - (5)].RELATION);
                            delete [](yyvsp[(3) - (5)].VAR_NAME);
                          }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 1765 "../src/parser.yy"
    {
                            int n_nodes = reachable_info->node_names.size();
                            int from_index = reachable_info->node_names.index((yyvsp[(3) - (7)].VAR_NAME));
                            if (!(from_index > 0 && from_index <= n_nodes)) {
                              yyerror(std::string("no such node ")+to_string((yyvsp[(3) - (7)].VAR_NAME)));
                              delete (yyvsp[(7) - (7)].RELATION);
                              delete [](yyvsp[(3) - (7)].VAR_NAME);
                              delete [](yyvsp[(5) - (7)].VAR_NAME);
                              delete reachable_info;
                              YYERROR;
                            }
                            int to_index = reachable_info->node_names.index((yyvsp[(5) - (7)].VAR_NAME));
                            if (!(to_index > 0 && to_index <= n_nodes)) {
                              yyerror(std::string("no such node ")+to_string((yyvsp[(5) - (7)].VAR_NAME)));
                              delete (yyvsp[(7) - (7)].RELATION);
                              delete [](yyvsp[(3) - (7)].VAR_NAME);
                              delete [](yyvsp[(5) - (7)].VAR_NAME);
                              delete reachable_info;
                              YYERROR;
                            }
                            reachable_info->transitions[from_index][to_index] = *(yyvsp[(7) - (7)].RELATION);
                            delete (yyvsp[(7) - (7)].RELATION);
                            delete [](yyvsp[(3) - (7)].VAR_NAME);
                            delete [](yyvsp[(5) - (7)].VAR_NAME);
                          }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 1790 "../src/parser.yy"
    {
                            int n_nodes = reachable_info->node_names.size();
                            int from_index = reachable_info->node_names.index((yyvsp[(1) - (5)].VAR_NAME));
                            if (!(from_index > 0 && from_index <= n_nodes)) {
                              yyerror(std::string("no such node ")+to_string((yyvsp[(1) - (5)].VAR_NAME)));
                              delete (yyvsp[(5) - (5)].RELATION);
                              delete [](yyvsp[(1) - (5)].VAR_NAME);
                              delete [](yyvsp[(3) - (5)].VAR_NAME);
                              delete reachable_info;
                              YYERROR;
                            }
                            int to_index = reachable_info->node_names.index((yyvsp[(3) - (5)].VAR_NAME));
                            if (!(to_index > 0 && to_index <= n_nodes)) {
                              yyerror(std::string("no such node ")+to_string((yyvsp[(3) - (5)].VAR_NAME)));
                              delete (yyvsp[(5) - (5)].RELATION);
                              delete [](yyvsp[(1) - (5)].VAR_NAME);
                              delete [](yyvsp[(3) - (5)].VAR_NAME);
                              delete reachable_info;
                              YYERROR;
                            }
                            reachable_info->transitions[from_index][to_index] = *(yyvsp[(5) - (5)].RELATION);
                            delete (yyvsp[(5) - (5)].RELATION);
                            delete [](yyvsp[(1) - (5)].VAR_NAME);
                            delete [](yyvsp[(3) - (5)].VAR_NAME);
                          }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 1815 "../src/parser.yy"
    {
                            int n_nodes = reachable_info->node_names.size();
                            int index = reachable_info->node_names.index((yyvsp[(1) - (3)].VAR_NAME));
                            if (!(index > 0 && index <= n_nodes)) {
                              yyerror(std::string("no such node ")+to_string((yyvsp[(1) - (3)].VAR_NAME)));
                              delete (yyvsp[(3) - (3)].RELATION);
                              delete [](yyvsp[(1) - (3)].VAR_NAME);
                              delete reachable_info;
                              YYERROR;
                            }
                            reachable_info->start_nodes[index] = *(yyvsp[(3) - (3)].RELATION);
                            delete (yyvsp[(3) - (3)].RELATION);
                            delete [](yyvsp[(1) - (3)].VAR_NAME);
                          }
    break;



/* Line 1806 of yacc.c  */
#line 4488 "parser.tab.cc"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 1831 "../src/parser.yy"


void yyerror(const std::string &s) {
  std::stringstream ss;
  if (is_interactive)
    ss << s << "\n";
  else
    ss << s << " at line " << mylexer.lineno() << "\n";
  err_msg = ss.str();
}


int main(int argc, char **argv) {
  if (argc > 2){
    fprintf(stderr, "Usage: %s [script_file]\n", argv[0]);
    exit(1);
  }

  if (argc == 2) {
    std::ifstream *ifs = new std::ifstream;
    ifs->open(argv[1], std::ifstream::in);
    if (!ifs->is_open()) {
        fprintf(stderr, "can't open input file %s\n", argv[1]);
        exit(1);
    }
    yy_buffer_state *bs = mylexer.yy_create_buffer(ifs, 8092);
    mylexer.yypush_buffer_state(bs);
  }

  //yydebug = 1;
  is_interactive = false;
  if (argc == 1) {
#if defined __USE_POSIX  
    if (isatty((int)fileno(stdin)))
      is_interactive = true;
#elif defined  __WIN32
    if (_isatty(_fileno(stdin)))
      is_interactive = true;
#endif
  }

  if (is_interactive) {
#ifdef BUILD_CODEGEN
    std::cout << "Omega+ and CodeGen+ ";
#else
    std::cout << "Omega+ ";
#endif
    std::cout << "v2.2.3 (built on " OMEGA_BUILD_DATE ")" << std::endl;
    std::cout << "Copyright (C) 1994-2000 the Omega Project Team" << std::endl;
    std::cout << "Copyright (C) 2005-2011 Chun Chen" << std::endl;
    std::cout << "Copyright (C) 2011-2012 University of Utah" << std::endl;
    std::cout << PROMPT_STRING << ' ';
    std::cout.flush();
  }

  need_coef = false;  
  current_Declaration_Site = globalDecls = new Global_Declaration_Site();

  if (yyparse() != 0) {
    if (!is_interactive)
      std::cout << "syntax error at the end of the file, missing ';'" << std::endl;
    else
      std::cout << std::endl;
    delete relationDecl;
    relationDecl = NULL;
  }
  else {
    if (is_interactive)
      std::cout << std::endl;
  }

  for (std::map<std::string, Relation *>::iterator i = relationMap.begin(); i != relationMap.end(); i++)
    delete (*i).second;
  delete globalDecls;  
  
  return 0;
}

Relation LexForward(int n) {
  Relation r(n,n);
  F_Or *f = r.add_or();
  for (int i=1; i <= n; i++) {
    F_And *g = f->add_and();
    for(int j=1;j<i;j++) {
      EQ_Handle e = g->add_EQ();
      e.update_coef(r.input_var(j),-1);
      e.update_coef(r.output_var(j),1);
      e.finalize();
    }
    GEQ_Handle e = g->add_GEQ();
    e.update_coef(r.input_var(i),-1);
    e.update_coef(r.output_var(i),1);
    e.update_const(-1);
    e.finalize();
  }
  r.finalize();
  return r;
}

