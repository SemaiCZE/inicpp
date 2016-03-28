#ifndef INICPP_CONFIG_H
#define INICPP_CONFIG_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "section.h"
#include "option.h"

namespace inicpp
{
	class config
	{
	private:
		std::vector<section> sections_;

	public:
		config();
		config(const config &src);
		config& operator=(const config &source);
		config(config &&src);
		config& operator=(config &&source);

		void add_section(section schm);
		void add_section(std::string section_name);

		void add_option(std::string section_name, option schm);
		void add_option(std::string section_name, std::string option_name);

		const std::vector<section> &get_sections();
		section &operator[](size_t index);

		std::ostream& operator<<(std::ostream& os);

		// TODO iterators
	};
}

#endif
