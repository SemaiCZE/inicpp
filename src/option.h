#ifndef INICPP_OPTION_H
#define INICPP_OPTION_H

#include <vector>
#include <iostream>

#include "exception.h"

namespace inicpp
{
	/**
	 * @brief The option class
	 */
	class option
	{
	private:
		/** */
		std::string name_;
		/** */
		bool is_list_;
		/** */
		std::string value_;
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
		 * @param is_list
		 * @param value
		 */
		option(const std::string &name, bool is_list = false, const std::string &value = "");

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
