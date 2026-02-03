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


#ifndef POOL_H_
#define POOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Export.h"

typedef struct Pool Pool;
typedef struct stdPool stdPool;

struct LIBSTD_API stdPool
{
	////////////////////////////////////////////////////////////
	/// \brief Contains all the data of the pool. DO NOT USE IT DIRECTLY.
	////////////////////////////////////////////////////////////
	Pool* _Data;

	////////////////////////////////////////////////////////////
	/// \brief Push a new element into an already allocated slot or at the end of the pool.
	///
	/// \param stdPool* The pool you are using.
	/// \param void* The element to push into the pool.
	////////////////////////////////////////////////////////////
	void (*push_back)(stdPool*, void*);

	////////////////////////////////////////////////////////////
	/// \brief Delete the element at the specified index.
	///
	/// \param stdPool* The pool you are using.
	/// \param unsigned int The index of the element to delete.
	////////////////////////////////////////////////////////////
	void (*erase)(stdPool*, unsigned int);

	////////////////////////////////////////////////////////////
	/// \brief Retrieve the data at the specified index.
	///        The return value must be cast to the desired type
	///        (e.g., `(int)pool->getData(&pool, 0)` if the pool stores integers).
	///
	/// \param stdPool* The pool you are using.
	/// \param unsigned int The index of the element to retrieve.
	/// \return A pointer to the data at the specified index.
	////////////////////////////////////////////////////////////
	void* (*getData)(stdPool*, unsigned int);

	////////////////////////////////////////////////////////////
	/// \brief Get the number of elements currently in the pool.
	///
	/// \param stdPool* The pool you are using.
	/// \return The size of the pool as an `int`.
	////////////////////////////////////////////////////////////
	size_t(*size)(stdPool*);

	////////////////////////////////////////////////////////////
	/// \brief Clear all elements from the pool.
	///        This function does not free memory allocated outside the pool.
	///        Ensure all external memory is properly freed before calling this function.
	///
	/// \param stdPool* The pool you are using.
	////////////////////////////////////////////////////////////
	void (*clear)(stdPool*);

	////////////////////////////////////////////////////////////
	/// \brief Destroy the pool and release all associated resources.
	///        Use this function only when you no longer need the pool.
	///
	/// \param stdPool** The address of the pool to destroy (e.g., `&pool`).
	////////////////////////////////////////////////////////////
	void (*destroy)(stdPool**);
};

////////////////////////////////////////////////////////////
/// \brief Create a new pool.
///
/// \param size_t The size of the type stored in the pool.
/// \param unsigned int The initial size of the pool.
/// \param ... Additional arguments, if needed.
/// \return A pointer to the newly created `stdPool` structure.
////////////////////////////////////////////////////////////
stdPool LIBSTD_API* stdPool_Create(size_t type, unsigned int size, ...);

#endif // POOL_H_
