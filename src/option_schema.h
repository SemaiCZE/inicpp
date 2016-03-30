#ifndef INICPP_OPTION_SCHEMA_H
#define INICPP_OPTION_SCHEMA_H

#include <vector>
#include <string>
#include <iostream>

#include "exception.h"
#include "option.h"

namespace inicpp
{
	enum class option_type { boolean_t, signed_t, unsigned_t, float_t, enum_t, string_t };
	
	typedef bool boolean_t;
	typedef int64_t signed_t;
	typedef uint64_t unsigned_t;
	typedef double float_t;
	typedef std::vector<std::string> enum_t;
	typedef std::string string_t;


	class option_schema
	{
	private:
		std::string name_;
		bool is_list_;
		option_type type_;
		std::string default_value_;
		bool mandatory_;
		// TODO: restriction function reference
		// TODO: access methods for private members

	public:
		option_schema();
		option_schema(const option_schema &source);
		option_schema &operator=(const option_schema &source);
		option_schema(option_schema &&source);
		option_schema &operator=(option_schema &&source);

		std::ostream &operator<<(std::ostream &os);
		
		bool is_list() const;
		
		bool validate(const std::string &str) const;
		bool validate(const option &opt) const;
	};
}

#endif
