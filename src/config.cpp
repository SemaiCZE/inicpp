#include "config.h"

namespace inicpp
{
	config::config() : sections_(), sections_map_()
	{
	}

	config::config(const config &source) : sections_(), sections_map_()
	{
		// we have to do deep copies of sections
		sections_.reserve(source.sections_.size());
		for (auto &sect : source.sections_) { sections_.push_back(std::make_shared<section>(*sect)); }

		// we already have constructed sections... now push them into map
		for (auto &sect : sections_) { sections_map_.insert(sections_map_pair(sect->get_name(), sect)); }
	}

	config &config::operator=(const config &source)
	{
		if (this != &source) {
			// make copy of input source config and swap it with this
			config new_src(source);
			std::swap(*this, new_src);
		}

		return *this;
	}

	config::config(config &&source) : sections_(), sections_map_()
	{
		operator=(std::move(source));
	}

	config &config::operator=(config &&source)
	{
		if (this != &source) {
			sections_ = std::move(source.sections_);
			sections_map_ = std::move(source.sections_map_);
		}
		return *this;
	}

	void config::add_section(const section &sect)
	{
		auto add_it = sections_map_.find(sect.get_name());
		if (add_it == sections_map_.end()) {
			std::shared_ptr<section> add = std::make_shared<section>(sect);
			sections_.push_back(add);
			sections_map_.insert(sections_map_pair(add->get_name(), add));
		} else {
			throw ambiguity_exception(sect.get_name());
		}
	}

	void config::add_section(const std::string &section_name)
	{
		auto add_it = sections_map_.find(section_name);
		if (add_it == sections_map_.end()) {
			std::shared_ptr<section> add = std::make_shared<section>(section_name);
			sections_.push_back(add);
			sections_map_.insert(sections_map_pair(add->get_name(), add));
		} else {
			throw ambiguity_exception(section_name);
		}
	}

	void config::remove_section(const std::string &section_name)
	{
		auto del_it = sections_map_.find(section_name);
		if (del_it != sections_map_.end()) {
			// remove from map
			sections_map_.erase(del_it);
			// remove from vector
			sections_.erase(
				std::remove_if(sections_.begin(),
					sections_.end(),
					[&](std::shared_ptr<section> sect) { return (sect->get_name() == section_name ? true : false); }),
				sections_.end());
		} else {
			throw not_found_exception(section_name);
		}
	}

	void config::add_option(const std::string &section_name, const option &opt)
	{
		auto sect_it = sections_map_.find(section_name);
		if (sect_it != sections_map_.end()) {
			sect_it->second->add_option(opt);
		} else {
			throw not_found_exception(section_name);
		}
	}

	void config::remove_option(const std::string &section_name, const std::string &option_name)
	{
		auto sect_it = sections_map_.find(section_name);
		if (sect_it != sections_map_.end()) {
			sect_it->second->remove_option(option_name);
		} else {
			throw not_found_exception(section_name);
		}
	}

	size_t config::size() const
	{
		return sections_.size();
	}

	section &config::operator[](size_t index)
	{
		if (index >= sections_.size()) { throw not_found_exception(index); }

		return *sections_[index];
	}

	const section &config::operator[](size_t index) const
	{
		if (index >= sections_.size()) { throw not_found_exception(index); }

		return *sections_[index];
	}

	section &config::operator[](const std::string &section_name)
	{
		std::shared_ptr<section> result;
		try {
			result = sections_map_.at(section_name);
		} catch (const std::out_of_range &) {
			throw not_found_exception(section_name);
		}
		return *result;
	}

	const section &config::operator[](const std::string &section_name) const
	{
		std::shared_ptr<section> result;
		try {
			result = sections_map_.at(section_name);
		} catch (const std::out_of_range &) {
			throw not_found_exception(section_name);
		}
		return *result;
	}

	bool config::contains(const std::string &section_name) const
	{
		try {
			sections_map_.at(section_name);
			return true;
		} catch (const std::out_of_range &) {
			return false;
		}
	}

	void config::validate(const schema &schm, schema_mode mode)
	{
		schm.validate_config(*this, mode);
	}

	bool config::operator==(const config &other) const
	{
		return std::equal(sections_.begin(),
			sections_.end(),
			other.sections_.begin(),
			[](const std::shared_ptr<section> &first, const std::shared_ptr<section> &second) {
				return *first == *second;
			});
	}

	bool config::operator!=(const config &other) const
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
		return const_iterator(const_cast<config &>(*this));
	}

	config::const_iterator config::end() const
	{
		return const_iterator(const_cast<config &>(*this), sections_.size());
	}

	config::const_iterator config::cbegin() const
	{
		return const_iterator(const_cast<config &>(*this));
	}

	config::const_iterator config::cend() const
	{
		return const_iterator(const_cast<config &>(*this), sections_.size());
	}

	std::ostream &operator<<(std::ostream &os, const config &conf)
	{
		for (auto &sect : conf.sections_) { os << *sect; }

		return os;
	}
} // namespace inicpp
