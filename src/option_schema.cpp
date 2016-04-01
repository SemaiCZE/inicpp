#include "option_schema.h"

namespace inicpp
{
	option_schema::option_schema()
	{
		throw not_implemented_exception();
	}

	option_schema::option_schema(const option_schema &source)
	{
		throw not_implemented_exception();
	}

	option_schema &option_schema::operator=(const option_schema &source)
	{
		throw not_implemented_exception();
	}
	
	option_schema::option_schema(option_schema &&source)
	{
		throw not_implemented_exception();
	}
	
	option_schema &option_schema::operator=(option_schema &&source)
	{
		throw not_implemented_exception();
	}

	option_schema::option_schema(const option_schema_params &arguments)
	{
		throw not_implemented_exception();
	}

	const std::string &option_schema::get_name() const
	{
		return name_;
	}

	option_type option_schema::get_type() const
	{
		return type_;
	}

	std::ostream &option_schema::operator<<(std::ostream &os)
	{
		throw not_implemented_exception();
	}

	bool option_schema::is_list() const
	{
		return is_list_;
	}

	const std::string &option_schema::get_default_value() const
	{
		return default_value_;
	}

	bool option_schema::is_mandatory() const
	{
		return mandatory_;
	}

	const std::string &option_schema::get_comment() const
	{
		return comment_;
	}
	
	bool option_schema::validate(const option &opt, schema_mode mode)
	{
		throw not_implemented_exception();
	}
}
