#include "exception.h"

namespace inicpp
{
	exception::exception()
		: what_("Generic inicpp exception")
	{}
	
	exception::exception(const std::string &what)
		: what_(what)
	{}

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

	bad_cast_exception::bad_cast_exception(const std::string &what)
		: inicpp::exception(what)
	{}

	bad_cast_exception::bad_cast_exception(const std::string &from, const std::string &to)
		: inicpp::exception("Bad conversion from: " + from + " to: " + to)
	{}

	not_found_exception::not_found_exception(const std::string &element_name)
		: inicpp::exception("Element: " + element_name + " not found in container")
	{
	}
}
