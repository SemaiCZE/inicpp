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
		option(const option &source);
		option &operator=(const option &source);
		option(option &&source);
		option &operator=(option &&source);

		template<typename ValueType> void set(ValueType value);
		template<typename ValueType> ValueType get();
		template<typename ValueType> std::vector<ValueType> get_list();

		std::ostream &operator<<(std::ostream &os);
		
		bool is_list();
	};
}

#endif
