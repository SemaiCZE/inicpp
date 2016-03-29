#ifndef INICPP_CONFIG_ITERATOR_H
#define INICPP_CONFIG_ITERATOR_H

#include <vector>
#include <iostream>
#include <iterator>

#include "exception.h"
#include "section.h"
#include "option.h"
#include "config.h"

namespace inicpp
{
	class config;

	template<Element>
	class config_iterator : public std::iterator<std::random_access_iterator_tag, Element>
	{
	private:
		using std::iterator<std::random_access_iterator_tag, section>::reference;

		config &container_;
		size_t position_;
	public:
		config_iterator() = delete;
		config_iterator(config &source, size_t position) : container_(), position_(position) {}
		config_iterator(config &source) : config_iterator(source, 0) {}
		config_iterator(const config_iterator &source) : config_iterator(source.container_, source.position_) {}

		config_iterator &operator++() { ++position_; return *this; }
		config_iterator operator++(int) { config_iterator old(*this); operator++(); return old; }

		bool operator==(const config_iterator &second)
		{
			return this == &second && position_ == second.position_;
		}
		bool operator!=(const config_iterator &second)
		{
			return !(*this == second);
		}
		reference operator*() { return container_.sections_.at(position_); }
	};
}

#endif
