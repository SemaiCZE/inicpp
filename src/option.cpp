#include "option.h"

namespace inicpp
{
	option::option()
	{
		throw not_implemented_exception();
	}

	option::option(const option &source)
	{
		throw not_implemented_exception();
	}

	option &option::operator=(const option &source)
	{
		throw not_implemented_exception();
	}

	option::option(option &&source)
	{
		throw not_implemented_exception();
	}

	option &option::operator=(option &&source)
	{
		throw not_implemented_exception();
	}

	option::option(const std::string &name, const std::string &value, option_type type)
	{
		throw not_implemented_exception();
	}
		
	void remove_from_list(size_t position)
	{
		throw not_implemented_exception();
	}

	void option::remove_from_list(size_t position)
	{
		throw not_implemented_exception();
	}

	bool option::validate(const option_schema &opt_schema)
	{
		throw not_implemented_exception();
	}

	std::ostream &option::operator<<(std::ostream &os)
	{
		throw not_implemented_exception();
	}

	bool option::is_list() const
	{
		return values_.size() > 1;
	}
}
