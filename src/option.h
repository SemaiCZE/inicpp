#ifndef INICPP_OPTION_H
#define INICPP_OPTION_H

#include <vector>
#include <memory>
#include <iostream>

#include "exception.h"
#include "types.h"

namespace inicpp
{
	class option_holder
	{
	public:
		virtual ~option_holder() {}
	};


	template<typename T>
	class option_value : public option_holder
	{
	public:
		option_value(T value) : value_(value) {}
		virtual ~option_value() {}
		T get()
		{
			return value_;
		}
		void set(T value)
		{
			value_ = value;
		}
	private:
		T value_;
	};

	
	/**
	 * @brief The option class
	 */
	class option
	{
	private:
		/** */
		std::string name_;
		/** */
		std::vector<std::unique_ptr<option_holder>> values_;
		// TODO: access methods for private members

	public:
		/**
		 * @brief option
		 */
		option();
		option(const option &source);
		option &operator=(const option &source);
		option(option &&source);
		option &operator=(option &&source);

		/**
		 * @brief option
		 * @param name
		 * @param value
		 */
		option(const std::string &name, const std::string &value = "", option_type type = option_type::string_t);

		/**
		 * @brief set
		 * @param value
		 */
		template<typename ValueType> void set(ValueType value)
		{
			throw not_implemented_exception();
		}

		/**
		 * @brief get
		 * @return
		 */
		template<typename ValueType> ValueType get() const
		{
			throw not_implemented_exception();
		}

		/**
		 * @brief set_list
		 * @param value
		 */
		template<typename ValueType> void set_list(const std::vector<ValueType> &value)
		{
			throw not_implemented_exception();
		}
		
		/**
		 * @brief set_list
		 * @param value
		 */
		template<typename ValueType> void set_list(std::vector<ValueType> &&value)
		{
			throw not_implemented_exception();
		}
		
		/**
		 * @brief get_list
		 * @return
		 */
		template<typename ValueType> std::vector<ValueType> get_list() const
		{
			throw not_implemented_exception();
		}

		/**
		 * @brief add_to_list
		 * @param value
		 */
		template<typename ValueType> void add_to_list(ValueType value)
		{
			throw not_implemented_exception();
		}

		/**
		 * @brief add_to_list
		 * @param value
		 * @param position
		 */
		template<typename ValueType> void add_to_list(ValueType value, size_t position)
		{
			throw not_implemented_exception();
		}

		/**
		 * @brief remove_from_list
		 * @param value
		 */
		template<typename ValueType> void remove_from_list(ValueType value)
		{
			throw not_implemented_exception();
		}

		/**
		 * @brief remove_from_list
		 * @param position
		 */
		void remove_from_list(size_t position);

		/**
		 * @brief operator <<
		 * @param os
		 * @return
		 */
		std::ostream &operator<<(std::ostream &os);

		/**
		 * @brief is_list
		 * @return
		 */
		bool is_list() const;
	};
}

#endif
