#ifndef INICPP_SECTION_ITERATOR_H
#define INICPP_SECTION_ITERATOR_H

#include <vector>
#include <iostream>
#include <iterator>

#include "exception.h"
#include "section.h"
#include "option.h"

namespace inicpp
{
	class section;

	class section_iterator : public std::iterator<std::random_access_iterator_tag, option>
	{
	private:
		using std::iterator<std::random_access_iterator_tag, option>::reference;
		
		section &container_;
		size_t pos_;
	public:
		section_iterator(section &source);
		section_iterator(const section_iterator &source);

		section_iterator &operator++();
		section_iterator operator++(int);

		bool operator==(const section_iterator &second);
		bool operator!=(const section_iterator &second);
		reference operator*();
	};


	class const_section_iterator : public std::iterator<std::random_access_iterator_tag, const option>
	{
	private:
		using std::iterator<std::random_access_iterator_tag, const option>::reference;
		
		const section &container_;
		size_t pos_;
	public:
		const_section_iterator(const section &source);
		const_section_iterator(const const_section_iterator &source);

		const_section_iterator &operator++();
		const_section_iterator operator++(int);

		bool operator==(const const_section_iterator &second);
		bool operator!=(const const_section_iterator &second);
		reference operator*() const;
	};
}

#endif
