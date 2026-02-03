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

#ifndef EXPORTS_H_
#define EXPORTS_H_

#ifdef DLL_EXPORTS
#define LIBSTD_API __declspec(dllexport)
#else
#define LIBSTD_API __declspec(dllimport)
#endif

#define FOR_EACH_TEMP(container,name,type,initFunc,func) container* name = initFunc;\
    for(int i =0; i < name->size(name);i++)\
    {func}\
    name->destroy(&name);

#define FOR_EACH(container,type,it_name,data_container_name,func)for(int it_name = 0; it_name < container->size(container); it_name++)\
    {\
    type* data_container_name = STD_GETDATA(container,type,it_name);\
    func}

#define FOR_EACH_POINTER(container,type,it_name,data_container_name,func)for(int it_name = 0; it_name < container->size(container); it_name++)\
    {\
    type* data_container_name##_ = STD_GETDATA(container,type,it_name);\
    type data_container_name = *data_container_name##_;\
    func}


#define STD_CONVERT(type, ...) \
(void*)&(type){__VA_ARGS__}

#define STD_GETDATA(container,type,index) ((type*)container->getData(container, index))

#endif // EXPORTS_H_