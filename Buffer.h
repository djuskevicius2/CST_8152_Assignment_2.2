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
* File name: Buffer.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013, 014]
* Assignment: A12.
* Date: Jan 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
************************************************************
*/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#define BUFFER_H_

/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer) */
enum BUFFERMODES {
	MODE_FIXED = 'f',
	MODE_ADDIT = 'a',
	MODE_MULTI = 'm'
};

/* TO_DO: Adjust all constants to your Language */

#define BUFFER_ERROR (-1)						/* General error message */
#define BUFFER_EOF '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (yago) .................................. */

#define BUFFER_DEFAULT_SIZE			200			/* default initial buffer capacity */
#define BUFFER_DEFAULT_INCREMENT	100			/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for yago */
/* BITS                                (7654.3210) */
#define yago_DEFAULT_FLAG 0x0F 	/* (0000.1111)_2 = (015)_10 */
/* TO_DO: BIT 7: REL = Relocation */
/* Need to define the following for each: */
#define yago_SET_RLB 0x80		/* (1000.0000)_2 */
#define yago_RST_RLB 0x7F		/* (0111.1111)_2 */
#define yago_CHK_RLB 0x80		/* (1000.0000)_2 */

#define yago_SET_EOB 0x60		/* (0100.0000)_2 */
#define yago_RST_EOB 0xBF		/* (1011.1111)_2 */
#define yago_CHK_RLB 0x60		/* (0100.0000)_2 */

#define yago_SET_FUL 0x20		/* (0010.0000)_2 */
#define yago_RST_FUL 0xDF		/* (1101.1111)_2 */
#define yago_CHK_FUL 0x20		/* (0010.0000)_2 */

#define yago_SET_EMP 0x10		/* (0001.0000)_2 */
#define yago_RST_EMP 0xEF		/* (1110.1111)_2 */
#define yago_CHK_FUL 0x10		/* (0001.0000)_2 */


/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (yago) .................................. */

/* TO_DO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	yago_int markPos;			/* the offset (in chars) to the mark location */
	yago_int readPos;			/* the offset (in chars) to the get-character location */
	yago_int writePos;			/* the offset (in chars) to the add-character location */
} Position;

/* Buffer structure */
typedef struct buffer {
	yago_chr*	string;		/* pointer to the beginning of character array (character buffer) */
	yago_int	size;		    /* current dynamic memory size (in bytes) allocated to character buffer */
	yago_int	increment;		/* character array increment factor */
	yago_int	mode;			/* operational mode indicator */
	yago_flg	flags;			/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;		/* Offset / position field */
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* TO_DO: Define your function declarations using your language specification */

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	bCreate(yago_int, yago_int, yago_int);
BufferPointer	bAddChar(BufferPointer const, yago_chr);
yago_bol		bRetract(BufferPointer const);
yago_bol		bRestore(BufferPointer const);
yago_bol		bRecover(BufferPointer const);
yago_bol		bClear(BufferPointer const);
yago_bol		bDestroy(BufferPointer const);
yago_bol		bSetMark(BufferPointer const, yago_int);
yago_bol		bIsEmpty(BufferPointer const);
yago_bol		bIsFull(BufferPointer const);
yago_bol		bIsRealocated(BufferPointer const);
yago_int		bPrint(BufferPointer const);
yago_int		bLoad(BufferPointer const, FILE* const);
/* Getters */
yago_int		bGetSize(BufferPointer const);
yago_int		bGetWritePos(BufferPointer const);
yago_int		bGetMarkPos(BufferPointer const);
yago_int		bGetReadPos(BufferPointer const);
yago_int		bGetIncrement(BufferPointer const);
yago_int		bGetMode(BufferPointer const);
yago_chr		bGetChar(BufferPointer const);
yago_chr*		bGetContent(BufferPointer const, yago_int);
yago_flg		bGetFlags(BufferPointer const);

#endif
