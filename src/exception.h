#ifndef INICPP_EXCEPTION_H
#define INICPP_EXCEPTION_H

#include <vector>
#include <string>
#include <iostream>
#include <exception>

namespace inicpp
{
	/**
	 * Generic inicpp exception.
	 */
	class exception : public std::exception
	{
	protected:
		/** Description of exception */
		std::string what_;
	public:
		/**
		 * Default constructor.
		 */
		exception();
		/**
		 * Constructor in which cause can be specified.
		 * @param what exception description
		 */
		exception(const std::string &what);
		
		/**
		 * Desctuctor.
		 */
		virtual ~exception();

		/**
		 * Return description of this exception instance.
		 * @return c-string textual description
		 */
		virtual const char *what() const noexcept;
	};


	/**
	 * Occurs when two elements cannot be successfully casted.
	 */
	class bad_cast_exception : public exception
	{
	public:
		/**
		 * General bad_cast_exception constructor with given description.
		 * @param what exception cause
		 */
		bad_cast_exception(const std::string &message);
		/**
		 * Constructor in which casted elements can be specified.
		 * @param from type from which conversion was invoked
		 * @param to type to which conversion was invoked
		*/
		bad_cast_exception(const std::string &from, const std::string &to);
	};


	/**
	 * Element not found exception.
	 * Raised when there is no element with specified name
	 * or with specified index.
	 */
	class not_found_exception : public exception
	{
	public:
		/**
		 * Element on specified index was not found.
		 * @param index
		 */
		not_found_exception(size_t index);
		/**
		 * Element with specified name was not found.
		 * @param element_name 
		 */
		not_found_exception(const std::string &element_name);
	};


	/**
	 * Element ambiguity exception.
	 * Raised when there are multiple elements with same name.
	 */
	class ambiguity_exception : public exception
	{
	public:
		/**
		 * There are multiple elements with specified name.
		 * @param element_name
		 */
		ambiguity_exception(const std::string &element_name);
	};


	/**
	 * Thrown in case of validation error.
	 */
	class validation_exception : public exception
	{
	public:
		/**
		 * Default generic constructor.
		 * @param message
		 */
		validation_exception(const std::string &message);
	};


	/**
	 * Thrown in case of bad format of input ini configuration.
	 */
	class invalid_config_exception : public exception
	{
	public:
		/**
		 * Default generic constructor.
		 * @param message
		 */
		invalid_config_exception(const std::string &message);
	};


	/**
	 * Thrown in case of missing function implementation.
	 */
	class not_implemented_exception : public exception
	{
	public:
		/**
		 * Generic constructor.
		 */
		not_implemented_exception();
	};
}

#endif
