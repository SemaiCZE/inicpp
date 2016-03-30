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
	 * @brief The option_type enum
	 */
	enum class option_type { boolean_t, signed_t, unsigned_t, float_t, enum_t, string_t };
	
	typedef bool boolean_t;
	typedef int64_t signed_t;
	typedef uint64_t unsigned_t;
	typedef double float_t;
	typedef std::vector<std::string> enum_t;
	typedef std::string string_t;


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
		 * @param str
		 * @return
		 */
		bool validate(const std::string &str) const;
		/**
		 * @brief validate
		 * @param opt
		 * @return
		 */
		bool validate(const option &opt) const;
	};
}

#endif
