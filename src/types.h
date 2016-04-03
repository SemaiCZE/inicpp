#ifndef INICPP_TYPES_H
#define INICPP_TYPES_H

namespace inicpp
{
	/**
	 * Types which can be used in option and option_schema classes.
	 * Only from and to this types casting is recommended.
	 * For all of this types appropriate typedefs are supplied.
	 */
	enum class option_type : char
	{
		boolean_e,
		signed_e,
		unsigned_e,
		float_e,
		enum_e,
		string_e
	};
	
	typedef bool boolean_t;
	typedef int64_t signed_t;
	typedef uint64_t unsigned_t;
	typedef double float_t;
	typedef std::vector<std::string> enum_t;
	typedef std::string string_t;

	/**
	 * Mode in which schema can be validated.
	 *  Strict - everything has to be right and in appropriate type.
	 *  Relaxed - config can contain unknown sections and options.
	 */
	enum class schema_mode : bool { strict, relaxed };
}

#endif // INICPP_TYPES_H
