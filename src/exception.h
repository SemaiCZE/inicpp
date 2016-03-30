#ifndef INICPP_EXCEPTION_H
#define INICPP_EXCEPTION_H

#include <vector>
#include <iostream>
#include <exception>

namespace inicpp
{
	/**
	 * @brief The exception class
	 */
	class exception : public std::exception
	{
	protected:
		/** */
		std::string what_;
	public:
		/**
		 * @brief exception
		 */
		exception();
		/**
		 * @brief exception
		 * @param what
		 */
		exception(const std::string &what);
		
		/**
		 * @brief ~exception
		 */
		virtual ~exception();

		/**
		 * @brief what
		 * @return
		 */
		virtual const char *what() const noexcept;
	};


	/**
	 * @brief The not_implemented_exception class
	 */
	class not_implemented_exception : public exception
	{
	public:
		/**
		 * @brief not_implemented_exception
		 */
		not_implemented_exception();

		/**
		 * @brief what
		 * @return
		 */
		virtual const char *what() const noexcept;
	};
}

#endif
