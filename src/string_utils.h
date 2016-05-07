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
	namespace string_utils
	{
		std::string trim(const std::string &str);

		bool find_needle(const std::string &haystack, const std::string &needle);

		bool starts_with(const std::string &str, const std::string &search_str);

		bool ends_with(const std::string &str, const std::string &search_str);

		std::vector<std::string> split(const std::string &str, char delim);

		signed_ini_t parse_signed_type(const std::string &value);
		unsigned_ini_t parse_unsigned_type(const std::string &value);
		float_ini_t parse_float_type(const std::string &value);
		enum_ini_t parse_enum_type(const std::string &value);
		boolean_ini_t parse_boolean_type(const std::string &value);
	}
}

#endif // INICPP_STRING_UTILS_H
