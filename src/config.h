#ifndef INICPP_CONFIG_H
#define INICPP_CONFIG_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "section.h"
#include "option.h"
#include "config_iterator.h"


namespace inicpp
{
	class config
	{
	private:
		std::vector<section> sections_;

		friend class config_iterator<section>;
		friend class config_iterator<const section>;

	public:
		typedef config_iterator<section> iterator;
		typedef config_iterator<const section> const_iterator;

		config();
		config(const config &src);
		config& operator=(const config &source);
		config(config &&src);
		config& operator=(config &&source);

		void add_section(section sect);
		void add_section(const std::string &section_name);

		void add_option(const std::string &section_name, option opt_schema);
		void add_option(const std::string &section_name, const std::string &option_name);

		const std::vector<section> &get_sections();
		section &operator[](size_t index);
		section &operator[](const std::string &section_name);

		std::ostream &operator<<(std::ostream &os);

		iterator begin();
		iterator end();
		const_iterator cbegin();
		const_iterator cend();
	};
}

#endif
