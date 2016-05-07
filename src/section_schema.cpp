#include "section_schema.h"
#include "string_utils.h"

namespace inicpp
{
	section_schema::section_schema(const section_schema &source)
		: name_(source.name_), requirement_(source.requirement_), comment_(source.comment_)
	{
		// we have to do deep copies of option schemas
		options_.reserve(source.options_.size());
		for (auto &opt : source.options_) {
			options_.push_back(std::make_shared<option_schema>(*opt));
		}

		// we already have constructed option schemas... now push them into map
		for (auto &opt : options_) {
			options_map_.insert(opt_schema_map_pair(opt->get_name(), opt));
		}
	}
	
	section_schema &section_schema::operator=(const section_schema &source)
	{
		if (this != &source) {
			section_schema new_src(source);
			std::swap(*this, new_src);
		}

		return *this;
	}

	section_schema::section_schema(section_schema &&source)
	{
		operator=(std::move(source));
	}

	section_schema &section_schema::operator=(section_schema &&source)
	{
		if (this != &source) {
			name_ = std::move(source.name_);
			requirement_ = std::move(source.requirement_);
			comment_ = std::move(source.comment_);
			options_ = std::move(source.options_);
			options_map_ = std::move(source.options_map_);
		}

		return *this;
	}

	section_schema::section_schema(const section_schema_params &arguments)
		: name_(arguments.name), requirement_(arguments.requirement),
		comment_(arguments.comment)
	{
	}

	const std::string &section_schema::get_name() const
	{
		return name_;
	}

	const std::string &section_schema::get_comment() const
	{
		return comment_;
	}

	bool section_schema::is_mandatory() const
	{
		return (requirement_ == item_requirement::mandatory ? true : false);
	}
	
	void section_schema::add_option(const option_schema &opt)
	{
		auto add_it = options_map_.find(opt.get_name());
		if (add_it == options_map_.end()) {
			std::shared_ptr<option_schema> add = std::make_shared<option_schema>(opt);
			options_.push_back(add);
			options_map_.insert(opt_schema_map_pair(add->get_name(), add));
		} else {
			throw ambiguity_exception(opt.get_name());
		}
	}

	void section_schema::remove_option(const std::string &option_name)
	{
		auto del_it = options_map_.find(option_name);
		if (del_it != options_map_.end()) {
			// remove from map
			options_map_.erase(del_it);
			// remove from vector
			options_.erase(
				std::remove_if(options_.begin(), options_.end(), [&](std::shared_ptr<option_schema> opt) {
				return (opt->get_name() == option_name ? true : false);
			}), options_.end());
		} else {
			throw not_found_exception(option_name);
		}
	}

	size_t section_schema::size() const
	{
		return options_.size();
	}

	option_schema &section_schema::operator[](size_t index)
	{
		if (index >= size()) {
			throw not_found_exception(index);
		}

		return *options_[index];
	}

	const option_schema &section_schema::operator[](size_t index) const
	{
		if (index >= size()) {
			throw not_found_exception(index);
		}

		return *options_[index];
	}

	option_schema &section_schema::operator[](const std::string &option_name)
	{
		// its not pretty but the code is not copy pasted
		// TODO: solve if it will be used or not
		return const_cast<option_schema &>(static_cast<const section_schema *>(this)->operator[](option_name));
	}

	const option_schema &section_schema::operator[](const std::string &option_name) const
	{
		std::shared_ptr<option_schema> result;
		try {
			result = options_map_.at(option_name);
		} catch (std::out_of_range) {
			throw not_found_exception(option_name);
		}
		return *result;
	}

	bool section_schema::contains(const std::string &option_name) const
	{
		try {
			options_map_.at(option_name);
			return true;
		} catch (std::out_of_range) {
			return false;
		}
	}

	bool section_schema::validate_section(section &sect, schema_mode mode) const
	{
		/*
		 * Here should be done:
		 * - check if section has proper options (compare by names) - depends on mode
		 * - for options with given schema call validate on that option
		 * - for missing options from schema (relaxed mode) add string options with
		 *   default value
		 */

		// firstly go through option schemas
		for (auto &opt : options_) {
			bool contains = sect.contains(opt->get_name());

			if (contains) {
				// even if option is not mandatory, we execute validation of option (both modes)
				if (!opt->validate_option(sect[opt->get_name()])) {
					return false;
				}
			} else if (opt->is_mandatory()) {
				// mandatory option is not present in given section (both modes)
				return false;
			} else if (mode == schema_mode::strict && !opt->is_mandatory()) {
				// option is not mandatory and not in given section
				// TODO: what about this? option which is not mandatory and is not present in given section
			} else if (mode == schema_mode::relaxed && !opt->is_mandatory()) {
				// if mode is relaxed, option not present and not mandatory
				//   => add option with default value
				sect.add_option(opt->get_name(), opt->get_default_value());
			}
		}

		// secondly go through options
		for (auto &opt : sect) {
			bool contains = this->contains(opt.get_name());

			// if section_schema contains option everything is fine, we handled this above
			if (contains) {
				continue;
			}

			// we have strict mode and option which is not in section_schema
			if (mode == schema_mode::strict) {
				return false;
			}
		}

		return true;
	}

	std::ostream &operator<<(std::ostream &os, const section_schema &sect_schema)
	{
		// write comment
		auto comment_lines = string_utils::split(sect_schema.get_comment(), '\n');
		for (auto &comment_line : comment_lines) {
			os << ";" << comment_line << std::endl;
		}

		// optional/mandatory
		std::string info_line = sect_schema.is_mandatory() ? "mandatory" : "optional";
		os << ";<" << info_line << ">" << std::endl;

		// write name
		os << "[" << sect_schema.get_name() << "]" << std::endl;

		// write all containing options
		for (auto &opt : sect_schema.options_) {
			os << *opt;
		}

		return os;
	}
}
