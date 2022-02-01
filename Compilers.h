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
* File name: compilers.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013, 014]
* Assignment: A12, A22, A32.
* Date: Jan 01 2022
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainBuffer(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/* Logical constants - adapt for your language */
#define YAGO_TRUE  1
#define YAGO_FALSE 0

/* You should add your own constant definitions here */
#define YAGO_MAX_SIZE 				SHRT_MAX-1	/* maximum capacity */ 

/*
------------------------------------------------------------
Data types definitions
------------------------------------------------------------
*/
/* TO_DO: Define your typedefs */
typedef char			yago_chr;
typedef short			yago_sht;
typedef int				yago_int;
typedef unsigned int	yago_uit;
typedef float			yago_flt;

typedef void			yago_nul;

typedef unsigned char	yago_bol;
typedef unsigned char	yago_flg;

typedef long			yago_lng;
typedef double			yago_dbl;

/*
------------------------------------------------------------
Programs:
1: Buffer - invokes MainBuffer code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_BUFFER	= '1',
	PGM_SCANNER = '2',
	PGM_PARSER	= '3'
};

/*
------------------------------------------------------------
Main functions signatures
(Codes will be updated during next assignments)
------------------------------------------------------------
*/
yago_int mainBuffer	(yago_int argc, yago_chr** argv);
/*
yago_int mainScanner	(yago_int argc, yago_chr** argv);
yago_int mainParser	(yago_int argc, yago_chr** argv);
*/
#endif
