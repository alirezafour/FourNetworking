# CMakeList.txt : CMake project for FourNetworking, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.11)
project(FourNetworking)

file(GLOB SOURCES src/* src/*/* src/*/*/*)

# Add source to this project's executable.
add_library (${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

