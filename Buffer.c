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
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013, 014]
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
	if (size == NULL || size == 0) {
		size = BUFFER_DEFAULT_SIZE;
		increment = BUFFER_DEFAULT_INCREMENT;
	}
	if (increment == NULL || increment == 0) {
		mode = MODE_FIXED;
	}
	if (!(mode == MODE_FIXED || mode == MODE_ADDIT || mode == MODE_MULTI)) {
		return BUFFER_ERROR; /* Exits because buffer cannot be created */
	}
	/* We can create the buffer because we have checked all the params */
	b = (BufferPointer)calloc(1, sizeof(Buffer));
	b->string = (yago_chr*)malloc(size);
	if (b->string == NULL) { // Defensive programming
		free(b);
		return BUFFER_ERROR;
	}
	/* TO_DO: Adjust properties */
	b->size = size;
	b->increment = increment;
	b->mode = mode;
	b->flags = YAGO_DEFAULT_FLAG;
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
	BufferPointer tempPBuffer;
	tempPBuffer = pBuffer; /* Making a temporary pBuffer to act upon in case NULL must be returned */
	/* TO_DO: Defensive programming */
	if (bIsFull(pBuffer)) {
		tempPBuffer->flags &= RST_RLB; /* resetting RLB bit on flags */
		switch (pBuffer->mode) {
		case MODE_FIXED:
			/* truncate the rest of the buffer to avoid memory overflow */
			bRetract(pBuffer);
			return pBuffer;
		case MODE_ADDIT:
			/* TO_DO: Adjust the additive mode */
			newSize = tempPBuffer->size + tempPBuffer->increment;
			if (newSize < 0 || newSize > YAGO_MAX_SIZE) {
				return NULL;
			}
			/* CREATE REALLOC FUNCTION HERE*/
			tempPBuffer->string = realloc(pBuffer->string, newSize);
			if (tempPBuffer->string == NULL) {
				free(tempPBuffer->string);
				return NULL;
			}
		case MODE_MULTI:
			/* TO_DO: Adjust the multiplicative mode */
			newSize = tempPBuffer->size * tempPBuffer->increment;
			if (newSize < 0 || newSize > YAGO_MAX_SIZE) {
				return NULL;
			}
			/* CREATE REALLOC FUNCTION HERE */
			tempPBuffer->string = realloc(pBuffer->string, newSize);
			if (tempPBuffer->string == NULL) {
				free(tempPBuffer);
				return NULL;
			}
		}
		/* TO_DO: Defensive programming */
		/* TO_DO: Adjust the buffer */
	}
	else {
		pBuffer->string[pBuffer->position.writePos++] = ch;
		return pBuffer;
	}
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
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	pBuffer->position.writePos = pBuffer->position.markPos = pBuffer->position.readPos = 0;
	/* TO_DO: Adjust flags original */
	pBuffer->flags = YAGO_DEFAULT_FLAG;
	return YAGO_TRUE;
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
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	/* TO_DO: Clear buffer data */
	free(pBuffer->string);
	free(pBuffer);
	return YAGO_TRUE;
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
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	if ((pBuffer->position.writePos >= pBuffer->size))
	{
		return YAGO_TRUE;
	}
	else if (pBuffer->flags & CHK_FUL == CHK_FUL) { /* 0010.0000 */
		return YAGO_TRUE;
	}
	else {
		/* TO_DO: Check flag if buffer is FUL */
		return YAGO_FALSE;
	}
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
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
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
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
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
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
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
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
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
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	/* TO_DO: Adjust the mark */
	if (mark >= 0 && mark <= pBuffer->position.writePos) {
		pBuffer->position.markPos = mark;
		return YAGO_TRUE;
	}
	else {
		return YAGO_FALSE;
	}
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
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	c = bGetChar(pBuffer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (c>0) {
		/* TO_DO: Adjust size */
		printf("%c", c);
		c = bGetChar(pBuffer);
		size++;
	}
	return size;
}  /* Can we check EOB in bGetChar()? Or does it have to be done here */

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
	if (pBuffer == NULL || fi == NULL) {
		return BUFFER_ERROR;
	}
	c = (yago_chr)fgetc(fi);
	while (!feof(fi)) {
		if (!bAddChar(pBuffer, c)) {
			ungetc(c, fi);
			return BUFFER_ERROR;
		}
		c = (char)fgetc(fi);
		/* Adjust size */
		size++;
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
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	/* TO_DO: Check if it is empty */
	else if ((pBuffer->flags & CHK_EMP) == CHK_EMP) {
		return YAGO_TRUE;
	}
	else {
		return YAGO_FALSE;
	}
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
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust EOB flag */
	if (pBuffer->position.readPos == pBuffer->position.writePos) {
		pBuffer->flags = pBuffer->flags | SET_EOB;
		return BUFFER_EOF;
	}
	pBuffer->flags = pBuffer->flags & RST_EOB;
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
	if (pBuffer == NULL) {
		return YAGO_FALSE;
	}
	pBuffer->position.readPos = 0;
	pBuffer->position.markPos = 0;
	return YAGO_TRUE;
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
	if ((pBuffer->position.readPos - 1) < 0) {
		return YAGO_FALSE;
	}
	else {
		pBuffer->position.readPos--;
		return YAGO_TRUE;
	}
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
	return YAGO_TRUE;
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
	if (pos < 0) {
		return BUFFER_EOF;
	}
	else if (pos >= pBuffer->position.writePos) {
		return BUFFER_EOF;
	}
	else {
		return pBuffer->string + pos;
	}
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
