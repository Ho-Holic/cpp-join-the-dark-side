cmake_minimum_required(VERSION 2.8)

project(Darkside)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("examples")

add_executable(${PROJECT_NAME} "main.cpp")

add_executable("enum_flattener" "EnumFlattener.hpp" "TestEnumFlattener.cpp")
add_executable("shadow" "Shadow.hpp" "TestShadow.cpp")
add_executable("previous_value" "PreviousValue.hpp" "TestPreviousValue.cpp")
add_executable("mirror_map" "MirrorMap.hpp" "TestMirrorMap.cpp")
add_executable("dimension_map" "DimensionMap.hpp" "TestDimensionMap.cpp")
add_executable("cycle_value" "CycleValue.hpp" "TestCycleValue.cpp")
#add_executable("??" "??.hpp" "Test.cpp")
