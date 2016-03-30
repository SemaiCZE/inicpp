project(inicpp_tests)

set(TESTS_NAME run_tests)
set(SRC_DIR ../src)

# Google Test and Google Mock headers
include_directories(${LIBS_DIR}/googletest/include)
include_directories(${LIBS_DIR}/googlemock/include)

add_executable(${TESTS_NAME}
	${SRC_DIR}/config.cpp
	${SRC_DIR}/exception.cpp
	${SRC_DIR}/option.cpp
	${SRC_DIR}/option_schema.cpp
	${SRC_DIR}/parser.cpp
	${SRC_DIR}/schema.cpp
	${SRC_DIR}/section.cpp
	${SRC_DIR}/section_schema.cpp
)

# Link with Google libraries
target_link_libraries(${TESTS_NAME} gtest gtest_main)
target_link_libraries(${TESTS_NAME} gmock gmock_main)

