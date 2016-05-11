project(inicpp_tests)

set(TESTS_NAME run_tests)
set(SRC_DIR ../src)
set(LIBS_DIR ../vendor)

# Google Test and Google Mock headers
include_directories(${LIBS_DIR}/googletest/googletest/include)
include_directories(${LIBS_DIR}/googletest/googlemock/include)

add_executable(${TESTS_NAME}
	${SRC_DIR}/config.cpp
	${SRC_DIR}/option.cpp
	${SRC_DIR}/option_schema.cpp
	${SRC_DIR}/parser.cpp
	${SRC_DIR}/schema.cpp
	${SRC_DIR}/section.cpp
	${SRC_DIR}/section_schema.cpp
	${SRC_DIR}/string_utils.cpp
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
	types.cpp
	schema.cpp
)

# Link with Google libraries
target_link_libraries(${TESTS_NAME} gtest gtest_main)
target_link_libraries(${TESTS_NAME} gmock gmock_main)

