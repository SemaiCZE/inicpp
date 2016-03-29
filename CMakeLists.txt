cmake_minimum_required(VERSION 2.8)
project(inicpp)

set(SRC_DIR src)

set(SOURCE_FILES
	${SRC_DIR}/config.h
	${SRC_DIR}/config.cpp
	${SRC_DIR}/config_iterator.h
	${SRC_DIR}/exception.h
	${SRC_DIR}/exception.cpp
	${SRC_DIR}/option.h
	${SRC_DIR}/option.cpp
	${SRC_DIR}/option_schema.h
	${SRC_DIR}/option_schema.cpp
	${SRC_DIR}/parser.h
	${SRC_DIR}/parser.cpp
	${SRC_DIR}/schema.h
	${SRC_DIR}/schema.cpp
	${SRC_DIR}/section.h
	${SRC_DIR}/section.cpp
	${SRC_DIR}/section_iterator.h
	${SRC_DIR}/section_schema.h
	${SRC_DIR}/section_schema.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Use C++14 features
if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
endif()

