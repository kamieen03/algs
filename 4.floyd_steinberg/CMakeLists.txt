cmake_minimum_required(VERSION 3.13)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ../0.algorithm )
add_executable(floyd_steinberg 4.floyd_steinberg.cpp)
target_link_libraries( floyd_steinberg ${OpenCV_LIBS} )

