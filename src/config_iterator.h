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

	class config_iterator : public std::iterator<std::random_access_iterator_tag, section>
	{
	private:
		using std::iterator<std::random_access_iterator_tag, section>::reference;

		config &container_;
		size_t pos_;
	public:
		config_iterator(config &source);
		config_iterator(const config_iterator &source);

		config_iterator &operator++();
		config_iterator operator++(int);

		bool operator==(const config_iterator &second);
		bool operator!=(const config_iterator &second);
		reference operator*();
	};


	class const_config_iterator : public std::iterator<std::random_access_iterator_tag, const section>
	{
	private:
		using std::iterator<std::random_access_iterator_tag, const section>::reference;

		const config &container_;
		size_t pos_;
	public:
		const_config_iterator(const config &source);
		const_config_iterator(const const_config_iterator &source);

		const_config_iterator &operator++();
		const_config_iterator operator++(int);

		bool operator==(const const_config_iterator &second);
		bool operator!=(const const_config_iterator &second);
		reference operator*() const;
	};
}

#endif
