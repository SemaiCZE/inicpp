#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "section.h"

using namespace inicpp;


TEST(section, creation_and_assignments)
{
	section sect("section name");
	EXPECT_EQ(sect.get_name(), "section name");

	// copy constructor and assignment
	section copy_constructed(sect);
	EXPECT_EQ(copy_constructed.get_name(), sect.get_name());
	section copy_assigned = sect;
	EXPECT_EQ(copy_assigned.get_name(), sect.get_name());

	// move constructor and assignment
	section move_constructed(std::move(copy_constructed));
	EXPECT_EQ(move_constructed.get_name(), sect.get_name());
	section move_assigned = std::move(copy_assigned);
	EXPECT_EQ(move_assigned.get_name(), sect.get_name());
}

TEST(section, adding_and_removing_options)
{
	section sect("name");
	EXPECT_EQ(sect.size(), 0u);
	sect.add_option("opt_key", "value");
	EXPECT_EQ(sect.size(), 1u);
	EXPECT_EQ(sect[0].get_name(), "opt_key");
	option opt("opt2", "12");
	sect.add_option(opt);
	EXPECT_EQ(sect.size(), 2u);
	EXPECT_EQ(sect[1].get_name(), "opt2");
	EXPECT_EQ(sect["opt2"].get_name(), "opt2");
	sect.remove_option("opt_key");
	EXPECT_EQ(sect.size(), 1u);
	EXPECT_EQ(sect[0].get_name(), "opt2");
}

TEST(section, iterators)
{
	section sect("name");
	EXPECT_EQ(sect.begin(), sect.end());
	EXPECT_EQ(sect.cbegin(), sect.cend());
	sect.add_option("opt_key", "value");
	auto it = sect.begin();
	EXPECT_EQ(it->get_name(), "opt_key");
	EXPECT_EQ(++it, sect.end());
	auto cit = sect.cbegin();
	EXPECT_EQ(cit->get_name(), "opt_key");
	EXPECT_EQ(++cit, sect.cend());
}

TEST(section, validation)
{
	// TODO:
}

TEST(section, stream_output)
{
	section sect("section name");
	std::ostringstream str;
	str << sect;
	EXPECT_EQ(str.str(), "[section name]\n");

	// write containing options too
	str.str("");
	sect.add_option("opt_name", "opt_value");
	sect.add_option("key", "value");
	str << sect;
	EXPECT_EQ(str.str(), "[section name]\nopt_name = opt_value\nkey = value\n");
}
