#ifndef INICPP_OPTION_H
#define INICPP_OPTION_H

#include <cctype>
#include <iostream>
#include <memory>
#include <vector>

#include "dll.h"
#include "exception.h"
#include "option_schema.h"
#include "string_utils.h"
#include "types.h"
#include "types.h"


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
		virtual ~option_holder()
		{
		}
	};


	/**
	 * Class which actually stores option value in templated manner.
	 * Getter and setter of course provided.
	 */
	template <typename ValueType> class option_value : public option_holder
	{
	public:
		/**
		 * Construct option_value with given value.
		 * @param value value which will be stored
		 */
		option_value(ValueType value) : value_(value)
		{
		}
		/**
		 * Stated for completion.
		 */
		virtual ~option_value()
		{
		}

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
	 * Converting functions are specific only for option,
	 * so hide them in anonymous namespace.
	 */
	namespace
	{
		/**
		 * Template class holding method for converting value to other type.
		 *
		 * This is separate class because of partial template specialization,
		 * which is not allowed for templated methods.
		 */
		template <typename ActualType, typename ReturnType> class convertor
		{
		public:
			/**
			 * Get value of type ActualType from value argument and try to convert it
			 * to ReturnType.
			 * @param value Pointer to internal representation of option value
			 * @return Converted option value
			 * @throws bad_cast_exception if such cast cannot be made
			 */
			static ReturnType get_converted_value(const std::unique_ptr<option_holder> &value)
			{
				option_value<ActualType> *ptr = dynamic_cast<option_value<ActualType> *>(&*value);
				if (ptr == nullptr) {
					throw bad_cast_exception("Cannot cast to requested type");
				}
				try {
					return static_cast<ReturnType>(ptr->get());
				} catch (std::runtime_error &e) {
					throw bad_cast_exception(e.what());
				}
			}
		};

		/**
		 * Specialization of @ref convertor class for string result type
		 */
		template <typename ActualType> class convertor<ActualType, string_ini_t>
		{
		public:
			static string_ini_t get_converted_value(const std::unique_ptr<option_holder> &value)
			{
				option_value<ActualType> *ptr = dynamic_cast<option_value<ActualType> *>(&*value);
				if (ptr == nullptr) {
					throw bad_cast_exception("Cannot cast to requested type");
				}
				return inistd::to_string(ptr->get());
			}
		};
	} // anonymous namespace

	/**
	 * Represent ini configuration option.
	 * Can store one element or list of elements.
	 * Stored elements should have only supported types from option_type enum.
	 */
	class INICPP_API option
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

		/** Save copy of opt option into self */
		template <typename ValueType> void copy_option(const std::unique_ptr<option_holder> &opt)
		{
			option_value<ValueType> *ptr = dynamic_cast<option_value<ValueType> *>(&*opt);
			auto new_option_value = std::make_unique<option_value<ValueType>>(ptr->get());
			values_.push_back(std::move(new_option_value));
		}

		/** Compare local and remote option values, both of ValueType type. */
		template <typename ValueType>
		bool compare_option(
			const std::unique_ptr<option_holder> &local, const std::unique_ptr<option_holder> &remote) const
		{
			option_value<ValueType> *loc = dynamic_cast<option_value<ValueType> *>(&*local);
			option_value<ValueType> *rem = dynamic_cast<option_value<ValueType> *>(&*remote);
			return loc->get() == rem->get();
		}

		template <typename ReturnType>
		ReturnType convert_single_value(option_type source_type, const std::unique_ptr<option_holder> &value) const
		{
			switch (source_type) {
			case option_type::boolean_e: return convertor<boolean_ini_t, ReturnType>::get_converted_value(value); break;
			case option_type::enum_e: return convertor<enum_ini_t, ReturnType>::get_converted_value(value); break;
			case option_type::float_e: return convertor<float_ini_t, ReturnType>::get_converted_value(value); break;
			case option_type::signed_e: return convertor<signed_ini_t, ReturnType>::get_converted_value(value); break;
			case option_type::string_e: {
				option_value<string_ini_t> *ptr = dynamic_cast<option_value<string_ini_t> *>(&*value);
				if (ptr == nullptr) {
					throw bad_cast_exception("Cannot cast to requested type");
				}

				// We have string, so try to parse it
				try {
					return string_utils::parse_string<ReturnType>(ptr->get(), get_name());
				} catch (invalid_type_exception &e) {
					throw bad_cast_exception(e.what());
				}
			} break;
			case option_type::unsigned_e:
				return convertor<unsigned_ini_t, ReturnType>::get_converted_value(value);
				break;
			case option_type::invalid_e:
			default:
				// never reached
				throw invalid_type_exception("Invalid option type");
				break;
			}
		}

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
		 */
		option(const std::string &name, const std::string &value = "");
		/**
		 * Construct ini option with specified value of specified list type.
		 * @param name name of newly created option
		 * @param values initial value
		 */
		option(const std::string &name, const std::vector<std::string> &values);

		/**
		 * Gets this option name.
		 * @return constant reference to name
		 */
		const std::string &get_name() const;

		/**
		 * Gets current type of inner value.
		 * @return current type
		 */
		option_type get_type() const;
		/**
		* Determines if option is list or not.
		* @return true if option is list, false otherwise
		*/
		bool is_list() const;

		/**
		 * Set single element value.
		 * If option cointaned list of values,
		 *   than its transformed to single value.
		 * @param value newly assigned option value
		 */
		template <typename ValueType> void set(ValueType value)
		{
			this->operator=(value);
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
		option &operator=(const char *arg);
		/**
		 * Overloaded alias for set() function.
		 * @param arg string_t
		 * @return reference to this
		 */
		option &operator=(string_ini_t arg);
		/**
		 * Overloaded alias for set() function.
		 * @param arg enum_t
		 * @return reference to this
		 */
		option &operator=(enum_ini_t arg);

		/**
		 * Get single element value.
		 * If option value is list, than return first element of array.
		 * @return templated copy by value
		 * @throws bad_cast_exception if internal type cannot be casted
		 * @throws not_found_exception if there is no value
		 */
		template <typename ReturnType> ReturnType get() const
		{
			if (values_.empty()) {
				throw not_found_exception(0);
			}

			// Get the value and try to convert it
			return convert_single_value<ReturnType>(type_, values_[0]);
		}

		/**
		 * Set internal list of values to given one.
		 * If option contained single value than its transformed to list
		 *   with given values.
		 * @param list reference to list of new values
		 * @throws bad_cast_exception if ValueType cannot be casted
		 * to internal type
		 */
		template <typename ValueType> void set_list(const std::vector<ValueType> &list)
		{
			values_.clear();
			type_ = get_option_enum_type<ValueType>();
			for (const auto &item : list) {
				add_to_list(item);
			}
		}

		/**
		 * Get list of internal values. Returning list is newly created.
		 * If option contains single value than its returned list
		 *   with one element.
		 * @return new list of all stored values
		 * @throws bad_cast_exception if internal type cannot be casted
		 * @throws not_found_exception if there is no value
		 */
		template <typename ReturnType> std::vector<ReturnType> get_list() const
		{
			if (values_.empty()) {
				throw not_found_exception(0);
			}
			std::vector<ReturnType> results;
			for (const auto &value : values_) {
				results.push_back(convert_single_value<ReturnType>(type_, value));
			}

			return results;
		}

		/**
		 * Adds element to internal value list.
		 * If option was single value than its transformed to list.
		 * @param value pushed value
		 * @throws bad_cast_exception if ValueType cannot be casted
		 */
		template <typename ValueType> void add_to_list(ValueType value)
		{
			if (get_option_enum_type<ValueType>() != type_) {
				throw bad_cast_exception("Cannot cast to requested type");
			}
			auto new_option_value = std::make_unique<option_value<ValueType>>(value);
			values_.push_back(std::move(new_option_value));
		}

		/**
		 * Add element to list on specified position.
		 * If option was single value than its transformed to list.
		 * @param value added value
		 * @param position position in internal list
		 * @throws bad_cast_exception if ValueType cannot be casted
		 * @throws not_found_exception if position is not in internal list
		 */
		template <typename ValueType> void add_to_list(ValueType value, size_t position)
		{
			if (get_option_enum_type<ValueType>() != type_) {
				throw bad_cast_exception("Cannot cast to requested type");
			}
			if (position > values_.size()) {
				throw not_found_exception(position);
			}
			auto new_option_value = std::make_unique<option_value<ValueType>>(value);
			values_.insert(values_.begin() + position, std::move(new_option_value));
		}

		/**
		 * Remove element with same value as given one.
		 * @param value
		 * @throws bad_cast_exception if ValueType cannot be casted
		 */
		template <typename ValueType> void remove_from_list(ValueType value)
		{
			if (get_option_enum_type<ValueType>() != type_) {
				throw bad_cast_exception("Cannot cast to requested type");
			}
			for (auto it = values_.cbegin(); it != values_.cend(); ++it) {
				option_value<ValueType> *ptr = dynamic_cast<option_value<ValueType> *>(&*(*it));
				if (ptr->get() == value) {
					values_.erase(it);
					break;
				}
			}
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
		 * @throws validation_exception if error occured
		 */
		void validate(const option_schema &opt_schema);

		/**
		 * Equality operator.
		 * @param other
		 * @return
		 */
		bool operator==(const option &other) const;
		/**
		 * Inequality operator.
		 * @param other
		 * @return
		 */
		bool operator!=(const option &other) const;

		/**
		 * Classic stream operator for printing this instance to output stream.
		 * @param os output stream
		 * @param opt reference to option instance to be written
		 * @return reference to output stream which allows chaining
		 */
		INICPP_API friend std::ostream &operator<<(std::ostream &os, const option &opt);
	};

	INICPP_API std::ostream &operator<<(std::ostream &os, const option &opt);
}

#endif
