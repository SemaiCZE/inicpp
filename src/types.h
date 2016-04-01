#ifndef INICPP_TYPES_H
#define INICPP_TYPES_H

namespace inicpp
{
	/**
	 * @brief The option_type enum
	 */
	enum class option_type : char { boolean_e, signed_e, unsigned_e, float_e, enum_e, string_e };
	
	typedef bool boolean_t;
	typedef int64_t signed_t;
	typedef uint64_t unsigned_t;
	typedef double float_t;
	typedef std::vector<std::string> enum_t;
	typedef std::string string_t;

	/**
	 * @brief The schema_mode enum
	 */
	enum class schema_mode : bool { strict, relaxed };
}

#endif // INICPP_TYPES_H
