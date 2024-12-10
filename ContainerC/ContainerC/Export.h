#pragma once
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


#define STD_GETDATA(container,type,index) ((type*)container->getData(container, index))

