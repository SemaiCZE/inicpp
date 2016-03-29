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

		static config load(const std::string &str);
		static config load(std::istream str);
		static config load(std::istream str, const schema &schm, const schema_mode &md);

		static config load_file(const std::string &file);
		static config load_file(const std::string &file, const schema &schm, const schema_mode &md);

		static void save(const config &cfg, const std::string &file);
		static void save(const config &cfg, std::ostream str);
		static void save(const schema &schm, const std::string &file);
		static void save(const schema &schm, std::ostream file);
	};
}

#endif
