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
#include "Vector.h"
#include "List.h"
#include <time.h>
#include "String.h"
#include "Pool.h"

int main()
{
	system("CLS");
	while(1)
	{
		//while (1)
		//{

		//	printf("List\n");
		//	stdList* list = STD_LIST_CREATE(int, 0);

		//	for (int i = 0; i < 2; i++)
		//	{
		//		list->push_back(list, STD_CONVERT(int, {i}));
		//	}

		//	int size = list->size(list) - 1;
		//	for (int i = size; i > -1; i--)
		//	{
		//		list->erase(list, i);
		//	}

		//	for (int i = 0; i < list->size(list); i++)
		//		printf("%d\n", *STD_GETDATA(list, int, i));

		//	list->destroy(&list);

		//}

		////while(1)
		//{

		//	printf("Vector\n");

		//	stdVector* vector = STD_VECTOR_CREATE(int, 3, STD_CONVERT(int, { 0 }), STD_CONVERT(int, { 1 }), STD_CONVERT(int, { 2 }));
		//	vector->push_back(vector, STD_CONVERT(int, { 4 }));
		//	vector->erase(vector, 2);
		//	for (int i = 0; i < vector->size(vector); i++)
		//	{
		//		printf("%d\n", *STD_GETDATA(vector, int, i));
		//	}
		//	vector->destroy(&vector);
		//}

		////while (1)
		//{

		//	stdString* string = stdStringCreate("String");
		//	string->append(string, " test");
		//	string->append(string, AddChar(" add ", IntToString(5)));
		//	string->append(string, " + ");
		//	string->append(string, AddChar(FloatToString(1.5f, 3), " = "));
		//	string->append(string, FloatToString(1.5f + 5, 2));
		//	stdStringPrint(string);

		//	string->destroy(&string);
		//}

		typedef struct
		{
			char test[44];
		}Test;

		//while (1)
		{
			printf("Pool\n");
			stdPool* pool = stdPool_Create(sizeof(Test*),0);
			
			Test* a = calloc(sizeof(Test), 1);
			pool->push_back(pool, &a);
			

			for (int i = 0; i < pool->size(pool); i++) {
				Test** it_ = ((Test**)pool->getData(pool, i));
				Test* it = *it_;				
				{
					free(it);
					pool->erase(pool, i);
					i--;
				}
			}


			Test* b = calloc(sizeof(Test), 1);
			pool->push_back(pool, &b);
			

			pool->destroy(&pool);
		}
		
	}
	
}
























//stdVector* vec = STD_VECTOR_CREATE(pos, 0);
//clock_t start_time, end_time;
//printf("Process with a vector of %d size\n\n", sizeTest);


//start_time = clock();
//vec->reserve(&vec, sizeTest * 2);
//end_time = clock();
//printf("Reserve time : %f\n\n", (float)(end_time - start_time) / CLOCKS_PER_SEC);


//start_time = clock();
//for (int i = 0; i < sizeTest; i++)
//{
//	STD_VECTOR_PUSHBACK(vec, pos, { i,i,i });
//}
//end_time = clock();
//printf("Pushback time : %f\n\n", (float)(end_time - start_time) / CLOCKS_PER_SEC);

//start_time = clock();
//vec->shrink_to_fit(&vec);
//end_time = clock();
//printf("Shrink time : %f\n\n", (float)(end_time - start_time) / CLOCKS_PER_SEC);

//start_time = clock();
//vec->clear(&vec);
//vec->destroy(&vec);
//end_time = clock();
//printf("Destroy time : %f\n\n", (float)(end_time - start_time) / CLOCKS_PER_SEC);
