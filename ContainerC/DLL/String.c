#include "String.h"
#include "List.h"

stdList* ressources_list;

struct String {
	char* str;
	size_t length;
};


#define INIT_LIST if (ressources_list == NULL)\
{\
	ressources_list = STD_LIST_CREATE(char**, 0, NULL);\
}\



static void stdStringDestroy(stdString** str)
{
	free((*str)->_Data->str);
	free((*str)->_Data);
	free((*str));
	(*str) = NULL;
}

static void stdStringAppend(stdString* str, const char* string)
{
	INIT_LIST;
	size_t length = strlen(string);
	char* tmp = (char*)realloc(str->_Data->str, str->_Data->length + length + 1);
	assert(tmp);
	str->_Data->str = tmp;
	assert(str->_Data->str != NULL);
	strcpy_s(str->_Data->str + str->_Data->length, length + 1, string);
	str->_Data->length += length;
	if (ressources_list)
	{
		for (int iterator = 0; iterator < ressources_list->size(ressources_list); iterator++)
		{
			char** it_name = STD_GETDATA(ressources_list, char*, iterator);
			free(*it_name);
		}
		ressources_list->clear(ressources_list);
	}
}

static void stdStringInsert(stdString* str, const char* string, size_t index)
{
	INIT_LIST;
	size_t length = strlen(string);
	char* tmp = (char*)realloc(str->_Data->str, str->_Data->length + length + 1);
	assert(tmp);
	str->_Data->str = tmp;
	assert(str->_Data->str != NULL);
	memmove(str->_Data->str + index + length, str->_Data->str + index, str->_Data->length - index + 1);
	memcpy(str->_Data->str + index, string, length);
	str->_Data->length += length;
	if (ressources_list)
	{
		ressources_list->clear(ressources_list);
	}
}

static void stdStringtRemove(stdString* str, size_t index, size_t length)
{
	INIT_LIST;
	memmove(str->_Data->str + index, str->_Data->str + index + length, str->_Data->length - index - length + 1);
	str->_Data->length -= length;
	char* tmp = (char*)realloc(str->_Data->str, str->_Data->length + 1);
	assert(tmp);
	str->_Data->str = tmp;
	assert(str->_Data->str != NULL);
	if (ressources_list)
	{
		ressources_list->clear(ressources_list);
	}
}

static void stdStringReplace(stdString* str, const char* string)
{
	INIT_LIST;
	size_t length2 = strlen(string);
	char* tmp = (char*)realloc(str->_Data->str, length2 + 1);
	assert(tmp);
	str->_Data->str = tmp;
	assert(str->_Data->str != NULL);
	strcpy_s(str->_Data->str, length2 + 1, string);
	str->_Data->length = length2;
	if (ressources_list)
	{
		ressources_list->clear(ressources_list);
	}
}

static const char* stdStringGetConst(const stdString* str)
{
	return str->_Data->str;
}

static size_t stdStringSize(stdString* str)
{
	return (size_t)str->_Data->length;
}

void stdStringPrint(stdString* str)
{
	printf("%s\n", str->_Data->str);
}

char* CopyAndAllocChar(const char* source)
{
	return _strdup(source);
}

stdString* stdStringCreate(const char* string)
{
	INIT_LIST;

	stdString* str = (stdString*)calloc(1, sizeof(stdString));
	assert(str != NULL);
	str->_Data = (String*)calloc(1, sizeof(String));
	assert(str->_Data != NULL);
	str->_Data->length = strlen(string);
	str->_Data->str = (char*)calloc(str->_Data->length + 1, sizeof(char));
	assert(str->_Data->str != NULL);
	strcpy_s(str->_Data->str, str->_Data->length + 1, string);

	if (ressources_list)
	{
		for (int iterator = 0; iterator < ressources_list->size(ressources_list); iterator++)
		{
			char** it_name = STD_GETDATA(ressources_list, char*, iterator);
			free(*it_name);
		}
		ressources_list->clear(ressources_list);
	}

	str->append = &stdStringAppend;
	str->insert = &stdStringInsert;
	str->replace = &stdStringReplace;
	str->size = &stdStringSize;
	str->getData = &stdStringGetConst;
	str->remove = &stdStringtRemove;
	str->destroy = &stdStringDestroy;
	return str;
}



char* AddChar(char* string_one, char* string_two)
{
	INIT_LIST;
	int totalSize = strlen(string_one) + strlen(string_two) + 1;
	char* tmp = calloc(totalSize, sizeof(char));
	if (tmp)
	{
		strcat(tmp, string_one);
		strcat(tmp, string_two);
	}
	if (ressources_list)
	{
		ressources_list->push_back(ressources_list, &tmp);
		return tmp;
	}
}



char* IntToString(int value)
{
	INIT_LIST;
	char* tmp = calloc(128, sizeof(char));
	if (tmp)
	{
		sprintf_s(tmp, 128, "%d", value);
		if (ressources_list)
		{
			ressources_list->push_back(ressources_list, &tmp);
		}
	}
	return tmp;
}

char* LongToString(long value)
{
	INIT_LIST;
	char* tmp = calloc(128, sizeof(char));
	if (tmp)
	{
		sprintf_s(tmp, 128, "%ld", value);
		if (ressources_list)
		{
			ressources_list->push_back(ressources_list, &tmp);
		}
	}
	return tmp;
}

char* ShortToString(short value)
{
	INIT_LIST;
	char* tmp = calloc(128, sizeof(char));
	if (tmp)
	{
		sprintf_s(tmp, 128, "%hd", value);
		if (ressources_list)
		{
			ressources_list->push_back(ressources_list, &tmp);
		}
	}
	return tmp;
}

char* FloatToString(float value, unsigned int decimalNumber)
{
	INIT_LIST;
	char* tmp = calloc(128, sizeof(char));
	if (tmp)
	{
		sprintf_s(tmp, 128, AddChar("%.", AddChar(IntToString(decimalNumber), "f")), value);
		if (ressources_list)
		{
			ressources_list->push_back(ressources_list, &tmp);
		}
	}
	return tmp;
}

char* CharToString(char value)
{
	INIT_LIST;
	char* tmp = calloc(128, sizeof(char));
	if (tmp)
	{
		sprintf_s(tmp, 128, "%c", value);
		if (ressources_list)
		{
			ressources_list->push_back(ressources_list, &tmp);
		}
	}
	return tmp;
}
