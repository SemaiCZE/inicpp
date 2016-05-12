#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "config.h"
#include "option.h"
#include "section.h"

using namespace inicpp;


TEST(config, creation_and_assignments)
{
	config conf;

	// copy constructor and assignment
	config copy_constructed(conf);
	EXPECT_TRUE(copy_constructed == conf);
	config copy_assigned = conf;
	EXPECT_TRUE(copy_assigned == conf);

	// move constructor and assignment
	config move_constructed(std::move(copy_constructed));
	EXPECT_TRUE(move_constructed == conf);
	config move_assigned = std::move(copy_assigned);
	EXPECT_TRUE(move_assigned == conf);
}

TEST(config, adding_and_removing_sections)
{
	config conf;
	EXPECT_EQ(conf.size(), 0u);
	conf.add_section("sect_name");
	EXPECT_EQ(conf.size(), 1u);
	EXPECT_EQ(conf[0].get_name(), "sect_name");
	section sect("sect2");
	conf.add_section(sect);
	EXPECT_EQ(conf.size(), 2u);
	EXPECT_EQ(conf[1].get_name(), "sect2");
	EXPECT_EQ(conf["sect2"].get_name(), "sect2");
	conf.remove_section("sect_name");
	EXPECT_EQ(conf.size(), 1u);
	EXPECT_EQ(conf[0].get_name(), "sect2");
}

TEST(config, adding_and_removing_options)
{
	config conf;
	conf.add_section("sect");
	EXPECT_EQ(conf["sect"].size(), 0u);
	conf.add_option<string_ini_t>("sect", "opt_key", "value");
	EXPECT_EQ(conf["sect"].size(), 1u);
	EXPECT_EQ(conf["sect"][0].get_name(), "opt_key");
	option opt("opt2", "12");
	conf.add_option("sect", opt);
	EXPECT_EQ(conf["sect"].size(), 2u);
	EXPECT_EQ(conf["sect"][1].get_name(), "opt2");
	conf.remove_option("sect", "opt_key");
	EXPECT_EQ(conf["sect"].size(), 1u);
	EXPECT_EQ(conf["sect"][0].get_name(), "opt2");
}

TEST(config, iterators)
{
	config conf;
	EXPECT_EQ(conf.begin(), conf.end());
	EXPECT_EQ(conf.cbegin(), conf.cend());
	conf.add_section("sect_name");
	auto it = conf.begin();
	EXPECT_EQ(it->get_name(), "sect_name");
	EXPECT_EQ(++it, conf.end());
	auto cit = conf.cbegin();
	EXPECT_EQ(cit->get_name(), "sect_name");
	EXPECT_EQ(++cit, conf.cend());
}

TEST(config, stream_output)
{
	config conf;
	std::ostringstream str;
	str << conf;
	EXPECT_EQ(str.str(), "");

	// write containing sections
	str.str("");
	conf.add_section("sect_name");
	conf.add_section("name2");
	str << conf;
	EXPECT_EQ(str.str(), "[sect_name]\n[name2]\n");
}
