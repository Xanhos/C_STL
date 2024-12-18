#include "List.h"
#include "Vector.h"
#include "Pool.h"

int main()
{
	printf("Pool\n");

	stdPool* pool = stdPool_Create(sizeof(int), 0);

	for (size_t i = 0; i < 6; i++)
	{
		pool->push_back(pool, STD_CONVERT(int,  i));
	}

	for (size_t i = 0; i < pool->size(pool); i++)
	{
		printf("%d\n", *STD_GETDATA(pool, int, i));
	}
	pool->destroy(&pool);



	printf("List\n");

	stdList* list = STD_LIST_CREATE(int, 0);

	for (int i = 0; i < 10; i++)
	{
		list->push_back(list, STD_CONVERT(int, i));
	}

	for (int i = 0; i < list->size(list); i++)
		printf("%d\n", *STD_GETDATA(list, int, i));

	printf("\nVector\n");
	stdVector* vec = STD_VECTOR_CREATE(int, 0);
	vec->reserve(vec, 10);
	for (int i = 0; i < 10; i++)
	{
		vec->push_back(vec, STD_CONVERT(int, i));
	}

	for (int i = 0; i < vec->size(vec); i++)
		printf("%d\n", *STD_GETDATA(vec, int, i));
}
