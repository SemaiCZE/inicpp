#ifndef INICPP_SECTION_H
#define INICPP_SECTION_H

#include <vector>
#include <iostream>
#include <iterator>

#include "exception.h"
#include "option.h"
#include "section_iterator.h"

namespace inicpp
{
	class section
	{
	private:
		std::vector<option> options_;
		bool name_;

		friend class section_iterator;

	public:
		typedef section_iterator iterator;
		typedef const_section_iterator const_iterator;

		section();
		section(const section &source);
		section& operator=(const section &source);
		section(section &&source);
		section& operator=(section &&source);
		
		template<ValueType> void add_option(std::string name, ValueType value);
		void add_option(const option &opt);

		const std::vector<option> &get_options();
		option &operator[](size_t index);

		std::ostream& operator<<(std::ostream& os);
	};
}

#endif
