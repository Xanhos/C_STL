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

int main()
{
	stdString* str = NULL;
	int i = 0;
	while (1)
	{
		str = stdStringCreate("");
		char* t = AddChar("5", "6");
		stdStringAppend(str, IntToString(i));
		stdStringPrint(str);
		stdStringDestroy(&str);
		i++;
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
