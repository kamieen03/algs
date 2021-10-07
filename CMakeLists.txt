cmake_minimum_required(VERSION 3.13)
project(algs)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)
set(COMPILE_FLAGS -Wall -Weffc++ -Wextra -Wsign-conversion -pedantic-errors)

add_subdirectory(1.eratosthenes)
add_subdirectory(2.convex_hull)
add_subdirectory(3.PCA)
add_subdirectory(4.floyd_steinberg)
add_subdirectory(5.filters)
add_subdirectory(6.BST)

