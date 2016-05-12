#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "config.h"
#include "section.h"
#include <vector>

using namespace inicpp;


TEST(config_iterator, construction_and_copying)
{
	config conf;
	conf.add_section("sect1");
	conf.add_section("sect2");
	conf.add_section("sect3");

	// basic constructor
	config_iterator<section> it(conf, 0);
	config_iterator<section> it_beg(conf);
	EXPECT_EQ(it, it_beg);

	// copy constructor + assignment
	config_iterator<section> copy_it(it);
	config_iterator<section> copy_it_assignment = it;
	EXPECT_EQ(copy_it, copy_it_assignment);

	// move constructor + assignment
	config_iterator<section> move_it(std::move(copy_it));
	config_iterator<section> move_it_assignment = std::move(copy_it_assignment);
	EXPECT_EQ(move_it, move_it_assignment);
}

TEST(config_iterator, incrementation)
{
	config conf;
	conf.add_section("sect1");
	conf.add_section("sect2");
	conf.add_section("sect3");
	config_iterator<section> it(conf, 0);

	EXPECT_EQ(it->get_name(), "sect1");
	EXPECT_EQ((*it).get_name(), "sect1");
	auto postinc_value = it++;
	EXPECT_EQ(postinc_value->get_name(), "sect1");
	EXPECT_EQ(it->get_name(), "sect2");
	auto preinc_value = ++it;
	EXPECT_EQ(preinc_value->get_name(), "sect3");
}

TEST(config_iterator, equality_operator)
{
	config conf;
	conf.add_section("sect1");
	conf.add_section("sect2");
	conf.add_section("sect3");
	config_iterator<section> it1(conf, 0);
	config_iterator<section> it2(conf, 0);
	EXPECT_EQ(it1, it1);
	EXPECT_EQ(it1, it2);
	++it1;
	++it2;
	EXPECT_EQ(it1, it2);
	++it2;
	EXPECT_NE(it1, it2);
}
