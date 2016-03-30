#ifndef INICPP_SECTION_H
#define INICPP_SECTION_H

#include <vector>
#include <iostream>
#include <iterator>

#include "exception.h"
#include "option.h"

namespace inicpp
{
	template<typename T> class section_iterator;
	

	class section
	{
	private:
		std::vector<option> options_;
		bool name_;

		friend class section_iterator<option>;
		friend class section_iterator<const option>;

	public:
		typedef section_iterator<option> iterator;
		typedef section_iterator<const option> const_iterator;

		section();
		section(const section &source);
		section& operator=(const section &source);
		section(section &&source);
		section& operator=(section &&source);
		
		template<typename ValueType> void add_option(const std::string &name, const ValueType &value)
		{
			throw not_implemented_exception();
		}
		void add_option(const option &opt);

		const std::vector<option> &get_options() const;
		option &operator[](size_t index);
		option &operator[](const std::string &option_name);

		std::ostream &operator<<(std::ostream &os);

		iterator begin();
		iterator end();
		const_iterator cbegin() const;
		const_iterator cend() const;
	};
	

	template<typename Element>
	class section_iterator : public std::iterator<std::random_access_iterator_tag, Element>
	{
	private:
		using typename std::iterator<std::random_access_iterator_tag, Element>::reference;
		
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
