#include "section_schema.h"

namespace inicpp
{
	section_schema::section_schema(const section_schema &source)
	{
		throw not_implemented_exception();
	}
	
	section_schema& section_schema::operator=(const section_schema &source)
	{
		throw not_implemented_exception();
	}

	section_schema::section_schema(section_schema &&source)
	{
		throw not_implemented_exception();
	}

	section_schema& section_schema::operator=(section_schema &&source)
	{
		throw not_implemented_exception();
	}

	section_schema::section_schema(const section_schema_params &arguments)
	{
		throw not_implemented_exception();
	}

	const std::string &section_schema::get_name() const
	{
		return name_;
	}

	const std::string &section_schema::get_comment() const
	{
		return comment_;
	}

	bool section_schema::is_mandatory() const
	{
		return mandatory_;
	}
	
	void section_schema::add_option(const option_schema &opt)
	{
		throw not_implemented_exception();
	}

	void section_schema::remove_option(const std::string &name)
	{
		throw not_implemented_exception();
	}

	bool section_schema::validate_section(const section &sect, schema_mode mode) const
	{
		throw not_implemented_exception();
	}

	std::ostream &operator<<(std::ostream &os, const section_schema &sect_schema)
	{
		throw not_implemented_exception();
	}
}
