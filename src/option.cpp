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

	std::ostream &option::operator<<(std::ostream &os)
	{
		throw not_implemented_exception();
	}

	bool option::is_list() const
	{
		return is_list_;
	}
}
