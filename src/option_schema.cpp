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

	template<typename ArgType>
	option_schema::option_schema(const option_schema_params<ArgType> &arguments)
	{
		throw not_implemented_exception();
	}

	const std::string &option_schema::get_name() const
	{
		return params_->name;
	}

	option_type option_schema::get_type() const
	{
		return params_->type;
	}

	std::ostream &option_schema::operator<<(std::ostream &os)
	{
		throw not_implemented_exception();
	}

	bool option_schema::is_list() const
	{
		return params_->is_list;
	}

	const std::string &option_schema::get_default_value() const
	{
		return params_->default_value;
	}

	bool option_schema::is_mandatory() const
	{
		return params_->mandatory;
	}

	const std::string &option_schema::get_comment() const
	{
		return params_->comment;
	}
	
	bool option_schema::validate(const option &opt, schema_mode mode)
	{
		throw not_implemented_exception();
	}
}
