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
	

	/**
	 * @brief The section class
	 */
	class section
	{
	private:
		/** */
		std::vector<option> options_;
		/** */
		bool name_;

		friend class section_iterator<option>;
		friend class section_iterator<const option>;

	public:
		typedef section_iterator<option> iterator;
		typedef section_iterator<const option> const_iterator;

		/**
		 * @brief section
		 */
		section();
		section(const section &source);
		section& operator=(const section &source);
		section(section &&source);
		section& operator=(section &&source);

		/**
		 * @brief section
		 * @param name
		 */
		section(const std::string &name);
		
		/**
		 * @brief add_option
		 * @param name
		 * @param value
		 */
		template<typename ValueType> void add_option(const std::string &name, const ValueType &value)
		{
			throw not_implemented_exception();
		}
		/**
		 * @brief add_option
		 * @param opt
		 */
		void add_option(const option &opt);

		/**
		 * @brief get_options
		 * @return
		 */
		const std::vector<option> &get_options() const;
		/**
		 * @brief operator []
		 * @param index
		 * @return
		 */
		option &operator[](size_t index);
		/**
		 * @brief operator []
		 * @param option_name
		 * @return
		 */
		option &operator[](const std::string &option_name);

		/**
		 * @brief operator <<
		 * @param os
		 * @return
		 */
		std::ostream &operator<<(std::ostream &os);

		/**
		 * @brief begin
		 * @return
		 */
		iterator begin();
		/**
		 * @brief end
		 * @return
		 */
		iterator end();
		/**
		 * @brief cbegin
		 * @return
		 */
		const_iterator cbegin() const;
		/**
		 * @brief cend
		 * @return
		 */
		const_iterator cend() const;
	};
	

	/**
	 *
	 */
	template<typename Element>
	class section_iterator : public std::iterator<std::random_access_iterator_tag, Element>
	{
	private:
		using typename std::iterator<std::random_access_iterator_tag, Element>::reference;
		
		/** */
		section &container_;
		/** */
		size_t position_;
	public:
		/**
		 * @brief section_iterator
		 */
		section_iterator() = delete;
		section_iterator(const section_iterator &source) = default;
		section_iterator& operator=(const section_iterator &source) = default;
		section_iterator(section_iterator &&source) = default;
		section_iterator& operator=(section_iterator &&source) = default;

		/**
		 * @brief section_iterator
		 * @param source
		 * @param position
		 */
		section_iterator(section &source, size_t position) : container_(source), position_(position) {}
		/**
		 * @brief section_iterator
		 * @param source
		 */
		section_iterator(section &source) : section_iterator(source, 0) {}

		/**
		 * @brief operator ++
		 * @return
		 */
		section_iterator &operator++()
		{
			++position_;
			return *this;
		}
		/**
		 * @brief operator ++
		 * @return
		 */
		section_iterator operator++(int)
		{
			section_iterator old(*this);
			operator++();
			return old;
		}

		/**
		 * @brief operator ==
		 * @param second
		 * @return
		 */
		bool operator==(const section_iterator &second)
		{
			return this == &second && position_ == second.position_;
		}
		/**
		 * @brief operator !=
		 * @param second
		 * @return
		 */
		bool operator!=(const section_iterator &second)
		{
			return !(*this == second);
		}

		/**
		 * @brief operator *
		 * @return
		 */
		reference operator*()
		{
			return container_.options_.at(position_);
		}
	};
}

#endif
