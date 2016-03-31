#ifndef INICPP_TYPES_H
#define INICPP_TYPES_H

namespace inicpp
{
	/**
	 * @brief The option_type enum
	 */
	enum class option_type { boolean_t, signed_t, unsigned_t, float_t, enum_t, string_t };
	
	typedef bool boolean_t;
	typedef int64_t signed_t;
	typedef uint64_t unsigned_t;
	typedef double float_t;
	typedef std::vector<std::string> enum_t;
	typedef std::string string_t;

	/**
	 * @brief The schema_mode enum
	 */
	enum class schema_mode { strict, relaxed };
}

#endif // INICPP_TYPES_H
