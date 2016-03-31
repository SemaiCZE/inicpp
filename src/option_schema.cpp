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

	option_schema::option_schema(const std::string &name, bool mandatory,
		option_type type, bool is_list, const std::string &default_value)
	{
		throw not_implemented_exception();
	}

	std::ostream &option_schema::operator<<(std::ostream &os)
	{
		throw not_implemented_exception();
	}

	bool option_schema::is_list() const
	{
		return is_list_;
	}
	
	bool option_schema::validate(const option &opt) const
	{
		throw not_implemented_exception();
	}
}
