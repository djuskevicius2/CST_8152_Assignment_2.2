/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa / George Kriger / Abdullah Kadri
************************************************************
*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013, 014]
* Assignment: A22, A32.
* Date: Feb 21 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20   /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1   /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
/* NOT YET COMPLETE - ADD YAG0 DEFINITIONS */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	LBR_T,		/*  5: Left brace token */
	RBR_T,		/*  6: Right brace token */
	KW_T,		/*  7: Keyword token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	SEOF_T		/* 10: Source end-of-file token */
	/*
	 * NEWLINE_T would need to work several ways:
		- if a newline has been emitted, and it comes after a COLON :,
		  then we would need to add a check to see if there is an indent
		- if a newline has been emitted, and no keyword comes next, and the
		  indentation has not changed, 
		  then next char (excluding whitespace) is not a keyword, 
		  we would need to treat it as part of the functon
		- need to keep a count of the number of indents (i.e:
			fun_main(void):							// 0 indents, colon, newline
				if (10 < 11):						// 1 indent,  colon, newline
					if (12 < 10):					// 2 indents, colon, newline
						print("12 less than 10")	// 3 indents, newline
				else:								// DEDENT, DEDENT, 1 indent, colon, newline
					print("Whoops!")                // 2 indents, colon, newline
													// DEDENT, DEDENT, 0 indents, eof
	NEWLINE_T   
	INDENT_T
	DEDENT_T
	*/
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	yago_int codeType;						/* integer attributes accessor */
	AriOperator arithmeticOperator;			/* arithmetic operator attribute code */
	RelOperator relationalOperator;			/* relational operator attribute code */
	LogOperator logicalOperator;			/* logical operator attribute code */
	EofOperator seofType;					/* source-end-of-file attribute code */
	yago_int intValue;						/* integer literal attribute (value) */
	yago_int keywordIndex;					/* keyword index in the keyword table */
	yago_int contentString;					/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	yago_flt floatValue;					/* floating-point literal attribute (value) */
	yago_chr idLexeme[VID_LEN + 1];			/* variable identifier token attribute */
	yago_chr errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttributes {
	yago_flg flags;			/* Flags information */
	union {
		yago_int intValue;				/* Integer value */
		yago_flt floatValue;			/* Float value */
		yago_nul* stringContent;		/* String value */
	} values;
} IdAttributes;

/* Token declaration */
typedef struct Token {
	yago_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttributes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, @comment@ , ',' , ';' , '-' , '+' , '*' , '/', ## , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Error states and illegal state */
/* STATES SHOULD BEGIN AFTER THE CLOUDS - BASED ON OUR TABLE, AT 19 */
#define ES  6		/* Error state with no retract */
#define ER  7		/* Error state with retract */
#define IS -1		/* Illegal state */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 12

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '&'
#define CHRCOL4 '\"'

/* These constants will be used on VID / MID function */
#define MNIDPREFIX '&'

/* TO_DO: Transition table - type of states defined in separate table
static yago_int transitionTable[][TABLE_COLUMNS] = {
/*   [A-z] , [0-9],    _,    &,    ", SEOF, other
	   L(0),  D(1), U(2), M(3), Q(4), E(5),  O(6) 
	{     1,    ES,   ES,   ES,    4,   ER,   ES}, // S0: NOAS
	{     1,     1,    1,    2,   ES,   ER,    3}, // S1: NOAS
	{    IS,    IS,   IS,   IS,   IS,   IS,   IS}, // S2: ASNR (MVID)
	{    IS,    IS,   IS,   IS,   IS,   IS,   IS}, // S3: ASWR (KEY)
	{     4,     4,    4,    4,    5,   ER,    4}, // S4: NOAS
	{    IS,    IS,   IS,   IS,   IS,   IS,   IS}, // S5: ASNR (SL)
	{    IS,    IS,   IS,   IS,   IS,   IS,   IS}, // S6: ASNR (ES)
	{    IS,    IS,   IS,   IS,   IS,   IS,   IS}  // S7: ASWR (ER)
}; */

static yago_int transitionTable[][TABLE_COLUMNS] = {
/*	  [A-z], [0-9], 	_, fun/U,	  ",	 ',	    #,    ###,	  .,	 :,  YEOF, other	
	   L(0),  D(1),  U(2),  M(3),  S(4), CH(5),  C(6), MLC(7), P(8), CO(9), E(10), O(11) */
	{     1,     7,     3,     5,    11,    13,    15,    17,    ES,    ES,    ER,    ES}, // S0:  NOAS
	{     1,     1,     1,    ES,    ES,    ES,    ES,    ES,    ES,    ES,    ER,    ES}, // S1:  NOAS
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS}, // S2:  ASWR (KEY)
	{     3,     3,     3,    ES,    ES,    ES,    ES,    ES,    ES,    ES,    ER,    ES}, // S3:  NOAS
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS}, // S4:  ASWR (VID)
	{     5,     5,     5,    ES,    ES,    ES,    ES,    ES,    ES,     6,    ER,    ES}, // S5:  NOAS
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS}, // S6:  ASNR (FNID)
	{    ES,     7,    ES,    ES,    ES,    ES,    ES,    ES,     9,    ES,    ER,    ES}, // S7:  NOAS
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS}, // S8:  ASWR (IL)
	{    ES,     9,    ES,    ES,    ES,    ES,    ES,    ES,    ES,    ES,    ER,    ES}, // S9:  NOAS
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS}, // S10: ASWR (FPL)
	{    11,    11,    11,    11,    11,    12,    11,    11,    11,    11,    ER,    11}, // S11: NOAS
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS}, // S12: ASNR (SL)
	{    13,    13,    13,    13,    13,    13,    14,    13,    13,    13,    ER,    13}, // S13: NOAS
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS}, // S14: ASNR (CL)
	{    15,    15,    15,    15,    15,    15,    15,    16,    15,    15,    ER,    15}, // S15: NOAS
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS}, // S16: ASNR (COM)
	{    17,    17,    17,    17,    17,    17,    17,    18,    17,    17,    ER,    17}, // S17: NOAS
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS,    IS}  // S18: ASNR (MLCOM)
};

/* Define accepting states types */
#define NOAS	0		/* not accepting state */
#define ASNR	1		/* accepting state with no retract */
#define ASWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static yago_int stateType[] = {
	NOAS, /* 00 */
	NOAS, /* 01 */
	ASNR, /* 02 (MID) - Methods */
	ASWR, /* 03 (KEY) */
	NOAS, /* 04 */
	ASNR, /* 05 (SL) */
	ASNR, /* 06 (Err1 - no retract) */
	ASWR  /* 07 (Err2 - retract) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
yago_int startScanner(BufferPointer psc_buf);
static yago_int nextClass(yago_chr c);			/* character class function */
static yago_int nextState(yago_int, yago_chr);		/* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(yago_chr* lexeme);

/* Declare accepting states functions */
Token funcSL	(yago_chr lexeme[]);
Token funcID	(yago_chr lexeme[]);
Token funcKEY	(yago_chr lexeme[]);
Token funcErr	(yago_chr lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	funcErr,	/* ERR1 [06] */
	funcErr		/* ERR2 [07] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 26 // yago is 25

/* TO_DO: Define the list of keywords */
static yago_chr* keywordTable[KWT_SIZE] = {
	"if", "elif", "else",
	"switch", "case", "default",
	"for", "while", "do", 
	"break", "continue", "void",
	"return", "class", "constant", 
	"true", "false", "short", 
	"int", "unsigned", "long", 
	"float", "double", "char",
	"string", "fun"
};

#endif
