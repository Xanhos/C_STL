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
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef DLL_EXPORTS
#define LIBSTD_API __declspec(dllexport)
#else
#define LIBSTD_API __declspec(dllimport)
#endif



#define STD_CONVERT(type,...)\
	(const void*)&(type)__VA_ARGS__

#define STD_VECTOR_CREATE(type, size, ...) \
    stdVector_Create(sizeof(type), size, __VA_ARGS__)

#define STD_VECTOR_PUSHBACK(vec,type, ...)\
	vec->push_back(&vec, (const void*)&(type)__VA_ARGS__)

#define STD_VECTOR_GETDATA(vec,type,index) ((type*)vec->getData(vec, index))

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
	/// \brief Allocate a new memory size to the vector 
	///
	/// \param unsigned int New memory size
	/// \param stdVector* The vector you are using
	////////////////////////////////////////////////////////////
	void (*reserve)(stdVector**, unsigned int);
	////////////////////////////////////////////////////////////
	/// \brief Free the unused memory of the vector.
	///
	/// \param stdVector* The vector you are using
	////////////////////////////////////////////////////////////
	void (*shrink_to_fit)(stdVector**);

	////////////////////////////////////////////////////////////
	/// \brief Return the actual memory size of the vector
	///
	/// \param stdVector* The vector you are using
	////////////////////////////////////////////////////////////
	int (*capacity)(stdVector*);
};

stdVector LIBSTD_API* stdVector_Create(size_t type, unsigned int size, ...);
