cmake_minimum_required(VERSION 3.1)
project(inicpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(INICPP_SRC_DIR src)
set(INICPP_INCLUDE_DIR include/inicpp)

set(INICPP_SOURCES
	${INICPP_INCLUDE_DIR}/config.h
	${INICPP_SRC_DIR}/config.cpp
	${INICPP_INCLUDE_DIR}/exception.h
	${INICPP_INCLUDE_DIR}/option.h
	${INICPP_SRC_DIR}/option.cpp
	${INICPP_INCLUDE_DIR}/option_schema.h
	${INICPP_SRC_DIR}/option_schema.cpp
	${INICPP_INCLUDE_DIR}/parser.h
	${INICPP_SRC_DIR}/parser.cpp
	${INICPP_INCLUDE_DIR}/schema.h
	${INICPP_SRC_DIR}/schema.cpp
	${INICPP_INCLUDE_DIR}/section.h
	${INICPP_SRC_DIR}/section.cpp
	${INICPP_INCLUDE_DIR}/section_schema.h
	${INICPP_SRC_DIR}/section_schema.cpp
	${INICPP_INCLUDE_DIR}/types.h
	${INICPP_INCLUDE_DIR}/string_utils.h
	${INICPP_SRC_DIR}/string_utils.cpp
	${INICPP_INCLUDE_DIR}/inicpp.h
	${INICPP_INCLUDE_DIR}/dll.h
)

# Find header files in include directory
include_directories(${INICPP_INCLUDE_DIR})

# Set options to determine what/how you want to build
option(INICPP_BUILD_SHARED "Specifies if shared library is built, if not set a static library will be built intstead." OFF)
option(INICPP_BUILD_TESTS "Specifies if tests should be built." OFF)
option(INICPP_BUILD_EXAMPLES "Specifies if examples should be built." OFF)

if(INICPP_BUILD_SHARED)
	add_library(${PROJECT_NAME} SHARED ${INICPP_SOURCES})
	if(MSVC)
		# set preprocessor macros for dll export
		target_compile_definitions(${PROJECT_NAME} PUBLIC
				INICPP_DLL)
		target_compile_definitions(${PROJECT_NAME} PRIVATE
				INICPP_EXPORT)
	endif()
else()
	add_library(${PROJECT_NAME} STATIC ${INICPP_SOURCES})
endif()

add_library(${PROJECT_NAME}_private_options INTERFACE)
if(UNIX)
	target_compile_options(${PROJECT_NAME}_private_options INTERFACE -Wall -Wextra -Wdeprecated -Wconversion -Wold-style-cast -Wformat)
else()
	target_compile_options(${PROJECT_NAME}_private_options INTERFACE /W4)
endif()

add_library(${PROJECT_NAME}_public_options INTERFACE)
target_compile_features(${PROJECT_NAME}_public_options INTERFACE cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE
		${PROJECT_NAME}_private_options)
target_link_libraries(${PROJECT_NAME} PUBLIC
		${PROJECT_NAME}_public_options)

if(INICPP_BUILD_TESTS)
	# Set up google testing framework
	set(NO_GOOGLE_TEST OFF CACHE BOOL "Disable google testing framework.  Useful when buidling from a tarball since google testing framework support requires fetching of additional git submodules.")
	if(NOT ${NO_GOOGLE_TEST})
		set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.")
		add_subdirectory(vendor/googletest)
	endif()

	# Add our very own unit tests
	enable_testing()
	add_subdirectory(tests)
endif()

if(INICPP_BUILD_EXAMPLES)
	# Add examples programs
	add_subdirectory(examples)
endif()

# ========== Install targets - 'cmake --install .' ==========
include(GNUInstallDirs)
include(InstallRequiredSystemLibraries)
if(UNIX)
	install(DIRECTORY ${INICPP_INCLUDE_DIR} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
	if(INICPP_BUILD_SHARED)
		install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library)
	else()
		install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library)
	endif()
elseif(WIN32)
	install(DIRECTORY ${INICPP_INCLUDE_DIR} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
	install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library)
else()
	install(DIRECTORY ${INICPP_INCLUDE_DIR} DESTINATION inicpp/include)
	install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION inicpp/lib COMPONENT library)
endif()


# ========== Formatting ==========
file(GLOB_RECURSE ALL_SOURCE_FILES src/*.cpp src/*.h tests/*.cpp tests/*.h include/inicpp/*.h)
if(UNIX)
	add_custom_target(format
			COMMAND clang-format --style=file -i ${ALL_SOURCE_FILES}
			COMMENT "Running clang-format"
			VERBATIM
	)

	# Count sum of lines in source files
	add_custom_target(lines
			COMMAND echo -n "Total lines of code: " && cat ${ALL_SOURCE_FILES} | wc -l
			COMMENT "Counting lines"
			VERBATIM
	)
endif()

