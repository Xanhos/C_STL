cmake_minimum_required(VERSION 4.0)
project(C_STL C)

set(CMAKE_C_STANDARD 23)

set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/C_STL)
set(LIB_TEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/C_STL_Test)

add_library(C_STL SHARED)

target_compile_definitions(C_STL PRIVATE DLL_EXPORTS=1)
target_compile_definitions(C_STL PRIVATE ${MY_DEFINES})

target_sources(C_STL PUBLIC ${LIB_PATH}/Export.h
        PUBLIC ${LIB_PATH}/List.h
        PUBLIC ${LIB_PATH}/Pool.h
        PUBLIC ${LIB_PATH}/stlString.h
        PUBLIC ${LIB_PATH}/Vector.h
        PRIVATE ${LIB_PATH}/List.c
        PRIVATE ${LIB_PATH}/Pool.c
        PRIVATE ${LIB_PATH}/stlString.c
        PRIVATE ${LIB_PATH}/Vector.c)

target_include_directories(C_STL PUBLIC ${LIB_PATH})


add_executable(C_STL_Test)

target_sources(C_STL_Test PUBLIC ${LIB_TEST_PATH}/main.c ${LIB_TEST_PATH}/test_suite.c)

target_include_directories(C_STL_Test PRIVATE ${LIB_TEST_PATH})

target_link_libraries(C_STL_Test PUBLIC C_STL)
