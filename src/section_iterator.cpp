#include "section_iterator.h"


namespace inicpp {
	section_iterator::section_iterator(section &source) : container_(source) {}
	section_iterator::section_iterator(const section_iterator &source) : container_(source.container_), pos_(source.pos_) {}
	
	section_iterator &section_iterator::operator++() { ++pos_; return *this; }
	section_iterator section_iterator::operator++(int) { section_iterator old(*this); operator++(); return old; }
	
	bool section_iterator::operator==(const section_iterator &second) { return pos_ == second.pos_; }
	bool section_iterator::operator!=(const section_iterator &second) { return pos_ != second.pos_; }
	section_iterator::reference section_iterator::operator*() { return container_.options_.at(pos_); }
	
	
	
	const_section_iterator::const_section_iterator(const section &source) : container_(source) {}
	const_section_iterator::const_section_iterator(const const_section_iterator &source) : container_(source.container_), pos_(source.pos_) {}
	
	const_section_iterator &const_section_iterator::operator++() { ++pos_; return *this; }
	const_section_iterator const_section_iterator::operator++(int) { const_section_iterator old(*this); operator++(); return old; }
	
	bool const_section_iterator::operator==(const const_section_iterator &second) { return pos_ == second.pos_; }
	bool const_section_iterator::operator!=(const const_section_iterator &second) { return pos_ != second.pos_; }
	const_section_iterator::reference const_section_iterator::operator*() const { return container_.options_.at(pos_); }
}

