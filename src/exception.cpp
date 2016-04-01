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
		: inicpp::exception("Not implemented")
	{}

	bad_cast_exception::bad_cast_exception(const std::string &what)
		: inicpp::exception(what)
	{}

	bad_cast_exception::bad_cast_exception(const std::string &from, const std::string &to)
		: inicpp::exception("Bad conversion from: " + from + " to: " + to)
	{}

	not_found_exception::not_found_exception(size_t index)
		: inicpp::exception("Element on index: " + std::to_string(index) + " was not found")
	{
	}

	not_found_exception::not_found_exception(const std::string &element_name)
		: inicpp::exception("Element: " + element_name + " not found in container")
	{
	}

	invalid_config_exception::invalid_config_exception(const std::string &message)
		: inicpp::exception(message)
	{
	}
}
