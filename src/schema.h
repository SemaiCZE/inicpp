#ifndef INICPP_SCHEMA_H
#define INICPP_SCHEMA_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "section_schema.h"
#include "option_schema.h"

namespace inicpp
{
	enum schema_mode { strict, relaxed };

	class schema
	{
	private:
		std::vector<section_schema> sections_;

	public:
		schema();
		schema(const schema &source);
		schema& operator=(const schema &source);
		schema(schema &&source);
		schema& operator=(schema &&source);

		void add_section(section_schema sect_schema);
		void add_section(std::string section_name);

		void add_option(std::string section_name, const option_schema &opt_schema);
		void add_option(std::string section_name, std::string option_name);

		std::ostream& operator<<(std::ostream& os);
	};
}

#endif
