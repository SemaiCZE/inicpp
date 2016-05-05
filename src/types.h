#ifndef INICPP_TYPES_H
#define INICPP_TYPES_H

#include <type_traits>


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
		string_e,
		invalid_e
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

	/**
	 * Function for convert type (one of *_ini_t) to option_type
	 * enumeration type. If type cannot be converted, invalid_e
	 * is returned.
	 * @return enum representation of templated type
	 */
	template <typename ValueType>
	option_type get_enum_type()
	{
		if (std::is_same<ValueType, boolean_ini_t>::value) {
			return option_type::boolean_e;
		} else if (std::is_same<ValueType, signed_ini_t>::value) {
			return option_type::signed_e;
		} else if (std::is_same<ValueType, unsigned_ini_t>::value) {
			return option_type::unsigned_e;
		} else if (std::is_same<ValueType, float_ini_t>::value) {
			return option_type::float_e;
		} else if (std::is_same<ValueType, string_ini_t>::value) {
			return option_type::string_e;
		} else if (std::is_same<ValueType, enum_ini_t>::value) {
			return option_type::enum_e;
		} else {
			return option_type::invalid_e;
		}
	}
}

#endif // INICPP_TYPES_H
