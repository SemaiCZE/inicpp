#ifndef INICPP_CONFIG_H
#define INICPP_CONFIG_H

#include <vector>
#include <iostream>

#include "exception.h"
#include "section.h"
#include "option.h"
#include "schema.h"


namespace inicpp
{
	/** Forward declaration, stated because of ring dependencies */
	class schema;
	/** Forward declaration of iterator used in config class */
	template<typename T> class config_iterator;


	/**
	 * @brief The config class
	 */
	class config
	{
	private:
		/** */
		std::vector<section> sections_;

		friend class config_iterator<section>;
		friend class config_iterator<const section>;

	public:
		typedef config_iterator<section> iterator;
		typedef config_iterator<const section> const_iterator;

		/**
		 * @brief config
		 */
		config();
		config(const config &src);
		config &operator=(const config &source);
		config(config &&src);
		config &operator=(config &&source);

		/**
		 * @brief config
		 * @param str
		 */
		config(const std::string &str);
		/**
		 * @brief config
		 * @param str
		 * @param schm
		 * @param md
		 */
		config(const std::string &str, const schema &schm, schema_mode mode);
		/**
		 * @brief config
		 * @param str
		 */
		config(std::istream &str);
		/**
		 * @brief config
		 * @param str
		 * @param schm
		 * @param md
		 */
		config(std::istream &str, const schema &schm, schema_mode mode);

		/**
		 * @brief add_section
		 * @param sect
		 */
		void add_section(section sect);
		/**
		 * @brief add_section
		 * @param section_name
		 */
		void add_section(const std::string &section_name);

		/**
		 * @brief add_option
		 * @param section_name
		 * @param opt
		 */
		void add_option(const std::string &section_name, option opt);
		/**
		 * @brief add_option
		 * @param section_name
		 * @param option_name
		 */
		template<typename ValueType>
		void add_option(const std::string &section_name, const std::string &option_name, const ValueType &value);

		/**
		 * @brief operator []
		 * @param index
		 * @return
		 */
		section &operator[](size_t index);
		/**
		 * @brief operator []
		 * @param section_name
		 * @return
		 */
		section &operator[](const std::string &section_name);

		/**
		 * @brief
		 * @param schm
		 * @return
		 */
		bool validate(const schema &schm, schema_mode mode);

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
	class config_iterator : public std::iterator<std::random_access_iterator_tag, Element>
	{
	private:
		using typename std::iterator<std::random_access_iterator_tag, Element>::reference;

		/** */
		config &container_;
		/** */
		size_t position_;
	public:
		config_iterator() = delete;
		config_iterator(const config_iterator &src) = default;
		config_iterator& operator=(const config_iterator &source) = default;
		config_iterator(config_iterator &&src) = default;
		config_iterator& operator=(config_iterator &&source) = default;

		/**
		 * @brief config_iterator
		 * @param source
		 * @param position
		 */
		config_iterator(config &source, size_t position) : container_(), position_(position) {}
		/**
		 * @brief config_iterator
		 * @param source
		 */
		config_iterator(config &source) : config_iterator(source, 0) {}

		/**
		 * @brief operator ++
		 * @return
		 */
		config_iterator &operator++()
		{
			++position_;
			return *this;
		}
		/**
		 * @brief operator ++
		 * @return
		 */
		config_iterator operator++(int)
		{
			config_iterator old(*this);
			operator++();
			return old;
		}

		/**
		 * @brief operator ==
		 * @param second
		 * @return
		 */
		bool operator==(const config_iterator &second)
		{
			return this == &second && position_ == second.position_;
		}
		/**
		 * @brief operator !=
		 * @param second
		 * @return
		 */
		bool operator!=(const config_iterator &second)
		{
			return !(*this == second);
		}

		/**
		 * @brief operator *
		 * @return
		 */
		reference operator*()
		{
			return container_.sections_.at(position_);
		}
	};
}

#endif
