#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/section_schema.h"

using namespace inicpp;


TEST(section_schema, sections_schema_params)
{
	section_schema_params params;

	EXPECT_EQ(params.name, "");
	EXPECT_EQ(params.requirement, item_requirement::mandatory);
	EXPECT_EQ(params.comment, "");

	params.name = "name";
	params.requirement = item_requirement::optional;
	params.comment = "comment";

	EXPECT_EQ(params.name, "name");
	EXPECT_EQ(params.requirement, item_requirement::optional);
	EXPECT_EQ(params.comment, "comment");
}

TEST(section_schema, creation_and_copying)
{
	section_schema_params params;
	params.name = "name";
	section_schema_params other_params;

	section_schema my_section(params);

	// copy constructor
	section_schema copied(my_section);
	EXPECT_EQ(copied.get_name(), my_section.get_name());

	// move constructor
	section_schema moved(std::move(copied));
	EXPECT_EQ(moved.get_name(), my_section.get_name());

	// copy assignment
	section_schema copied_assingment(other_params);
	copied_assingment = my_section;
	EXPECT_EQ(copied_assingment.get_name(), my_section.get_name());

	// move assignment
	section_schema moved_assignment(other_params);
	moved_assignment = std::move(copied_assingment);
	EXPECT_EQ(moved_assignment.get_name(), my_section.get_name());
}

TEST(section_schema, querying_properties)
{
	section_schema_params params;
	params.name = "name";
	params.requirement = item_requirement::optional;
	params.comment = "comment";

	section_schema my_section(params);

	EXPECT_EQ(my_section.get_name(), "name");
	EXPECT_FALSE(my_section.is_mandatory());
	EXPECT_EQ(my_section.get_comment(), "comment");
}

TEST(section_schema, adding_and_removing_options)
{
	section_schema_params params;
	params.name = "section";
	section_schema my_section(params);

	option_schema_params<signed_ini_t> opt_params;
	opt_params.name = "name";
	opt_params.requirement = item_requirement::optional;
	opt_params.type = option_item::list;
	opt_params.default_value = "default_value";
	opt_params.comment = "comment";
	opt_params.validator = [](signed_ini_t i){ return true; };
	option_schema my_option(opt_params);

	EXPECT_NO_THROW(my_section.add_option(my_option));
	EXPECT_THROW(my_section.add_option(my_option), ambiguity_exception);

	opt_params.name ="other";
	EXPECT_NO_THROW(my_section.add_option(opt_params));

	EXPECT_THROW(my_section.remove_option("unknown name"), not_found_exception);
	EXPECT_NO_THROW(my_section.remove_option(my_option.get_name()));
	EXPECT_NO_THROW(my_section.remove_option(opt_params.name));
}

TEST(section_schema, validation)
{
	//TODO:
}

TEST(section_schema, writing_to_ostream)
{
	std::ostringstream str;
	section_schema_params params;
	params.name = "name";
	params.requirement = item_requirement::optional;
	params.comment = "comment\nmultiline";
	section_schema my_section(params);

	str << my_section;

	std::string expected_output =
		";comment\n"
		";multiline\n"
		"[name] ;optional\n"
		"opt_name = default_value\n";
	EXPECT_EQ(str.str(), expected_output);
}
