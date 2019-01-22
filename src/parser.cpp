#include "parser.h"

namespace inicpp
{
	size_t parser::find_first_nonescaped(const std::string &str, char ch)
	{
		size_t result = std::string::npos;
		bool escaped = false;

		for (size_t i = 0; i < str.length(); ++i) {
			if (escaped) {
				// escaped character, do not do anything
				escaped = false;
			} else if (str[i] == '\\') {
				// next character will be escaped
				escaped = true;
			} else if (str[i] == ch) {
				// we tracked down non escaped character... return it
				result = i;
				break;
			}
		}

		return result;
	}

	size_t parser::find_last_escaped(const std::string &str, char ch)
	{
		size_t result = std::string::npos;
		bool escaped = false;

		for (size_t i = 0; i < str.length(); ++i) {
			if (escaped) {
				// escaped character, do not do anything
				escaped = false;

				if (str[i] == ch) { result = i; }
			} else if (str[i] == '\\') {
				// next character will be escaped
				escaped = true;
			}
		}

		return result;
	}

	std::string parser::unescape(const std::string &str)
	{
		std::string result = str;
		bool escaped = false;

		auto it = result.begin();
		while (it != result.end()) {
			if (escaped) {
				// escaped character, it should remain in string
				escaped = false;
			} else if (*it == '\\') {
				// next character will be escaped, so delete escaping character
				escaped = true;
				it = result.erase(it);
				continue;
			}

			// we have while cycle so we have to do this manually
			++it;
		}

		return result;
	}

	std::string parser::delete_comment(const std::string &str)
	{
		return str.substr(0, find_first_nonescaped(str, ';'));
	}

	std::vector<std::string> parser::parse_option_list(const std::string &str)
	{
		using namespace string_utils;

		std::string searched = str;
		std::vector<std::string> result;
		char delim = ',';

		size_t pos = find_first_nonescaped(searched, ',');
		if (pos == std::string::npos) {
			// if no escaped strokes are present in given string,
			//   try to use colon
			delim = ':';
		}

		while (true) {
			pos = find_first_nonescaped(searched, delim);

			// extract option value and process it
			std::string value = searched.substr(0, pos);
			value = left_trim(value);
			// check if last escaped character is whitespace
			size_t whitespace_pos = find_last_escaped(value, ' ');
			value = right_trim(value);
			if (whitespace_pos != std::string::npos) {
				// last character is escaped whitespace
				if (value.size() == whitespace_pos) { value.push_back(' '); }
			}
			// finally unescape
			value = unescape(value);

			// save extracted and processed option value and cut searched string
			result.push_back(value);

			if (pos == std::string::npos) {
				// no delimiter found
				break;
			}
			searched = searched.substr(pos + 1);
		}

		return result;
	}

	void parser::handle_links(
		const config &cfg, const section &last_section, std::vector<std::string> &option_val_list, size_t line_number)
	{
		using namespace string_utils;

		for (auto &opt_value : option_val_list) {
			if (starts_with(opt_value, "${") && ends_with(opt_value, "}")) {
				std::string link = opt_value.substr(2, opt_value.length() - 3);
				size_t delim = find_first_nonescaped(link, '#');

				// link always has to be in format "section#option"
				// section and option cannot be empty
				if (delim == std::string::npos || (delim + 1) == link.length()) {
					throw parser_exception("Bad format of link on line " + std::to_string(line_number));
				}

				std::string sect_link = link.substr(0, delim);
				std::string opt_link = link.substr(delim + 1);

				if (sect_link.empty()) {
					throw parser_exception(
						"Section name in link cannot be empty on line " + std::to_string(line_number));
				}

				// find section with name specifid in link
				const section *selected_section = nullptr;
				if (last_section.get_name() == sect_link) {
					selected_section = &last_section;
				} else if (cfg.contains(sect_link)) {
					selected_section = &cfg[sect_link];
				} else {
					throw parser_exception("Bad link on line " + std::to_string(line_number));
				}

				// from selected section take appropriate option and set its value to options list
				if (selected_section->contains(opt_link)) {
					opt_value = selected_section->operator[](opt_link).get<string_ini_t>();
				} else {
					throw parser_exception("Option name in link not found on line " + std::to_string(line_number));
				}
			}
		}
	}

	void parser::validate_identifier(const std::string &str, size_t line_number)
	{
		std::regex reg_expr("^[a-zA-Z.$:][-a-zA-Z0-9_~.:$ ]*$");
		if (!std::regex_match(str, reg_expr)) {
			throw parser_exception("Identifier contains forbidden characters on line " + std::to_string(line_number));
		}
	}

	config parser::internal_load(std::istream &str)
	{
		using namespace string_utils;

		config cfg;
		std::shared_ptr<section> last_section = nullptr;
		std::string line;
		size_t line_number = 0;

		while (std::getline(str, line)) {
			line_number++;

			// if there was comment delete it
			line = delete_comment(line);
			line = left_trim(line);

			if (line.empty()) { // empty line
				continue;
			} else if (starts_with(line, "[")) { // start of section
				line = right_trim(line);
				if (ends_with(line, "]")) {
					// empty section name cannot be present
					if (line.length() == 2) {
						throw parser_exception("Section name cannot be empty on line " + std::to_string(line_number));
					}

					// if there is cached section, save it
					if (last_section != nullptr) { cfg.add_section(*last_section); }

					// extract name and validate it and finally create section object
					std::string sect_name = unescape(line.substr(1, line.length() - 2));
					validate_identifier(sect_name, line_number);
					last_section = std::make_shared<section>(sect_name);
				} else {
					throw parser_exception("Section not ended on line " + std::to_string(line_number));
				}
			} else { // option
				size_t opt_delim = find_first_nonescaped(line, '=');
				if (opt_delim == std::string::npos) {
					throw parser_exception("Unknown element option expected on line " + std::to_string(line_number));
				}

				// if there is no opened section, option has no parent section
				if (last_section == nullptr) {
					throw parser_exception("Option not in section on line " + std::to_string(line_number));
				}

				// equals character was right at the end of line, should not be
				if ((opt_delim + 1) == line.length()) {
					throw parser_exception("Option value cannot be empty on line " + std::to_string(line_number));
				}

				// retrieve option name and value from line
				std::string option_name = unescape(trim(line.substr(0, opt_delim)));
				std::string option_val = line.substr(opt_delim + 1);

				// validate option name
				validate_identifier(option_name, line_number);

				if (option_name.empty()) {
					throw parser_exception("Option name cannot be empty on line " + std::to_string(line_number));
				}

				auto option_val_list = parse_option_list(option_val);
				if (option_val_list.empty()) {
					throw parser_exception("Option value cannot be empty on line " + std::to_string(line_number));
				}

				handle_links(cfg, *last_section, option_val_list, line_number);

				// and finally create option and store it in current section
				option opt(option_name, option_val_list);
				last_section->add_option(opt);
			}
		}

		// if there is cached section we have to add it to created config too
		if (last_section != nullptr) { cfg.add_section(*last_section); }

		return cfg;
	}

	void parser::internal_save(const config &cfg, const schema &schm, std::ostream &str)
	{
		for (auto &sect : cfg) {
			bool contains = schm.contains(sect.get_name());
			if (!contains) {
				// write section which is not in schema
				// if this happens we can safely write all section and its option to output
				// we do not have to go through them and write their additional info
				str << sect;
				continue;
			}

			// if schema contains section from config, write additional info and name first
			auto &sect_schema = schm[sect.get_name()];
			sect_schema.write_additional_info(str);
			sect_schema.write_section_name(str);

			// go through options and write them to output with info from option_schema
			for (auto &opt : sect) {
				if (sect_schema.contains(opt.get_name())) {
					// if option is in section_schema, then write additional info
					sect_schema[opt.get_name()].write_additional_info(str);
				}

				// write option name and value to output
				str << opt;
			}

			// get through option_schema in appropriate section_schema
			for (size_t i = 0; i < sect_schema.size(); ++i) {
				auto &opt_schema = sect_schema[i];
				if (sect.contains(opt_schema.get_name())) {
					// already written to output stream
					continue;
				}

				// option with this name does not exist in config,
				//   so write its option_schema interpretation
				str << opt_schema;
			}
		}
	}

	config parser::load(const std::string &str)
	{
		std::istringstream input(str);
		return internal_load(input);
	}

	config parser::load(const std::string &str, const schema &schm, schema_mode mode)
	{
		std::istringstream input(str);
		config cfg = internal_load(input);
		cfg.validate(schm, mode);
		return cfg;
	}

	config parser::load(std::istream &str)
	{
		return internal_load(str);
	}

	config parser::load(std::istream &str, const schema &schm, schema_mode mode)
	{
		config cfg = internal_load(str);
		cfg.validate(schm, mode);
		return cfg;
	}

	config parser::load_file(const std::string &file)
	{
		std::ifstream input(file);
		if (input.fail()) { throw parser_exception("File reading error"); }

		return internal_load(input);
	}

	config parser::load_file(const std::string &file, const schema &schm, schema_mode mode)
	{
		std::ifstream input(file);
		if (input.fail()) { throw parser_exception("File reading error"); }

		config cfg = internal_load(input);
		cfg.validate(schm, mode);
		return cfg;
	}

	void parser::save(const config &cfg, const std::string &file)
	{
		std::ofstream output(file);
		output << cfg;
		output.close();
	}

	void parser::save(const config &cfg, std::ostream &str)
	{
		str << cfg;
	}

	void parser::save(const config &cfg, const schema &schm, const std::string &file)
	{
		std::ofstream output(file);
		internal_save(cfg, schm, output);
		output.close();
	}

	void parser::save(const config &cfg, const schema &schm, std::ostream &str)
	{
		internal_save(cfg, schm, str);
	}

	void parser::save(const schema &schm, const std::string &file)
	{
		std::ofstream output(file);
		output << schm;
		output.close();
	}

	void parser::save(const schema &schm, std::ostream &str)
	{
		str << schm;
	}
} // namespace inicpp
