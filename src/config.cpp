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

	config::config(const std::string &str)
	{
		throw not_implemented_exception();
	}

	config::config(const std::string &str, const schema &schm, schema_mode mode)
	{
		throw not_implemented_exception();
	}

	config::config(std::istream &str)
	{
		throw not_implemented_exception();
	}

	config::config(std::istream &str, const schema &schm, schema_mode mode)
	{
		throw not_implemented_exception();
	}

	void config::add_section(section sect)
	{
		throw not_implemented_exception();
	}

	void config::add_section(const std::string &section_name)
	{
		throw not_implemented_exception();
	}

	void config::add_option(const std::string &section_name, option opt)
	{
		throw not_implemented_exception();
	}

	template<typename ValueType>
	void config::add_option(const std::string &section_name, const std::string &option_name, const ValueType &value)
	{
		throw not_implemented_exception();
	}
	
	section &config::operator[](size_t index)
	{
		throw not_implemented_exception();
	}

	section &config::operator[](const std::string &section_name)
	{
		throw not_implemented_exception();
	}

	bool config::validate(const schema &schm, schema_mode mode)
	{
		throw not_implemented_exception();
	}

	std::ostream &config::operator<<(std::ostream& os)
	{
		throw not_implemented_exception();
	}

	config::iterator config::begin()
	{
		throw not_implemented_exception();
	}

	config::iterator config::end()
	{
		throw not_implemented_exception();
	}

	config::const_iterator config::cbegin() const
	{
		throw not_implemented_exception();
	}

	config::const_iterator config::cend() const
	{
		throw not_implemented_exception();
	}
}
