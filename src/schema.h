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
	 * Represents base point of schema validation.
	 * Object of config class is validated against this one.
	 * Can contain schemes of sections and in them schemes for options.
	 */
	class schema
	{
	private:
		/** Container for section_schema objects */
		std::vector<section_schema> sections_;

	public:
		/**
		 * Default constructor.
		 */
		schema();
		/**
		 * Copy constructor.
		 */
		schema(const schema &source);
		/**
		 * Copy assignment.
		 */
		schema &operator=(const schema &source);
		/**
		 * Move constructor.
		 */
		schema(schema &&source);
		/**
		 * Move assignment.
		 */
		schema &operator=(schema &&source);

		/**
		 * Adds section from given attribute to internal container.
		 * @param sect_schema constant reference to section_schema object
		 * @throws ambiguity_exception if section_schema with given name exists
		 */
		void add_section(const section_schema &sect_schema);
		/**
		 * From given section_schema_params structure
		 * section_schema is created and added to this scheme.
		 * @param arguments non-editable reference to input arguments
		 * @throws ambiguity_exception if section_schema with given name exists
		 */
		void add_section(const section_schema_params &arguments);

		/**
		 * Adds option to the section_schema with specified name.
		 * @param section_name name of existing section
		 * @param opt_schema options_schema which will be added to section
		 * @throws not_found_exception if section_name does not exist
		 * @throws ambiguity_exception if option_schema with given name exists
		 */
		void add_option(const std::string &section_name,
			const option_schema &opt_schema);
		/**
		 * Creates option_schema from given arguments
		 * and adds it to specified section.
		 * @param section_name
		 * @param arguments option_schema creation parameters
		 * @throws not_found_exception if section_name does not exist
		 * @throws ambiguity_exception if option_schema with given name exists
		 */
		template<typename ArgType>
		void add_option(const std::string &section_name,
			option_schema_params<ArgType> &arguments);

		/**
		 * Validate cfg against this schema in specified mode.
		 * @param cfg configuration which will be validated
		 * @param mode validation mode
		 * @return true if config conforms requirements of this schema,
		 * false otherwise
		 */
		bool validate_config(config &cfg, schema_mode mode) const;

		/**
		 * Classic stream operator for printing this instance to output stream.
		 * @param os output stream
		 * @return reference to output stream which allows chaining
		 */
		friend std::ostream &operator<<(std::ostream &os, const schema &schm);
	};

	std::ostream &operator<<(std::ostream &os, const schema &schm);
}

#endif
