#ifndef INICPP_OPTION_SCHEMA_H
#define INICPP_OPTION_SCHEMA_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "option_schema.h"
#include "option.h"
#include "option_type.h"

namespace inicpp
{
	class option_schema
	{
	private:
		std::string name_;
		option_type type_;
		std::string default_value_;
		bool mandatory_;
		// TODO: restriction function reference
		// TODO: access methods for private members

	public:
		option_schema();
		option_schema(const option_schema &src);
		option_schema& operator=(const option_schema &source);
		option_schema(option_schema &&src);
		option_schema& operator=(option_schema &&source);

		std::ostream& operator<<(std::ostream& os);
		
		bool is_list();
		
		bool is_valid(std::string str); // validate is probably better?
		bool is_valid(option opt);
	};
}

#endif
