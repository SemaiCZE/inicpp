#ifndef INICPP_SECTION_SCHEMA_H
#define INICPP_SECTION_SCHEMA_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "option_schema.h"
#include "section.h"


namespace inicpp
{
	/** Forward declaration, stated because of ring dependencies */
	class section;

	/**
	 * @brief The section_schema class
	 */
	class section_schema
	{
	private:
		/** */
		std::string name_;
		/** */
		std::vector<option_schema> options_;
		/** */
		bool mandatory_;
		/** */
		std::string comment_;

	public:
		/**
		 * @brief section_schema
		 */
		section_schema();
		section_schema(const section_schema &source);
		section_schema& operator=(const section_schema &source);
		section_schema(section_schema &&source);
		section_schema& operator=(section_schema &&source);

		/**
		 * @brief section_schema
		 * @param name
		 * @param is_mandatory
		 */
		section_schema(const std::string &name, bool mandatory = true);

		/**
		 * @brief
		 * @return
		 */
		const std::string &get_name() const;
		/**
		 * @brief
		 * @return
		 */
		const std::string &get_comment() const;
		/**
		 * @brief
		 * @return
		 */
		bool is_mandatory() const;

		/**
		 * @brief add_option
		 * @param opt
		 */
		void add_option(const option_schema &opt);
		/**
		 * @brief add_option
		 * @param option_name
		 */
		void add_option(const option_schema_params &arguments);

		/**
		 * @brief
		 * @param schm
		 * @return
		 */
		bool validate(const section &sect, schema_mode mode);

		/**
		 * @brief operator <<
		 * @param os
		 * @return
		 */
		std::ostream &operator<<(std::ostream &os);
	};
}

#endif
