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
* File name: Compilers.h
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa, Daniel Juskevicius, Iain MacEachern
* Course: CST 8152 – Compilers, Lab Section: 012
* Assignment: A12
* Date: Feb 03 2022
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainBuffer(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/* Logical constants */
#define YAGO_TRUE  1
#define YAGO_FALSE 0

/* Constant Max size of the buffer, in bytes */
#define YAGO_MAX_SIZE 				SHRT_MAX-1	/* maximum capacity */ 

/*
------------------------------------------------------------
Data types definitions
------------------------------------------------------------
*/
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
