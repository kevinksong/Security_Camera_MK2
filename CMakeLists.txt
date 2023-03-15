cmake_minimum_required(VERSION 3.10)
project( displayMotion )

include_directories(./include/cam.h)

file(GLOB SOURCES "./include/cam.cpp" "./main.cpp")

find_package( OpenCV REQUIRED)

add_executable( displayMotion ${SOURCES} )
target_link_libraries( displayMotion ${OpenCV_LIBS})

