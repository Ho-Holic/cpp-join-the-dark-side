cmake_minimum_required(VERSION 2.8)

project(Darkside)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(test_headers
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/TestShadow.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/TestRandom.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/TestPreviousValue.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/TestMirrorMap.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/TestIdentifierGenerator.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/tests/TestEnumFlattener.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/TestDimensionMap.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/TestCycleValue.hpp
)

set(core_headers
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Shadow.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Random.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Protest.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/PreviousValue.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/MirrorMap.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/IdentifierGenerator.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/EnumFlattener.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/DimensionMap.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/CycleValue.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/CommonConcepts.hpp
)

add_executable(${PROJECT_NAME} "main.cpp" ${test_headers} ${core_headers})
add_executable("Test${PROJECT_NAME}" "test_main.cpp" ${test_headers} ${core_headers})
