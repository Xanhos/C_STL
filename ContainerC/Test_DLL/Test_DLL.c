#include "List.h"
#include "Vector.h"


int main()
{
	printf("List\n");

	stdList* a = STD_LIST_CREATE(int, 0);

	for (int i = 0; i < 10; i++)
	{
		a->push_back(&a, STD_CONVERT(int, i));
	}

	for (int i = 0; i < a->size(a); i++)
		printf("%d\n", *STD_LIST_GETDATA(a, int, i));

	printf("\nVector\n");
	stdVector* vec = STD_VECTOR_CREATE(int, 0);
	vec->reserve(&vec, 10);
	for (int i = 0; i < 10; i++)
	{
		vec->push_back(&vec, STD_CONVERT(int, i));
	}

	for (int i = 0; i < vec->size(vec); i++)
		printf("%d\n", *STD_VECTOR_GETDATA(vec, int, i));
}
