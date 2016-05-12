#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exception.h"
#include "string_utils.h"

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

TEST(string_utils, starts_with)
{
	string str = "";
	ASSERT_TRUE(starts_with(str, ""));

	str = " ";
	ASSERT_TRUE(starts_with(str, " "));

	str = "A";
	ASSERT_TRUE(starts_with(str, ""));

	str = "A";
	ASSERT_TRUE(starts_with(str, "A"));

	str = "ABCD";
	ASSERT_FALSE(starts_with(str, "BC"));

	str = "ABCD";
	ASSERT_FALSE(starts_with(str, "BCD"));

	str = " ABCD ";
	ASSERT_FALSE(starts_with(str, "ABCD"));

	str = "ABCD";
	ASSERT_FALSE(starts_with(str, "ABCDEFGH"));

	str = "Hello World!";
	ASSERT_TRUE(starts_with(str, "Hello"));

	str = "Hello World!";
	ASSERT_FALSE(starts_with(str, "World!"));
}

TEST(string_utils, ends_with)
{
	string str = "";
	ASSERT_TRUE(ends_with(str, ""));

	str = " ";
	ASSERT_TRUE(ends_with(str, " "));

	str = "A";
	ASSERT_TRUE(ends_with(str, ""));

	str = "A";
	ASSERT_TRUE(ends_with(str, "A"));

	str = "ABCD";
	ASSERT_FALSE(ends_with(str, "BC"));

	str = "ABCD";
	ASSERT_FALSE(ends_with(str, "ABC"));

	str = " ABCD ";
	ASSERT_FALSE(ends_with(str, "ABCD"));

	str = "ABCD";
	ASSERT_FALSE(ends_with(str, "ABCDEFGH"));

	str = "Hello World!";
	ASSERT_TRUE(ends_with(str, "World!"));

	str = "Hello World!";
	ASSERT_FALSE(ends_with(str, "Hello"));
}

TEST(string_utils, find_needle)
{
	string str = "";
	ASSERT_TRUE(find_needle(str, ""));

	str = "A";
	ASSERT_TRUE(find_needle(str, ""));

	str = "A";
	ASSERT_TRUE(find_needle(str, "A"));

	str = "ABCD";
	ASSERT_TRUE(find_needle(str, "BC"));

	str = "ABCD";
	ASSERT_FALSE(find_needle(str, "AD"));

	str = "ABCD";
	ASSERT_TRUE(find_needle(str, "ABCD"));

	str = "ABCD";
	ASSERT_FALSE(find_needle(str, "ABCDEFGH"));

	str = "ABCD=EFGH";
	ASSERT_TRUE(find_needle(str, "="));

	str = "Hello World!";
	ASSERT_TRUE(find_needle(str, "o W"));
}

TEST(string_utils, split)
{
	string str = "";
	std::vector<std::string> expected;

	ASSERT_EQ(expected, split(str, 0));

	str = ":";
	expected.resize(1);
	ASSERT_EQ(expected, split(str, ':'));

	str = "A:A";
	expected.resize(2);
	expected[0] = "A";
	expected[1] = "A";
	ASSERT_EQ(expected, split(str, ':'));

	str = "Hello World!";
	expected.resize(2);
	expected[0] = "Hello";
	expected[1] = "World!";
	ASSERT_EQ(expected, split(str, ' '));

	str = "This sentence will be splitted";
	expected.resize(5);
	expected[0] = "This";
	expected[1] = "sentence";
	expected[2] = "will";
	expected[3] = "be";
	expected[4] = "splitted";
	ASSERT_EQ(expected, split(str, ' '));

	str = " Multiple      delims  ";
	expected.resize(9);
	expected[0] = "";
	expected[1] = "Multiple";
	expected[2] = "";
	expected[3] = "";
	expected[4] = "";
	expected[5] = "";
	expected[6] = "";
	expected[7] = "delims";
	expected[8] = "";
	ASSERT_EQ(expected, split(str, ' '));
}

TEST(string_utils, parse_unsigned_number)
{
	EXPECT_EQ(string_utils::parse_string<unsigned_ini_t>("0b111", ""), 7u);
	EXPECT_EQ(string_utils::parse_string<unsigned_ini_t>("0x3C", ""), 60u);
	EXPECT_EQ(string_utils::parse_string<unsigned_ini_t>("5", ""), 5u);
	EXPECT_THROW(string_utils::parse_string<unsigned_ini_t>("random", ""), invalid_type_exception);
}

TEST(string_utils, parse_signed_number)
{
	EXPECT_EQ(string_utils::parse_string<signed_ini_t>("0b11110000", ""), 240);
	EXPECT_EQ(string_utils::parse_string<signed_ini_t>("0b111", ""), 7);
	EXPECT_EQ(string_utils::parse_string<signed_ini_t>("-0x3C", ""), -60);
	EXPECT_EQ(string_utils::parse_string<signed_ini_t>("-5", ""), -5);
	EXPECT_THROW(string_utils::parse_string<signed_ini_t>("random", ""), invalid_type_exception);
}

TEST(string_utils, parse_float_number)
{
	EXPECT_NEAR(string_utils::parse_string<float_ini_t>("3.14", ""), 3.14, 0.00001);
	EXPECT_NEAR(string_utils::parse_string<float_ini_t>("+4.1234565E+45", ""), 4.12346e+45, 1e+40);
	EXPECT_NEAR(string_utils::parse_string<float_ini_t>("-1.1245864E-6", ""), -1.1245864E-6, 1e-10);
	EXPECT_THROW(string_utils::parse_string<float_ini_t>("random", ""), invalid_type_exception);
}

TEST(string_utils, parse_boolean_value)
{
	EXPECT_TRUE(string_utils::parse_string<boolean_ini_t>("1", ""));
	EXPECT_TRUE(string_utils::parse_string<boolean_ini_t>("t", ""));
	EXPECT_TRUE(string_utils::parse_string<boolean_ini_t>("y", ""));
	EXPECT_TRUE(string_utils::parse_string<boolean_ini_t>("on", ""));
	EXPECT_TRUE(string_utils::parse_string<boolean_ini_t>("yes", ""));
	EXPECT_TRUE(string_utils::parse_string<boolean_ini_t>("enabled", ""));

	EXPECT_FALSE(string_utils::parse_string<boolean_ini_t>("0", ""));
	EXPECT_FALSE(string_utils::parse_string<boolean_ini_t>("f", ""));
	EXPECT_FALSE(string_utils::parse_string<boolean_ini_t>("n", ""));
	EXPECT_FALSE(string_utils::parse_string<boolean_ini_t>("off", ""));
	EXPECT_FALSE(string_utils::parse_string<boolean_ini_t>("no", ""));
	EXPECT_FALSE(string_utils::parse_string<boolean_ini_t>("disabled", ""));

	EXPECT_THROW(string_utils::parse_string<boolean_ini_t>("random", ""), invalid_type_exception);
}
