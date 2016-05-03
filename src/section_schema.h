#ifndef INICPP_SECTION_SCHEMA_H
#define INICPP_SECTION_SCHEMA_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "option_schema.h"
#include "section.h"
#include "types.h"


namespace inicpp
{
	/**
	 * Creation arguments which has to be supplied to section_schema.
	 */
	struct section_schema_params
	{
		/** Name of section_schema */
		std::string name;
		/** Determines whether this section is mandatory in configuration */
		item_requirement requirement = item_requirement::mandatory;
		/** Description of section */
		std::string comment;
	};


	/** Forward declaration, stated because of ring dependencies */
	class section;


	/**
	 * In section_schema are defined rules which ini section should fulfil.
	 * Section can be validated against section_schema objects.
	 */
	class section_schema
	{
	private:
		/** Section name */
		std::string name_;
		/** Determines if section is mandatory or not */
		bool mandatory_;
		/** Description of this section */
		std::string comment_;
		/** Options stored in this section. */
		std::vector<option_schema> options_;

	public:
		/**
		 * Default constructor is deleted.
		 */
		section_schema() = delete;
		/**
		 * Copy constructor.
		 */
		section_schema(const section_schema &source);
		/**
		 * Copy assignment.
		 */
		section_schema &operator=(const section_schema &source);
		/**
		 * Move constructor.
		 */
		section_schema(section_schema &&source);
		/**
		 * Move assignment.
		 */
		section_schema &operator=(section_schema &&source);

		/**
		 * Construct section_schema from given arguments.
		 * @param arguments creation parameters
		 */
		section_schema(const section_schema_params &arguments);

		/**
		 * Gets name of section.
		 * @return constant reference
		 */
		const std::string &get_name() const;
		/**
		 * Determines whether this section is mandatory.
		 * @return true if section has to be in configuration
		 */
		bool is_mandatory() const;
		/**
		 * Get textual description of section.
		 * @return constant reference
		 */
		const std::string &get_comment() const;

		/**
		 * Add option_schema to options list from given parameter.
		 * @param opt option_schema which will be added to this instance
		 * @throws ambiguity_exception if option_schema with given name exists
		 */
		void add_option(const option_schema &opt);
		/**
		 * Creates option_schema from given arguments
		 * and add it to options list.
		 * @param arguments creation paramaters
		 * @throws ambiguity_exception if option_schema with given name exists
		 */
		template<typename ArgType>
		void add_option(const option_schema_params<ArgType> &arguments)
		{
			throw not_implemented_exception();
		}
		/**
		 * Remove containing option schema of given name.
		 * @param name name of option schema to be removed
		 * @throws not_found_exception if given option does not exist
		 */
		void remove_option(const std::string &name);

		/**
		 * Validate given section againts this section_schema.
		 * @param sect validated section
		 * @param mode validation mode
		 * @return true if section is successfully validated
		 */
		bool validate(const section &sect, schema_mode mode);

		/**
		 * Classic stream operator for printing this instance to output stream.
		 * @param os output stream
		 * @return reference to output stream which allows chaining
		 */
		friend std::ostream &operator<<(std::ostream &os, const section_schema &sect_schema);
	};

	std::ostream &operator<<(std::ostream &os, const section_schema &sect_schema);
}

#endif
