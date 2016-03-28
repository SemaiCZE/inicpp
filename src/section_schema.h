#ifndef INICPP_SECTION_SCHEMA_H
#define INICPP_SECTION_SCHEMA_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "option_schema.h"

namespace inicpp
{
	class section_schema
	{
	private:
		std::vector<option_schema> options_;
		bool mandatory_;

	public:
		section_schema();
		section_schema(const section_schema &src);
		section_schema& operator=(const section_schema &source);
		section_schema(section_schema &&src);
		section_schema& operator=(section_schema &&source);

		void add_option(std::string option_name);
		void add_option(const &option_schema option);

		std::ostream& operator<<(std::ostream& os);
	};
}

#endif
