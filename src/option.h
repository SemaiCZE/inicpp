#ifndef INICPP_OPTION_H
#define INICPP_OPTION_H

#include <vector>
#include <iostream>

#include "exception.h"

namespace inicpp
{
	class option
	{
	private:
		std::string name_;
		std::string value_;
		// TODO: access methods for private members

	public:
		option();
		option(const option &src);
		option& operator=(const option &source);
		option(option &&src);
		option& operator=(option &&source);

		template<ValueType> void set(ValueType value);
		template<ValueType> ValueType get();
		template<ValueType> std::vector<ValueType> get_list();

		std::ostream& operator<<(std::ostream& os);
		
		bool is_list();
	};
}

#endif
