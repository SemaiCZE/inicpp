#ifndef INICPP_PARSER_H
#define INICPP_PARSER_H

#include <iostream>

#include "exception.h"
#include "config.h"
#include "schema.h"

namespace inicpp
{
	/**
	 * @brief The parser class
	 */
	class parser
	{
	public:
		/**
		 * @brief parser
		 */
		parser() = delete;
		parser(const parser &source) = delete;
		parser& operator=(const parser &source) = delete;
		parser(parser &&source) = delete;
		parser& operator=(parser &&source) = delete;

		/**
		 * @brief load
		 * @param str
		 * @return
		 */
		static config load(const std::string &str);
		/**
		 * @brief load
		 * @param str
		 * @param schm
		 * @param md
		 * @return
		 */
		static config load(const std::string &str, const schema &schm, schema_mode mode);
		/**
		 * @brief load
		 * @param str
		 * @return
		 */
		static config load(std::istream str);
		/**
		 * @brief load
		 * @param str
		 * @param schm
		 * @param md
		 * @return
		 */
		static config load(std::istream str, const schema &schm, schema_mode mode);

		/**
		 * @brief load_file
		 * @param file
		 * @return
		 */
		static config load_file(const std::string &file);
		/**
		 * @brief load_file
		 * @param file
		 * @param schm
		 * @param md
		 * @return
		 */
		static config load_file(const std::string &file, const schema &schm, schema_mode mode);

		/**
		 * @brief save
		 * @param cfg
		 * @param file
		 */
		static void save(const config &cfg, const std::string &file);
		/**
		 * @brief save
		 * @param cfg
		 * @param str
		 */
		static void save(const config &cfg, std::ostream str);
		/**
		 * @brief save
		 * @param schm
		 * @param file
		 */
		static void save(const schema &schm, const std::string &file);
		/**
		 * @brief save
		 * @param schm
		 * @param file
		 */
		static void save(const schema &schm, std::ostream file);
	};
}

#endif
