#ifndef INICPP_EXCEPTION_H
#define INICPP_EXCEPTION_H

#include <vector>
#include <iostream>
#include <exception>

#include "exception.h"
#include "section_schema.h"
#include "option_schema.h"

namespace inicpp
{
	class exception : public std::exception
	{
	protected:
		std::string what_;
	public:
		exception();
		exception(const std::string &what);
		
		virtual ~exception();

		virtual const char *what() const noexcept;
	};

	class not_implemented_exception : public exception
	{
	public:
		not_implemented_exception();
		not_implemented_exception(const std::string &what);

		virtual ~not_implemented_exception();

		virtual const char *what() const noexcept;
	};
}

#endif
