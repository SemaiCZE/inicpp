cmake_minimum_required(VERSION 2.8)
project(inicpp)

set(SRC_DIR src)
set(INCLUDE_DIR include/inicpp)

set(SOURCE_FILES
	${INCLUDE_DIR}/config.h
	${SRC_DIR}/config.cpp
	${INCLUDE_DIR}/exception.h
	${SRC_DIR}/exception.cpp
	${INCLUDE_DIR}/option.h
	${SRC_DIR}/option.cpp
	${INCLUDE_DIR}/option_schema.h
	${SRC_DIR}/option_schema.cpp
	${INCLUDE_DIR}/parser.h
	${SRC_DIR}/parser.cpp
	${INCLUDE_DIR}/schema.h
	${SRC_DIR}/schema.cpp
	${INCLUDE_DIR}/section.h
	${SRC_DIR}/section.cpp
	${INCLUDE_DIR}/section_schema.h
	${SRC_DIR}/section_schema.cpp
	${INCLUDE_DIR}/types.h
	${INCLUDE_DIR}/string_utils.h
	${SRC_DIR}/string_utils.cpp
	${INCLUDE_DIR}/inicpp.h
)

# Find header files in include directory
include_directories(${INCLUDE_DIR})

# Set options to disable build of shared and static library
option(BUILD_SHARED "Specifies if shared library is build." ON)
option(BUILD_STATIC "Specifies if static library is build." ON)

# Compile dynamic library
if(BUILD_SHARED)
	add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
endif()

# Compile static library
if(BUILD_STATIC)
	add_library(${PROJECT_NAME}_static STATIC ${SOURCE_FILES})
endif()

# Use C++14 features
if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
endif()

# Set up google testing framework (not compile by default)
set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.")
add_subdirectory(vendor/googletest EXCLUDE_FROM_ALL)

# Add our very own unit tests (not compile by default)
add_subdirectory(tests EXCLUDE_FROM_ALL)

