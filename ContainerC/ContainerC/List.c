
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

#define MIN(a,b) ((a < b) ? a : b)

typedef struct Link Link;
struct Link
{
	void* data;
	Link* pNext;
	Link* pBack;
	int id;
};

struct List
{
	Link* listBegin;
	Link* endList;
	size_t elementSize;
	unsigned int size;
};

typedef enum ITDIRECTION ITDIRECTION;
enum ITDIRECTION { BEGIN = 1, MID, END, REVERSE };



static int stdList_GetSize(stdList* listBegin)
{
	return listBegin->_Data->size;
}


static void* stdList_GetData(stdList* listBegin, unsigned int index)
{
	Link* tmpLink = listBegin->_Data->listBegin;
	while (tmpLink != NULL)
	{
		if (tmpLink->id == index)
			return ((char*)tmpLink->data);
		tmpLink = tmpLink->pNext;
	}
}

static int HigherProximity(int index, int _begin, int _end)
{
	int result = 0;
	_begin = abs(_begin - index);
	_end = abs(_end - index);

	if (MIN(_begin, _end) == _begin)
		result = BEGIN;
	else
		result = END;
	
	return result;

}


static void* stdList_GetData2(stdList* listBegin, unsigned int index)
{
	Link* tmpLink;
	switch (HigherProximity(index, listBegin->_Data->listBegin->id, listBegin->_Data->endList->id))
	{
	case BEGIN:
		tmpLink = listBegin->_Data->listBegin;
		while (tmpLink != NULL)
		{
			if (tmpLink->id == index)
				return ((char*)tmpLink->data);
			tmpLink = tmpLink->pNext;
		}
		break;
	case END:
		tmpLink = listBegin->_Data->endList;
		while (tmpLink != NULL)
		{
			if (tmpLink->id == index)
				return ((char*)tmpLink->data);
			tmpLink = tmpLink->pBack;
		}
		break;	
	default:
		break;
	}
}



static void deleteLink(Link** listBegin, Link* element, List** list)
{
	(*list)->size--;
	if (element == (*listBegin))
	{
		Link* tmp = element->pNext;
		(*listBegin) = tmp;
		if (tmp != NULL)
			tmp->pBack = NULL;
		else (*list)->endList = NULL;
		

		free(element->data);
		free(element);

	}
	else
	{
		Link* next = element->pNext;
		if (next)
		{
			element->pBack->pNext = next;
			next->pBack = element->pBack;
		}
		if(element == (*list)->endList)
		{
			(*list)->endList = element->pBack;
			element->pBack->pNext = NULL;
		}

		free(element->data);
		free(element);


	}
}

static void stdList_Erase(stdList* listBegin, unsigned int index)
{
	Link* tmpLink = listBegin->_Data->listBegin;
	int newId = -1;
	while (tmpLink != NULL)
	{
		if (tmpLink->id == index)
		{
			newId = tmpLink->id;
			deleteLink(&listBegin->_Data->listBegin, tmpLink, &listBegin->_Data);
			break;
		}
		tmpLink = tmpLink->pNext;
	}

	tmpLink = listBegin->_Data->endList;

	if(newId < 0 || newId >= listBegin->_Data->size)
		return;

	while (tmpLink != NULL)
	{
		tmpLink->id--;
		if (newId == tmpLink->id)
			break;
		tmpLink = tmpLink->pBack;
	}

}

static void stdList_Clear(stdList* listBegin)
{
	int size = listBegin->_Data->size;
	for (int i = 0; i < size; i++)
	{
		stdList_Erase(listBegin, 0);
	}

}

static void AddElement(Link** listBegin, Link* element, List** list)
{
	if ((*list)->listBegin == NULL)
	{
		*listBegin = element;
		(*list)->endList = element;
	}
	else
	{
		(*list)->endList->pNext = element;
		element->pBack = (*list)->endList;
		(*list)->endList = element;
	}
	
	/*element->pNext = (*listBegin);
	(*listBegin) = element;
	Link* tmp = (*listBegin);
	if ((*list)->endList)
		tmp = (*list)->endList;

	do
	{
		if (tmp->id == element->id - 1)
		{
			tmp->pBack = element;
		}
		if (tmp->pNext == NULL)
		{
			(*list)->endList = tmp;
		}
		tmp = tmp->pNext;
	} while (tmp != NULL);*/
}

static void stdList_Add(stdList* listBegin, void* element)
{
	Link* tmp = (Link*)calloc(1, sizeof(Link));
	assert(tmp != NULL);
	tmp->data = calloc(1, listBegin->_Data->elementSize);
	char* tempData = (char*)tmp->data;
	assert(tempData != NULL);
	memcpy(tempData, element, listBegin->_Data->elementSize);
	tmp->id = listBegin->_Data->size++;
	AddElement(&listBegin->_Data->listBegin, tmp, &listBegin->_Data);

}

static void stdList_Destroy(stdList** listBegin)
{
	stdList_Clear(*listBegin);
	free((*listBegin)->_Data);
	free(*listBegin);
	*listBegin = NULL;
}


stdList* stdList_Create(size_t elementSize, int size, ...)
{
	va_list params;
	va_start(params, size);
	stdList* list = (stdList*)calloc(1, sizeof(stdList));
	assert(list != NULL);
	list->_Data = (List*)calloc(1, sizeof(List));
	assert(list->_Data != NULL);
	list->_Data->size = 0;
	list->_Data->elementSize = elementSize;
	list->_Data->listBegin = NULL;

	for (int i = 0; i < size; i++)
	{
		void* vaNext = va_arg(params, void*);
		stdList_Add(list, vaNext);/*
		Link* tmp = (Link*)calloc(1, sizeof(Link));
		assert(tmp != NULL);
		tmp->id = i;
		tmp->data = calloc(1, elementSize);
		char* tempData = (char*)tmp->data;
		assert(tempData != NULL);
		memcpy(tempData, vaNext, elementSize);
		AddElement(&list->_Data->listBegin, tmp, &list->_Data);*/
	}

	list->size = &stdList_GetSize;
	list->push_back = &stdList_Add;
	list->getData = &stdList_GetData2;
	list->erase = &stdList_Erase;
	list->destroy = &stdList_Destroy;
	list->clear = &stdList_Clear;

	va_end(params);

	return list;

}