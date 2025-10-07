cmake_minimum_required(VERSION 3.10)
project(Algo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_LIST "src/*.cpp")

foreach(src_file ${SRC_LIST})
    file(READ ${src_file} file_content)
    if(file_content MATCHES "int[ \t]+main[ \t]*\\(")
        get_filename_component(name ${src_file} NAME_WE)
        add_executable(${name} ${src_file})
    endif()
endforeach()
