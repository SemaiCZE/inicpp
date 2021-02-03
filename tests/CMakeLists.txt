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

add_test(${TESTS_NAME} ${TESTS_NAME})
set_target_properties(${TESTS_NAME} PROPERTIES FOLDER tests)
