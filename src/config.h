#ifndef INICPP_CONFIG_H
#define INICPP_CONFIG_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "section.h"
#include "option.h"


namespace inicpp
{
	template<typename T> class config_iterator;


	class config
	{
	private:
		std::vector<section> sections_;

		friend class config_iterator<section>;
		friend class config_iterator<const section>;

	public:
		typedef config_iterator<section> iterator;
		typedef config_iterator<const section> const_iterator;

		config();
		config(const config &src);
		config& operator=(const config &source);
		config(config &&src);
		config& operator=(config &&source);

		void add_section(section sect);
		void add_section(const std::string &section_name);

		void add_option(const std::string &section_name, option opt);
		void add_option(const std::string &section_name, const std::string &option_name);

		const std::vector<section> &get_sections();
		section &operator[](size_t index);
		section &operator[](const std::string &section_name);

		std::ostream &operator<<(std::ostream &os);

		iterator begin();
		iterator end();
		const_iterator cbegin();
		const_iterator cend();
	};


	template<typename Element>
	class config_iterator : public std::iterator<std::random_access_iterator_tag, Element>
	{
	private:
		using typename std::iterator<std::random_access_iterator_tag, Element>::reference;

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
