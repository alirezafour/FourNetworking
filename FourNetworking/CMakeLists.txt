# Silence warning about PROJECT_VERSION
cmake_policy(SET CMP0048 NEW)

cmake_minimum_required (VERSION 3.11)
project(FourNetworking)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)

file(GLOB SOURCES src/* src/*/* src/*/*/*)

# Add source to this project's executable.
add_library (${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		${Boost_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		${Boost_LIBRARIES}
)

