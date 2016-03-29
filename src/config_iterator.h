#ifndef INICPP_CONFIG_ITERATOR_H
#define INICPP_CONFIG_ITERATOR_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "section.h"
#include "option.h"

namespace inicpp
{
	class config {};

	class config_iterator : public std::iterator<std::random_access_iterator_tag, option>
	{
	private:
		config &container_;
		size_t pos_;
	public:
		config_iterator(config &source) : container_(source) {}
		config_iterator(const config_iterator &source) : container_(source.container_), pos_(source.pos_) {}

		config_iterator &operator++() { ++pos_; return *this; }
		config_iterator operator++(int) { config_iterator old(*this); operator++(); return old; }

		bool operator==(const config_iterator &second) { return pos_ == second.pos_; }
		bool operator!=(const config_iterator &second) { return pos_ != second.pos_; }
		reference operator*() { return container_.sections_.at(pos_); }
	};

	class const_config_iterator : public std::iterator<std::random_access_iterator_tag, option>
	{
	private:
		const config &container_;
		size_t pos_;
	public:
		const_config_iterator(const config &source) : container_(source) {}
		const_config_iterator(const const_config_iterator &source) : container_(source.container_), pos_(source.pos_) {}

		const_config_iterator &operator++() { ++pos_; return *this; }
		const_config_iterator operator++(int) { const_config_iterator old(*this); operator++(); return old; }

		bool operator==(const const_config_iterator &second) { return pos_ == second.pos_; }
		bool operator!=(const const_config_iterator &second) { return pos_ != second.pos_; }
		const reference operator*() { return container_.sections_.at(pos_); }
	};
}

#endif
