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
	
	typedef bool boolean_ini_t;
	typedef int64_t signed_ini_t;
	typedef uint64_t unsigned_ini_t;
	typedef double float_ini_t;
	typedef std::string enum_ini_t;
	typedef std::string string_ini_t;

	/**
	 * Enumeration type used in schema specification which distinguishes
	 * between single item and list of items.
	 */
	enum class option_item: bool { single, list };

	/**
	 * Type used to distinguish between mandatory and optional values
	 * in schema specification.
	 */
	enum class item_requirement : bool { mandatory, optional };

	/**
	 * Mode in which schema can be validated.
	 *  Strict - everything has to be right and in appropriate type.
	 *  Relaxed - config can contain unknown sections and options.
	 */
	enum class schema_mode : bool { strict, relaxed };
}

#endif // INICPP_TYPES_H
