#ifndef INICPP_OPTION_SCHEMA_H
#define INICPP_OPTION_SCHEMA_H

#include <vector>
#include <string>
#include <iostream>

#include "exception.h"
#include "option.h"

namespace inicpp
{
	/** Forward declaration, stated because of ring dependencies */
	class option;


	/**
	 * @brief The option_schema class
	 */
	class option_schema
	{
	private:
		/** */
		std::string name_;
		/** */
		option_type type_;
		/** */
		bool is_list_;
		/** */
		std::string default_value_;
		/** */
		bool mandatory_;
		/** */
		std::string comment_;
		// TODO: restriction function reference
		// TODO: access methods for private members

	public:
		/**
		 * @brief option_schema
		 */
		option_schema();
		option_schema(const option_schema &source);
		option_schema &operator=(const option_schema &source);
		option_schema(option_schema &&source);
		option_schema &operator=(option_schema &&source);

		/**
		 * @brief option_schema
		 * @param name
		 * @param is_mandatory
		 * @param type
		 * @param is_list
		 * @param default_value
		 */
		option_schema(const std::string &name, bool mandatory = true,
			option_type type = option_type::string_t, bool is_list = false,
			const std::string &default_value = "");

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

		/**
		 * @brief validate
		 * @param opt
		 * @return
		 */
		bool validate(const option &opt) const;
	};
}

#endif
