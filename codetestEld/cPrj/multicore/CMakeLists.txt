cmake_minimum_required (VERSION 2.8)
set(CMAKE_C_STANDARD 99)
project (Demo1)
set(CFLAGS
    -g
    -pthread
    )
add_compile_options(${CFLAGS})
#MESSAGE(STATUS "Project: Demo1") #打印相关消息消息
add_executable(main main.c)
find_package(Threads)
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})