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
	size_t elementDeleted;
};


static void AddElement(stdPool* pool, void* element)
{
	stdVector* vector = pool->_Data->container;
	for (int i = 0; i < vector->size(vector); i++)
	{
		Data* it = ((Data*)vector->getData(vector, i));
		if (it->isFree)
		{
			memcpy_s(it->data, pool->_Data->elementSize, element, pool->_Data->elementSize);
			pool->_Data->elementDeleted--;
			return;
		}
	};
	Data tmp = {
		.data = calloc(1, pool->_Data->elementSize),
		.isFree = false
	};
	memcpy_s(tmp.data, pool->_Data->elementSize, element, pool->_Data->elementSize);

	vector->push_back(vector, &tmp);
}

static void RemoveElement(stdPool* pool, unsigned int index)
{
	VEC_OFR(pool->_Data->container, index);

	for (int i = 0; i < pool->_Data->container->size(pool->_Data->container); i++)
	{
		Data* it = ((Data*)pool->_Data->container->getData(pool->_Data->container, i));
		if (i == index)
		{
			it->isFree = 1;
			pool->_Data->elementDeleted++;
			return;
		}
	};

}

static void* GetElement(stdPool* pool, unsigned int index)
{
	VEC_OFR(pool->_Data->container, index);

	int id = 0;


	for (int i = 0; i < pool->_Data->container->size(pool->_Data->container); i++)
	{
		Data* it = ((Data*)pool->_Data->container->getData(pool->_Data->container, i));
		if (id == index && !it->isFree)
		{
			return it->data;
		}
		if (!it->isFree)
		{
			id++;
		}
	};


	printf("Pool out of range !\n");
	abort();

}

static size_t GetSize(stdPool* pool)
{
	return pool->_Data->container->size(pool->_Data->container) - pool->_Data->elementDeleted;
}

static void Clear(stdPool* pool)
{
	pool->_Data->container->clear(pool->_Data->container);
}

static void Destroy(stdPool** pool)
{
	Pool* data = (*pool)->_Data;
	for (int i = 0; i < data->container->size(data->container); i++)
	{
		Data* it = ((Data*)data->container->getData(data->container, i));
		free(it->data);
	}


	data->container->destroy(&data->container);
	free(data);
	free(*pool);
	*pool = NULL;
}


stdPool* stdPool_Create(size_t type, unsigned int size, ...)
{
	stdPool* pool = (stdPool*)calloc(1, sizeof(stdPool));
	assert(pool);
	Pool* data = (Pool*)calloc(1, sizeof(Pool));
	assert(data);
	pool->_Data = data;

	data->elementSize = type;
	data->elementDeleted = 0;
	data->container = stdVector_Create(sizeof(Data), 0);
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
	pool->push_back = &AddElement;
	pool->getData = &GetElement;
	pool->size = &GetSize;
	pool->erase = &RemoveElement;
	pool->clear = &Clear;
	pool->destroy = &Destroy;
	va_end(params);
	return pool;
}