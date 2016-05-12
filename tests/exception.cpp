#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exception.h"

// import literals
// we use string operator "" s() - the 's' suffix
// of const char * string makes it std::string. For example:
// auto str = "hello"s;
// str variable is std::string type. This needs C++14 support.
using namespace std::literals;
using namespace inicpp;


TEST(exceptions, generic)
{
	exception ex;
	EXPECT_EQ(ex.what(), "Generic inicpp exception"s);
	exception ex_init("text");
	EXPECT_EQ(ex_init.what(), "text"s);
}

TEST(exceptions, parser)
{
	parser_exception ex("message");
	EXPECT_EQ(ex.what(), "message"s);
}

TEST(exceptions, bad_cast)
{
	bad_cast_exception ex_init("text");
	EXPECT_EQ(ex_init.what(), "text"s);
	bad_cast_exception ex_from_to("integer", "boolean");
	EXPECT_EQ(ex_from_to.what(), "Bad conversion from: integer to: boolean"s);
}

TEST(exceptions, not_found)
{
	not_found_exception ex(5);
	EXPECT_EQ(ex.what(), "Element on index: 5 was not found"s);
	not_found_exception ex_name("name");
	EXPECT_EQ(ex_name.what(), "Element: name not found in container"s);
}

TEST(exceptions, ambiguity)
{
	ambiguity_exception ex("elname");
	EXPECT_EQ(ex.what(), "Ambiguous element with name: elname"s);
}

TEST(exceptions, validation)
{
	validation_exception ex("message");
	EXPECT_EQ(ex.what(), "message"s);
}

TEST(exceptions, invalid_type)
{
	invalid_type_exception ex("message");
	EXPECT_EQ(ex.what(), "message"s);
}

TEST(exceptions, not_implemented)
{
	not_implemented_exception ex;
	EXPECT_EQ(ex.what(), "Not implemented"s);
}
