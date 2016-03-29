#include "config.h"

namespace inicpp
{
	config::config()
	{
		throw not_implemented_exception();
	}

	config::config(const config &src)
	{
		throw not_implemented_exception();
	}

	config &config::operator=(const config &source)
	{
		throw not_implemented_exception();
	}

	config::config(config &&src)
	{
		throw not_implemented_exception();
	}

	config &config::operator=(config &&source)
	{
		throw not_implemented_exception();
	}

	void config::add_section(section sect)
	{
		throw not_implemented_exception();
	}

	void config::add_section(std::string section_name)
	{
		throw not_implemented_exception();
	}

	void config::add_option(std::string section_name, option opt_schema)
	{
		throw not_implemented_exception();
	}

	void config::add_option(std::string section_name, std::string option_name)
	{
		throw not_implemented_exception();
	}

	const std::vector<section> &config::get_sections()
	{
		throw not_implemented_exception();
	}
	
	section &config::operator[](size_t index)
	{
		throw not_implemented_exception();
	}

	std::ostream &config::operator<<(std::ostream& os)
	{
		throw not_implemented_exception();
	}
}
