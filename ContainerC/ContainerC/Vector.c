/*
    Author: GRALLAN Yann

    Description: Generic C container library

    Date: 2024/02/26

    MIT License

    Copyright (c) 2024 GRALLAN Yann


    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Vector.h"
#include <stdarg.h>
#include <stdbool.h>

#define VEC_OFR(vec,index)\
	if (index > vec->size(vec))\
	{\
		printf("Vector out of range ! (index %d, vector max size %d)\n", index, vec->size(vec));\
		abort();\
	}\
	else if (index < 0)\
	{\
		printf("Index cannot be under 0 !\n");\
		abort();\
	}\

#define INIT_VEC_SIZE 1

struct Vector
{
	void* type;
	int size;
	int memoryCapacity;
	size_t elementSize;
};


static void* stdVector_getData(stdVector* T, int index)
{
	VEC_OFR(T, index);

	return ((char*)T->_Data->type) + index * T->_Data->elementSize;
}

static int stdVector_getSize(stdVector* T)
{
	return T->_Data->size;
}

static void stdVector_Add(stdVector* T, void* element)
{
	if ((T->_Data->elementSize * T->_Data->size) < (T->_Data->elementSize * T->_Data->memoryCapacity))
	{	
		char* tempData = (char*)T->_Data->type;
		memcpy(tempData + T->_Data->size * T->_Data->elementSize, element, T->_Data->elementSize);
		T->_Data->size++;
	}
	else
	{
		T->_Data->memoryCapacity *= 2;

		void* temp = realloc(T->_Data->type, (T->_Data->memoryCapacity * T->_Data->elementSize));

		char* tempData = (char*)temp;

		assert(tempData != NULL);

		memcpy(tempData + T->_Data->size * T->_Data->elementSize, element, T->_Data->elementSize);

		T->_Data->size++;

		T->_Data->type = temp;

	}
}

static void stdVector_Remove(stdVector* T, int index)
{
	VEC_OFR(T, index);	

	char* tempData = (char*)T->_Data->type;

	int offset = T->_Data->size - index;

	for (int i = 0; i < offset; i++)
	{
		memcpy(tempData + (index + i)* T->_Data->elementSize, tempData + (index + i + 1) * T->_Data->elementSize, T->_Data->elementSize);
	}

	T->_Data->size--;
}


static void stdVector_Destructor(stdVector** T)
{
	free((*T)->_Data->type);
	free((*T)->_Data);
	free(*T);
	(*T) = NULL;
}

static void stdVector_Clear(stdVector* T)
{
	T->_Data->memoryCapacity = 1;
	void* temp = calloc(T->_Data->memoryCapacity, T->_Data->elementSize);

	free(T->_Data->type);
	T->_Data->type = temp;

	T->_Data->size = 0;
}




static void stdVector_Reserve(stdVector* T, unsigned int newCapacity)
{
	if(newCapacity > T->_Data->memoryCapacity)
	{
		void* temp = realloc(T->_Data->type, newCapacity * T->_Data->elementSize);

		T->_Data->memoryCapacity = newCapacity;

		T->_Data->type = temp;
	}
}

static void stdVector_ShrinkToFit(stdVector* T)
{
	T->_Data->memoryCapacity = T->_Data->size;

	
	void* temp = calloc(T->_Data->memoryCapacity, T->_Data->elementSize);

	char* newData = (char*)temp;
	char* oldData = (char*)T->_Data->type;


	for (int i = 0; i < T->_Data->size; i++)
	{		
		memcpy(newData + i * T->_Data->elementSize, oldData + i * T->_Data->elementSize, T->_Data->elementSize);	
	}

	assert(temp != NULL);

	free(T->_Data->type);
	T->_Data->type = temp;
}

static int stdVector_GetCapacity(stdVector* T)
{
	return T->_Data->memoryCapacity;
}

stdVector* stdVector_Create(size_t T, unsigned int size, ...)
{
	stdVector* vector = (stdVector*)calloc(1, sizeof(stdVector));

	assert(vector != NULL);

	vector->_Data = (Vector*)calloc(1, sizeof(Vector));


	assert(vector->_Data != NULL);

	vector->_Data->type = calloc(INIT_VEC_SIZE, T);

	vector->_Data->memoryCapacity = INIT_VEC_SIZE;

	vector->_Data->size = 0;

	vector->_Data->elementSize = T;


	va_list params;
	va_start(params, size);

	for (int i = 0; i < size; i++)
	{
		void* vaNext = va_arg(params, void*);
		stdVector_Add(vector, vaNext);
	}

	vector->erase = &stdVector_Remove;
	vector->getData = &stdVector_getData;
	vector->push_back = &stdVector_Add;
	vector->size = &stdVector_getSize;
	vector->clear = &stdVector_Clear;
	vector->destroy = &stdVector_Destructor;
	vector->reserve = &stdVector_Reserve;
	vector->shrink_to_fit = &stdVector_ShrinkToFit;
	vector->capacity = &stdVector_GetCapacity;
	va_end(params);
	return vector;
}