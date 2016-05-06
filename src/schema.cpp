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

	void schema::add_section(const section_schema_params &arguments)
	{
		throw not_implemented_exception();
	}

	void schema::add_option(const std::string &section_name, const option_schema &opt_schema)
	{
		throw not_implemented_exception();
	}

	size_t schema::size() const
	{
		return sections_.size();
	}

	section_schema &schema::operator[](size_t index)
	{
		throw not_implemented_exception();
	}

	const section_schema &schema::operator[](size_t index) const
	{
		throw not_implemented_exception();
	}

	section_schema &schema::operator[](const std::string &section_name)
	{
		throw not_implemented_exception();
	}

	const section_schema &schema::operator[](const std::string &section_name) const
	{
		throw not_implemented_exception();
	}

	bool schema::contains(const std::string &section_name) const
	{
		throw not_implemented_exception();
	}

	template<typename ArgType>
	void schema::add_option(const std::string &section_name, option_schema_params<ArgType> &arguments)
	{
		throw not_implemented_exception();
	}

	bool schema::validate_config(config &cfg, schema_mode mode) const
	{
		throw not_implemented_exception();
	}

	std::ostream &operator<<(std::ostream &os, const schema &schm)
	{
		throw not_implemented_exception();
	}
}
