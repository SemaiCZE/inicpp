#ifndef INICPP_SECTION_ITERATOR_H
#define INICPP_SECTION_ITERATOR_H

#include <vector>
#include <iostream>
#include <iterator>

#include "exception.h"
#include "option.h"

namespace inicpp
{
	class section {};

	class section_iterator : public std::iterator<std::random_access_iterator_tag, option>
	{
	private:
		section &container_;
		size_t pos_;
	public:
		section_iterator(const section &source) : container_(source) {}
		section_iterator(const section_iterator &source) : container_(source.container_), pos_(source.pos_) {}

		section_iterator &operator++() { ++pos_; return *this; }
		section_iterator operator++(int) { section_iterator old(*this); operator++(); return old; }

		bool operator==(const section_iterator &second) { return pos_ == second.pos_; }
		bool operator!=(const section_iterator &second) { return pos_ != second.pos_; }
		reference operator*() { return container_.options_.at(pos_); }
	};

	class const_section_iterator : public std::iterator<std::random_access_iterator_tag, option>
	{
	private:
		const section &container_;
		size_t pos_;
	public:
		const_section_iterator(const section &source) : container_(source) {}
		const_section_iterator(const const_section_iterator &source) : container_(source.container_), pos_(source.pos_) {}

		const_section_iterator &operator++() { ++pos_; return *this; }
		const_section_iterator operator++(int) { const_section_iterator old(*this); operator++(); return old; }

		bool operator==(const const_section_iterator &second) { return pos_ == second.pos_; }
		bool operator!=(const const_section_iterator &second) { return pos_ != second.pos_; }
		const reference operator*() { return container_.options_.at(pos_); }
	};
}

#endif
