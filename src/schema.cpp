#include "schema.h"

namespace inicpp
{
	schema::schema()
	{
		throw not_implemented_exception();
	}

	schema::schema(const schema &source)
	{
		throw not_implemented_exception();
	}

	schema& schema::operator=(const schema &source)
	{
		throw not_implemented_exception();
	}

	schema::schema(schema &&source)
	{
		throw not_implemented_exception();
	}

	schema& schema::operator=(schema &&source)
	{
		throw not_implemented_exception();
	}

	void schema::add_section(const section_schema &sect_schema)
	{
		throw not_implemented_exception();
	}

	void schema::add_section(const std::string &section_name, bool mandatory)
	{
		throw not_implemented_exception();
	}

	void schema::add_option(const std::string &section_name, const option_schema &opt_schema)
	{
		throw not_implemented_exception();
	}

	void schema::add_option(const option_schema_params &arguments)
	{
		throw not_implemented_exception();
	}

	bool schema::validate(const config &cfg, schema_mode mode)
	{
		throw not_implemented_exception();
	}

	std::ostream &schema::operator<<(std::ostream &os)
	{
		throw not_implemented_exception();
	}
}
