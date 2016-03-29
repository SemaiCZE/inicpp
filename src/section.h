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

		friend class section_iterator<option>;
		friend class section_iterator<const option>;

	public:
		typedef section_iterator<option> iterator;
		typedef section_iterator<const option> const_iterator;

		section();
		section(const section &source);
		section& operator=(const section &source);
		section(section &&source);
		section& operator=(section &&source);
		
		template<typename ValueType> void add_option(const std::string &name, const ValueType &value)
		{
			throw not_implemented_exception();
		}
		void add_option(const option &opt);

		const std::vector<option> &get_options();
		option &operator[](size_t index);
		option &operator[](const std::string &option_name);

		std::ostream &operator<<(std::ostream &os);

		iterator begin();
		iterator end();
		const_iterator cbegin();
		const_iterator cend();
	};
}

#endif
