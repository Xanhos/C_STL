#include "Pool.h"
#include "Vector.h"

#include <stdarg.h>
#include <stdbool.h>

typedef struct
{
	void* data;
	bool isFree;
} Data;

struct Pool
{
	stdVector* container;
	size_t elementSize;

};

stdPool* stdPool_Create(size_t type, unsigned int size,...)
{
	stdPool* pool = (stdPool*)calloc(size, type);
	assert(pool);
	Pool* data = (Pool*)calloc(size, type);
	assert(data);
	pool->_Data = data;

	data->elementSize = type;
	data->container = stdVector_Create(sizeof(Data), size);
	va_list params;
	va_start(params, size);

	for (int i = 0; i < size; i++)
	{
		void* vaNext = va_arg(params, void*);
		Data tmpData = {
			.data = vaNext,
			.isFree = false
		};
		data->container->push_back(data->container, &tmpData);
	}

	va_end(params);
	return pool;
}

void AddElement(stdPool* pool, void* element)
{
	stdVector* vector = pool->_Data->container;
	FOR_EACH(vector, Data, i, it, 
		if (it->isFree)
		{
			memcpy_s(it->data, pool->_Data->elementSize, element, pool->_Data->elementSize);
			return;
		});
	Data tmp = {
		.data = element,
		.isFree = false
	};

	vector->push_back(&vector, &tmp);
}

void RemoveElement(stdPool* pool, unsigned int index)
{
	VEC_OFR(pool->_Data->container, index);

	FOR_EACH(pool->_Data->container, Data, i, it,
		if (i == index)
		{
			it->isFree = true;
			return;
		}
		);

}

void* GetElement(stdPool* pool, unsigned int index)
{
	VEC_OFR(pool->_Data->container, index);

	Data* it = STD_GETDATA(pool->_Data->container, Data, index);
	return it->data;
}