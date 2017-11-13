cmake_minimum_required(VERSION 2.8)

project(examples)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("examples")

add_executable(${PROJECT_NAME}
    "main.cpp"
    "MirrorMap.hpp"
    "EnumFlattener.hpp"
    "PreviousValue.hpp"
    "Shadow.hpp"
    )
