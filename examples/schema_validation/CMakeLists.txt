cmake_minimum_required(VERSION 3.1)
project(inicpp_schema)

set(EXEC_NAME ${PROJECT_NAME})
set(${EXEC_NAME}_SOURCES
	main.cpp
)

#include_directories(${INCLUDE_DIR})  # this is set from parent project

add_executable(${EXEC_NAME} ${${EXEC_NAME}_SOURCES})
target_link_libraries(${EXEC_NAME} inicpp)
