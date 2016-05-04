#include "parser.h"

namespace inicpp
{
	std::string parser::delete_comment(const std::string &str)
	{
		std::string res = str;
		bool escaped = false;

		for (size_t i = 0; i < str.length(); ++i) {
			if (escaped) {
				// escaped character, do not do anything
				escaped = false;
			} else if (str[i] == '\\') {
				// next character will be escaped
				escaped = true;
			} else if (str[i] == ';') {
				// we tracked down a comment... delete it and return
				res = res.substr(0, i);
				break;
			}
		}

		return res;
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
					// if there is cached section save it
					if (last_section != nullptr) {
						cfg.add_section(*last_section);
					}

					std::string sect_name = line.substr(1, line.length() - 2);
					last_section = std::make_shared<section>(sect_name);
				} else {
					throw parser_exception("Section not ended on line " + line_number);
				}
			} else if (find_needle(line, "=")) { // option
				if (last_section == nullptr) {
					throw parser_exception("Option not in section on line " + line_number);
				}

				// TODO
			} else {
				throw parser_exception("Unknown element on line " + line_number);
			}
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
		return internal_load(input);
	}

	config parser::load_file(const std::string &file, const schema &schm, schema_mode mode)
	{
		std::ifstream input(file);
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
