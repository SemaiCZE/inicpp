#ifndef INICPP_OPTION_SCHEMA_H
#define INICPP_OPTION_SCHEMA_H

#include <vector>
#include <string>
#include <iostream>

#include "exception.h"
#include "option.h"

namespace inicpp
{
	/**
	 * Struct which sums up all information needed for option_schema creation.
	 */
	struct option_schema_params
	{
		/** Name of option_schema */
		std::string name;
		/** Determines if this option is mandatory or not */
		bool mandatory = true;
		/** Assumed type of option */
		option_type type = option_type::string_e;
		/** True if list has to be stored in option */
		bool is_list = false;
		/** Default value of optional option */
		std::string default_value = "";
		/** Description of option */
		std::string comment;
	};

	
	/** Forward declaration, stated because of ring dependencies */
	class option;


	/**
	 * In option_schema are defined rules which ini option should fulfil,
	 * including its name, type and if option is list or not.
	 * Options can be validated against option_schema objects.
	 */
	class option_schema
	{
	private:
		/** Name of option */
		std::string name_;
		/** Type which option should have */
		option_type type_;
		/** Determines whether value in option is list */
		bool is_list_;
		/** Default value of appropriate option */
		std::string default_value_;
		/** Determines if option is mandatory */
		bool mandatory_;
		/** Description of appropriate option */
		std::string comment_;

	public:
		/**
		 * Deleted default constructor.
		 */
		option_schema() = delete;
		/**
		 * Copy constructor.
		 */
		option_schema(const option_schema &source);
		/**
		 * Copy assignment.
		 */
		option_schema &operator=(const option_schema &source);
		/**
		 * Move constructor.
		 */
		option_schema(option_schema &&source);
		/**
		 * Move assignment.
		 */
		option_schema &operator=(option_schema &&source);

		/**
		 * Construct option_schema from given parameters.
		 * @param arguments creation arguments
		 */
		option_schema(const option_schema_params &arguments);

		/**
		 * Get name of this option.
		 * @return constant reference
		 */
		const std::string &get_name() const;
		/**
		 * Gets type of option.
		 * @return option_type structure
		 */
		option_type get_type() const;
		/**
		 * Determines if list has to be stored in option.
		 * @return true if option should store list
		 */
		bool is_list() const;
		/**
		 * Get option default value.
		 * @return constant reference
		 */
		const std::string &get_default_value() const;
		/**
		 * Determines whether option is mandatory in configuration.
		 * @return true if option is mandatory and should be in configuration
		 */
		bool is_mandatory() const;
		/**
		 * Returns textual description of option.
		 * @return constant reference
		 */
		const std::string &get_comment() const;

		/**
		 * Validate given option against this option_schema.
		 * @param opt validated option
		 * @param mode validation mode
		 * @return true if option comply option_schema
		 */
		bool validate(const option &opt, schema_mode mode);

		/**
		 * Classic stream operator for printing this instance to output stream.
		 * @param os output stream
		 * @return reference to output stream which allows chaining
		 */
		std::ostream &operator<<(std::ostream &os);
	};
}

#endif
