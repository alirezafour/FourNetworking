# CMakeList.txt : CMake project for FourNetworking, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)
project(SampleClient)

set(CMAKE_CXX_STANDARD 20)

include_directories("src")

file(GLOB SOURCES Source.cpp src/* src/*/* src/*/*)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${SOURCES} "client.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC FourNetworking)

target_link_libraries(${PROJECT_NAME} PUBLIC FourNetworking)
