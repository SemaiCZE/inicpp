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