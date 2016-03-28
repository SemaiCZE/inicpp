#ifndef INICPP_SECTION_H
#define INICPP_SECTION_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "option.h"

namespace inicpp
{
	class section
	{
	private:
		std::vector<option> options_;
		bool name_;
		std::string comment_;

	public:
		section();
		section(const section &src);
		section& operator=(const section &source);
		section(section &&src);
		section& operator=(section &&source);
		
		template<ValueType> void add_option(std::string name, ValueType value);
		void add_option(const option &option);

		const std::vector<option> &get_options();
		option &operator[](size_t index);

		std::ostream& operator<<(std::ostream& os);

		// TODO: iterators
	};
}

#endif
