#ifndef INICPP_STRING_UTILS_H
#define INICPP_STRING_UTILS_H

#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>
#include "types.h"

namespace inicpp
{
	/**
	 * Namespace which contains methods for everyday work with string.
	 * Should be contextless and can be used in any other library or program.
	 */
	namespace string_utils
	{
		/**
		 * Trim whitespaces from start and end of given string.
		 * @param str processed string
		 * @return newly created instance of string
		 */
		std::string trim(const std::string &str);
		/**
		 * In @a haystack find any occurence of needle.
		 * @param haystack string in which search is executed
		 * @param needle string which is searched for
		 * @return true if at least one @a needle was found, false otherwise
		 */
		bool find_needle(const std::string &haystack, const std::string &needle);
		/**
		 * Tries to find out if given @a str starts with @a search_str.
		 * @param str searched string
		 * @param search_str string which is searched for
		 * @return true if given string starts with @a search_str
		 */
		bool starts_with(const std::string &str, const std::string &search_str);
		/**
		 * Tries to find out if given @a str ends with @a search_str.
		 * @param str searched string
		 * @param search_str string which is searched for
		 * @return true if given string starts with @a search_str
		 */
		bool ends_with(const std::string &str, const std::string &search_str);
		/**
		 * Split given string with given delimiter.
		 * @param str text which will be splitted
		 * @param delim delimiter
		 * @return array of newly created substrings
		 */
		std::vector<std::string> split(const std::string &str, char delim);

		signed_ini_t parse_signed_type(const std::string &value, const std::string &option_name);
		unsigned_ini_t parse_unsigned_type(const std::string &value, const std::string &option_name);
		float_ini_t parse_float_type(const std::string &value, const std::string &option_name);
		enum_ini_t parse_enum_type(const std::string &value, const std::string &option_name);
		boolean_ini_t parse_boolean_type(const std::string &value, const std::string &option_name);
	}
}

#endif // INICPP_STRING_UTILS_H
