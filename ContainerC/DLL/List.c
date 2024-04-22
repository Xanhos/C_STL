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
#include "List.h"
#include <stdarg.h>

typedef struct Link Link;
struct Link
{
	void* data;
	Link* pNext;
	int id;
};

struct List
{
	Link* listBegin;
	unsigned int size;
	size_t elementSize;
};

void deleteLink(Link** listBegin, Link* element);
void AddElement(Link** listBegin, Link* element);
int stdList_GetSize(stdList* listBegin);
void stdList_Add(stdList** listBegin, void* element);
void* stdList_GetData(stdList* listBegin, unsigned int index);
void stdList_Erase(stdList** listBegin, unsigned int index);
void stdList_Clear(stdList** listBegin);
void stdList_Destroy(stdList** listBegin);




stdList* stdList_Create(size_t elementSize, int size, ...)
{
	va_list params;
	va_start(params, size);
	stdList* list = (stdList*)calloc( 1, sizeof(stdList));
	assert(list != NULL);
	list->_Data = (List*)calloc(1, sizeof(List));
	assert(list->_Data != NULL);
	list->_Data->size = size;
	list->_Data->elementSize = elementSize;
	list->_Data->listBegin = NULL;

	for (int i = 0; i < size; i++)
	{
		void* vaNext = va_arg(params, void*);
		Link* tmp = (Link*)calloc(1, sizeof(Link));
		assert(tmp != NULL);
		tmp->id = i;
		tmp->data = calloc(1,elementSize);
		char* tempData = (char*)tmp->data;
		assert(tempData != NULL);
		memcpy(tempData, vaNext, elementSize);
		AddElement(&list->_Data->listBegin, tmp);
	}

	list->size = &stdList_GetSize;
	list->push_back = &stdList_Add;
	list->getData = &stdList_GetData;
	list->erase = &stdList_Erase;
	list->destroy = &stdList_Destroy;
	list->clear = &stdList_Clear;

	va_end(params);

	return list;

}

int stdList_GetSize(stdList* listBegin)
{
	return listBegin->_Data->size;
}

void stdList_Add(stdList** listBegin, void* element)
{
	Link* tmp = (Link*)calloc(1, sizeof(Link));
	assert(tmp != NULL);
	tmp->data = calloc(1, (*listBegin)->_Data->elementSize);
	char* tempData = (char*)tmp->data;
	assert(tempData != NULL);
	memcpy(tempData, element, (*listBegin)->_Data->elementSize);
	tmp->id = (*listBegin)->_Data->size++;
	AddElement(&(*listBegin)->_Data->listBegin, tmp);
	
}


void* stdList_GetData(stdList* listBegin, unsigned int index)
{
	Link* tmpLink = listBegin->_Data->listBegin;
	while (tmpLink != NULL)
	{
		if (tmpLink->id == index)
			return ((char*)tmpLink->data);
		tmpLink = tmpLink->pNext;
	}

	return NULL;
}

void stdList_Erase(stdList** listBegin, unsigned int index)
{
	Link* tmpLink = (*listBegin)->_Data->listBegin;
	while (tmpLink != NULL)
	{
		if (tmpLink->id == index)
		{
			deleteLink(&(*listBegin)->_Data->listBegin, tmpLink);
			break;
		}
		tmpLink = tmpLink->pNext;
	}

	int newId = --(*listBegin)->_Data->size -1;
	tmpLink = (*listBegin)->_Data->listBegin;
	while (tmpLink != NULL)
	{
		if (tmpLink->id == newId)
			break;
		tmpLink->id = newId--;
		tmpLink = tmpLink->pNext;
	}

}

void stdList_Clear(stdList** listBegin)
{
	int size = (*listBegin)->_Data->size -1;
	for (int i = size; i >= 0; i--)
	{
		stdList_Erase(listBegin, i);
	}

}

void deleteLink(Link** listBegin, Link* element)
{
	if (element == (*listBegin))
	{
		Link* tmp = element->pNext;
		(*listBegin) = tmp;

		free(element->data);
		free(element);
	}
	else
	{
		Link* tmp = (*listBegin);
		while (tmp->pNext != element)
		{
			tmp = tmp->pNext;
		}
		tmp->pNext = element->pNext;


		free(element->data);
		free(element);
	}
}

void AddElement(Link** listBegin, Link* element)
{
	element->pNext = (*listBegin);
	(*listBegin) = element;
}

void stdList_Destroy(stdList** listBegin)
{
	stdList_Clear(listBegin);
	free((*listBegin)->_Data);
	free(*listBegin);
	*listBegin = NULL;
}