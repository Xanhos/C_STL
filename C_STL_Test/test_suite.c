/*
 * Suite de tests complète pour C_STL
 * Compile avec RUN_FULL_SUITE=1 dans main.c pour l'exécuter.
 */
#include "List.h"
#include "Vector.h"
#include "Pool.h"
#include "stlString.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static unsigned int g_tests_run;
static unsigned int g_tests_ok;

#define TEST_ASSERT(cond, msg) do { \
	if (!(cond)) { printf("  FAIL: %s\n", (msg)); g_tests_run++; return; } \
} while(0)

#define TEST_END() do { g_tests_run++; g_tests_ok++; } while(0)

/* ---------- List ---------- */
static void Suite_List_CreateEmpty(void)
{
	stdList* L = stdList_Create(sizeof(int), 0);
	TEST_ASSERT(L != NULL, "List create empty");
	TEST_ASSERT(L->size(L) == 0, "List size 0");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_CreateWithElements(void)
{
	stdList* L = stdList_Create(sizeof(int), 3, STD_CONVERT(int, 10), STD_CONVERT(int, 20), STD_CONVERT(int, 30));
	TEST_ASSERT(L != NULL && L->size(L) == 3, "List create 3 elements");
	TEST_ASSERT(*(int*)L->getData(L, 0) == 10, "List getData 0");
	TEST_ASSERT(*(int*)L->getData(L, 1) == 20, "List getData 1");
	TEST_ASSERT(*(int*)L->getData(L, 2) == 30, "List getData 2");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_PushBack(void)
{
	stdList* L = stdList_Create(sizeof(int), 0);
	for (int i = 0; i < 20; i++)
		L->push_back(L, STD_CONVERT(int, i));
	TEST_ASSERT(L->size(L) == 20, "List push_back 20");
	for (int i = 0; i < 20; i++)
		TEST_ASSERT(*(int*)L->getData(L, i) == i, "List push_back value");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_GetDataEmpty(void)
{
	stdList* L = stdList_Create(sizeof(int), 0);
	void* p = L->getData(L, 0);
	TEST_ASSERT(p == NULL, "List getData empty -> NULL");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_EraseFirst(void)
{
	stdList* L = stdList_Create(sizeof(int), 4, STD_CONVERT(int, 1), STD_CONVERT(int, 2), STD_CONVERT(int, 3), STD_CONVERT(int, 4));
	L->erase(L, 0);
	TEST_ASSERT(L->size(L) == 3, "List erase first size");
	TEST_ASSERT(*(int*)L->getData(L, 0) == 2, "List erase first [0]");
	TEST_ASSERT(*(int*)L->getData(L, 2) == 4, "List erase first [2]");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_EraseLast(void)
{
	stdList* L = stdList_Create(sizeof(int), 4, STD_CONVERT(int, 1), STD_CONVERT(int, 2), STD_CONVERT(int, 3), STD_CONVERT(int, 4));
	L->erase(L, 3);
	TEST_ASSERT(L->size(L) == 3, "List erase last size");
	TEST_ASSERT(*(int*)L->getData(L, 2) == 3, "List erase last [2]");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_EraseMiddle(void)
{
	stdList* L = stdList_Create(sizeof(int), 5, STD_CONVERT(int, 0), STD_CONVERT(int, 1), STD_CONVERT(int, 2), STD_CONVERT(int, 3), STD_CONVERT(int, 4));
	L->erase(L, 2);
	TEST_ASSERT(L->size(L) == 4, "List erase middle size");
	TEST_ASSERT(*(int*)L->getData(L, 0) == 0 && *(int*)L->getData(L, 1) == 1, "List erase middle left");
	TEST_ASSERT(*(int*)L->getData(L, 2) == 3 && *(int*)L->getData(L, 3) == 4, "List erase middle right");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_Clear(void)
{
	stdList* L = stdList_Create(sizeof(int), 5, STD_CONVERT(int, 0), STD_CONVERT(int, 1), STD_CONVERT(int, 2), STD_CONVERT(int, 3), STD_CONVERT(int, 4));
	L->clear(L);
	TEST_ASSERT(L->size(L) == 0, "List clear size 0");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_ClearEmpty(void)
{
	stdList* L = stdList_Create(sizeof(int), 0);
	L->clear(L);
	TEST_ASSERT(L->size(L) == 0, "List clear empty");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_EraseAllFromFront(void)
{
	stdList* L = stdList_Create(sizeof(int), 3, STD_CONVERT(int, 1), STD_CONVERT(int, 2), STD_CONVERT(int, 3));
	L->erase(L, 0);
	L->erase(L, 0);
	L->erase(L, 0);
	TEST_ASSERT(L->size(L) == 0, "List erase all from front");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_EraseAllFromBack(void)
{
	stdList* L = stdList_Create(sizeof(int), 3, STD_CONVERT(int, 1), STD_CONVERT(int, 2), STD_CONVERT(int, 3));
	L->erase(L, 2);
	L->erase(L, 1);
	L->erase(L, 0);
	TEST_ASSERT(L->size(L) == 0, "List erase all from back");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_OneElementErase(void)
{
	stdList* L = stdList_Create(sizeof(int), 1, STD_CONVERT(int, 42));
	L->erase(L, 0);
	TEST_ASSERT(L->size(L) == 0, "List one element erase");
	L->destroy(&L);
	TEST_END();
}

static void Suite_List_GetFirstLink(void)
{
	stdList* L = stdList_Create(sizeof(int), 2, STD_CONVERT(int, 1), STD_CONVERT(int, 2));
	Link* first = L->get_first_link(L);
	TEST_ASSERT(first != NULL && *(int*)first->data == 1, "List get_first_link");
	L->destroy(&L);
	TEST_END();
}

/* ---------- Vector ---------- */
static void Suite_Vector_CreateEmpty(void)
{
	stdVector* V = STD_VECTOR_CREATE_EMPTY(int);
	TEST_ASSERT(V != NULL, "Vector create empty");
	TEST_ASSERT(V->size(V) == 0, "Vector size 0");
	V->destroy(&V);
	TEST_END();
}

static void Suite_Vector_PushBack(void)
{
	stdVector* V = STD_VECTOR_CREATE_EMPTY(int);
	for (int i = 0; i < 50; i++)
		V->push_back(V, STD_CONVERT(int, i));
	TEST_ASSERT(V->size(V) == 50, "Vector push_back 50");
	for (int i = 0; i < 50; i++)
		TEST_ASSERT(*(int*)V->getData(V, i) == i, "Vector getData");
	V->destroy(&V);
	TEST_END();
}

static void Suite_Vector_EraseFirst(void)
{
	stdVector* V = STD_VECTOR_CREATE_EMPTY(int);
	for (int i = 0; i < 5; i++)
		V->push_back(V, STD_CONVERT(int, i));
	V->erase(V, 0);
	TEST_ASSERT(V->size(V) == 4, "Vector erase first size");
	TEST_ASSERT(*(int*)V->getData(V, 0) == 1, "Vector erase first [0]");
	V->destroy(&V);
	TEST_END();
}

static void Suite_Vector_EraseLast(void)
{
	stdVector* V = STD_VECTOR_CREATE_EMPTY(int);
	for (int i = 0; i < 5; i++)
		V->push_back(V, STD_CONVERT(int, i));
	V->erase(V, 4);
	TEST_ASSERT(V->size(V) == 4, "Vector erase last size");
	TEST_ASSERT(*(int*)V->getData(V, 3) == 3, "Vector erase last [3]");
	V->destroy(&V);
	TEST_END();
}

static void Suite_Vector_EraseMiddle(void)
{
	stdVector* V = STD_VECTOR_CREATE_EMPTY(int);
	for (int i = 0; i < 5; i++)
		V->push_back(V, STD_CONVERT(int, i));
	V->erase(V, 2);
	TEST_ASSERT(V->size(V) == 4, "Vector erase middle size");
	TEST_ASSERT(*(int*)V->getData(V, 2) == 3, "Vector erase middle [2]");
	V->destroy(&V);
	TEST_END();
}

static void Suite_Vector_Clear(void)
{
	stdVector* V = STD_VECTOR_CREATE_EMPTY(int);
	for (int i = 0; i < 10; i++)
		V->push_back(V, STD_CONVERT(int, i));
	V->clear(V);
	TEST_ASSERT(V->size(V) == 0, "Vector clear size 0");
	V->destroy(&V);
	TEST_END();
}

static void Suite_Vector_Reserve(void)
{
	stdVector* V = STD_VECTOR_CREATE_EMPTY(int);
	V->reserve(V, 100);
	TEST_ASSERT(V->capacity(V) >= 100, "Vector reserve capacity");
	for (int i = 0; i < 10; i++)
		V->push_back(V, STD_CONVERT(int, i));
	TEST_ASSERT(V->size(V) == 10, "Vector after reserve push_back");
	V->destroy(&V);
	TEST_END();
}

static void Suite_Vector_ShrinkToFit(void)
{
	stdVector* V = STD_VECTOR_CREATE_EMPTY(int);
	for (int i = 0; i < 8; i++)
		V->push_back(V, STD_CONVERT(int, i));
	V->shrink_to_fit(V);
	TEST_ASSERT(V->capacity(V) == 8, "Vector shrink_to_fit capacity");
	TEST_ASSERT(V->size(V) == 8, "Vector shrink_to_fit size");
	for (int i = 0; i < 8; i++)
		TEST_ASSERT(*(int*)V->getData(V, i) == i, "Vector shrink_to_fit data");
	V->destroy(&V);
	TEST_END();
}

static void Suite_Vector_ShrinkToFitEmpty(void)
{
	stdVector* V = STD_VECTOR_CREATE_EMPTY(int);
	V->shrink_to_fit(V);
	TEST_ASSERT(V->size(V) == 0, "Vector shrink_to_fit empty size");
	V->destroy(&V);
	TEST_END();
}

static void Suite_Vector_CreateWithElements(void)
{
	stdVector* V = stdVector_Create(sizeof(int), 3, STD_CONVERT(int, 7), STD_CONVERT(int, 8), STD_CONVERT(int, 9));
	TEST_ASSERT(V != NULL && V->size(V) == 3, "Vector create with 3");
	TEST_ASSERT(*(int*)V->getData(V, 0) == 7 && *(int*)V->getData(V, 2) == 9, "Vector create values");
	V->destroy(&V);
	TEST_END();
}

static void Suite_Vector_MultipleErase(void)
{
	stdVector* V = STD_VECTOR_CREATE_EMPTY(int);
	for (int i = 0; i < 8; i++)
		V->push_back(V, STD_CONVERT(int, i));
	V->erase(V, 3);
	V->erase(V, 4);
	TEST_ASSERT(V->size(V) == 6, "Vector multiple erase size");
	TEST_ASSERT(*(int*)V->getData(V, 3) == 4 && *(int*)V->getData(V, 4) == 6, "Vector multiple erase values");
	V->destroy(&V);
	TEST_END();
}

static void Suite_Vector_OneElementErase(void)
{
	stdVector* V = STD_VECTOR_CREATE_EMPTY(int);
	V->push_back(V, STD_CONVERT(int, 1));
	V->erase(V, 0);
	TEST_ASSERT(V->size(V) == 0, "Vector one element erase");
	V->destroy(&V);
	TEST_END();
}

/* ---------- Pool ---------- */
static void Suite_Pool_CreateEmpty(void)
{
	stdPool* P = stdPool_Create(sizeof(int), 0);
	TEST_ASSERT(P != NULL, "Pool create empty");
	TEST_ASSERT(P->size(P) == 0, "Pool size 0");
	P->destroy(&P);
	TEST_END();
}

static void Suite_Pool_CreateVariadic(void)
{
	stdPool* P = stdPool_Create(sizeof(int), 3, STD_CONVERT(int, 11), STD_CONVERT(int, 22), STD_CONVERT(int, 33));
	TEST_ASSERT(P != NULL && P->size(P) == 3, "Pool create variadic");
	TEST_ASSERT(*STD_GETDATA(P, int, 0) == 11 && *STD_GETDATA(P, int, 2) == 33, "Pool variadic values");
	P->destroy(&P);
	TEST_END();
}

static void Suite_Pool_PushBack(void)
{
	stdPool* P = stdPool_Create(sizeof(int), 0);
	for (int i = 0; i < 15; i++)
		P->push_back(P, STD_CONVERT(int, i));
	TEST_ASSERT(P->size(P) == 15, "Pool push_back 15");
	for (size_t i = 0; i < P->size(P); i++)
		TEST_ASSERT(*STD_GETDATA(P, int, i) == (int)i, "Pool push_back values");
	P->destroy(&P);
	TEST_END();
}

static void Suite_Pool_EraseOne(void)
{
	stdPool* P = stdPool_Create(sizeof(int), 0);
	for (int i = 0; i < 5; i++)
		P->push_back(P, STD_CONVERT(int, i));
	P->erase(P, 1);
	TEST_ASSERT(P->size(P) == 4, "Pool erase size");
	TEST_ASSERT(*STD_GETDATA(P, int, 0) == 0, "Pool after erase [0]");
	TEST_ASSERT(*STD_GETDATA(P, int, 1) == 2, "Pool after erase [1]");
	TEST_ASSERT(*STD_GETDATA(P, int, 3) == 4, "Pool after erase [3]");
	P->destroy(&P);
	TEST_END();
}

static void Suite_Pool_EraseMultiple(void)
{
	stdPool* P = stdPool_Create(sizeof(int), 0);
	for (int i = 0; i < 6; i++)
		P->push_back(P, STD_CONVERT(int, i));
	P->erase(P, 1);
	P->erase(P, 2);
	TEST_ASSERT(P->size(P) == 4, "Pool erase multiple size");
	TEST_ASSERT(*STD_GETDATA(P, int, 0) == 0 && *STD_GETDATA(P, int, 1) == 2, "Pool erase multiple [0],[1]");
	TEST_ASSERT(*STD_GETDATA(P, int, 2) == 4 && *STD_GETDATA(P, int, 3) == 5, "Pool erase multiple [2],[3]");
	P->destroy(&P);
	TEST_END();
}

static void Suite_Pool_ReuseAfterErase(void)
{
	stdPool* P = stdPool_Create(sizeof(int), 0);
	for (int i = 0; i < 3; i++)
		P->push_back(P, STD_CONVERT(int, i));
	P->erase(P, 1);
	P->push_back(P, STD_CONVERT(int, 99));
	TEST_ASSERT(P->size(P) == 3, "Pool reuse size");
	TEST_ASSERT(*STD_GETDATA(P, int, 0) == 0 && *STD_GETDATA(P, int, 1) == 99 && *STD_GETDATA(P, int, 2) == 2, "Pool reuse values");
	P->destroy(&P);
	TEST_END();
}

static void Suite_Pool_Clear(void)
{
	stdPool* P = stdPool_Create(sizeof(int), 0);
	for (int i = 0; i < 5; i++)
		P->push_back(P, STD_CONVERT(int, i));
	P->clear(P);
	TEST_ASSERT(P->size(P) == 0, "Pool clear size 0");
	P->destroy(&P);
	TEST_END();
}

static void Suite_Pool_EraseFirst(void)
{
	stdPool* P = stdPool_Create(sizeof(int), 0);
	for (int i = 0; i < 4; i++)
		P->push_back(P, STD_CONVERT(int, i));
	P->erase(P, 0);
	TEST_ASSERT(P->size(P) == 3 && *STD_GETDATA(P, int, 0) == 1 && *STD_GETDATA(P, int, 2) == 3, "Pool erase first");
	P->destroy(&P);
	TEST_END();
}

static void Suite_Pool_EraseLast(void)
{
	stdPool* P = stdPool_Create(sizeof(int), 0);
	for (int i = 0; i < 4; i++)
		P->push_back(P, STD_CONVERT(int, i));
	P->erase(P, 3);
	TEST_ASSERT(P->size(P) == 3 && *STD_GETDATA(P, int, 2) == 2, "Pool erase last");
	P->destroy(&P);
	TEST_END();
}

/* ---------- String ---------- */
static void Suite_String_Create(void)
{
	stdString* S = stdStringCreate("hello");
	TEST_ASSERT(S != NULL, "String create");
	TEST_ASSERT(S->size(S) == 5, "String size");
	TEST_ASSERT(strcmp(S->getData(S), "hello") == 0, "String getData");
	S->destroy(&S);
	TEST_END();
}

static void Suite_String_Append(void)
{
	stdString* S = stdStringCreate("ab");
	S->append(S, "cd");
	TEST_ASSERT(S->size(S) == 4, "String append size");
	TEST_ASSERT(strcmp(S->getData(S), "abcd") == 0, "String append content");
	S->destroy(&S);
	TEST_END();
}

static void Suite_String_InsertStart(void)
{
	stdString* S = stdStringCreate("world");
	S->insert(S, "hello ", 0);
	TEST_ASSERT(strcmp(S->getData(S), "hello world") == 0, "String insert start");
	S->destroy(&S);
	TEST_END();
}

static void Suite_String_InsertMiddle(void)
{
	stdString* S = stdStringCreate("helo");
	S->insert(S, "l", 3);
	TEST_ASSERT(strcmp(S->getData(S), "hello") == 0, "String insert middle");
	S->destroy(&S);
	TEST_END();
}

static void Suite_String_InsertOOB(void)
{
	stdString* S = stdStringCreate("hi");
	S->insert(S, "!", 10);
	TEST_ASSERT(S->size(S) == 3, "String insert OOB size");
	TEST_ASSERT(strcmp(S->getData(S), "hi!") == 0, "String insert OOB clamped");
	S->destroy(&S);
	TEST_END();
}

static void Suite_String_Remove(void)
{
	stdString* S = stdStringCreate("hello");
	S->remove(S, 1, 2);
	TEST_ASSERT(strcmp(S->getData(S), "hlo") == 0, "String remove middle");
	S->destroy(&S);
	TEST_END();
}

static void Suite_String_RemoveOOB(void)
{
	stdString* S = stdStringCreate("hello");
	S->remove(S, 0, 10);
	TEST_ASSERT(S->size(S) == 0, "String remove OOB size");
	S->destroy(&S);
	TEST_END();
}

static void Suite_String_Replace(void)
{
	stdString* S = stdStringCreate("old");
	S->replace(S, "new");
	TEST_ASSERT(strcmp(S->getData(S), "new") == 0, "String replace");
	S->destroy(&S);
	TEST_END();
}

static void Suite_String_IntToString(void)
{
	CleanUpTempMemory();
	char* s = IntToString(42);
	TEST_ASSERT(s != NULL && strcmp(s, "42") == 0, "IntToString");
	CleanUpTempMemory();
	TEST_END();
}

static void Suite_String_FloatToString(void)
{
	CleanUpTempMemory();
	char* s = FloatToString(3.14f, 2);
	TEST_ASSERT(s != NULL && strstr(s, "3.14") != NULL, "FloatToString");
	CleanUpTempMemory();
	TEST_END();
}

static void Suite_String_CharToString(void)
{
	CleanUpTempMemory();
	char* s = CharToString('A');
	TEST_ASSERT(s != NULL && s[0] == 'A' && s[1] == '\0', "CharToString");
	CleanUpTempMemory();
	TEST_END();
}

static void Suite_String_EmptyCreate(void)
{
	stdString* S = stdStringCreate("");
	TEST_ASSERT(S != NULL && S->size(S) == 0, "String empty create");
	S->destroy(&S);
	TEST_END();
}

static void Suite_String_LongToString(void)
{
	CleanUpTempMemory();
	char* s = LongToString(12345678L);
	TEST_ASSERT(s != NULL && strstr(s, "12345678") != NULL, "LongToString");
	CleanUpTempMemory();
	TEST_END();
}

static void Suite_String_AppendMultiple(void)
{
	stdString* S = stdStringCreate("a");
	S->append(S, "b");
	S->append(S, "c");
	TEST_ASSERT(strcmp(S->getData(S), "abc") == 0, "String append multiple");
	S->destroy(&S);
	TEST_END();
}

static void Suite_String_RemoveAll(void)
{
	stdString* S = stdStringCreate("xyz");
	S->remove(S, 0, 3);
	TEST_ASSERT(S->size(S) == 0 && S->getData(S)[0] == '\0', "String remove all");
	S->destroy(&S);
	TEST_END();
}

/* ---------- Runner ---------- */
void RunFullTestSuite(void)
{
	g_tests_run = 0;
	g_tests_ok = 0;

	printf("=== Suite List ===\n");
	Suite_List_CreateEmpty();
	Suite_List_CreateWithElements();
	Suite_List_PushBack();
	Suite_List_GetDataEmpty();
	Suite_List_EraseFirst();
	Suite_List_EraseLast();
	Suite_List_EraseMiddle();
	Suite_List_Clear();
	Suite_List_ClearEmpty();
	Suite_List_EraseAllFromFront();
	Suite_List_EraseAllFromBack();
	Suite_List_OneElementErase();
	Suite_List_GetFirstLink();

	printf("=== Suite Vector ===\n");
	Suite_Vector_CreateEmpty();
	Suite_Vector_PushBack();
	Suite_Vector_EraseFirst();
	Suite_Vector_EraseLast();
	Suite_Vector_EraseMiddle();
	Suite_Vector_Clear();
	Suite_Vector_Reserve();
	Suite_Vector_ShrinkToFit();
	Suite_Vector_ShrinkToFitEmpty();
	Suite_Vector_CreateWithElements();
	Suite_Vector_MultipleErase();
	Suite_Vector_OneElementErase();

	printf("=== Suite Pool ===\n");
	Suite_Pool_CreateEmpty();
	Suite_Pool_CreateVariadic();
	Suite_Pool_PushBack();
	Suite_Pool_EraseOne();
	Suite_Pool_EraseMultiple();
	Suite_Pool_ReuseAfterErase();
	Suite_Pool_Clear();
	Suite_Pool_EraseFirst();
	Suite_Pool_EraseLast();

	printf("=== Suite String ===\n");
	Suite_String_Create();
	Suite_String_Append();
	Suite_String_InsertStart();
	Suite_String_InsertMiddle();
	Suite_String_InsertOOB();
	Suite_String_Remove();
	Suite_String_RemoveOOB();
	Suite_String_Replace();
	Suite_String_IntToString();
	Suite_String_FloatToString();
	Suite_String_CharToString();
	Suite_String_EmptyCreate();
	Suite_String_LongToString();
	Suite_String_AppendMultiple();
	Suite_String_RemoveAll();

	printf("\n=== Resultat: %u / %u tests reussis ===\n", g_tests_ok, g_tests_run);
	if (g_tests_ok != g_tests_run)
	{
		printf("ECHEC: %u test(s) en echec.\n", g_tests_run - g_tests_ok);
		exit(1);
	}
}
