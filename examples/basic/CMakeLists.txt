cmake_minimum_required(VERSION 2.8)
project(inicpp_basic)

set(EXEC_NAME ${PROJECT_NAME})
set(SOURCE_FILES
	main.cpp
)

#include_directories(${INCLUDE_DIR})  # this is set from parent project

add_executable(${EXEC_NAME} ${SOURCE_FILES})
target_link_libraries(${EXEC_NAME} inicpp)
