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
		bool is_list_;
		std::string value_;
		// TODO: access methods for private members

	public:
		option();
		option(const option &source);
		option &operator=(const option &source);
		option(option &&source);
		option &operator=(option &&source);

		option(const std::string &name, bool is_list = false, const std::string &value = "");

		template<typename ValueType> void set(ValueType value)
		{
			throw not_implemented_exception();
		}
		template<typename ValueType> ValueType get() const
		{
			throw not_implemented_exception();
		}

		template<typename ValueType> void set_list(const std::vector<ValueType> &value)
		{
			throw not_implemented_exception();
		}
		template<typename ValueType> std::vector<ValueType> get_list() const
		{
			throw not_implemented_exception();
		}

		template<typename ValueType> void add_to_list(ValueType value)
		{
			throw not_implemented_exception();
		}

		std::ostream &operator<<(std::ostream &os);

		bool is_list() const;
	};
}

#endif
