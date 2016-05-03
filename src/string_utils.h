#ifndef INICPP_STRING_UTILS_H
#define INICPP_STRING_UTILS_H

#include <string>
#include <cctype>
#include <algorithm>

namespace inicpp
{
	namespace string_utils
	{
		inline std::string trim(const std::string &str)
		{
			auto front = std::find_if(str.begin(), str.end(), [] (int c) { return !std::isspace(c); });
			auto back = std::find_if(str.rbegin(), str.rend(), [] (int c) { return !std::isspace(c); }).base();

			if (back <= front) {
				return "";
			}
			return std::string(front, back);
		}
	}
}

#endif // INICPP_STRING_UTILS_H
