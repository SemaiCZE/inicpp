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

	std::string parser::unescape(const std::string &str)
	{
		std::string result = str;
		bool escaped = false;

		for (auto &it = result.begin(); it != result.end(); ++it) {
			if (escaped) {
				// escaped character, it should remain in string
				escaped = false;
			} else if (*it == '\\') {
				// next character will be escaped, so delete escaping character
				escaped = true;
				it = result.erase(it);
			}
		}

		return result;
	}

	std::string parser::delete_comment(const std::string &str)
	{
		return str.substr(0, find_first_nonescaped(str, ';'));
	}

	std::vector<std::string> parser::parse_option_list(const std::string &str)
	{
		std::string searched = str;
		std::vector<std::string> result;

		size_t pos;
		while ((pos = find_first_nonescaped(searched, ',')) != std::string::npos) {
			result.push_back(unescape(string_utils::trim(searched.substr(0, pos))));
			searched = searched.substr(pos + 1);
		}
		result.push_back(unescape(string_utils::trim(searched)));

		return result;
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
			line = trim(line);

			if (line.empty()) { // empty line
				continue;
			} else if (starts_with(line, "[")) { // start of section
				if (ends_with(line, "]")) {
					// empty section name cannot be present
					if (line.length() == 2) {
						throw parser_exception("Section name cannot be empty");
					}

					// if there is cached section, save it
					if (last_section != nullptr) {
						cfg.add_section(*last_section);
					}

					std::string sect_name = unescape(line.substr(1, line.length() - 2));
					last_section = std::make_shared<section>(sect_name);
				} else {
					throw parser_exception("Section not ended on line " + line_number);
				}
			} else { // option
				size_t opt_delim = find_first_nonescaped(line, '=');
				if (opt_delim == std::string::npos) {
					throw parser_exception("Unknown element option expected on line " + line_number);
				}

				// if there is no opened section, option has no parent section
				if (last_section == nullptr) {
					throw parser_exception("Option not in section on line " + line_number);
				}

				// equals character was right at the end of line, should not be
				if ((opt_delim + 1) == line.length()) {
					throw parser_exception("Option value cannot be empty");
				}

				// retrieve option name and value from line
				std::string option_name = unescape(trim(line.substr(0, opt_delim)));
				std::string option_val = trim(line.substr(opt_delim + 1));
				
				if (option_name.empty()) {
					throw parser_exception("Option name cannot be empty");
				}

				auto option_val_list = parse_option_list(option_val);
				if (option_val_list.empty()) {
					throw parser_exception("Option value cannot be empty");
				}

				// TODO: links

				// and finally create option and store it in current section
				option opt(option_name, option_val_list);
				last_section->add_option(opt);
			}
		}

		// if there is cached section we have to add it to created config too
		if (last_section != nullptr) {
			cfg.add_section(*last_section);
		}

		return cfg;
	}

	void parser::internal_save(const config &cfg, const schema &schm, std::ostream &str)
	{
		for (auto &sect : cfg) {
			for (auto &opt : sect) {
				// TODO
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
		if (input.fail()) {
			throw parser_exception("File reading error");
		}

		return internal_load(input);
	}

	config parser::load_file(const std::string &file, const schema &schm, schema_mode mode)
	{
		std::ifstream input(file);
		if (input.fail()) {
			throw parser_exception("File reading error");
		}

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
}
