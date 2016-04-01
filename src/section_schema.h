#ifndef INICPP_SECTION_SCHEMA_H
#define INICPP_SECTION_SCHEMA_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "option_schema.h"
#include "section.h"


namespace inicpp
{
	/**
	 * Creation arguments which has to be supplied to section_schema
	 */
	struct section_schema_params
	{
		/** Name of section_schema */
		std::string name;
		/** Determines whether this section is mandatory in configuration */
		bool mandatory = true;
		/** Description of this section */
		std::string comment;
	};


	/** Forward declaration, stated because of ring dependencies */
	class section;


	/**
	 * 
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
		section_schema(const section_schema_params &arguments);

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
		 * Classic stream operator for printing this instance to output stream.
		 * @param os output stream
		 * @return reference to output stream which allows chaining
		 */
		std::ostream &operator<<(std::ostream &os);
	};
}

#endif
