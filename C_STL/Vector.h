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


#define STD_VECTOR_CREATE(type, size, ...) \
    stdVector_Create(sizeof(type), size, __VA_ARGS__)

#define STD_VECTOR_CREATE_EMPTY(type) \
stdVector_Create(sizeof(type), 0)

#define STD_VECTOR_PUSHBACK(vec, type, ...) \
	vec->push_back(&vec, (const void*)&(type)__VA_ARGS__)

#define VEC_OFR(vec, index) \
	if (index >= vec->size(vec)) \
	{ \
		printf("Vector out of range! (index %d, vector max size %d)\n", index, vec->size(vec)); \
		abort(); \
	} \
	else if (index < 0) \
	{ \
		printf("Index cannot be less than 0!\n"); \
		abort(); \
	}

typedef struct Vector Vector;
typedef struct stdVector stdVector;

struct LIBSTD_API stdVector
{
	////////////////////////////////////////////////////////////
	/// \brief Contains all the data of the vector. DO NOT USE IT DIRECTLY.
	////////////////////////////////////////////////////////////
	Vector* _Data;

	////////////////////////////////////////////////////////////
	/// \brief Push a new element at the back of the vector.
	///
	/// \param stdVector* Pointer to the vector.
	/// \param void* The element to push.
	////////////////////////////////////////////////////////////
	void (*push_back)(stdVector*, void*);

	////////////////////////////////////////////////////////////
	/// \brief Delete the element at the specified index.
	///
	/// \param stdVector* Pointer to the vector.
	/// \param int Index of the element to delete.
	////////////////////////////////////////////////////////////
	void (*erase)(stdVector*, int);

	////////////////////////////////////////////////////////////
	/// \brief Return the number of elements in the vector.
	///
	/// \param stdVector* Pointer to the vector.
	/// \return int The size of the vector.
	////////////////////////////////////////////////////////////
	int (*size)(stdVector*);

	////////////////////////////////////////////////////////////
	/// \brief Retrieve the data at the specified index.
	///        The return value must be cast to the desired type
	///        (e.g., `(int)vector->getData(&vector, 0)` if the vector stores integers).
	///
	/// \param stdVector* Pointer to the vector.
	/// \param int Index of the element to retrieve.
	/// \return void* A pointer to the data at the specified index.
	////////////////////////////////////////////////////////////
	void* (*getData)(stdVector*, int);

	////////////////////////////////////////////////////////////
	/// \brief Clear all elements from the vector.
	///        This function does not free memory allocated outside the vector.
	///        Ensure all external memory is properly freed before calling this function.
	///
	/// \param stdVector* Pointer to the vector.
	////////////////////////////////////////////////////////////
	void (*clear)(stdVector*);

	////////////////////////////////////////////////////////////
	/// \brief Destroy the vector and release all associated resources.
	///        Use this function only when you no longer need the vector.
	///
	/// \param stdVector** Address of the pointer to the vector (e.g., `&vector`).
	////////////////////////////////////////////////////////////
	void (*destroy)(stdVector**);

	////////////////////////////////////////////////////////////
	/// \brief Reserve memory for a specified number of elements in the vector.
	///
	/// \param stdVector* Pointer to the vector.
	/// \param unsigned int Number of elements to reserve memory for.
	////////////////////////////////////////////////////////////
	void (*reserve)(stdVector*, unsigned int);

	////////////////////////////////////////////////////////////
	/// \brief Reduce the capacity of the vector to fit its current size.
	///
	/// \param stdVector* Pointer to the vector.
	////////////////////////////////////////////////////////////
	void (*shrink_to_fit)(stdVector*);

	////////////////////////////////////////////////////////////
	/// \brief Get the current capacity of the vector (the amount of memory reserved).
	///
	/// \param stdVector* Pointer to the vector.
	/// \return int The current capacity of the vector.
	////////////////////////////////////////////////////////////
	int (*capacity)(stdVector*);
};

////////////////////////////////////////////////////////////
/// \brief Create a new vector with the specified element size and initial capacity.
///
/// \param size_t Size of each element.
/// \param unsigned int Initial capacity of the vector.
/// \param ... Optional initial elements to populate the vector.
/// \return stdVector* A pointer to the newly created vector.
////////////////////////////////////////////////////////////
stdVector LIBSTD_API* stdVector_Create(size_t type, unsigned int size, ...);

#endif // VECTOR_H_
