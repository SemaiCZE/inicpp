#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/string_utils.h"

using namespace inicpp;
using namespace string_utils;
using namespace std;


TEST(string_utils, trim)
{
	string str = "";
	ASSERT_EQ("", trim(str));

	str = " A";
	ASSERT_EQ("A", trim(str));

	str = "A ";
	ASSERT_EQ("A", trim(str));

	str = " A ";
	ASSERT_EQ("A", trim(str));

	str = " A B ";
	ASSERT_EQ("A B", trim(str));

	str = "          A         ";
	ASSERT_EQ("A", trim(str));

	str = "                    ";
	ASSERT_EQ("", trim(str));

	// advanced tests
	str = "\f\n\r\t\v";
	ASSERT_EQ("", trim(str));

	str = "\f\n\r\t\vA\v\t\r\n\f";
	ASSERT_EQ("A", trim(str));

	str = " \f \n \r \t \v A \v \t \r \n \f";
	ASSERT_EQ("A", trim(str));

	str = " \f \n \r \t \v Hello World! \v \t \r \n \f";
	ASSERT_EQ("Hello World!", trim(str));
}
