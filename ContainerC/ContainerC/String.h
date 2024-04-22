#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct String String;
typedef struct stdString stdString;

struct stdString {
	String* _Data;
};

stdString* stdStringCreate(const char* string);
stdString* stdStringCreate_s(const char* string, char free_string);
void stdStringDestroy(stdString** str);
void stdStringAppend(stdString* str, const char* string);
void stdStringInsert(stdString* str, const char* string, size_t index);
void stdStringtRemove(stdString* str, size_t index, size_t length);
void stdStringReplace(stdString* str, const char* string);
char* stdStringGet(stdString* str);
const char* stdStringGetConst(const stdString* str);
unsigned int stdStringSize(stdString* str);
void stdStringPrint(stdString* str);

char* AddChar(char* string_one, char* string_two);
char* AddChar_s(char* string_one, char freeStringOne, char* string_two, char freeStringTwo);
char* IntToString(int value);
char* LongToString(long value);
char* ShortToString(short value);
char* FloatToString(float value);
char* CharToString(char value);