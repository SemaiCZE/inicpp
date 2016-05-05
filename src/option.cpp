#include "option.h"

namespace inicpp
{
	option::option(const option &source)
	{
		this->operator =(source);
	}

	option &option::operator=(const option &source)
	{
		if (source != *this) {
			values_.clear();
			name_ = source.name_;
			type_ = source.type_;
			for (const auto &value : source.values_) {
				switch (type_) {
				case option_type::boolean_e:
					copy_option<boolean_ini_t>(value);
					break;
				case option_type::enum_e:
					copy_option<enum_ini_t>(value);
					break;
				case option_type::float_e:
					copy_option<float_ini_t>(value);
					break;
				case option_type::signed_e:
					copy_option<signed_ini_t>(value);
					break;
				case option_type::string_e:
					copy_option<string_ini_t>(value);
					break;
				case option_type::unsigned_e:
					copy_option<unsigned_ini_t>(value);
					break;
				case option_type::invalid_e:
					// never reached
					throw invalid_config_exception("Invalid option type");
					break;
				}
			}
			option_schema_ = source.option_schema_;
		}
		return *this;
	}

	option::option(option &&source)
	{
		name_ = source.name_;
		type_ = source.type_;
		values_ = std::move(source.values_);
		option_schema_ = std::move(source.option_schema_);
	}

	option &option::operator=(option &&source)
	{
		name_ = source.name_;
		type_ = source.type_;
		values_ = std::move(source.values_);
		option_schema_ = std::move(source.option_schema_);
		return *this;
	}

	//TODO:
	option::option(const std::string &name, const std::string &value, option_type type)
		: name_(name), type_(option_type::string_e)
	{
		add_to_list<string_ini_t>(value);
	}

	//TODO:
	option::option(const std::string &name, const std::vector<std::string> &values, option_type type)
		: name_(name), type_(option_type::string_e)
	{
		for (const auto &input_value : values) {
			add_to_list<string_ini_t>(input_value);
		}
	}

	const std::string &option::get_name() const
	{
		return name_;
	}

	void option::remove_from_list_pos(size_t position)
	{
		if (position >= values_.size()) {
			throw not_found_exception(position);
		}
		values_.erase(values_.begin() + position);
	}

	bool option::validate(const option_schema &opt_schema, schema_mode mode)
	{
		return opt_schema.validate_option(*this, mode);
	}

	bool option::operator==(const option &other) const
	{
		bool same_values = true;
		if (values_.size() != other.values_.size()) {
			same_values = false;
		} else {
			for (size_t i = 0; i < values_.size(); ++i) {
				//TODO: compare values
			}
		}
		return name_ == other.name_ && type_ == other.type_ && same_values;
	}

	bool option::operator!=(const option &other) const
	{
		return !(*this == other);
	}

	bool option::is_list() const
	{
		return values_.size() > 1;
	}

	option &option::operator=(boolean_ini_t arg)
	{
		values_.clear();
		type_ = option_type::boolean_e;
		add_to_list<boolean_ini_t>(arg);
		return *this;
	}

	option &option::operator=(signed_ini_t arg)
	{
		values_.clear();
		type_ = option_type::signed_e;
		add_to_list<signed_ini_t>(arg);
		return *this;
	}

	option &option::operator=(unsigned_ini_t arg)
	{
		values_.clear();
		type_ = option_type::unsigned_e;
		add_to_list<unsigned_ini_t>(arg);
		return *this;
	}

	option &option::operator=(float_ini_t arg)
	{
		values_.clear();
		type_ = option_type::float_e;
		add_to_list<float_ini_t>(arg);
		return *this;
	}

	option &option::operator=(string_ini_t arg)
	{
		values_.clear();
		type_ = option_type::string_e;
		add_to_list<string_ini_t>(arg);
		return *this;
	}

	std::ostream &operator<<(std::ostream &os, const option &opt)
	{
		throw not_implemented_exception();
	}
}
