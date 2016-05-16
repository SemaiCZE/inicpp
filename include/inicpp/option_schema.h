#ifndef INICPP_OPTION_SCHEMA_H
#define INICPP_OPTION_SCHEMA_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "dll.h"
#include "exception.h"
#include "option.h"
#include "types.h"

namespace inicpp
{
	/**
	 * Base struct which sums up all common information needed
	 * for option_schema creation.
	 */
	class option_schema_params_base
	{
	public:
		virtual ~option_schema_params_base()
		{
		}
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
	template <typename ArgType> class option_schema_params : public option_schema_params_base
	{
	public:
		virtual ~option_schema_params()
		{
		}
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
	class INICPP_API option_schema
	{
	private:
		/** Assumed type of option */
		option_type type_;
		/** Internal properties of the option */
		std::unique_ptr<option_schema_params_base> params_;

		template <typename ValueType>
		std::unique_ptr<option_schema_params_base> copy_schema(const std::unique_ptr<option_schema_params_base> &opt)
		{
			option_schema_params<ValueType> *ptr = dynamic_cast<option_schema_params<ValueType> *>(&*opt);
			// call copy constructor of option_schema_params<ValueType>
			auto new_schema_value = std::make_unique<option_schema_params<ValueType>>(*ptr);
			return std::move(new_schema_value);
		}

		/**
		 * Run provided validator on all items in option.
		 * @param opt
		 */
		void validate_option_items(option &opt) const;

		template <typename ValueType>
		void validate_typed_option_items(const std::vector<ValueType> &items, const std::string &option_name) const
		{
			for (const auto &item : items) {
				option_schema_params<ValueType> *ptr = dynamic_cast<option_schema_params<ValueType> *>(&*params_);
				if (ptr != nullptr && ptr->validator != nullptr && !ptr->validator(item)) {
					throw validation_exception("Option '" + option_name + "' - validation failed");
				}
			}
		}

		void parse_option_items(option &opt) const;

		template <typename ValueType>
		std::vector<ValueType> parse_typed_option_items(const std::vector<std::string> &items,
			std::function<ValueType(const std::string &, const std::string &)> parser,
			const std::string &option_name) const
		{
			std::vector<ValueType> typed_items;
			for (const auto &item : items) {
				typed_items.push_back(parser(item, option_name));
			}
			return typed_items;
		}

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
		 * @throws invalid_type_exception if given type is not valid
		 */
		template <typename ArgType> option_schema(const option_schema_params<ArgType> &arguments)
		{
			type_ = get_option_enum_type<ArgType>();
			if (type_ == option_type::invalid_e) {
				throw invalid_type_exception("Invalid schema type");
			}

			params_ = std::make_unique<option_schema_params<ArgType>>(arguments);
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
		 * @throws validation_exception if error occured
		 */
		void validate_option(option &opt) const;

		/**
		 * To given output stream writes additional information about option.
		 * Written info is in ini comment format.
		 * @param os output stream
		 * @return reference to output stream for better chaining
		 */
		std::ostream &write_additional_info(std::ostream &os) const;
		/**
		 * Classic stream operator for printing this instance to output stream.
		 * @param os output stream
		 * @param opt_schema reference to option_schema instance to be written
		 * @return reference to output stream which allows chaining
		 */
		INICPP_API friend std::ostream &operator<<(std::ostream &os, const option_schema &opt_schema);
	};

	INICPP_API std::ostream &operator<<(std::ostream &os, const option_schema &opt_schema);
}

#endif
