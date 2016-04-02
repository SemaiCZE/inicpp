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
	template<typename Element> class config_iterator;


	/**
	 * Represents the base object of ini configuration.
	 * Contains list of sections in logical map structure.
	 * Can be constructed directly from string or stream.
	 */
	class config
	{
	private:
		/** List of sections in this config instance */
		std::vector<section> sections_;
		/** Corresponding schema if any */
		std::shared_ptr<schema> schema_;

		friend class config_iterator<section>;
		friend class config_iterator<const section>;

	public:
		typedef config_iterator<section> iterator;
		typedef config_iterator<const section> const_iterator;

		/**
		 * Default constructor.
		 */
		config();
		/**
		 * Copy constructor.
		 */
		config(const config &src);
		/**
		 * Copy assignment.
		 */
		config &operator=(const config &source);
		/**
		 * Move constructor.
		 */
		config(config &&src);
		/**
		 * Move assignment.
		 */
		config &operator=(config &&source);

		/**
		 * Construct ini config from given string.
		 * @param str input string
		 * @throws invalid_config_exception in case of bad configuration
		 */
		config(const std::string &str);
		/**
		 * Construct config from given string and validate it against schema.
		 * @param str input string
		 * @param schm validation schema
		 * @param mode validation mode
		 * @throws invalid_config_exception in case of bad configuration
		 * @throws validation_exception if schema was not satisfied
		 */
		config(const std::string &str, const schema &schm, schema_mode mode);
		/**
		 * Construct ini config from given stream.
		 * @param str input stream
		 * @throws invalid_config_exception in case of bad configuration
		 */
		config(std::istream &str);
		/**
		 * Construct config from stream and validate it against schema.
		 * @param str input stream
		 * @param schm validation schema
		 * @param mode validation mode
		 * @throws invalid_config_exception in case of bad configuration
		 * @throws validation_exception if schema was not satisfied
		 */
		config(std::istream &str, const schema &schm, schema_mode mode);

		/**
		 * Add section to this ini configuration.
		 * @param sect section which will be added
		 * @throws ambiguity_exception if section with specified name exists
		 */
		void add_section(const section &sect);
		/**
		 * Create and add section with specified name.
		 * @param section_name section with same name cannot exist in config
		 * @throws ambiguity_exception if section with specified name exists
		 */
		void add_section(const std::string &section_name);
		/**
		 * Remove section from internal sections list.
		 * @param section_name name should exist in section list
		 * @throws not_found_exception if section with given name does not exist
		 */
		void remove_section(const std::string &section_name);

		/**
		 * Add given option to specified section.
		 * @param section_name should exist
		 * @param opt option which will be added to appropriate section
		 * @throws not_found_exception if section with given name does not exist
		 * @throws ambiguity_exception if option with specified name exists
		 */
		void add_option(const std::string &section_name, const option &opt);
		/**
		 * Creates and add option to specified section.
		 * @param section_name should exist in this config
		 * @param option_name name of newly created option
		 * @param value value which will be stored in new option
		 * @throws not_found_exception if section with given name does not exist
		 */
		template<typename ValueType>
		void add_option(const std::string &section_name,
			const std::string &option_name, const ValueType &value);
		/**
		 * Removes option with given name from given section.
		 * @param section_name index to section list
		 * @param option_name option with this name will be removed
		 * @throws not_found_exception if section or option
		 * with given name does not exist
		 * @throws ambiguity_exception if option with specified name exists
		 */
		void remove_option(const std::string &section_name,
			const std::string &option_name);

		/**
		 * Returns size of sections list
		 * @return unsigned integer
		 */
		size_t size();
		/**
		 * Access section on specified index.
		 * @param index
		 * @return modifiable reference to stored section
		 * @throws not_found_exception if index is out of range
		 */
		section &operator[](size_t index);
		/**
		 * Access section with specified name.
		 * @param index
		 * @return modifiable reference to stored section
		 * @throws not_found_exception if section with given name does not exist
		 */
		section &operator[](const std::string &section_name);

		/**
		 * Validates this config agains given schema.
		 * @param schm specifies how this config should look like
		 * @param mode validation mode
		 * @return true if this config comply given schema
		 */
		bool validate(const schema &schm, schema_mode mode);

		/**
		 * Classic stream operator for printing this instance to output stream.
		 * @param os output stream
		 * @return reference to output stream which allows chaining
		 */
		std::ostream &operator<<(std::ostream &os);

		/**
		 * Iterator pointing at the beginning of sections list.
		 * @return config_iterator
		 */
		iterator begin();
		/**
		 * Iterator pointing at the end of sections list.
		 * @return config_iterator
		 */
		iterator end();
		/**
		 * Constant iterator pointing at the beginning of sections list.
		 * @return config_iterator
		 */
		const_iterator cbegin() const;
		/**
		 * Constant iterator pointing at the end of sections list.
		 * @return config_iterator
		 */
		const_iterator cend() const;
	};


	/**
	 * Templated config iterator.
	 * Templates provide const and non-const iterator in one implementation.
	 * For easier implementation inheritance from std::iterator is used.
	 */
	template<typename Element>
	class config_iterator
		: public std::iterator<std::random_access_iterator_tag, Element>
	{
	private:
		using typename std::iterator<std::random_access_iterator_tag, Element>::reference;

		/** Reference to container which can be iterated */
		config &container_;
		/** Position in iterable container */
		size_t position_;
	public:
		/**
		 * Deleted default constructor.
		 */
		config_iterator() = delete;
		/**
		 * Copy constructor.
		 */
		config_iterator(const config_iterator &src) = default;
		/**
		 * Copy assignment.
		 */
		config_iterator& operator=(const config_iterator &source) = default;
		/**
		 * Move constructor.
		 */
		config_iterator(config_iterator &&src) = default;
		/**
		 * Move assignment.
		 */
		config_iterator& operator=(config_iterator &&source) = default;

		/**
		 * Construct iterator on given container
		 * and pointing at specified postion.
		 * @param source container which can be iterated
		 * @param position initial position to given container
		 */
		config_iterator(config &source, size_t position)
			: container_(), position_(position) {}
		/**
		 * Construct iterator on given container pointing at the start.
		 * @param source container which can be iterated
		 */
		config_iterator(config &source) : config_iterator(source, 0) {}

		/**
		 * Moves iterator to next position.
		 * @return iterator itself
		 */
		config_iterator &operator++()
		{
			++position_;
			return *this;
		}
		/**
		 * Moves iterator to next position.
		 * @return new iterator with old position
		 */
		config_iterator operator++(int)
		{
			config_iterator old(*this);
			operator++();
			return old;
		}

		/**
		 * Equality compare method for iterators.
		 * @param second
		 * @return true if iterators are the same
		 */
		bool operator==(const config_iterator &second)
		{
			return this == &second && position_ == second.position_;
		}
		/**
		 * Non-equality compare method for iterators.
		 * @param second
		 * @return true if iterators are different
		 */
		bool operator!=(const config_iterator &second)
		{
			return !(*this == second);
		}

		/**
		 * Iterator dereference operator.
		 * @return reference to section on current position
		 */
		reference operator*()
		{
			return container_.sections_.at(position_);
		}
	};
}

#endif
