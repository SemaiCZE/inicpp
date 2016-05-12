#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "types.h"


using namespace inicpp;


TEST(types, get_option_enum_type)
{
	EXPECT_EQ(get_option_enum_type<boolean_ini_t>(), option_type::boolean_e);
	EXPECT_EQ(get_option_enum_type<enum_ini_t>(), option_type::enum_e);
	EXPECT_EQ(get_option_enum_type<float_ini_t>(), option_type::float_e);
	EXPECT_EQ(get_option_enum_type<signed_ini_t>(), option_type::signed_e);
	EXPECT_EQ(get_option_enum_type<unsigned_ini_t>(), option_type::unsigned_e);
	EXPECT_EQ(get_option_enum_type<string_ini_t>(), option_type::string_e);
	EXPECT_EQ(get_option_enum_type<const char *>(), option_type::invalid_e);
}
