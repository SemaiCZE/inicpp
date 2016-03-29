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

	template<Element>
	class section_iterator : public std::iterator<std::random_access_iterator_tag, Element>
	{
	private:
		using std::iterator<std::random_access_iterator_tag, option>::reference;
		
		section &container_;
		size_t position_;
	public:
		section_iterator() = delete;
		section_iterator(section &source, size_t position) : container_(source), position_(position) {}
		section_iterator(section &source) : section_iterator(source, 0) {}
		section_iterator(const section_iterator &source) : section_iterator(source.container_, source.position_) {}

		section_iterator &operator++() { ++position_; return *this; }
		section_iterator operator++(int) { section_iterator old(*this); operator++(); return old; }

		bool operator==(const section_iterator &second)
		{
			return this == &second && position_ == second.position_;
		}
		bool operator!=(const section_iterator &second)
		{
			return !(*this == second);
		}
		reference operator*() { return container_.options_.at(position_); }
	};
}

#endif
