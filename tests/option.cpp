#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "option.h"
#include "types.h"
#include <vector>

using namespace std::literals;
using namespace inicpp;


/**
 * Create @ref option with single @ref string_t type and get some values.
 */
TEST(option, simple_option_class)
{
	option string_option("name of option", "simple value");
	EXPECT_EQ(string_option.get_name(), "name of option");
	EXPECT_FALSE(string_option.is_list());
	EXPECT_EQ(string_option.get<string_ini_t>(), "simple value");
	EXPECT_THROW(string_option.get<float_ini_t>(), bad_cast_exception);
	EXPECT_EQ(string_option.get_list<string_ini_t>(), std::vector<string_ini_t>{"simple value"});
}

/**
 * Create @ref option with list of @ref string_t types and get some values.
 */
TEST(option, option_list_creation)
{
	std::vector<std::string> values = {"value1", "value2"};
	option string_option("name of option", values);
	EXPECT_EQ(string_option.get_name(), "name of option");
	EXPECT_TRUE(string_option.is_list());
	EXPECT_EQ(string_option.get<string_ini_t>(), "value1");
	EXPECT_EQ(string_option.get_list<string_ini_t>(), values);
}

/**
 * Test adding and removing items to/from an option. Assert that all items
 * in list are of the same type.
 */
TEST(option, value_list_manipulation)
{
	option string_option("name of option", "simple value");
	EXPECT_FALSE(string_option.is_list());
	string_option.add_to_list<string_ini_t>("value 2");
	EXPECT_TRUE(string_option.is_list());
	std::vector<string_ini_t> expected_result = {"simple value", "value 2"};
	EXPECT_EQ(string_option.get_list<string_ini_t>(), expected_result);
	EXPECT_THROW(string_option.add_to_list<unsigned_ini_t>(2u), bad_cast_exception);
	string_option.add_to_list<string_ini_t>("last value", 1);
	expected_result.insert(++expected_result.begin(), "last value");
	EXPECT_EQ(string_option.get_list<string_ini_t>(), expected_result);

	EXPECT_THROW(string_option.remove_from_list<unsigned_ini_t>(2u), bad_cast_exception);
	string_option.remove_from_list_pos(0);
	expected_result.erase(expected_result.begin());
	EXPECT_EQ(string_option.get_list<string_ini_t>(), expected_result);
	string_option.remove_from_list<string_ini_t>("last value");
	expected_result.clear();
	expected_result.push_back("value 2");
	EXPECT_EQ(string_option.get_list<string_ini_t>(), expected_result);
	EXPECT_FALSE(string_option.is_list());
	EXPECT_EQ(string_option.get<string_ini_t>(), "value 2");
}

/**
 * Test setting values to an option, including type change. Also test
 * overloads of assignment operator.
 */
TEST(option, setting_values)
{
	// Single values
	option my_option("name", "value");
	my_option.set<double_t>(5.2f);
	EXPECT_EQ(my_option.get<double_t>(), 5.2f);
	my_option.set<boolean_ini_t>(true);
	EXPECT_TRUE(my_option.get<boolean_ini_t>());
	// struct custom_type { int a, b; } instance {4, 5};
	// EXPECT_THROW(my_option.set<custom_type>(instance), bad_cast_exception);

	// assignmet operators
	my_option = "string"s;
	EXPECT_EQ(my_option.get<string_ini_t>(), "string");
	my_option = false;
	EXPECT_FALSE(my_option.get<boolean_ini_t>());
	my_option = (signed_ini_t) -56;
	EXPECT_EQ(my_option.get<signed_ini_t>(), -56);
	my_option = (unsigned_ini_t) 789u;
	EXPECT_EQ(my_option.get<unsigned_ini_t>(), 789u);
	my_option = (float_ini_t) 25.6;
	EXPECT_EQ(my_option.get<float_ini_t>(), 25.6);

	// vector types
	std::vector<signed_ini_t> values = {5, 6, 8, 9};
	my_option.set_list<signed_ini_t>(values);
	EXPECT_EQ(my_option.get_list<signed_ini_t>(), values);
}

/**
 * Test various ways of copying the option - copy and move constructors,
 * assignments operators.
 */
TEST(option, copying)
{
	option my_option("name", "value");

	// copy constructor
	option copied(my_option);
	EXPECT_EQ(copied.get_name(), my_option.get_name());
	EXPECT_EQ(copied.get<string_ini_t>(), my_option.get<string_ini_t>());

	// move constructor
	option moved(std::move(copied));
	EXPECT_EQ(moved.get_name(), my_option.get_name());
	EXPECT_EQ(moved.get<string_ini_t>(), my_option.get<string_ini_t>());

	// copy assignment
	option copied_assingment("other name", "different value");
	copied_assingment = my_option;
	EXPECT_EQ(copied_assingment.get_name(), my_option.get_name());
	EXPECT_EQ(copied_assingment.get<string_ini_t>(), my_option.get<string_ini_t>());

	// move assignment
	option moved_assignment("other name", "different value");
	moved_assignment = std::move(copied_assingment);
	EXPECT_EQ(moved_assignment.get_name(), my_option.get_name());
	EXPECT_EQ(moved_assignment.get<string_ini_t>(), my_option.get<string_ini_t>());
}

/**
 * Test format of output stream.
 */
TEST(option, writing_to_stream)
{
	option my_option("name", "value");
	std::ostringstream str;

	// string
	str << my_option;
	EXPECT_EQ(str.str(), "name = value\n");

	// signed
	str.str("");
	my_option.set<signed_ini_t>(-89);
	str << my_option;
	EXPECT_EQ(str.str(), "name = -89\n");

	// unsigned
	str.str("");
	my_option.set<unsigned_ini_t>(42);
	str << my_option;
	EXPECT_EQ(str.str(), "name = 42\n");

	// float
	str.str("");
	my_option.set<float_ini_t>(52.4);
	str << my_option;
	EXPECT_EQ(str.str(), "name = 52.4\n");

	// boolean
	str.str("");
	my_option.set<boolean_ini_t>(true);
	str << my_option;
	EXPECT_EQ(str.str(), "name = yes\n");

	// enum
	str.str("");
	enum_ini_t en("enum_value");
	my_option.set<enum_ini_t>(en);
	str << my_option;
	EXPECT_EQ(str.str(), "name = enum_value\n");

	// string list
	str.str("");
	my_option.set_list<string_ini_t>({"option 1", "option 2"});
	str << my_option;
	EXPECT_EQ(str.str(), "name = option 1,option 2\n");
}
