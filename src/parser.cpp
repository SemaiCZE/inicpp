#include "parser.h"

namespace inicpp
{
	config parser::load(std::string str)
	{
		throw not_implemented_exception();
	}

	config parser::load(std::istream str)
	{
		throw not_implemented_exception();
	}

	config parser::load(std::istream str, schema schm, schema_mode md)
	{
		throw not_implemented_exception();
	}

	config parser::load_file(std::string file)
	{
		throw not_implemented_exception();
	}

	config parser::load_file(std::string file, schema schm, schema_mode md)
	{
		throw not_implemented_exception();
	}

	void parser::save(config cfg, std::string file)
	{
		throw not_implemented_exception();
	}

	void parser::save(config cfg, std::ostream str)
	{
		throw not_implemented_exception();
	}

	void parser::save(schema schm, std::string file)
	{
		throw not_implemented_exception();
	}

	void parser::save(schema schm, std::ostream file)
	{
		throw not_implemented_exception();
	}
}
