#ifndef INICPP_STRING_UTILS_H
#define INICPP_STRING_UTILS_H

#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>

namespace inicpp
{
	namespace string_utils
	{
		std::string trim(const std::string &str);

		bool find_needle(const std::string &haystack, const std::string &needle);

		bool starts_with(const std::string &str, const std::string &search_str);

		bool ends_with(const std::string &str, const std::string &search_str);

		std::vector<std::string> split(const std::string &str, char delim);
	}
}

#endif // INICPP_STRING_UTILS_H
