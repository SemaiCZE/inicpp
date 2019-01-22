#include "schema.h"

namespace inicpp
{
	schema::schema() : sections_(), sections_map_()
	{
	}

	schema::schema(const schema &source) : sections_(), sections_map_()
	{
		// we have to do deep copies of section schemas
		sections_.reserve(source.sections_.size());
		for (auto &sect : source.sections_) { sections_.push_back(std::make_shared<section_schema>(*sect)); }

		// we already have constructed section schemas... now push them into map
		for (auto &sect : sections_) { sections_map_.insert(sect_schema_map_pair(sect->get_name(), sect)); }
	}

	schema &schema::operator=(const schema &source)
	{
		if (this != &source) {
			schema new_src(source);
			std::swap(*this, new_src);
		}

		return *this;
	}

	schema::schema(schema &&source) : sections_(), sections_map_()
	{
		*this = std::move(source);
	}

	schema &schema::operator=(schema &&source)
	{
		if (this != &source) {
			sections_ = std::move(source.sections_);
			sections_map_ = std::move(source.sections_map_);
		}

		return *this;
	}

	void schema::add_section(const section_schema &sect_schema)
	{
		auto add_it = sections_map_.find(sect_schema.get_name());
		if (add_it == sections_map_.end()) {
			std::shared_ptr<section_schema> add = std::make_shared<section_schema>(sect_schema);
			sections_.push_back(add);
			sections_map_.insert(sect_schema_map_pair(add->get_name(), add));
		} else {
			throw ambiguity_exception(sect_schema.get_name());
		}
	}

	void schema::add_section(const section_schema_params &arguments)
	{
		auto add_it = sections_map_.find(arguments.name);
		if (add_it == sections_map_.end()) {
			std::shared_ptr<section_schema> add = std::make_shared<section_schema>(arguments);
			sections_.push_back(add);
			sections_map_.insert(sect_schema_map_pair(add->get_name(), add));
		} else {
			throw ambiguity_exception(arguments.name);
		}
	}

	void schema::add_option(const std::string &section_name, const option_schema &opt_schema)
	{
		auto sect_it = sections_map_.find(section_name);
		if (sect_it != sections_map_.end()) {
			sect_it->second->add_option(opt_schema);
		} else {
			throw not_found_exception(section_name);
		}
	}

	size_t schema::size() const
	{
		return sections_.size();
	}

	section_schema &schema::operator[](size_t index)
	{
		if (index >= sections_.size()) { throw not_found_exception(index); }

		return *sections_[index];
	}

	const section_schema &schema::operator[](size_t index) const
	{
		if (index >= sections_.size()) { throw not_found_exception(index); }

		return *sections_[index];
	}

	section_schema &schema::operator[](const std::string &section_name)
	{
		std::shared_ptr<section_schema> result;
		try {
			result = sections_map_.at(section_name);
		} catch (const std::out_of_range &) {
			throw not_found_exception(section_name);
		}
		return *result;
	}

	const section_schema &schema::operator[](const std::string &section_name) const
	{
		std::shared_ptr<section_schema> result;
		try {
			result = sections_map_.at(section_name);
		} catch (const std::out_of_range &) {
			throw not_found_exception(section_name);
		}
		return *result;
	}

	bool schema::contains(const std::string &section_name) const
	{
		try {
			sections_map_.at(section_name);
			return true;
		} catch (const std::out_of_range &) {
			return false;
		}
	}

	void schema::validate_config(config &cfg, schema_mode mode) const
	{
		/*
		 * Here should be done:
		 * - check if config has proper sections (compare by names) - depends on mode
		 * - for sections with given schema call validate on that section
		 * - sections which are in schema but not in config
		 *   will be added to config with all their options
		 */

		// firstly go through section schemas
		for (auto &sect : sections_) {
			bool contains = cfg.contains(sect->get_name());

			if (contains) {
				// even if section is not mandatory, we execute validation of section (both modes)
				sect->validate_section(cfg[sect->get_name()], mode);
			} else if (sect->is_mandatory()) {
				// mandatory section is not present in given config (both modes)
				throw validation_exception("Mandatory section '" + sect->get_name() + "' is missing in config");
			} else {
				// section is not mandatory and not in given config
				//   => add section to config and all its options with default values
				cfg.add_section(sect->get_name());
				for (size_t i = 0; i < sect->size(); ++i) {
					auto &opt = sect->operator[](i);
					cfg.add_option(sect->get_name(), opt.get_name(), opt.get_default_value());
				}
			}
		}

		// secondly go through sections
		for (auto &sect : cfg) {
			bool contains = this->contains(sect.get_name());

			// if schema contains section everything is fine, we handled this above
			if (contains) { continue; }

			// we have strict mode and section which is not in schema
			if (mode == schema_mode::strict) {
				throw validation_exception("Section '" + sect.get_name() + "' not specified in schema");
			}
		}
	}

	std::ostream &operator<<(std::ostream &os, const schema &schm)
	{
		for (auto &sect : schm.sections_) { os << *sect; }

		return os;
	}
} // namespace inicpp
