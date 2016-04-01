#ifndef INICPP_OPTION_SCHEMA_H
#define INICPP_OPTION_SCHEMA_H

#include <vector>
#include <string>
#include <iostream>

#include "exception.h"
#include "option.h"

namespace inicpp
{
	/** */
	struct option_schema_params
	{
		/** */
		std::string name;
		/** */
		bool mandatory = true;
		/** */
		option_type type = option_type::string_e;
		/** */
		bool is_list = false;
		/** */
		std::string default_value = "";
		/** */
		std::string comment;
	};

	
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
		option_schema(const option_schema_params &arguments);

		/**
		 * @brief
		 * @return
		 */
		const std::string &get_name() const;
		/**
		 * @brief
		 * @return
		 */
		option_type get_type() const;
		/**
		 * @brief is_list
		 * @return
		 */
		bool is_list() const;
		/**
		 * @brief
		 * @return
		 */
		const std::string &get_default_value() const;
		/**
		 * @brief
		 * @return
		 */
		bool is_mandatory() const;
		/**
		 * @brief
		 * @return
		 */
		const std::string &get_comment() const;

		/**
		 * @brief validate
		 * @param opt
		 * @return
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
