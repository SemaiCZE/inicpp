#include "string_utils.h"
#include "exception.h"

namespace inicpp
{
	namespace string_utils
	{
		std::string trim(const std::string &str)
		{
			auto front = std::find_if(str.begin(), str.end(), [](int c) { return !std::isspace(c); });
			auto back = std::find_if(str.rbegin(), str.rend(), [](int c) { return !std::isspace(c); }).base();

			if (back <= front) {
				return "";
			}
			return std::string(front, back);
		}

		bool find_needle(const std::string &haystack, const std::string &needle)
		{
			return (haystack.find(needle) == std::string::npos ? false : true);
		}

		bool starts_with(const std::string &str, const std::string &search_str)
		{
			size_t search_str_length = search_str.length();

			if (search_str_length > str.length()) {
				return false;
			}

			for (size_t i = 0; i < search_str_length; ++i) {
				if (str[i] != search_str[i]) {
					return false;
				}
			}

			return true;
		}

		bool ends_with(const std::string &str, const std::string &search_str)
		{
			size_t search_str_length = search_str.length();
			size_t str_length = str.length();

			if (search_str_length > str.length()) {
				return false;
			}

			for (size_t i = 0; i < search_str_length; ++i) {
				if (str[str_length - i - 1] != search_str[search_str_length - i - 1]) {
					return false;
				}
			}

			return true;
		}

		std::vector<std::string> split(const std::string &str, char delim)
		{
			std::vector<std::string> result;
			std::stringstream stream(str);
			std::string item;

			while (std::getline(stream, item, delim)) {
				result.push_back(item);
			}
			return result;
		}

		signed_ini_t parse_signed_type(const std::string &value)
		{
			try {
				return std::stoll(value);
			} catch (std::exception &e) {
				throw invalid_type_exception(e.what());
			}
		}
	}
}
