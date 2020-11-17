#include "string_utils.h"
#include "exception.h"
#include <algorithm>
#include <string>

namespace inicpp
{
	namespace string_utils
	{
		std::string left_trim(const std::string &str)
		{
			auto front = std::find_if(str.begin(), str.end(), [](int c) { return !std::isspace(c); });
			return std::string(front, str.end());
		}

		std::string right_trim(const std::string &str)
		{
			auto back = std::find_if(str.rbegin(), str.rend(), [](int c) { return !std::isspace(c); }).base();
			return std::string(str.begin(), back);
		}

		std::string trim(const std::string &str)
		{
			auto front = std::find_if(str.begin(), str.end(), [](int c) { return !std::isspace(c); });
			auto back = std::find_if(str.rbegin(), str.rend(), [](int c) { return !std::isspace(c); }).base();

			if (back <= front) { return ""; }
			return std::string(front, back);
		}

		bool find_needle(const std::string &haystack, const std::string &needle)
		{
			return (haystack.find(needle) == std::string::npos ? false : true);
		}

		bool starts_with(const std::string &str, const std::string &search_str)
		{
			size_t search_str_length = search_str.length();

			if (search_str_length > str.length()) { return false; }

			for (size_t i = 0; i < search_str_length; ++i) {
				if (str[i] != search_str[i]) { return false; }
			}

			return true;
		}

		bool ends_with(const std::string &str, const std::string &search_str)
		{
			size_t search_str_length = search_str.length();
			size_t str_length = str.length();

			if (search_str_length > str.length()) { return false; }

			for (size_t i = 0; i < search_str_length; ++i) {
				if (str[str_length - i - 1] != search_str[search_str_length - i - 1]) { return false; }
			}

			return true;
		}

		std::vector<std::string> split(const std::string &str, char delim)
		{
			std::vector<std::string> result;
			std::stringstream stream(str);
			std::string item;

			while (std::getline(stream, item, delim)) { result.push_back(item); }
			return result;
		}


		template <> string_ini_t parse_string<string_ini_t>(const std::string &value, const std::string &)
		{
			return value;
		}
		template <> boolean_ini_t parse_string<boolean_ini_t>(const std::string &value, const std::string &option_name)
		{
			if (value == "0" || value == "f" || value == "n" || value == "off" || value == "no" ||
				value == "disabled") {
				return false;
			} else if (value == "1" || value == "t" || value == "y" || value == "on" || value == "yes" ||
				value == "enabled") {
				return true;
			} else {
				throw invalid_type_exception(
					"Option '" + option_name + "' parsing failed: String '" + value + "' is not valid boolean type.");
			}
		}

		template <> enum_ini_t parse_string<enum_ini_t>(const std::string &value, const std::string &)
		{
			return enum_ini_t(value);
		}

		template <> float_ini_t parse_string<float_ini_t>(const std::string &value, const std::string &option_name)
		{
			try {
				return std::stod(value);
			} catch (std::exception &e) {
				throw invalid_type_exception("Option '" + option_name + "' parsing failed: " + e.what());
			}
		}

		template <> signed_ini_t parse_string<signed_ini_t>(const std::string &value, const std::string &option_name)
		{
			try {
				std::string binary_prefix = "0b";
				if (std::equal(binary_prefix.begin(), binary_prefix.end(), value.begin())) {
					// this is binary number
					return std::stoll(value.substr(2), 0, 2);
				} else {
					// decimal and hexadecimal number can handle stoll itself
					return std::stoll(value, 0, 0);
				}
			} catch (std::exception &e) {
				throw invalid_type_exception("Option '" + option_name + "' parsing failed: " + e.what());
			}
		}

		template <>
		unsigned_ini_t parse_string<unsigned_ini_t>(const std::string &value, const std::string &option_name)
		{
			try {
				std::string binary_prefix = "0b";
				if (value.size() > binary_prefix.size() &&
					std::equal(binary_prefix.begin(), binary_prefix.end(), value.begin())) {
					// this is binary number
					return std::stoull(value.substr(2), 0, 2);
				} else {
					// decimal and hexadecimal number can handle stoull itself
					return std::stoull(value, 0, 0);
				}
			} catch (std::exception &e) {
				throw invalid_type_exception("Option '" + option_name + "' parsing failed: " + e.what());
			}
		}
	} // namespace string_utils

	namespace inistd
	{
		std::string to_string(const enum_ini_t &value)
		{
			return static_cast<std::string>(value);
		}
	} // namespace inistd
} // namespace inicpp
