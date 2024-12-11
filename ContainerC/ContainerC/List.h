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

#define STD_CONVERT(type,...)\
	(const void*)&(type)__VA_ARGS__

#define STD_LIST_PUSHBACK(list,type, ...)\
	list->push_back(&list, (const void*)&(type)__VA_ARGS__)


typedef struct List List;
typedef struct stdList stdList;

struct stdList
{
	////////////////////////////////////////////////////////////
	/// \brief Contains all the data of the list, DO NOT USE IT AT ALL
	////////////////////////////////////////////////////////////
	List* _Data;
	////////////////////////////////////////////////////////////
	/// \brief Push a new element at the back of the list
	///
	/// \param stdList** Adress of the list (example : &list)
	/// \param void* Element to push
	////////////////////////////////////////////////////////////
	void (*push_back)(stdList*, void*);
	////////////////////////////////////////////////////////////
	/// \brief Delete the element pointed to by the index
	///
	/// \param stdList** Adress of the list (example : &list)
	/// \param int Index to delete
	////////////////////////////////////////////////////////////
	void (*erase)(stdList*, unsigned int);
	////////////////////////////////////////////////////////////
	/// \brief Return the data pointed to by the index. You need to cast the return value to the desired type (example: (int)list->getData(&list, 0) if the list is storing int).
	///
	/// \param stdList* The list you are using
	/// \param int Index to retrieve.
	////////////////////////////////////////////////////////////
	void* (*getData)(stdList*, unsigned int);
	////////////////////////////////////////////////////////////
	/// \brief Return the size of the list
	///
	/// \param stdList* The list you are using
	////////////////////////////////////////////////////////////
	int (*size)(stdList*);
	////////////////////////////////////////////////////////////
	/// \brief Clear the list. This function does not free memory allocated outside the list function, so make sure all memory is freed properly before calling it.
	///
	/// \param stdList** Address of the list (example: &list).
	////////////////////////////////////////////////////////////
	void (*clear)(stdList*);
	////////////////////////////////////////////////////////////
	/// \brief Destroy the list, use it ONLY when you don't need the list anymore.
	///
	/// \param stdList* The list you are using
	////////////////////////////////////////////////////////////
	void (*destroy)(stdList**);
};

stdList* stdList_Create(size_t elementSize, int size, ...);

#endif LIST_H_