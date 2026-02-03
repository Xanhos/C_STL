#include "List.h"
#include "Vector.h"
#include "Pool.h"
#include "stlString.h"
#include "test_suite.h"

#include <limits.h>

#define RUN_FULL_SUITE 1


#define TEST_LIST_EMPTY_GETDATA 1
#define TEST_LIST_ERASE_FIRST 1
#define TEST_LIST_ERASE_LAST 1
#define TEST_LIST_CLEAR 1

#define TEST_VECTOR_ERASE_LAST 1
#define TEST_VECTOR_RESERVE_HUGE 1
#define TEST_VECTOR_SHRINK_TO_FIT 1

#define TEST_POOL_VARIADIC_CREATE 1
#define TEST_POOL_ADD_AND_DESTROY 1
#define TEST_POOL_GET_AFTER_REMOVE 1

#define TEST_STRING_INSERT_OOB 1
#define TEST_STRING_REMOVE_OOB 1
#define TEST_STRING_FLOAT_FORMAT 1

static void Test_List_Empty_GetData(void)
{
	printf("[List] getData sur liste vide (attendu: crash si bug)\n");
	stdList* empty = stdList_Create(sizeof(int), 0);
	void* data = empty->getData(empty, 0);
	printf("getData(empty, 0) = %p\n", data);
	empty->destroy(&empty);
}

static void Test_List_Erase_First(void)
{
	printf("[List] erase premier element (attendu: crash si pBack NULL)\n");
	stdList* list = stdList_Create(sizeof(int), 3, STD_CONVERT(int, 1), STD_CONVERT(int, 2), STD_CONVERT(int, 3));
	list->erase(list, 0);
	list->destroy(&list);
}

static void Test_List_Erase_Last(void)
{
	printf("[List] erase dernier element (attendu: comportement correct)\n");
	stdList* list = stdList_Create(sizeof(int), 3, STD_CONVERT(int, 1), STD_CONVERT(int, 2), STD_CONVERT(int, 3));
	list->erase(list, 2);
	list->destroy(&list);
}

static void Test_List_Clear(void)
{
	printf("[List] clear sur liste non vide (attendu: size=0)\n");
	stdList* list = stdList_Create(sizeof(int), 5,
		STD_CONVERT(int, 0), STD_CONVERT(int, 1), STD_CONVERT(int, 2),
		STD_CONVERT(int, 3), STD_CONVERT(int, 4));
	list->clear(list);
	printf("size apres clear = %d\n", list->size(list));
	list->destroy(&list);
}

static void Test_Vector_Erase_Last(void)
{
	printf("[Vector] erase dernier element (attendu: pas d'OOB)\n");
	stdVector* vec = STD_VECTOR_CREATE_EMPTY(int);
	for (int i = 0; i < 5; i++)
		vec->push_back(vec, STD_CONVERT(int, i));
	vec->erase(vec, 4);
	printf("size apres erase = %d\n", vec->size(vec));
	vec->destroy(&vec);
}

static void Test_Vector_Reserve_Huge(void)
{
	printf("[Vector] reserve tres grande capacite (attendu: risque realloc NULL)\n");
	stdVector* vec = STD_VECTOR_CREATE_EMPTY(int);
	vec->reserve(vec, UINT_MAX / 2);
	vec->destroy(&vec);
}

static void Test_Vector_ShrinkToFit(void)
{
	printf("[Vector] shrink_to_fit sur vecteur non vide\n");
	stdVector* vec = STD_VECTOR_CREATE_EMPTY(int);
	for (int i = 0; i < 4; i++)
		vec->push_back(vec, STD_CONVERT(int, i));
	vec->shrink_to_fit(vec);
	vec->destroy(&vec);
}

static void Test_Pool_Variadic_Create(void)
{
	printf("[Pool] create variadique (attendu: pointeurs invalides si bug)\n");
	printf("  - avant stdPool_Create\n");
	stdPool* pool = stdPool_Create(sizeof(int), 3,
		STD_CONVERT(int, 10), STD_CONVERT(int, 20), STD_CONVERT(int, 30));
	printf("  - apres stdPool_Create\n");
	for (size_t i = 0; i < pool->size(pool); i++)
	{
		printf("  - getData index %zu\n", i);
		printf("%d\n", *STD_GETDATA(pool, int, i));
	}
	printf("  - avant destroy\n");
	pool->destroy(&pool);
	printf("  - apres destroy\n");
}

static void Test_Pool_Add_And_Destroy(void)
{
	printf("[Pool] push_back multiples + destroy (attendu: fuite si bug)\n");
	stdPool* pool = stdPool_Create(sizeof(int), 0);
	for (size_t i = 0; i < 10; i++)
		pool->push_back(pool, STD_CONVERT(int, i));
	pool->destroy(&pool);
}

static void Test_Pool_Get_After_Remove(void)
{
	printf("[Pool] getData apres suppression (attendu: possible incoherence)\n");
	stdPool* pool = stdPool_Create(sizeof(int), 0);
	for (size_t i = 0; i < 4; i++)
		pool->push_back(pool, STD_CONVERT(int, i));
	pool->erase(pool, 1);
	printf("getData index 1 = %d\n", *STD_GETDATA(pool, int, 1));
	pool->destroy(&pool);
}

static void Test_String_Insert_OOB(void)
{
	printf("[String] insert hors limites (attendu: OOB si bug)\n");
	stdString* str = stdStringCreate("hello");
	str->insert(str, "world", 10);
	str->destroy(&str);
}

static void Test_String_Remove_OOB(void)
{
	printf("[String] remove hors limites (attendu: OOB si bug)\n");
	stdString* str = stdStringCreate("hello");
	str->remove(str, 0, 10);
	str->destroy(&str);
}

static void Test_String_Float_Format(void)
{
	printf("[String] FloatToString format dynamique\n");
	char* result = FloatToString(3.14f, 100);
	printf("FloatToString = %s\n", result);
}

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("C_STL tests\n");

#if RUN_FULL_SUITE
	RunFullTestSuite();
	printf("Fin des tests (suite complete)\n");
	return 0;
#endif

#if TEST_LIST_EMPTY_GETDATA
	Test_List_Empty_GetData();
#endif
#if TEST_LIST_ERASE_FIRST
	Test_List_Erase_First();
#endif
#if TEST_LIST_ERASE_LAST
	Test_List_Erase_Last();
#endif
#if TEST_LIST_CLEAR
	Test_List_Clear();
#endif

#if TEST_VECTOR_ERASE_LAST
	Test_Vector_Erase_Last();
#endif
#if TEST_VECTOR_RESERVE_HUGE
	Test_Vector_Reserve_Huge();
#endif
#if TEST_VECTOR_SHRINK_TO_FIT
	Test_Vector_ShrinkToFit();
#endif

#if TEST_POOL_VARIADIC_CREATE
	Test_Pool_Variadic_Create();
#endif
#if TEST_POOL_ADD_AND_DESTROY
	Test_Pool_Add_And_Destroy();
#endif
#if TEST_POOL_GET_AFTER_REMOVE
	Test_Pool_Get_After_Remove();
#endif

#if TEST_STRING_INSERT_OOB
	Test_String_Insert_OOB();
#endif
#if TEST_STRING_REMOVE_OOB
	Test_String_Remove_OOB();
#endif
#if TEST_STRING_FLOAT_FORMAT
	Test_String_Float_Format();
#endif

	printf("Fin des tests\n");
	return 0;
}
