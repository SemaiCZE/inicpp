#include "config.h"

namespace inicpp
{
	config::config() : schema_(nullptr)
	{
	}

	config::config(const config &source)
		: schema_(std::make_shared<schema>(*source.schema_))
	{
		// we have to do deep copies of sections
		sections_.reserve(source.sections_.size());
		for (auto &sect : source.sections_) {
			sections_.push_back(std::make_shared<section>(*sect));
		}
		
		// we already have constructed section... now push them into map
		for (auto &sect : sections_) {
			sections_map_.insert(sections_map_pair(sect->get_name(), sect));
		}
	}

	config &config::operator=(const config &source)
	{
		// in case of self assignment
		if (this == &source) {
			return *this;
		}

		// make copy of input source config
		config new_src(source);

		// and then swap all elements with mines
		std::swap(sections_, new_src.sections_);
		std::swap(sections_map_, new_src.sections_map_);
		std::swap(schema_, new_src.schema_);

		return *this;
	}

	config::config(config &&source) : sections_(source.sections_),
		sections_map_(source.sections_map_), schema_(source.schema_)
	{
	}

	config &config::operator=(config &&source)
	{
		sections_ = source.sections_;
		sections_map_ = source.sections_map_;
		schema_ = source.schema_;
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
			throw ambiguity_exception("Section name is already defined");
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
			throw ambiguity_exception("Section name is already defined");
		}
	}

	void config::remove_section(const std::string &section_name)
	{
		auto del_it = sections_map_.find(section_name);
		if (del_it != sections_map_.end()) {
			// remove from map
			sections_map_.erase(del_it);
			// remove from vector
			std::remove_if(sections_.begin(), sections_.end(), [&](std::shared_ptr<section> sect) {
				return (sect->get_name() == section_name ? true : false);
			});
		} else {
			throw not_found_exception("Index out of range, section not found");
		}
	}

	void config::add_option(const std::string &section_name, const option &opt)
	{
		auto sect_it = sections_map_.find(section_name);
		if (sect_it != sections_map_.end()) {
			sect_it->second->add_option(opt);
		} else {
			throw not_found_exception("Index out of range, section not found");
		}
	}
	
	void config::remove_option(const std::string &section_name, const std::string &option_name)
	{
		auto sect_it = sections_map_.find(section_name);
		if (sect_it != sections_map_.end()) {
			sect_it->second->remove_option(option_name);
		} else {
			throw not_found_exception("Index out of range, section not found");
		}
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
		return schm.validate_config(*this, mode);
	}

	bool config::operator ==(const config &other) const
	{
		return std::equal(sections_.begin(), sections_.end(), other.sections_.begin(),
			[](const std::shared_ptr<section> &first, const std::shared_ptr<section> &second) {
			return *first == *second;
		});
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
		for (auto &sect : conf.sections_) {
			os << sect;
		}

		return os;
	}
}
