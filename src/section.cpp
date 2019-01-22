#include "section.h"

namespace inicpp
{
	section::section(const section &source) : options_(), options_map_(), name_(source.name_)
	{
		// we have to do deep copies of options
		options_.reserve(source.options_.size());
		for (auto &opt : source.options_) { options_.push_back(std::make_shared<option>(*opt)); }

		// we already have constructed options... now push them into map
		for (auto &opt : options_) { options_map_.insert(options_map_pair(opt->get_name(), opt)); }
	}

	section &section::operator=(const section &source)
	{
		if (this != &source) {
			// make copy of input source section and swap it with this
			section new_src(source);
			std::swap(*this, new_src);
		}

		return *this;
	}

	section::section(section &&source) : options_(), options_map_(), name_()
	{
		operator=(std::move(source));
	}

	section &section::operator=(section &&source)
	{
		if (this != &source) {
			options_ = std::move(source.options_);
			options_map_ = std::move(source.options_map_);
			name_ = std::move(source.name_);
		}
		return *this;
	}

	section::section(const std::string &name) : options_(), options_map_(), name_(name)
	{
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
			throw ambiguity_exception(opt.get_name());
		}
	}

	void section::remove_option(const std::string &option_name)
	{
		auto del_it = options_map_.find(option_name);
		if (del_it != options_map_.end()) {
			// remove from map
			options_map_.erase(del_it);
			// remove from vector
			options_.erase(
				std::remove_if(options_.begin(),
					options_.end(),
					[&](std::shared_ptr<option> opt) { return (opt->get_name() == option_name ? true : false); }),
				options_.end());
		} else {
			throw not_found_exception(option_name);
		}
	}

	size_t section::size() const
	{
		return options_.size();
	}

	option &section::operator[](size_t index)
	{
		if (index >= size()) { throw not_found_exception(index); }

		return *options_[index];
	}

	const option &section::operator[](size_t index) const
	{
		if (index >= size()) { throw not_found_exception(index); }

		return *options_[index];
	}

	option &section::operator[](const std::string &option_name)
	{
		std::shared_ptr<option> result;
		try {
			result = options_map_.at(option_name);
		} catch (const std::out_of_range &) {
			throw not_found_exception(option_name);
		}
		return *result;
	}

	const option &section::operator[](const std::string &option_name) const
	{
		std::shared_ptr<option> result;
		try {
			result = options_map_.at(option_name);
		} catch (const std::out_of_range &) {
			throw not_found_exception(option_name);
		}
		return *result;
	}

	bool section::contains(const std::string &option_name) const
	{
		try {
			options_map_.at(option_name);
			return true;
		} catch (const std::out_of_range &) {
			return false;
		}
	}

	void section::validate(const section_schema &sect_schema, schema_mode mode)
	{
		sect_schema.validate_section(*this, mode);
	}

	bool section::operator==(const section &other) const
	{
		if (name_ != other.name_) { return false; }

		return std::equal(options_.begin(),
			options_.end(),
			other.options_.begin(),
			[](const std::shared_ptr<option> &first, const std::shared_ptr<option> &second) {
				return *first == *second;
			});
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
		return const_iterator(const_cast<section &>(*this));
	}

	section::const_iterator section::end() const
	{
		return const_iterator(const_cast<section &>(*this), options_.size());
	}

	section::const_iterator section::cbegin() const
	{
		return const_iterator(const_cast<section &>(*this));
	}

	section::const_iterator section::cend() const
	{
		return const_iterator(const_cast<section &>(*this), options_.size());
	}

	std::ostream &operator<<(std::ostream &os, const section &sect)
	{
		os << "[" << sect.get_name() << "]" << std::endl;
		for (auto &opt : sect.options_) { os << *opt; }

		return os;
	}
} // namespace inicpp
