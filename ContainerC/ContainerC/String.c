#include "String.h"

struct String {
	char *str;
	size_t length;
};

stdString* stdStringCreate(const char* string)
{
	stdString* str = (stdString*)calloc(1, sizeof(stdString));
	assert(str != NULL);
	str->_Data = (String*)calloc(1, sizeof(String));
	assert(str->_Data != NULL);
	str->_Data->length = strlen(string);
	str->_Data->str = (char*)calloc(str->_Data->length + 1, sizeof(char));
	assert(str->_Data->str != NULL);
	strcpy_s(str->_Data->str, str->_Data->length + 1, string);
	return str;
}

stdString* stdStringCreate_s(const char* string, char free_string)
{
	stdString* str = (stdString*)calloc(1, sizeof(stdString));
	assert(str != NULL);
	str->_Data = (String*)calloc(1, sizeof(String));
	assert(str->_Data != NULL);
	str->_Data->length = strlen(string);
	str->_Data->str = (char*)calloc(str->_Data->length + 1, sizeof(char));
	assert(str->_Data->str != NULL);
	strcpy_s(str->_Data->str, str->_Data->length + 1, string);
	if (free_string)
		free(string);
	return str;
}

void stdStringDestroy(stdString** str)
{
	free((*str)->_Data->str);
	free((*str)->_Data);
	free((*str));
	(*str) = NULL;
}

void stdStringAppend(stdString* str, const char* string)
{
	size_t length = strlen(string);
	char* tmp = (char*)realloc(str->_Data->str, str->_Data->length + length + 1);
	assert(tmp);
	str->_Data->str = tmp;
	assert(str->_Data->str != NULL);
	strcpy_s(str->_Data->str + str->_Data->length, length + 1, string);
	str->_Data->length += length;
}

void stdStringInsert(stdString* str, const char* string, size_t index)
{
	size_t length = strlen(string);
	char* tmp = (char*)realloc(str->_Data->str, str->_Data->length + length + 1);
	assert(tmp);
	str->_Data->str = tmp;
	assert(str->_Data->str != NULL);
	memmove(str->_Data->str + index + length, str->_Data->str + index, str->_Data->length - index + 1);
	memcpy(str->_Data->str + index, string, length);
	str->_Data->length += length;
}

void stdStringtRemove(stdString* str, size_t index, size_t length)
{
	memmove(str->_Data->str + index, str->_Data->str + index + length, str->_Data->length - index - length + 1);
	str->_Data->length -= length;
	char* tmp = (char*)realloc(str->_Data->str, str->_Data->length + 1);
	assert(tmp);
	str->_Data->str = tmp;
	assert(str->_Data->str != NULL);
}

void stdStringReplace(stdString* str, const char* string)
{
	size_t length2 = strlen(string);
	char* tmp = (char*)realloc(str->_Data->str, length2 + 1);
	assert(tmp);
	str->_Data->str = tmp;
	assert(str->_Data->str != NULL);
	strcpy_s(str->_Data->str, length2 + 1,string);
	str->_Data->length = length2;
}

char* stdStringGet(stdString* str)
{
	return str->_Data->str;
}

const char* stdStringGetConst(const stdString* str)
{
	return str->_Data->str;
}

unsigned int stdStringSize(stdString* str)
{
	return (unsigned int)str->_Data->length;
}

void stdStringPrint(stdString* str)
{
	printf("%s", str->_Data->str);
}

char* AddChar(char* string_one, char* string_two)
{
	int totalSize = strlen(string_one) + strlen(string_two) + 1;
	char* tmp = calloc(totalSize, sizeof(char));
	if(tmp)
	{
		strcat(tmp, string_one);
		strcat(tmp, string_two);
	}
	return tmp;
}

char* AddChar_s(char* string_one, char freeStringOne, char* string_two, char freeStringTwo)
{
	int totalSize = strlen(string_one) + strlen(string_two) + 1;
	char* tmp = calloc(totalSize, sizeof(char));
	if (tmp)
	{
		strcat(tmp, string_one);
		strcat(tmp, string_two);
	}
	if (freeStringOne)
		free(string_one);
	if (freeStringTwo)
		free(string_two);

	return tmp;
}

char* IntToString(int value)
{
	char* tmp = calloc(100, sizeof(char));
	if(tmp)
		sprintf_s(tmp, 100, "%d", value);
	return tmp;
}

char* LongToString(long value)
{
	char* tmp = calloc(100, sizeof(char));
	if (tmp)
		sprintf_s(tmp, 100, "%ld", value);
	return tmp;
}

char* ShortToString(short value)
{
	char* tmp = calloc(100, sizeof(char));
	if (tmp)
		sprintf_s(tmp, 100, "%hd", value);
	return tmp;
}

char* FloatToString(float value)
{
	char* tmp = calloc(100, sizeof(char));
	if (tmp)
		sprintf_s(tmp, 100, "%f", value);
	return tmp;
}

char* CharToString(char value)
{
	char* tmp = calloc(100, sizeof(char));
	if (tmp)
		sprintf_s(tmp, 100, "%c", value);
	return tmp;
}
