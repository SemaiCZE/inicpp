#include "config_iterator.h"


namespace inicpp {
	config_iterator::config_iterator(config &source) : container_(source) {}
	config_iterator::config_iterator(const config_iterator &source) : container_(source.container_), pos_(source.pos_) {}
	
	config_iterator &config_iterator::operator++() { ++pos_; return *this; }
	config_iterator config_iterator::operator++(int) { config_iterator old(*this); operator++(); return old; }
	
	bool config_iterator::operator==(const config_iterator &second) { return pos_ == second.pos_; }
	bool config_iterator::operator!=(const config_iterator &second) { return pos_ != second.pos_; }
	config_iterator::reference config_iterator::operator*() { return container_.sections_.at(pos_); }
	
	
	
	const_config_iterator::const_config_iterator(const config &source) : container_(source) {}
	const_config_iterator::const_config_iterator(const const_config_iterator &source) : container_(source.container_), pos_(source.pos_) {}
	
	const_config_iterator &const_config_iterator::operator++() { ++pos_; return *this; }
	const_config_iterator const_config_iterator::operator++(int) { const_config_iterator old(*this); operator++(); return old; }
	
	bool const_config_iterator::operator==(const const_config_iterator &second) { return pos_ == second.pos_; }
	bool const_config_iterator::operator!=(const const_config_iterator &second) { return pos_ != second.pos_; }
	const_config_iterator::reference const_config_iterator::operator*() const { return container_.sections_.at(pos_); }
}

