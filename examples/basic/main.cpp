#include "inicpp.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace inicpp;
using namespace std::literals;


std::string get_config()
{
	std::string conf_str = ""
		"[Section 1]\n"
		"; comment\n"
		"Option 1 = value 1                     ; option 'Option 1' has value 'value 1'\n"
		"oPtion 1    =  \\ value 2\\ \\ \\      ; option 'oPtion 1' has value ' value 2   ', 'oPtion 1' and 'Option 1' are different\n"
		"\n"
		"[$Section::subsection]                 ; no subsection, only valid identifier of section\n"
		"Option 2=value 1:value 2:value 3       ; option 'Option 2' is list of 'value 1', 'value 2' and 'value 3'\n"
		"Option 3 =value 1, ${Section 1#Option 1} ; option 'Option 3' is list of 'value 1' and 'value 1'\n"
		"Option 4= v1,${$Section::subsection#Option 3},v2 ; option 'Option 4' is list of 'v1', 'value 1', 'value 1', 'v2'\n"
		"Option 5= v1, v2:v3                    ; option 'Option 5' is list of 'v1' a 'v2:v3'\n"
		"\n"
		"[Numbers]\n"
		"num = -1285\n"
		"num_bin = 0b01101001\n"
		"num_hex = 0x12ae,0xAc2B\n"
		"num_oct = 01754\n"
		"\n"
		"float1 = -124.45667356\n"
		"float2 = +4.1234565E+45\n"
		"float3 = 412.34565e45\n"
		"float4 = -1.1245864E-6\n"
		"\n"
		"[Other]\n"
		"bool1 = 1\n"
		"bool2 = on\n"
		"bool3=f\n";
	return conf_str;
}


int main(void)
{
	std::cout << "Load and parse config from string" << std::endl;
	std::cout << "---------------------------------" << std::endl;
	config example_conf = parser::load(get_config());
	std::cout << "done..." << std::endl << std::endl;


	std::cout << "Iterate through whole config and print it" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	for(auto &sect : example_conf) {
		std::cout << "  Section: '" << sect.get_name() << "'" << std::endl;
		// Iterate through options in a section
		for(auto &opt : sect) {
			std::cout << "    Option: '" << opt.get_name() << "' with value(s): ";
			if (!opt.is_list()) {
				std::cout << "'" << opt.get<string_ini_t>() << "'";
			} else {
				for (auto &list_item : opt.get_list<string_ini_t>())
					std::cout << "'" << list_item << "' ";
			}
			std::cout << std::endl;
		}
	}
	std::cout << "done..." << std::endl << std::endl;


	std::cout << "Get number as signed_ini_t type" << std::endl;
	std::cout << "-------------------------------" << std::endl;
	try {
		signed_ini_t number = example_conf["Numbers"]["num"].get<signed_ini_t>();
		std::cout << "  Item 'num' in 'Numbers' section casted to signed_ini_t type has value '" <<
			number << "'" << std::endl;
	} catch (const bad_cast_exception &) {
		std::cout << "  Item 'num' in 'Numbers' section cannot be casted to signed_ini_t type" << std::endl;
	}
	std::cout << "done..." << std::endl << std::endl;


	std::cout << "Change some values - could be properly typed" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	// Make reference to the section
	section &number_sect = example_conf["Numbers"];
	// Change some values
	number_sect["num"].set<signed_ini_t>(42222);
	signed_ini_t new_num = number_sect["num"].get<signed_ini_t>();
	std::cout << "  Option 'num' in 'Numbers' section is '" << new_num << "'" << std::endl;
	// Following two lines are equivalent
	number_sect["num_oct"].set<string_ini_t>("0756");
	number_sect["num_oct"] = "0756"s;
	std::cout << "  set method and assingment operator on option are equivalent" << std::endl;
	std::cout << "done..." << std::endl << std::endl;


	std::cout << "Typed value can be casted to string" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	try {
		string_ini_t str_number = example_conf["Numbers"]["num"].get<string_ini_t>();
		std::cout << "  Item 'num' in 'Numbers' section is signed_ini_t type, but string '" <<
			str_number << "' can be retrieved" << std::endl;
	} catch (const bad_cast_exception &) {
		std::cout << "  Item 'num' in 'Numbers' section cannot be casted to string_ini_t type" << std::endl;
	}
	std::cout << "done..." << std::endl << std::endl;


	std::cout << "Change single value to list and vice versa" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	option &num_opt = number_sect["num"];
	num_opt.add_to_list<signed_ini_t>(99);
	if (num_opt.is_list()) {
		std::cout << "  'num' option in 'Numbers' section is list" << std::endl;
	} else {
		std::cout << "  'num' option in 'Numbers' section is single value" << std::endl;
	}
	// Remove item from the list (specifying position)
	num_opt.remove_from_list_pos(0); // remove first item
	std::cout << "  first item from 'num' option list removed" << std::endl;
	if (num_opt.is_list()) {
		std::cout << "  'num' option in 'Numbers' section is list" << std::endl;
	} else {
		std::cout << "  'num' option in 'Numbers' section is single value" << std::endl;
	}
	std::cout << "  'num' option value is '" << num_opt.get<signed_ini_t>() << "'" << std::endl;
	std::cout << "done..." << std::endl << std::endl;


	std::cout << "Save changes to ostream and print the result" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	std::ostringstream ofs;
	ofs << example_conf;
	std::cout << ofs.str();
	std::cout << "done..." << std::endl << std::endl;
}
