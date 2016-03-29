#include "section.h"

namespace inicpp
{
	section::section()
	{
		throw not_implemented_exception();
	}

	section::section(const section &source)
	{
		throw not_implemented_exception();
	}

	section &section::operator=(const section &source)
	{
		throw not_implemented_exception();
	}

	section::section(section &&source)
	{
		throw not_implemented_exception();
	}

	section &section::operator=(section &&source)
	{
		throw not_implemented_exception();
	}

	void section::add_option(const option &opt)
	{
		throw not_implemented_exception();
	}

	const std::vector<option> &section::get_options()
	{
		throw not_implemented_exception();
	}

	option &section::operator[](size_t index)
	{
		throw not_implemented_exception();
	}

	option &section::operator[](const std::string &option_name)
	{
		throw not_implemented_exception();
	}

	std::ostream &section::operator<<(std::ostream &os)
	{
		throw not_implemented_exception();
	}

	section::iterator section::begin()
	{
		throw not_implemented_exception();
	}
	
	section::iterator section::end()
	{
		throw not_implemented_exception();
	}
	
	section::const_iterator section::cbegin()
	{
		throw not_implemented_exception();
	}
	
	section::const_iterator section::cend()
	{
		throw not_implemented_exception();
	}
}
