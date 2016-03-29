#include "exception.h"

namespace inicpp
{
	exception::exception()
	{}
	
	exception::exception(const std::string &what)
	{
		what_ = what;
	}

	exception::~exception()
	{
	}

	const char *exception::what() const noexcept
	{
		return what_.c_str();
	}

	not_implemented_exception::not_implemented_exception()
	{}

	const char *not_implemented_exception::what() const noexcept
	{
		return "Not implemented";
	}
}
