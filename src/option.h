#ifndef INICPP_OPTION_H
#define INICPP_OPTION_H

#include <vector>
#include <memory>
#include <iostream>

#include "exception.h"
#include "types.h"
#include "option_schema.h"

namespace inicpp
{
	/** Forward declaration, stated because of ring dependencies */
	class option_schema;


	/**
	 * Base class for option_value objects,
	 * which allows storing templated option values in option instance.
	 */
	class option_holder
	{
	public:
		/**
		 * Has to be stated for completion.
		 */
		virtual ~option_holder() {}
	};


	/**
	 * Class which actually stores option value in templated manner.
	 * Getter and setter of course provided.
	 */
	template<typename ValueType>
	class option_value : public option_holder
	{
	public:
		/**
		 * Construct option_value with given value.
		 * @param value value which will be stored
		 */
		option_value(ValueType value) : value_(value) {}
		/**
		 * Stated for completion.
		 */
		virtual ~option_value() {}

		/**
		 * Get this instance internal value.
		 * @return returned by value
		 */
		ValueType get()
		{
			return value_;
		}
		/**
		 * Set internal value to given one.
		 * @param value
		 */
		void set(ValueType value)
		{
			value_ = value;
		}

	private:
		/** Stored option value. */
		ValueType value_;
	};

	
	/**
	 * Represent ini configuration option.
	 * Can store one element or list of elements.
	 * Stored elements should have only supported types from option_type enum.
	 */
	class option
	{
	private:
		/** Name of this ini option */
		std::string name_;
		/** Type of this ini option */
		option_type type_;
		/** Values which corresponds with this option */
		std::vector<std::unique_ptr<option_holder>> values_;
		/** Corresponding option_schema if any */
		std::shared_ptr<option_schema> option_schema_;

	public:
		/**
		 * Default constructor is deleted.
		 */
		option() = delete;
		/**
		 * Copy constructor.
		 */
		option(const option &source);
		/**
		 * Copy assignment.
		 */
		option &operator=(const option &source);
		/**
		 * Move constructor.
		 */
		option(option &&source);
		/**
		 * Move assignment.
		 */
		option &operator=(option &&source);

		/**
		 * Construct ini option with specified value of specified type.
		 * @param name name of newly created option
		 * @param value initial value
		 * @param type non-editable option type
		 */
		option(const std::string &name, const std::string &value = "",
			option_type type = option_type::string_e);
		/**
		 * Construct ini option with specified value of specified list type.
		 * @param name name of newly created option
		 * @param value initial value
		 * @param type non-editable option type
		 */
		option(const std::string &name, const std::vector<std::string> &values = {},
			option_type type = option_type::string_e);

		/**
		 * Gets this option name.
		 * @return constant reference to name
		 */
		const std::string &get_name() const;

		/**
		* Determines if option is list or not.
		* @return true if option is list, false otherwise
		*/
		bool is_list() const;

		/**
		 * Set single element value.
		 * @param value newly assigned option value
		 * @throws bad_cast_exception if ValueType cannot be casted
		 * to internal type
		 */
		template<typename ValueType> void set(ValueType value)
		{
			throw not_implemented_exception();
		}
		/**
		 * Overloaded alias for set() function.
		 * @param arg boolean_t
		 * @return reference to this
		 */
		option &operator=(boolean_ini_t arg);
		/**
		 * Overloaded alias for set() function.
		 * @param arg signed_t
		 * @return reference to this
		 */
		option &operator=(signed_ini_t arg);
		/**
		 * Overloaded alias for set() function.
		 * @param arg unsigned_t
		 * @return reference to this
		 */
		option &operator=(unsigned_ini_t arg);
		/**
		 * Overloaded alias for set() function.
		 * @param arg float_t
		 * @return reference to this
		 */
		option &operator=(float_ini_t arg);
		/**
		 * Overloaded alias for set() function.
		 * @param arg string_t
		 * @return reference to this
		 */
		option &operator=(string_ini_t arg);

		/**
		 * Get single element value.
		 * @return templated copy by value
		 * @throws bad_cast_exception if internal type cannot be casted
		 */
		template<typename ValueType> ValueType get() const
		{
			throw not_implemented_exception();
		}

		/**
		 * Set internal list of values to given one.
		 * @param value reference to list of new values
		 * @throws bad_cast_exception if ValueType cannot be casted
		 * to internal type
		 */
		template<typename ValueType> void set_list(
			const std::vector<ValueType> &value)
		{
			throw not_implemented_exception();
		}
		
		/**
		 * Set internal list of values to given one.
		 * @param value rvalue reference to list of new values
		 * @throws bad_cast_exception if ValueType cannot be casted
		 * to internal type
		 */
		template<typename ValueType> void set_list(
			std::vector<ValueType> &&value)
		{
			throw not_implemented_exception();
		}
		
		/**
		 * Get list of internal values. Returning list is newly created.
		 * @return new list of all stored values
		 * @throws bad_cast_exception if internal type cannot be casted
		 */
		template<typename ValueType> std::vector<ValueType> get_list() const
		{
			throw not_implemented_exception();
		}

		/**
		 * Adds element to internal value list.
		 * @param value pushed value
		 * @throws bad_cast_exception if ValueType cannot be casted
		 */
		template<typename ValueType> void add_to_list(ValueType value)
		{
			throw not_implemented_exception();
		}

		/**
		 * Add element to list on specified position.
		 * @param value added value
		 * @param position position in internal list
		 * @throws bad_cast_exception if ValueType cannot be casted
		 */
		template<typename ValueType> void add_to_list(ValueType value,
			size_t position)
		{
			throw not_implemented_exception();
		}

		/**
		 * Remove element with same value as given one.
		 * @param value
		 * @throws bad_cast_exception if ValueType cannot be casted
		 * @throws not_found_exception if value was not found in list
		 */
		template<typename ValueType> void remove_from_list(ValueType value)
		{
			throw not_implemented_exception();
		}

		/**
		 * Remove list element on specified position.
		 * @param position
		 * @throws not_found_exception in case of out of range
		 */
		void remove_from_list_pos(size_t position);

		/**
		 * Validate this option against given option_schema.
		 * @param opt_schema validation schema
		 * @param mode validation mode
		 * @return true if option matches given option_schema, false otherwise
		 */
		bool validate(const option_schema &opt_schema, schema_mode mode);

		/**
		 * Classic stream operator for printing this instance to output stream.
		 * @param os output stream
		 * @return reference to output stream which allows chaining
		 */
		friend std::ostream &operator<<(std::ostream &os, const option &opt);
	};

	std::ostream &operator<<(std::ostream &os, const option &opt);
}

#endif
