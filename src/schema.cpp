#include "schema.h"

namespace inicpp
{
	schema::schema()
	{
	}

	schema::schema(const schema &source)
	{
		// we have to do deep copies of section schemas
		sections_.reserve(source.sections_.size());
		for (auto &sect : source.sections_) {
			sections_.push_back(std::make_shared<section_schema>(*sect));
		}

		// we already have constructed section schemas... now push them into map
		for (auto &sect : sections_) {
			sections_map_.insert(sect_schema_map_pair(sect->get_name(), sect));
		}
	}

	schema &schema::operator=(const schema &source)
	{
		if (this != &source) {
			schema new_src(source);
			std::swap(*this, new_src);
		}

		return *this;
	}

	schema::schema(schema &&source)
	{
		throw not_implemented_exception();
	}

	schema &schema::operator=(schema &&source)
	{
		throw not_implemented_exception();
	}

	void schema::add_section(const section_schema &sect_schema)
	{
		throw not_implemented_exception();
	}

	void schema::add_section(const section_schema_params &arguments)
	{
		throw not_implemented_exception();
	}

	void schema::add_option(const std::string &section_name, const option_schema &opt_schema)
	{
		throw not_implemented_exception();
	}

	size_t schema::size() const
	{
		return sections_.size();
	}

	section_schema &schema::operator[](size_t index)
	{
		throw not_implemented_exception();
	}

	const section_schema &schema::operator[](size_t index) const
	{
		throw not_implemented_exception();
	}

	section_schema &schema::operator[](const std::string &section_name)
	{
		throw not_implemented_exception();
	}

	const section_schema &schema::operator[](const std::string &section_name) const
	{
		throw not_implemented_exception();
	}

	bool schema::contains(const std::string &section_name) const
	{
		try {
			sections_map_.at(section_name);
			return true;
		} catch (std::out_of_range) {
			return false;
		}
	}

	template<typename ArgType>
	void schema::add_option(const std::string &section_name, option_schema_params<ArgType> &arguments)
	{
		throw not_implemented_exception();
	}

	bool schema::validate_config(config &cfg, schema_mode mode) const
	{
		throw not_implemented_exception();
	}

	std::ostream &operator<<(std::ostream &os, const schema &schm)
	{
		for (auto &sect : schm.sections_) {
			os << *sect;
		}

		return os;
	}
}
