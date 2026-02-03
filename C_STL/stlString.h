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


#ifndef STRING_H_
#define STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Export.h"

typedef struct String String;
typedef struct stdString stdString;

struct stdString {

	////////////////////////////////////////////////////////////
	/// \brief Contains all the data of the string. DO NOT USE IT DIRECTLY.
	////////////////////////////////////////////////////////////
	String* _Data;

	////////////////////////////////////////////////////////////
	/// \brief Append a new string at the end of the existing string.
	/// 
	/// \param stdString* The string you are using.
	/// \param const char* The string to append.
	////////////////////////////////////////////////////////////
	void (*append)(stdString*, const char*);

	////////////////////////////////////////////////////////////
	/// \brief Insert a new string at the specified index.
	/// 
	/// \param stdString* The string you are using.
	/// \param const char* The string to insert.
	/// \param size_t Index where the string will be inserted.
	////////////////////////////////////////////////////////////
	void (*insert)(stdString*, const char*, size_t);

	////////////////////////////////////////////////////////////
	/// \brief Replace the existing string with a new one.
	/// 
	/// \param stdString* The string you are using.
	/// \param const char* The new string.
	////////////////////////////////////////////////////////////
	void (*replace)(stdString*, const char*);

	////////////////////////////////////////////////////////////
	/// \brief Get the `const char*` data held by the string.
	/// 
	/// \param stdString const* The string you are using.
	/// \return A `const char*` pointing to the internal string data.
	////////////////////////////////////////////////////////////
	const char* (*getData)(stdString const*);

	////////////////////////////////////////////////////////////
	/// \brief Get the length of the string.
	/// 
	/// \param stdString* The string you are using.
	/// \return The length of the string as a `size_t`.
	////////////////////////////////////////////////////////////
	size_t(*size)(stdString*);

	////////////////////////////////////////////////////////////
	/// \brief Remove a portion of the string.
	///
	/// \param stdString* The string you are using.
	/// \param size_t Index of the first character to remove.
	/// \param size_t Number of characters to remove.
	////////////////////////////////////////////////////////////
	void (*remove)(stdString* str, size_t index, size_t length);

	////////////////////////////////////////////////////////////
	/// \brief Destroy the string and set the pointer to NULL.
	/// 
	/// \param stdString** Address of the string you are using (example: &string).
	////////////////////////////////////////////////////////////
	void (*destroy)(stdString**);
};

////////////////////////////////////////////////////////////
/// \brief Create a new `stdString` instance.
/// 
/// \param const char* The initial value of the string.
/// \return A pointer to the newly created `stdString` structure.
////////////////////////////////////////////////////////////
stdString LIBSTD_API* stdStringCreate(const char* string);

////////////////////////////////////////////////////////////
/// \brief Print the contents of the string to stdout.
/// 
/// \param stdString* The string to print.
////////////////////////////////////////////////////////////
void LIBSTD_API stdStringPrint(stdString* str);

////////////////////////////////////////////////////////////
/// \brief Copy a C string into a newly allocated memory area.
/// 
/// \param const char* The source string to copy.
/// \return A pointer to the newly allocated copy of the string.
////////////////////////////////////////////////////////////
char LIBSTD_API* CopyAndAllocChar(const char* source);

////////////////////////////////////////////////////////////
/// \brief Free all the temporary memory allocated.
/// 
////////////////////////////////////////////////////////////
void LIBSTD_API CleanUpTempMemory();

/*
 * Description of utility functions:
 *
 * - char* AddChar(char* string_one, char* string_two);
 *   This function concatenates two strings, `string_one` and `string_two`, into a single string.
 *
 * - char* IntToString(int value);
 *   This function converts an integer (`int`) to a string.
 *
 * - char* LongToString(long value);
 *   This function converts a long integer (`long`) to a string.
 *
 * - char* ShortToString(short value);
 *   This function converts a short integer (`short`) to a string.
 *
 * - char* FloatToString(float value, unsigned int decimalNumber);
 *   This function converts a floating-point number (`float`) to a string, specifying the number of
 *   decimal places using `decimalNumber`.
 *
 * - char* CharToString(char value);
 *   This function converts a character (`char`) to a string.
 *
 * Important Warning:
 * The return values of these functions are likely stored in a temporary memory area (such as a static
 * buffer or locally allocated memory). Therefore, if you need to reuse these values outside their immediate
 * context or after subsequent calls to any of these functions, you must copy them to a separate buffer using
 * functions like `strdup()` or `memcpy()`.
 *
 * Example:
 * string.append(string, IntToString(42)); // Temporary usage, no need to copy.
 * char* permanentCopy = strdup(temp); // Copy the string if you need to retain it.
 *
 * Note: Failing to copy these values could result in undefined behavior, such as data being overwritten
 * during successive calls to these functions.
 */

 ////////////////////////////////////////////////////////////
 /// \brief Concatenate two strings into a new string.
 /// 
 /// \param char* The first string.
 /// \param char* The second string.
 /// \return A pointer to the concatenated string.
 ////////////////////////////////////////////////////////////
char LIBSTD_API* AddChar(char* string_one, char* string_two);

////////////////////////////////////////////////////////////
/// \brief Convert an integer to a string.
/// 
/// \param int The integer value to convert.
/// \return A pointer to the resulting string.
////////////////////////////////////////////////////////////
char LIBSTD_API* IntToString(int value);

////////////////////////////////////////////////////////////
/// \brief Convert a long integer to a string.
/// 
/// \param long The long value to convert.
/// \return A pointer to the resulting string.
////////////////////////////////////////////////////////////
char LIBSTD_API* LongToString(long value);

////////////////////////////////////////////////////////////
/// \brief Convert a short integer to a string.
/// 
/// \param short The short value to convert.
/// \return A pointer to the resulting string.
////////////////////////////////////////////////////////////
char LIBSTD_API* ShortToString(short value);

////////////////////////////////////////////////////////////
/// \brief Convert a floating-point number to a string with a specific number of decimal places.
/// 
/// \param float The float value to convert.
/// \param unsigned int The number of decimal places.
/// \return A pointer to the resulting string.
////////////////////////////////////////////////////////////
char LIBSTD_API* FloatToString(float value, unsigned int decimalNumber);

////////////////////////////////////////////////////////////
/// \brief Convert a character to a string.
/// 
/// \param char The character to convert.
/// \return A pointer to the resulting string.
////////////////////////////////////////////////////////////
char LIBSTD_API* CharToString(char value);

#endif // STRING_H_
