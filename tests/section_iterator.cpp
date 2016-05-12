#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "option.h"
#include "section.h"
#include <vector>

using namespace inicpp;
using namespace std::literals;


TEST(section_iterator, construction_and_copying)
{
	section sec("section name");
	sec.add_option("opt1", "value1");
	sec.add_option("opt2", "value2");
	sec.add_option("opt3", "value3");

	// basic constructor
	section_iterator<option> it(sec, 0);
	section_iterator<option> it_beg(sec);
	EXPECT_EQ(it, it_beg);

	// copy constructor + assignment
	section_iterator<option> copy_it(it);
	section_iterator<option> copy_it_assignment = it;
	EXPECT_EQ(copy_it, copy_it_assignment);

	// move constructor + assignment
	section_iterator<option> move_it(std::move(copy_it));
	section_iterator<option> move_it_assignment = std::move(copy_it_assignment);
	EXPECT_EQ(move_it, move_it_assignment);
}

TEST(section_iterator, incrementation)
{
	section sec("section name");
	sec.add_option("opt1", "value1");
	sec.add_option("opt2", "value2");
	sec.add_option("opt3", "value3");
	section_iterator<option> it(sec, 0);

	EXPECT_EQ(it->get_name(), "opt1");
	EXPECT_EQ((*it).get_name(), "opt1");
	auto postinc_value = it++;
	EXPECT_EQ(postinc_value->get_name(), "opt1");
	EXPECT_EQ(it->get_name(), "opt2");
	auto preinc_value = ++it;
	EXPECT_EQ(preinc_value->get_name(), "opt3");
}

TEST(section_iterator, equality_operator)
{
	section sec("section name");
	sec.add_option("opt1", "value1");
	sec.add_option("opt2", "value2");
	sec.add_option("opt3", "value3");
	section_iterator<option> it1(sec, 0);
	section_iterator<option> it2(sec, 0);
	EXPECT_EQ(it1, it1);
	EXPECT_EQ(it1, it2);
	++it1;
	++it2;
	EXPECT_EQ(it1, it2);
	++it2;
	EXPECT_NE(it1, it2);
}
