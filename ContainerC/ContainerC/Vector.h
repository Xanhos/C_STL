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
#ifndef VECTOR_H_
#define VECTOR_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "Export.h"

#define STD_CONVERT(type,...)\
	(const void*)&(type)__VA_ARGS__

#define STD_VECTOR_CREATE(type, size, ...) \
    stdVector_Create(sizeof(type), size, __VA_ARGS__)

#define STD_VECTOR_PUSHBACK(vec,type, ...)\
	vec->push_back(&vec, (const void*)&(type)__VA_ARGS__)

#define VEC_OFR(vec, index)\
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

typedef struct Vector Vector;
typedef struct stdVector stdVector;

struct stdVector
{
	////////////////////////////////////////////////////////////
	/// \brief Contain all the data of the vector, DO NOT USE IT AT ALL
	////////////////////////////////////////////////////////////
	Vector* _Data;
	////////////////////////////////////////////////////////////
	/// \brief Push a new element at the back of the vector
	///
	/// \param stdVector** Adress of the vector (example : &vector)
	/// \param void* Element to push
	////////////////////////////////////////////////////////////
	void (*push_back)(stdVector**, void*);
	////////////////////////////////////////////////////////////
	/// \brief Delete the element pointed to by the index
	///
	/// \param stdVector** Adress of the vector (example : &vector)
	/// \param int Index to delete
	////////////////////////////////////////////////////////////
	void (*erase)(stdVector**, int);
	////////////////////////////////////////////////////////////
	/// \brief Return the size of the vector
	///
	/// \param stdVector* The vector you are using
	////////////////////////////////////////////////////////////
	int (*size)(stdVector*);
	////////////////////////////////////////////////////////////
	/// \brief Return the data pointed to by the index. You need to cast the return value to the desired type (example: (int)vector->getData(&vector, 0) if the vector is storing int).
	///
	/// \param stdVector* The vector you are using
	/// \param int Index to retrieve.
	////////////////////////////////////////////////////////////
	void* (*getData)(stdVector*, int);
	////////////////////////////////////////////////////////////
	/// \brief Clear the vector. This function does not free memory allocated outside the vector function, so make sure all memory is freed properly before calling it.
	///
	/// \param stdVector** Address of the vector (example: &vector).
	////////////////////////////////////////////////////////////
	void (*clear)(stdVector**);
	////////////////////////////////////////////////////////////
	/// \brief Destroy the vector, use it ONLY when you don't need the vector anymore.
	///
	/// \param stdVector* The vector you are using
	////////////////////////////////////////////////////////////
	void (*destroy)(stdVector**);
	////////////////////////////////////////////////////////////
	/// \brief Reserves memory for a specified number of elements in the vector.
	///
	/// \param stdVector** Address of the vector (example: &vector).
	/// \param unsigned int Number of elements to reserve memory for.
	////////////////////////////////////////////////////////////
	void (*reserve)(stdVector**, unsigned int);

	////////////////////////////////////////////////////////////
	/// \brief Reduces the capacity of the vector to fit its size.
	///
	/// \param stdVector** Address of the vector (example: &vector).
	////////////////////////////////////////////////////////////
	void (*shrink_to_fit)(stdVector**);

	////////////////////////////////////////////////////////////
	/// \brief Retrieves the current capacity of the vector.
	///
	/// \param stdVector* Pointer to the vector.
	/// \return int The current capacity of the vector.
	////////////////////////////////////////////////////////////
	int (*capacity)(stdVector*);
};

stdVector* stdVector_Create(size_t type, unsigned int size, ...);

#endif VECTOR_H_
