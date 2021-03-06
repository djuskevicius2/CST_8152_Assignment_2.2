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
* File name: Buffer.c
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa, Daniel Juskevicius, Iain MacEachern
* Course: CST 8152 ? Compilers, Lab Section: 012
* Assignment: A12.
* Date: Feb 03 2022
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
* Algorithm: Allocation of memory according to initial (default) values.
*************************************************************
*/

BufferPointer bCreate(yago_int size, yago_int increment, yago_int mode) {
	BufferPointer b;
	/* Set the buffer to a default size and increment if no params are passed to main(). */
	if (size == 0) {
		size = BUFFER_DEFAULT_SIZE;
		increment = BUFFER_DEFAULT_INCREMENT;
	}
	if (increment == 0) {
		mode = MODE_FIXED;
	}
	/* If the assigned mode does not match any other modes,
	 * the program exits because buffer cannot be created. 
	 */
	if (!(mode == MODE_FIXED || mode == MODE_ADDIT || mode == MODE_MULTI)) {
		return NULL; 
	}
	/* Buffer can now be created since all params have been checked. */
	b = (BufferPointer)calloc(1, sizeof(Buffer));
	if (b == NULL) return NULL;
	b->string = (yago_chr*)malloc(size);
	if (b->string == NULL) { // Defensive programming
		free(b);
		return NULL;
	}
	/* Adjusting properties of buffer after creation. */
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
*************************************************************
*/

BufferPointer bAddChar(BufferPointer const pBuffer, yago_chr ch) {
	yago_int newSize = 0;
	yago_chr* tempPBuffer;
	/* Making a temporary pBuffer->string to act upon in case NULL must be returned */
	tempPBuffer = pBuffer->string; 
	pBuffer->flags = pBuffer->flags & RST_RLB;
	
	if (bIsFull(pBuffer)) {
		switch (pBuffer->mode) {
		/* If mode is fixed, we truncate the rest of the buffer. */
		case MODE_FIXED:
			bRetract(pBuffer);
			return pBuffer;
		/* If mode is additive, we adjust accordingly. */
		case MODE_ADDIT:
			/* Assigning a temp variable the new size of the buffer. */
			newSize = pBuffer->size + pBuffer->increment;
			if (newSize < 0 || newSize > YAGO_MAX_SIZE) {
				return NULL;
			}
			/* Reallocating memory for the temp buffer, in case of failure. */
			tempPBuffer = (yago_chr*)realloc(pBuffer->string, newSize);
			if (!tempPBuffer)
				return NULL;
			/* As long as there is no crash, we modify the original buffer */
			if (tempPBuffer != pBuffer->string) {
				pBuffer->flags = pBuffer->flags | SET_RLB;
				pBuffer->string = tempPBuffer;
			}
			/* We reset the buffer full bit */
			if (pBuffer->flags & CHK_FUL)
				pBuffer->flags = pBuffer->flags & RST_FUL;
			pBuffer->size = newSize;
		case MODE_MULTI:
			/* Assigning a temp variable the new size of the buffer. */
			newSize = pBuffer->size * pBuffer->increment;
			if (newSize < 0 || newSize > YAGO_MAX_SIZE) {
				return NULL;
			}
			/* Reallocating memory for the temp buffer, in case of failure. */
			tempPBuffer = (yago_chr*)realloc(pBuffer->string, newSize);
			if (!tempPBuffer) {
				return NULL;
			}
			/* As long as there is no crash, we modify the original buffer */
			if (tempPBuffer != pBuffer->string) {
				pBuffer->flags = pBuffer->flags | SET_RLB;
				pBuffer->string = tempPBuffer;
			}
			/* We reset the buffer full bit */
			if (pBuffer->flags & CHK_FUL)
				pBuffer->flags = pBuffer->flags & RST_FUL;
			pBuffer->size = newSize;
		}
	}
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
*************************************************************
*/
yago_bol bClear(BufferPointer const pBuffer) {
	/* Defensive programming in case the operation fails */
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	pBuffer->position.writePos = pBuffer->position.markPos = pBuffer->position.readPos = 0;
	/* Adjust the default flags */
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
*************************************************************
*/
yago_bol bDestroy(BufferPointer const pBuffer) {
	/* Defensive programming in case the operation fails */
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
*************************************************************
*/
yago_bol bIsFull(BufferPointer const pBuffer) {
	/* Defensive programming in case the operation fails */
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	if ((pBuffer->position.writePos >= pBuffer->size))
	{
		return YAGO_TRUE;
	}
	else if ((pBuffer->flags & CHK_FUL) == CHK_FUL) { /* 0010.0000 */
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
*************************************************************
*/
yago_int bGetWritePos(BufferPointer const pBuffer) {
	/* Defensive programming in case the operation fails */
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
*************************************************************
*/
yago_int bGetSize(BufferPointer const pBuffer) {
	/* Defensive programming in case the operation fails */
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
*************************************************************
*/
yago_int bGetMode(BufferPointer const pBuffer) {
	/* Defensive programming in case the operation fails */
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
*************************************************************
*/
yago_int bGetMarkPos(BufferPointer const pBuffer) {
	/* Defensive programming in case the operation fails */
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
*************************************************************
*/
yago_bol bSetMark(BufferPointer const pBuffer, yago_int mark) {
	/* Defensive programming in case the operation fails */
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	/* Adjust the mark */
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
*************************************************************
*/
yago_int bPrint(BufferPointer const pBuffer) {
	yago_int size = 1;
	yago_chr c;
	/* Defensive programming in case the operation fails */
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	c = bGetChar(pBuffer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (c>0) {
		/* TO_DO: Adjust size */
		printf("%c", c);
		c = bGetChar(pBuffer);
		pBuffer->flags = pBuffer->flags & CHK_EOB;
		size++;
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
*************************************************************
*/
yago_int bLoad(BufferPointer const pBuffer, FILE* const fi) {
	yago_int size = 1;
	yago_chr c;
	/* Defensive programming in case the operation fails */
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
	/* Defensive programming in case the operation fails */
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
	/* Defensive programming in case the operation fails */
	if (pBuffer == NULL) {
		return BUFFER_ERROR;
	}
	/* TO_DO: Adjust EOB flag */
	if (pBuffer->position.readPos == pBuffer->position.writePos) { /* Either size = 0 or we have reached end of buffer (full or not) */
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
	/* Defensive programming in case the operation fails */
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
	/* Defensive programming in case the operation fails */
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
	/* Defensive programming in case the operation fails */
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
	/* Defensive programming in case the operation fails */
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
	/* Defensive programming in case the operation fails */
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
*************************************************************
*/
yago_chr* bGetContent(BufferPointer const pBuffer, yago_int pos) {
	/* Defensive programming in case the operation fails */
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
*************************************************************
*/
#define FLAGS_
#undef FLAGS_
#ifndef FLAGS_
yago_flg bGetFlags(BufferPointer const pBuffer) {
	return pBuffer->flags;
}
#else
#define bGetFlags(pBuffer) ((pBuffer)?(pBuffer->flags):(RT_FAIL_1))
#endif
