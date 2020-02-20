#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "option_schema.h"

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
	params.validator = [](signed_ini_t i) { return true; };

	EXPECT_EQ(params.name, "name");
	EXPECT_EQ(params.requirement, item_requirement::optional);
	EXPECT_EQ(params.type, option_item::list);
	EXPECT_EQ(params.default_value, "default_value");
	EXPECT_EQ(params.comment, "comment");
	EXPECT_TRUE(params.validator(5));
}

TEST(option_schema, creation_and_copying)
{
	option_schema_params<signed_ini_t> params;
	params.name = "name";
	option_schema_params<unsigned_ini_t> other_params;
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
	params.validator = [](signed_ini_t i) { return true; };

	option_schema my_option(params);

	EXPECT_EQ(my_option.get_name(), "name");
	EXPECT_FALSE(my_option.is_mandatory());
	EXPECT_TRUE(my_option.holds_type<signed_ini_t>());
	EXPECT_TRUE(my_option.is_list());
	EXPECT_EQ(my_option.get_default_value(), "default_value");
	EXPECT_EQ(my_option.get_comment(), "comment");
}

TEST(option_schema, type_deduction)
{
	option_schema_params<signed_ini_t> signed_params;
	option_schema signed_option(signed_params);
	EXPECT_TRUE(signed_option.holds_type<signed_ini_t>());

	option_schema_params<unsigned_ini_t> unsigned_params;
	option_schema unsigned_option(unsigned_params);
	EXPECT_TRUE(unsigned_option.holds_type<unsigned_ini_t>());

	option_schema_params<boolean_ini_t> boolean_params;
	option_schema boolean_option(boolean_params);
	EXPECT_TRUE(boolean_option.holds_type<boolean_ini_t>());

	option_schema_params<string_ini_t> string_params;
	option_schema string_option(string_params);
	EXPECT_TRUE(string_option.holds_type<string_ini_t>());

	option_schema_params<float_ini_t> float_params;
	option_schema float_option(float_params);
	EXPECT_TRUE(float_option.holds_type<float_ini_t>());

	option_schema_params<enum_ini_t> enum_params;
	option_schema enum_option(enum_params);
	EXPECT_TRUE(enum_option.holds_type<enum_ini_t>());
}

TEST(option_schema, validation)
{
	// single value
	option signed_option("name", "-45");
	option_schema_params<signed_ini_t> signed_params;
	signed_params.name = "name";
	signed_params.type = option_item::single;
	signed_params.validator = [](signed_ini_t i) { return i < 5; };

	option_schema signed_schema(signed_params);
	EXPECT_NO_THROW(signed_schema.validate_option(signed_option));
	EXPECT_EQ(signed_option.get<signed_ini_t>(), -45);

	signed_params.validator = [](signed_ini_t i) { return i > 0; };
	option_schema validator_fail_schema(signed_params);
	EXPECT_THROW(validator_fail_schema.validate_option(signed_option), validation_exception);

	signed_option.set<string_ini_t>("63");
	EXPECT_THROW(signed_schema.validate_option(signed_option), validation_exception);

	// list value
	option float_option("name", "");
	std::vector<string_ini_t> string_values{"4.5", "-6.3", "0.0"};
	float_option.set_list(string_values);
	option_schema_params<float_ini_t> float_params;
	float_params.name = "name";
	float_params.type = option_item::list;
	float_params.validator = [](float_ini_t i) { return i < 5.2 && i > -81.1; };

	option_schema float_schema(float_params);
	EXPECT_NO_THROW(float_schema.validate_option(float_option));
	std::vector<float_ini_t> float_values{4.5, -6.3, 0.0};
	EXPECT_EQ(float_option.get_list<float_ini_t>(), float_values);
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
	params.validator = [](signed_ini_t i) { return true; };
	option_schema my_option(params);

	str << my_option;

	std::string expected_output = ";comment\n"
								  ";multiline\n"
								  ";<optional, list>\n"
								  ";<default value: \"default_value\">\n"
								  "name = default_value\n";
	EXPECT_EQ(str.str(), expected_output);
}
