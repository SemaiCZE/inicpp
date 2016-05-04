#include "section.h"

namespace inicpp
{
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

	section::section(const std::string &name)
	{
		throw not_implemented_exception();
	}

	const std::string &section::get_name() const
	{
		return name_;
	}

	void section::add_option(const option &opt)
	{
		auto add_it = options_map_.find(opt.get_name());
		if (add_it == options_map_.end()) {
			std::shared_ptr<option> add = std::make_shared<option>(opt);
			options_.push_back(add);
			options_map_.insert(options_map_pair(add->get_name(), add));
		} else {
			throw ambiguity_exception("Option name is already defined");
		}
	}

	void section::remove_option(const std::string &option_name)
	{
		auto del_it = options_map_.find(option_name);
		if (del_it != options_map_.end()) {
			// remove from map
			options_map_.erase(del_it);
			// remove from vector
			std::remove_if(options_.begin(), options_.end(), [&](std::shared_ptr<option> opt) {
				return (opt->get_name() == option_name ? true : false);
			});
		} else {
			throw not_found_exception("Index out of range");
		}
	}

	size_t section::size()
	{
		return options_.size();
	}

	option &section::operator[](size_t index)
	{
		if (index >= size()) {
			throw not_found_exception("Index out of range");
		}

		return *options_[index];
	}

	option &section::operator[](const std::string &option_name)
	{
		std::shared_ptr<option> result;
		try {
			result = options_map_.at(option_name);
		} catch (std::out_of_range) {
			throw not_found_exception("Index out of range");
		}
		return *result;
	}

	bool section::validate(const section_schema &sect_schema, schema_mode mode)
	{
		return sect_schema.validate_section(*this, mode);
	}

	bool section::operator==(const section &other) const
	{
		throw not_implemented_exception();
	}

	bool section::operator!=(const section &other) const
	{
		return !(*this == other);
	}

	section::iterator section::begin()
	{
		return iterator(*this);
	}
	
	section::iterator section::end()
	{
		return iterator(*this, options_.size());
	}
	
	section::const_iterator section::begin() const
	{
		return const_iterator((section &)*this);
	}

	section::const_iterator section::end() const
	{
		return const_iterator((section &)*this, options_.size());
	}

	section::const_iterator section::cbegin() const
	{
		return const_iterator((section &)*this);
	}
	
	section::const_iterator section::cend() const
	{
		return const_iterator((section &)*this, options_.size());
	}

	std::ostream &operator<<(std::ostream &os, const section &sect)
	{
		throw not_implemented_exception();
	}
}
