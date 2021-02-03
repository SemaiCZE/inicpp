cmake_minimum_required(VERSION 3.1)
project(inicpp_basic)

set(EXEC_NAME ${PROJECT_NAME})
set(${EXEC_NAME}_SOURCES
	main.cpp
)

add_executable(${EXEC_NAME} ${${EXEC_NAME}_SOURCES})
target_link_libraries(${EXEC_NAME} inicpp)
