#include "parser.h"

namespace inicpp
{
	static config parser::load(const std::string &str)
	{
		throw not_implemented_exception();
	}

	config parser::load(std::istream str)
	{
		throw not_implemented_exception();
	}

	static config parser::load(std::istream str, const schema &schm, const schema_mode &md)
	{
		throw not_implemented_exception();
	}

	static config parser::load_file(const std::string &file)
	{
		throw not_implemented_exception();
	}

	static config parser::load_file(const std::string &file, const schema &schm, const schema_mode &md)
	{
		throw not_implemented_exception();
	}

	static void parser::save(const config &cfg, const std::string &file)
	{
		throw not_implemented_exception();
	}

	static void parser::save(const config &cfg, std::ostream str)
	{
		throw not_implemented_exception();
	}

	static void parser::save(const schema &schm, const std::string &file)
	{
		throw not_implemented_exception();
	}

	static void parser::save(const schema &schm, std::ostream file)
	{
		throw not_implemented_exception();
	}
}
