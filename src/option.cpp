#include "option.h"

namespace inicpp
{
	option::option(const option &source) : name_(), values_(), option_schema_()
	{
		this->operator=(source);
	}

	option &option::operator=(const option &source)
	{
		if (&source != this) {
			values_.clear();
			name_ = source.name_;
			for (const auto &value : source.values_) { values_.push_back(value); }
			option_schema_ = source.option_schema_;
		}
		return *this;
	}

	option::option(option &&source) : name_(), values_(), option_schema_()
	{
		name_ = source.name_;
		values_ = std::move(source.values_);
		option_schema_ = std::move(source.option_schema_);
	}

	option &option::operator=(option &&source)
	{
		if (&source != this) {
			name_ = source.name_;
			values_ = std::move(source.values_);
			option_schema_ = std::move(source.option_schema_);
		}
		return *this;
	}

	option::option(const std::string &name, const std::string &value) : name_(name), values_(), option_schema_()
	{
		add_to_list<string_ini_t>(value);
	}

	option::option(const std::string &name, const std::vector<std::string> &values)
		: name_(name), values_(), option_schema_()
	{
		for (const auto &input_value : values) { add_to_list<string_ini_t>(input_value); }
	}

	const std::string &option::get_name() const
	{
		return name_;
	}

	void option::remove_from_list_pos(size_t position)
	{
		if (position >= values_.size()) { throw not_found_exception(position); }
		auto p = static_cast<std::iterator_traits<decltype(values_.begin())>::difference_type>(position);
		values_.erase(std::next(values_.begin(), p));
	}

	void option::validate(const option_schema &opt_schema)
	{
		opt_schema.validate_option(*this);
	}

	bool option::operator==(const option &other) const
	{
		if (name_ != other.name_) { return false; }

		if (values_.size() != other.values_.size()) { return false; }

		for (size_t i = 0; i < values_.size(); ++i) {
			if (values_[i] != other.values_[i]) { return false; }
		}

		return true;
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
		add_to_list<boolean_ini_t>(arg);
		return *this;
	}

	option &option::operator=(signed_ini_t arg)
	{
		values_.clear();
		add_to_list<signed_ini_t>(arg);
		return *this;
	}

	option &option::operator=(unsigned_ini_t arg)
	{
		values_.clear();
		add_to_list<unsigned_ini_t>(arg);
		return *this;
	}

	option &option::operator=(float_ini_t arg)
	{
		values_.clear();
		add_to_list<float_ini_t>(arg);
		return *this;
	}

	option &option::operator=(const char *arg)
	{
		values_.clear();
		add_to_list<string_ini_t>(arg);
		return *this;
	}

	option &option::operator=(string_ini_t arg)
	{
		values_.clear();
		add_to_list<string_ini_t>(arg);
		return *this;
	}

	option &option::operator=(enum_ini_t arg)
	{
		values_.clear();
		add_to_list<enum_ini_t>(arg);
		return *this;
	}

	// ----- Write functions -----

	// Internal type specific functions
	namespace
	{
		void write_boolean_option(std::vector<boolean_ini_t> values, std::ostream &os)
		{
			if (values[0]) {
				os << "yes";
			} else {
				os << "no";
			}
			for (auto it = values.begin() + 1; it != values.end(); ++it) {
				os << ",";
				if (*it) {
					os << "yes";
				} else {
					os << "no";
				}
			}
		}
		void write_enum_option(std::vector<enum_ini_t> values, std::ostream &os)
		{
			os << escape_option_value(static_cast<std::string>(values[0]));
			for (auto it = values.begin() + 1; it != values.end(); ++it) {
				os << "," << escape_option_value(static_cast<std::string>(*it));
			}
		}
		void write_float_option(std::vector<float_ini_t> values, std::ostream &os)
		{
			os << values[0];
			for (auto it = values.begin() + 1; it != values.end(); ++it) { os << "," << *it; }
		}
		void write_signed_option(std::vector<signed_ini_t> values, std::ostream &os)
		{
			os << values[0];
			for (auto it = values.begin() + 1; it != values.end(); ++it) { os << "," << *it; }
		}
		void write_unsigned_option(std::vector<unsigned_ini_t> values, std::ostream &os)
		{
			os << values[0];
			for (auto it = values.begin() + 1; it != values.end(); ++it) { os << "," << *it; }
		}
		void write_string_option(std::vector<string_ini_t> values, std::ostream &os)
		{
			os << escape_option_value(values[0]);
			for (auto it = values.begin() + 1; it != values.end(); ++it) { os << "," << escape_option_value(*it); }
		}
	} // namespace

	std::ostream &operator<<(std::ostream &os, const option &opt)
	{
		os << opt.name_ << " = ";
		std::visit(overloaded{[&](boolean_ini_t) { write_boolean_option(opt.get_list<boolean_ini_t>(), os); },
					   [&](enum_ini_t) { write_enum_option(opt.get_list<enum_ini_t>(), os); },
					   [&](float_ini_t) { write_float_option(opt.get_list<float_ini_t>(), os); },
					   [&](signed_ini_t) { write_signed_option(opt.get_list<signed_ini_t>(), os); },
					   [&](unsigned_ini_t) { write_unsigned_option(opt.get_list<unsigned_ini_t>(), os); },
					   [&](string_ini_t) { write_string_option(opt.get_list<string_ini_t>(), os); }},
			opt.values_[0]);

		os << std::endl;
		return os;
	}
} // namespace inicpp
