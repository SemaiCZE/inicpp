#ifndef INICPP_OPTION_SCHEMA_H
#define INICPP_OPTION_SCHEMA_H

#include <vector>
#include <string>
#include <iostream>
#include <functional>

#include "exception.h"
#include "option.h"
#include "types.h"

namespace inicpp
{
	/**
	 * Base struct which sums up all common information needed
	 * for option_schema creation.
	 */
	struct option_schema_params_base
	{
		/** Name of option_schema */
		std::string name;
		/** Determines if this option is mandatory or not */
		item_requirement requirement = item_requirement::mandatory;
		/** True if list has to be stored in option */
		option_item type = option_item::single;
		/** Default value of optional option */
		std::string default_value = "";
		/** Description of option */
		std::string comment = "";
	};

	
	/**
	 * Extended struct which adds type of the option (as template argument)
	 * and holds in addition to parent functor for value validation.
	 */
	template<typename ArgType>
	struct option_schema_params : public option_schema_params_base
	{
		/**
		 * Validating function - takes one argument of @a ArgType
		 * and returns bool if valid or not
		 */
		std::function<bool(ArgType)> validator = nullptr;
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
		/** Assumed type of option */
		option_type type_;
		/** Internal properties of the option */
		std::shared_ptr<option_schema_params_base> params_;

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
		template<typename ArgType>
		option_schema(const option_schema_params<ArgType> &arguments)
		{
			throw not_implemented_exception();
		}

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
		bool validate_option(const option &opt, schema_mode mode) const;

		/**
		 * Classic stream operator for printing this instance to output stream.
		 * @param os output stream
		 * @return reference to output stream which allows chaining
		 */
		friend std::ostream &operator<<(std::ostream &os, const option_schema &opt_schema);
	};

	std::ostream &operator<<(std::ostream &os, const option_schema &opt_schema);
}

#endif
