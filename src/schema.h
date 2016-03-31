#ifndef INICPP_SCHEMA_H
#define INICPP_SCHEMA_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "section_schema.h"
#include "option_schema.h"
#include "config.h"


namespace inicpp
{
	/** Forward declaration, stated because of ring dependencies */
	class config;

	/**
	 * @brief The schema class
	 */
	class schema
	{
	private:
		/** */
		std::vector<section_schema> sections_;

	public:
		/**
		 * @brief schema
		 */
		schema();
		schema(const schema &source);
		schema &operator=(const schema &source);
		schema(schema &&source);
		schema &operator=(schema &&source);

		/**
		 * @brief add_section
		 * @param sect_schema
		 */
		void add_section(const section_schema &sect_schema);
		/**
		 * @brief add_section
		 * @param section_name
		 * @param mandatory
		 */
		void add_section(const std::string &section_name, bool mandatory = true);

		/**
		 * @brief add_option
		 * @param section_name
		 * @param opt_schema
		 */
		void add_option(const std::string &section_name, const option_schema &opt_schema);
		/**
		 * @brief add_option
		 * @param section_name
		 * @param option_name
		 */
		void add_option(const std::string &section_name, const std::string &option_name,
			bool mandatory = true, option_type type = option_type::string_t,
			bool is_list = false, const std::string &default_value = "");

		/**
		 * @brief
		 * @param cfg
		 * @return
		 */
		bool validate(const config &cfg);

		/**
		 * @brief operator <<
		 * @param os
		 * @return
		 */
		std::ostream &operator<<(std::ostream &os);
	};
}

#endif
