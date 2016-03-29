#ifndef INICPP_PARSER_H
#define INICPP_PARSER_H

#include <iostream>

#include "exception.h"
#include "config.h"
#include "schema.h"
#include "schema_mode.h"

namespace inicpp
{
	class parser
	{
	public:
		parser() = delete;
		parser(const parser &source) = delete;
		parser& operator=(const parser &source) = delete;
		parser(parser &&source) = delete;
		parser& operator=(parser &&source) = delete;

		config load(std::string str);
		config load(std::istream str);
		config load(std::istream str, schema schm, schema_mode md);

		config load_file(std::string file);
		config load_file(std::string file, schema schm, schema_mode md);

		void save(config cfg, std::string file);
		void save(config cfg, std::ostream str);
		void save(schema schm, std::string file);
		void save(schema schm, std::ostream file);
	};
}

#endif
