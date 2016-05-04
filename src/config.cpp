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

	void config::add_section(const section &sect)
	{
		std::shared_ptr<section> add = std::make_shared<section>(sect);
		sections_.push_back(add);
		sections_map_.insert(sections_map_pair(add->get_name(), add));
	}

	void config::add_section(const std::string &section_name)
	{
		throw not_implemented_exception();
	}

	void config::remove_section(const std::string &section_name)
	{
		throw not_implemented_exception();
	}

	void config::add_option(const std::string &section_name, const option &opt)
	{
		throw not_implemented_exception();
	}
	
	void config::remove_option(const std::string &section_name, const std::string &option_name)
	{
		throw not_implemented_exception();
	}

	size_t config::size() const
	{
		return sections_.size();
	}

	section &config::operator[](size_t index)
	{
		if (index >= size()) {
			throw not_found_exception("Index out of range");
		}
		
		return *sections_[index];
	}

	section &config::operator[](const std::string &section_name)
	{
		std::shared_ptr<section> result;
		try {
			result = sections_map_.at(section_name);
		} catch (std::out_of_range) {
			throw not_found_exception("Index out of range");
		}
		return *result;
	}

	bool config::validate(const schema &schm, schema_mode mode)
	{
		throw not_implemented_exception();
	}

	bool config::operator ==(const config &other) const
	{
		throw not_implemented_exception();
	}

	bool config::operator !=(const config &other) const
	{
		return !(*this == other);
	}

	config::iterator config::begin()
	{
		return iterator(*this);
	}

	config::iterator config::end()
	{
		return iterator(*this, sections_.size());
	}

	config::const_iterator config::begin() const
	{
		return const_iterator((config &)*this);
	}

	config::const_iterator config::end() const
	{
		return const_iterator((config &)*this, sections_.size());
	}

	config::const_iterator config::cbegin() const
	{
		return const_iterator((config &)*this);
	}

	config::const_iterator config::cend() const
	{
		return const_iterator((config &)*this, sections_.size());
	}

	std::ostream &operator<<(std::ostream &os, const config &conf)
	{
		throw not_implemented_exception();
	}
}
