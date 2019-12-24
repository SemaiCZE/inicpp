#include "option_schema.h"
#include "string_utils.h"

namespace inicpp
{
	option_schema::option_schema(const option_schema &source) : params_()
	{
		this->operator=(source);
	}

	option_schema &option_schema::operator=(const option_schema &source)
	{
		params_ = source.params_;

		return *this;
	}

	option_schema::option_schema(option_schema &&source) : params_()
	{
		this->operator=(std::move(source));
	}

	option_schema &option_schema::operator=(option_schema &&source)
	{
		if (this != &source) { params_ = std::move(source.params_); }
		return *this;
	}

	std::string option_schema::get_name() const
	{
		return std::visit([](const auto &arg) { return arg.name; }, params_);
	}

	bool option_schema::is_list() const
	{
		return std::visit([](const auto &arg) { return arg.type == option_item::list; }, params_);
	}

	std::string option_schema::get_default_value() const
	{
		return std::visit([](const auto &arg) { return arg.default_value; }, params_);
	}

	bool option_schema::is_mandatory() const
	{
		return std::visit([](const auto &arg) { return arg.requirement == item_requirement::mandatory; }, params_);
	}

	std::string option_schema::get_comment() const
	{
		return std::visit([](const auto &arg) { return arg.comment; }, params_);
	}

	void option_schema::validate_option(option &opt) const
	{
		if (!is_list() && opt.is_list()) {
			throw validation_exception("Option '" + opt.get_name() + "' - list given, single value expected");
		} else if (is_list() && !opt.is_list()) {
			throw validation_exception("Option '" + opt.get_name() + "' - single value given, list expected");
		}

		// if option type doesn't match, parse it to proper one
		std::visit(
			[&](auto &&arg) {
				using T = std::decay_t<decltype(arg)>;
				if (!opt.holds_type<typename T::data_t>()) {
					opt.set_list<typename T::data_t>(parse_typed_option_items<typename T::data_t>(
						opt.get_list<string_ini_t>(), string_utils::parse_string<typename T::data_t>, opt.get_name()));
				}
			},
			params_);

		// validate range using provided validator
		validate_option_items(opt);
	}

	void option_schema::validate_option_items(option &opt) const
	{
		// load value and call validate function on it
		std::visit(
			[&](auto &&arg) {
				using T = std::decay_t<decltype(arg)>;
				validate_typed_option_items<typename T::data_t>(opt.get_list<typename T::data_t>(), opt.get_name());
			},
			params_);
	}

	std::ostream &option_schema::write_additional_info(std::ostream &os) const
	{
		// write comment
		auto comment_lines = string_utils::split(get_comment(), '\n');
		for (auto &comment_line : comment_lines) { os << ";" << comment_line << std::endl; }

		// optional/mandatory and single/list
		std::string info_line = is_mandatory() ? "mandatory" : "optional";
		info_line += ", ";
		info_line += is_list() ? "list" : "single";
		os << ";<" << info_line << ">" << std::endl;

		// default value given at construction
		os << ";<default value: \"" << get_default_value() << "\">" << std::endl;

		return os;
	}

	std::ostream &operator<<(std::ostream &os, const option_schema &opt_schema)
	{
		// write additional information about given option
		opt_schema.write_additional_info(os);

		// write name and default value
		os << opt_schema.get_name() << " = " << opt_schema.get_default_value() << std::endl;

		return os;
	}
} // namespace inicpp
