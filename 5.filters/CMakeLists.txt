cmake_minimum_required(VERSION 3.13)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ../0.algorithm )
add_executable(filter 5.filtering.cpp 5.filters.cpp)
target_link_libraries( filter ${OpenCV_LIBS} )

