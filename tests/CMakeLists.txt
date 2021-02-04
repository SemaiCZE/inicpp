set(TESTS_NAME inicpp_tests)

set(${TESTS_NAME}_SOURCES
	option.cpp
	section_iterator.cpp
	section.cpp
	config_iterator.cpp
	config.cpp
	exception.cpp
	parser.cpp
	option_schema.cpp
	section_schema.cpp
	string_utils.cpp
	schema.cpp)

add_executable(${TESTS_NAME} ${${TESTS_NAME}_SOURCES})

target_link_libraries(${TESTS_NAME} gtest gtest_main)
target_link_libraries(${TESTS_NAME} gmock gmock_main)

target_link_libraries(${TESTS_NAME} inicpp)

if(MSVC)
	set_target_properties(${TESTS_NAME}
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
	)
endif()

add_test(NAME ${TESTS_NAME} COMMAND $<TARGET_FILE:${TESTS_NAME}>)
set_target_properties(${TESTS_NAME} PROPERTIES FOLDER inicpp_tests)
