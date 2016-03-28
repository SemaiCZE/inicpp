#ifndef INICPP_SCHEMA_H
#define INICPP_SCHEMA_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "section_schema.h"
#include "option_schema.h"

namespace inicpp
{
	class schema
	{
	private:
		std::vector<section_schema> sections_;

	public:
		schema();
		schema(const schema &src);
		schema& operator=(const schema &source);
		schema(schema &&src);
		schema& operator=(schema &&source);

		void add_section(section_schema schm);
		void add_section(std::string section_name);

		void add_option(std::string section_name, const option_schema &schm);
		void add_option(std::string section_name, std::string option_name);

		std::ostream& operator<<(std::ostream& os);
	};
}

#endif
