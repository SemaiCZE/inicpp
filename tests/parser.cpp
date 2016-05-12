#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "parser.h"

using namespace inicpp;

/*
 * In tests of parser, we won't make sure every possible situation is handled
 * right. Instead, these tests will test basic functionality as the whole
 * (so technically this isn't unit test, but some kind of integration test).
 * All corner cases are tested separated by belonging class.
 */

TEST(parser, load_config)
{
	EXPECT_THROW(parser::load_file("nonexisting_file.txt"), parser_exception);

	std::string str_config = ""
							 "[section]\n"
							 "opt = val\n"
							 "opt2 = val2, val3, val4\n"
							 "; other comment\n"
							 "[section2::a] ;with comment\n"
							 "link = ${section#opt}";
	auto loaded_config = parser::load(str_config);
	EXPECT_EQ(loaded_config.size(), 2u);
	EXPECT_EQ(loaded_config[0].get_name(), "section");
	EXPECT_EQ(loaded_config[1].get_name(), "section2::a");
	EXPECT_EQ(loaded_config[0].size(), 2u);
	EXPECT_EQ(loaded_config[1].size(), 1u);
	EXPECT_FALSE(loaded_config[0][0].is_list());
	EXPECT_TRUE(loaded_config[0][1].is_list());
	EXPECT_EQ(loaded_config[0][0].get_name(), "opt");
	EXPECT_EQ(loaded_config[0][1].get_name(), "opt2");
	EXPECT_EQ(loaded_config[0][0].get<string_ini_t>(), "val");
	std::vector<std::string> expected_list{"val2", "val3", "val4"};
	EXPECT_EQ(loaded_config[0][1].get_list<string_ini_t>(), expected_list);
	EXPECT_EQ(loaded_config[1][0].get<string_ini_t>(), "val");

	str_config = ""
				 "[section]\n"
				 "opt = 15";
	schema validatin_schema;

	// Following is not possible in MS Visual C++ yet
	// section_schema_params sect_params{ "section", item_requirement::mandatory, "comment" };
	section_schema_params sect_params;
	sect_params.name = "section";
	sect_params.requirement = item_requirement::mandatory;
	sect_params.comment = "comment";
	section_schema sect_schema(sect_params);

	option_schema_params<unsigned_ini_t> opt_params;
	opt_params.name = "opt";
	opt_params.requirement = item_requirement::mandatory;
	opt_params.type = option_item::single;
	sect_schema.add_option(opt_params);
	validatin_schema.add_section(sect_schema);

	config my_config;
	EXPECT_NO_THROW(my_config = parser::load(str_config, validatin_schema, schema_mode::strict));
	EXPECT_EQ(my_config["section"]["opt"].get<unsigned_ini_t>(), 15u);

	opt_params.name = "other name";
	option_schema opt_schema(opt_params);
	validatin_schema.add_option("section", opt_schema);
	EXPECT_THROW(parser::load(str_config, validatin_schema, schema_mode::strict), validation_exception);
}

TEST(parser, store_config)
{
	/*
	 * Storing confing and schema is just some call of << operator of given
	 * instance. Some of the instances could be mocked and tested, but it's
	 * quite overkill to do so much work including API changes (new interfaces)
	 * for testing oneliner method. Instead, interesting part is write given
	 * (partial) configuration and schema and the goal is to write values from
	 * config accompanied with default values of other options from schema.
	 */
	config my_config;
	my_config.add_section("section_name");
	my_config.add_option("section_name", "opt", "value");
	schema validatin_schema;

	// Following is not possible in MS Visual C++ yet
	// section_schema sect_schema({ "section_name", item_requirement::mandatory, "comment" });

	section_schema_params sect_params;
	sect_params.name = "section_name";
	sect_params.requirement = item_requirement::mandatory;
	sect_params.comment = "comment";
	section_schema sect_schema(sect_params);

	// Following will be possible in C++17
	// option_schema_params<string_ini_t> opt { {"opt", item_requirement::mandatory,
	//	option_item::single, "default value", "opt comment"}, nullptr};

	option_schema_params<string_ini_t> opt1;
	opt1.name = "opt";
	opt1.requirement = item_requirement::mandatory;
	opt1.type = option_item::single;
	opt1.default_value = "default value";
	opt1.comment = "opt comment";
	opt1.validator = nullptr;
	sect_schema.add_option(opt1);

	option_schema_params<unsigned_ini_t> opt2;
	opt2.name = "unsigned";
	opt2.requirement = item_requirement::optional;
	opt2.type = option_item::single;
	opt2.default_value = "42";
	opt2.comment = "unsigned comment";
	opt2.validator = nullptr;
	sect_schema.add_option(opt2);
	validatin_schema.add_section(sect_schema);

	std::ostringstream str;
	EXPECT_NO_THROW(parser::save(my_config, validatin_schema, str));
	std::string expected_result = ""
								  ";comment\n"
								  ";<mandatory>\n"
								  "[section_name]\n"
								  ";opt comment\n"
								  ";<mandatory, single>\n"
								  ";<default value: \"default value\">\n"
								  "opt = value\n"
								  ";unsigned comment\n"
								  ";<optional, single>\n"
								  ";<default value: \"42\">\n"
								  "unsigned = 42\n";
	EXPECT_EQ(str.str(), expected_result);
}
