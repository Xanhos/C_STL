#ifndef POOL_H_
#define POOL_H_
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

#define STD_VECTOR_GETDATA(vec,type,index) ((type*)vec->getData(vec, index))

typedef struct Pool Pool;
typedef struct stdPool stdPool;

struct stdPool
{
	Pool* _Data;
};


stdPool* stdPool_Create(size_t type, unsigned int size, ...);
void AddElement(stdPool* pool, void* element);
void RemoveElement(stdPool* pool, unsigned int index);
void* GetElement(stdPool* pool, unsigned int index);
size_t GetSize(stdPool* pool);
#endif POOL_H_