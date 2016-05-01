#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/exception.h"

using namespace inicpp;


TEST(exceptions, generic)
{
	exception ex;
	EXPECT_EQ(ex.what(), std::string("Generic inicpp exception"));
	exception ex_init("text");
	EXPECT_EQ(ex_init.what(), std::string("text"));
}

TEST(exceptions, bad_cast)
{
	bad_cast_exception ex_init("text");
	EXPECT_EQ(ex_init.what(), std::string("text"));
	bad_cast_exception ex_from_to("integer", "boolean");
	EXPECT_EQ(ex_from_to.what(), std::string("Bad conversion from: integer to: boolean"));
}

TEST(exceptions, not_found)
{
	not_found_exception ex(5);
	EXPECT_EQ(ex.what(), std::string("Element on index: 5 was not found"));
	not_found_exception ex_name("name");
	EXPECT_EQ(ex_name.what(), std::string("Element: name not found in container"));
}

TEST(exceptions, ambiguity)
{
	ambiguity_exception ex("elname");
	EXPECT_EQ(ex.what(), std::string("Ambiguous element with name: elname"));
}

TEST(exceptions, validation)
{
	validation_exception ex("message");
	EXPECT_EQ(ex.what(), std::string("message"));
}

TEST(exceptions, invalid_config)
{
	invalid_config_exception ex("message");
	EXPECT_EQ(ex.what(), std::string("message"));
}

TEST(exceptions, not_implemented)
{
	not_implemented_exception ex;
	EXPECT_EQ(ex.what(), std::string("Not implemented"));
}
