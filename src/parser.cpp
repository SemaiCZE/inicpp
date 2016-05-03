#include "parser.h"

namespace inicpp
{
	config parser::internal_load(std::istream &str)
	{
		config cfg;
		std::string line;

		while (std::getline(str, line)) {
			// TODO
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
