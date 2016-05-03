#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/option_schema.h"

using namespace inicpp;


TEST(option_schema, options_schema_params)
{
	option_schema_params<signed_ini_t> params;

	EXPECT_EQ(params.name, "");
	EXPECT_EQ(params.requirement, item_requirement::mandatory);
	EXPECT_EQ(params.type, option_item::single);
	EXPECT_EQ(params.default_value, "");
	EXPECT_EQ(params.comment, "");
	EXPECT_EQ(params.validator, nullptr);

	params.name = "name";
	params.requirement = item_requirement::optional;
	params.type = option_item::list;
	params.default_value = "default_value";
	params.comment = "comment";
	params.validator = [](signed_ini_t i){ return true; };

	EXPECT_EQ(params.name, "name");
	EXPECT_EQ(params.requirement, item_requirement::optional);
	EXPECT_EQ(params.type, option_item::list);
	EXPECT_EQ(params.default_value, "default_value");
	EXPECT_EQ(params.comment, "comment");
	EXPECT_TRUE(params.validator(5));
}

TEST(option_schema, creation_and_copying)
{
	option_schema_params<int> params;
	params.name = "name";
	option_schema_params<char> other_params;

	option_schema my_option(params);

	// copy constructor
	option_schema copied(my_option);
	EXPECT_EQ(copied.get_name(), my_option.get_name());

	// move constructor
	option_schema moved(std::move(copied));
	EXPECT_EQ(moved.get_name(), my_option.get_name());

	// copy assignment
	option_schema copied_assingment(other_params);
	copied_assingment = my_option;
	EXPECT_EQ(copied_assingment.get_name(), my_option.get_name());

	// move assignment
	option_schema moved_assignment(other_params);
	moved_assignment = std::move(copied_assingment);
	EXPECT_EQ(moved_assignment.get_name(), my_option.get_name());
}

TEST(option_schema, querying_properties)
{
	option_schema_params<signed_ini_t> params;
	params.name = "name";
	params.requirement = item_requirement::optional;
	params.type = option_item::list;
	params.default_value = "default_value";
	params.comment = "comment";
	params.validator = [](signed_ini_t i){ return true; };

	option_schema my_option(params);

	EXPECT_EQ(my_option.get_name(), "name");
	EXPECT_FALSE(my_option.is_mandatory());
	EXPECT_EQ(my_option.get_type(), option_type::signed_e);
	EXPECT_TRUE(my_option.is_list());
	EXPECT_EQ(my_option.get_default_value(), "default_value");
	EXPECT_EQ(my_option.get_comment(), "comment");
}

TEST(option_schema, type_deduction)
{
	option_schema_params<signed_ini_t> signed_params;
	option_schema signed_option(signed_params);
	EXPECT_EQ(signed_option.get_type(), option_type::signed_e);

	option_schema_params<unsigned_ini_t> unsigned_params;
	option_schema unsigned_option(unsigned_params);
	EXPECT_EQ(unsigned_option.get_type(), option_type::unsigned_e);

	option_schema_params<boolean_ini_t> boolean_params;
	option_schema boolean_option(boolean_params);
	EXPECT_EQ(boolean_option.get_type(), option_type::boolean_e);

	option_schema_params<string_ini_t> string_params;
	option_schema string_option(string_params);
	EXPECT_EQ(string_option.get_type(), option_type::string_e);

	option_schema_params<float_ini_t> float_params;
	option_schema float_option(float_params);
	EXPECT_EQ(float_option.get_type(), option_type::float_e);

	// TODO: enum
}

TEST(option_schema, validation)
{
	//TODO:
}

TEST(option_schema, writing_to_ostream)
{
	std::ostringstream str;
	option_schema_params<signed_ini_t> params;
	params.name = "name";
	params.requirement = item_requirement::optional;
	params.type = option_item::list;
	params.default_value = "default_value";
	params.comment = "comment\nmultiline";
	params.validator = [](signed_ini_t i){ return true; };
	option_schema my_option(params);

	str << my_option;

	std::string expected_output =
		";comment\n"
		";multiline\n"
		"name = default_value ;optional\n";
	EXPECT_EQ(str.str(), expected_output);
}
