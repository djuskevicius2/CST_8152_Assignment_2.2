/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa / George Kriger / Abdullah Kadri
************************************************************
*/

/*
***********************************************************
* File name: buffer.c
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013, 014]
* Assignment: A12.
* Date: Jan 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer (A12)
************************************************************
*/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Buffer.h"
#endif

/*
***********************************************************
* Function name: bCreate
* Purpose: Creates the buffer according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: Ver 2.1
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to Buffer)
* Algorithm: Allocation of memory according to inicial (default) values.
* TO_DO: 
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

BufferPointer bCreate(yago_int size, yago_int increment, yago_int mode) {
	BufferPointer b;
	/* TO_DO: Defensive programming */
	b = (BufferPointer)calloc(1, sizeof(Buffer));
	b->string = (yago_chr*)malloc(size);
	/* TO_DO: Adjust properties */
	return b;
}


/*
***********************************************************
* Function name: bAddChar
* Purpose: Adds a char to buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   ch = char to be added
* Return value:
*	bPointer (pointer to Buffer)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

BufferPointer bAddChar(BufferPointer const pBuffer, yago_chr ch) {
	yago_int newSize = 0;
	/* TO_DO: Defensive programming */
	switch (pBuffer->mode) {
	case MODE_FIXED:
		/* TO_DO: Adjust the fixed mode */
		/* NO REALLOC HERE, MODE IS FIXED */
	case MODE_ADDIT:
		/* TO_DO: Adjust the additive mode */
		/* CREAT REALLOC FUNCTION HERE*/
	case MODE_MULTI:
		/* TO_DO: Adjust the multiplicative mode */
		/* CREATE REALLOC FUNCTION HERE */
		;
	}
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust the buffer */
	pBuffer->string[pBuffer->position.writePos++] = ch;
	return pBuffer;
}

/*
***********************************************************
* Function name: bClear
* Purpose: Clears the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_bol bClear(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	pBuffer->position.writePos = pBuffer->position.markPos = pBuffer->position.readPos = 0;
	/* TO_DO: Adjust flags original */
	return yago_TRUE;
}

/*
***********************************************************
* Function name: bDestroy
* Purpose: Releases the buffer address
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_bol bDestroy(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Clear buffer data */
	return yago_TRUE;
}

/*
***********************************************************
* Function name: bIsFull
* Purpose: Checks if buffer is full
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_bol bIsFull(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is FUL */
	return yago_TRUE;
}

/*
***********************************************************
* Function name: bGetWritePos
* Purpose: Returns the position of char to be added
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	addcPosition value
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_int bGetWritePos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	return pBuffer->position.writePos;
}

/*
***********************************************************
* Function name: bGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_int bGetSize(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	return pBuffer->size;
}

/*
***********************************************************
* Function name: bGetMode
* Purpose: Returns the operational mode
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_int bGetMode(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	return pBuffer->mode;
}


/*
***********************************************************
* Function name: bGetMarkPos
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	mark offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_int bGetMarkPos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	return pBuffer->position.markPos;
}


/*
***********************************************************
* Function name: bSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_bol bSetMark(BufferPointer const pBuffer, yago_int mark) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust the mark */
	return yago_TRUE;
}

/*
***********************************************************
* Function name: bPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_int bPrint(BufferPointer const pBuffer) {
	yago_int size = 1;
	yago_chr c;
	/* TO_DO: Defensive programming */
	c = bGetChar(pBuffer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (c>0) {
		/* TO_DO: Adjust size */
		printf("%c", c);
		c = bGetChar(pBuffer);
	}
	return size;
}

/*
***********************************************************
* Function name: bLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   fi = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_int bLoad(BufferPointer const pBuffer, FILE* const fi) {
	yago_int size = 1;
	yago_chr c;
	/* TO_DO: Defensive programming */
	c = (yago_chr)fgetc(fi);
	while (!feof(fi)) {
		if (!bAddChar(pBuffer, c)) {
			ungetc(c, fi);
			return BUFFER_ERROR;
		}
		c = (char)fgetc(fi);
		/* Adjust size */
	}
	/* TO_DO: Defensive programming */
	return size;
}

/*
***********************************************************
* Function name: bIsEmpty
* Purpose: Checks if buffer is empty.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_bol bIsEmpty(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check if it is empty */
	return yago_FALSE;
}

/*
***********************************************************
* Function name: bGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_chr bGetChar(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust EOB flag */
	return pBuffer->string[pBuffer->position.readPos++];
}


/*
***********************************************************
* Function name: bRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_bol bRecover(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	pBuffer->position.readPos = 0;
	pBuffer->position.markPos = 0;
	return yago_TRUE;
}


/*
***********************************************************
* Function name: bRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_bol bRetract(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	pBuffer->position.readPos--;
	return yago_TRUE;
}


/*
***********************************************************
* Function name: bRestore
* Purpose: Resets the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_bol bRestore(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	pBuffer->position.readPos = pBuffer->position.markPos;
	return yago_TRUE;
}


/*
***********************************************************
* Function name: bGetReadPos
* Purpose: Returns the value of getCPosition.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	The readPos offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_int bGetReadPos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	return pBuffer->position.readPos;
}


/*
***********************************************************
* Function name: bGetIncrement
* Purpose: Returns the buffer increment.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_int bGetIncrement(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	return pBuffer->increment;
}


/*
***********************************************************
* Function name: bGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
yago_chr* bGetContent(BufferPointer const pBuffer, yago_int pos) {
	/* TO_DO: Defensive programming */
	return pBuffer->string + pos;
}


/*
***********************************************************
* Function name: bGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
#define FLAGS_
#undef FLAGS_
#ifndef FLAGS_
yago_flg bGetFlags(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	return pBuffer->flags;
}
#else
#define bGetFlags(pBuffer) ((pBuffer)?(pBuffer->flags):(RT_FAIL_1))
#endif
