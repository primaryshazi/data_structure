cmake_minimum_required(VERSION 3.10.0)

project(DATA_STRUCTURE)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -m64")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/build)

add_subdirectory(list)
add_subdirectory(stack)
add_subdirectory(queue)
add_subdirectory(tree)
add_subdirectory(hash)
add_subdirectory(heap)
add_subdirectory(disjoint_set)
add_subdirectory(graph)
