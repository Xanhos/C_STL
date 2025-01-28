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

#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Export.h"

#define STD_LIST_CREATE(type, size, ...) \
  stdList_Create(sizeof(type), size, __VA_ARGS__)

#define STD_CONVERT(type, ...) \
	(const void*)&(type)__VA_ARGS__

#define STD_LIST_PUSHBACK(list, type, ...) \
	list->push_back(&list, (const void*)&(type)__VA_ARGS__)

typedef struct List List;
typedef struct stdList stdList;

struct LIBSTD_API stdList
{
	////////////////////////////////////////////////////////////
	/// \brief Contains all the data of the list. DO NOT USE IT DIRECTLY.
	////////////////////////////////////////////////////////////
	List* _Data;

	////////////////////////////////////////////////////////////
	/// \brief Push a new element at the back of the list.
	///
	/// \param stdList* The list you are using.
	/// \param void* The element to push.
	////////////////////////////////////////////////////////////
	void (*push_back)(stdList*, void*);

	////////////////////////////////////////////////////////////
	/// \brief Delete the element at the specified index.
	///
	/// \param stdList* The list you are using.
	/// \param unsigned int The index of the element to delete.
	////////////////////////////////////////////////////////////
	void (*erase)(stdList*, unsigned int);

	////////////////////////////////////////////////////////////
	/// \brief Retrieve the data at the specified index.
	///        The return value must be cast to the desired type
	///        (e.g., `(int)list->getData(&list, 0)` if the list stores integers).
	///
	/// \param stdList* The list you are using.
	/// \param unsigned int The index of the element to retrieve.
	/// \return A pointer to the data at the specified index.
	////////////////////////////////////////////////////////////
	void* (*getData)(stdList*, unsigned int);

	////////////////////////////////////////////////////////////
	/// \brief Get the number of elements currently in the list.
	///
	/// \param stdList* The list you are using.
	/// \return The size of the list as an `int`.
	////////////////////////////////////////////////////////////
	int (*size)(stdList*);

	////////////////////////////////////////////////////////////
	/// \brief Clear all elements from the list.
	///        This function does not free memory allocated outside the list.
	///        Ensure all external memory is properly freed before calling this function.
	///
	/// \param stdList* The list you are using.
	////////////////////////////////////////////////////////////
	void (*clear)(stdList*);

	////////////////////////////////////////////////////////////
	/// \brief Destroy the list and release all associated resources.
	///        Use this function only when you no longer need the list.
	///
	/// \param stdList** The address of the list to destroy (e.g., `&list`).
	////////////////////////////////////////////////////////////
	void (*destroy)(stdList**);
};

////////////////////////////////////////////////////////////
/// \brief Create a new list.
///
/// \param size_t The size of the elements to store in the list.
/// \param int The initial size of the list.
/// \param ... Additional arguments, if needed.
/// \return A pointer to the newly created `stdList` structure.
////////////////////////////////////////////////////////////
stdList LIBSTD_API* stdList_Create(size_t elementSize, int size, ...);

#endif // LIST_H_
