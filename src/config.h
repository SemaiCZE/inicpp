#ifndef INICPP_CONFIG_H
#define INICPP_CONFIG_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "section.h"
#include "option.h"

namespace inicpp
{
	class config {};

	class config_iterator : public std::iterator<std::random_access_iterator_tag, option>
	{
	private:
		friend class config;
		const config &container_;
		size_t pos_;
	public:
		config_iterator(const section &source) : container_(source) {}
		config_iterator(const config_iterator& source) : container_(source.container_), pos_(source.pos_) {}

		config_iterator& operator++() { ++pos_; return *this; }
		config_iterator operator++(int) { config_iterator old(*this); operator++(); return old; }

		bool operator==(const config_iterator &second) { return pos_ == second.pos_; }
		bool operator!=(const config_iterator &second) { return pos_ != second.pos_; }

		reference operator*() { return container_.sections_.at(pos_); }
	};


	class config
	{
	private:
		std::vector<section> sections_;

	public:
		typedef config_iterator iterator;

		config();
		config(const config &src);
		config& operator=(const config &source);
		config(config &&src);
		config& operator=(config &&source);

		void add_section(section sect);
		void add_section(std::string section_name);

		void add_option(std::string section_name, option opt_schema);
		void add_option(std::string section_name, std::string option_name);

		const std::vector<section> &get_sections();
		section &operator[](size_t index);

		std::ostream& operator<<(std::ostream& os);
		std::ostream& operator>>(std::ostream& os);
	};
}

#endif
