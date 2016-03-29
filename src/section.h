#ifndef INICPP_SECTION_H
#define INICPP_SECTION_H

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
		friend class section;
		const section &container_;
		size_t pos_;
	public:
		section_iterator(const section &source) : container_(source) {}
		section_iterator(const section_iterator& source) : container_(source.container_), pos_(source.pos_) {}

		section_iterator& operator++() { ++pos_; return *this; }
		section_iterator operator++(int) { section_iterator old(*this); operator++(); return old; }

		bool operator==(const section_iterator &second) { return pos_ == second.pos_; }
		bool operator!=(const section_iterator &second) { return pos_ != second.pos_; }

		reference operator*() { return container_.options_.at(pos_); }
	};


	class section
	{
	private:
		std::vector<option> options_;
		bool name_;

	public:
		typedef section_iterator iterator;

		section();
		section(const section &source);
		section& operator=(const section &source);
		section(section &&source);
		section& operator=(section &&source);
		
		template<ValueType> void add_option(std::string name, ValueType value);
		void add_option(const option &opt);

		const std::vector<option> &get_options();
		option &operator[](size_t index);

		std::ostream& operator<<(std::ostream& os);
	};
}

#endif
