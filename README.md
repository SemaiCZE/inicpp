# inicpp

[![Linux Build Status](https://github.com/SemaiCZE/inicpp/workflows/Linux%20Build/badge.svg)](https://github.com/SemaiCZE/inicpp/actions)
[![Windows Build Status](https://github.com/SemaiCZE/inicpp/workflows/Windows%20Build/badge.svg)](https://github.com/SemaiCZE/inicpp/actions)
[![License](https://img.shields.io/badge/license-mit-blue.svg)](http://badges.mit-license.org)
[![Wiki](https://img.shields.io/badge/docs-wiki-orange.svg)](https://github.com/SemaiCZE/inicpp/wiki)
[![Docs](https://img.shields.io/badge/docs-latest-brightgreen.svg)](http://semaicze.github.io/inicpp)

C++ parser of INI files with schema validation.

## About

This project started as semestral work for _Recommended Programming Practices_ class at **MFF UK**, Prague, in 2016. After deadline the project was published at _GitHub_ under MIT license.

Great emphasis was put on qualities of object oriented design and clean implementation with modern C++ features.

Originally written by:

- Petr Stefan (_[SemaiCZE](https://github.com/SemaiCZE/)_)
- Martin Polanka (_[Neloop](https://github.com/Neloop/)_)

## Versions

`Master` branch contains source code using `std::variant` feature and it requires compiler with C++17 support. Older version with C++14 support is in `cpp14` branch and is still supported by us.

## Build instructions

**Inicpp** is build as shared and static library using `cmake`. There are two options to control which libraries are built, by default both are set to ON. Basic syntax is:

```
cmake [-G generator] [-DBUILD_STATIC=ON|OFF] [-DBUILD_SHARED=ON|OFF] source_dir
```

Also C++ compiler with at least C++17 support is required.

### Linux

To build the library run following commands from root of source code directory:

```.sh
$ mkdir -p build
$ cd build
$ cmake ..
$ make
```

To build and run unit tests using Google Test framework run additional commands:

```.sh
$ make -f tests/Makefile
$ ./tests/run_tests
```

**Note:** For building tests you must have all the sources including git submodules. This could be done using `git clone --recursive https://github.com/SemaiCZE/inicpp.git` command when clonning or `git submodule update --init` when you already have the sources.

### Windows

For Windows there are two ways of building `inicpp`. For both ways `cmake` has to be installed on machine.

Using **MS Visual Studio**:
- As stated `Visual Studio 2017` (or later) should be installed on the machine.
- If dependencies are successfully fulfilled then run `cmake` in root directory of repository using:
```
> cmake -G "Visual Studio 15 2017"
```
- This command will generate solution files
- Open solution file `inicpp.sln` using `Visual Studio`
- Build `ALL_BUILD` project which will hopefully successfully build whole library
- Distribute static or shared binaries which can be found in target build directories to your program/library

Using **MS Visual C++**:
- Besides `Visual C++ 2017` (or later) `nmake` compilation tool is needed (both should be part of `Windows SDK`)
- Run `cmake` in root directory of repository using:
```
> cmake -G "NMake Makefiles"
```
- This will generate file `Makefile` which can be interpreted with `nmake`
- Now enter following easy command:
```
> nmake
```
- After this compiled library should appear in working directory
- Depending on your needs use `inicpp` or `inicpp_static` in your library or program

## Examples

Some examples are located in `examples` directory. Compiling them requires additional steps after standard library compilation, for example on Linux (note that you must be in `build` directory):

```.sh
$ make -f examples/Makefile
```

Compiled examples can be run as follows:

```.sh
$ ./examples/schema_validation/inicpp_schema
$ ./examples/basic/inicpp_basic
```

Expected outputs are also provided with examples sources.


### Basic usage without schema

Slightly modified version of basic example.

```.cpp
std::cout << "Load and parse config from string" << std::endl;
config example_conf = parser::load(get_config());

std::cout << "Iterate through whole config and print it" << std::endl;
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
	}
}

std::cout << "Get number as signed_ini_t type" << std::endl;
try {
	signed_ini_t number = example_conf["Numbers"]["num"].get<signed_ini_t>();
	std::cout << "  " << number << std::endl;
} catch (bad_cast_exception) {
	std::cout << "  Item 'num' in 'Numbers' section cannot be casted to signed_ini_t type" << std::endl;
}

std::cout << "Change some values - could be properly typed" << std::endl;
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

std::cout << "Change single value to list and vice versa" << std::endl;
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

std::cout << "Save changes to ostream and print the result" << std::endl;
std::ostringstream ofs;
ofs << example_conf;
std::cout << ofs.str();
```

Without schema all items are treated as string type, but runtime conversion could be done to one of supported types if possible.

### Schema validation support

Schema validation can bring you ability to make sure, that a config file contain what you expect with type safety. In addition, this implies better performance on heavy reading of validated configuration. Slightly modified version of schema validation example.

```.cpp
std::cout << "Create config schema" << std::endl;
schema schm;

// add section 'Section 1'
section_schema_params section_1_params;
section_1_params.name = "Section 1";
section_1_params.comment = "comment";
section_1_params.requirement = item_requirement::optional;
schm.add_section(section_1_params);

// add options to 'Section 1'
option_schema_params<signed_ini_t> option_1_params;
option_1_params.name = "Option 1";
option_1_params.type = option_item::single;
option_1_params.requirement = item_requirement::mandatory;
option_1_params.validator = [](signed_ini_t i){ return i < 0; }; // valid values are only negative ones
option_1_params.comment = "Important option\nshould be negative";
option_1_params.default_value = "-1";
schm.add_option("Section 1", option_1_params);

option_schema_params<float_ini_t> option_4_params;
option_4_params.name = "float1";
option_4_params.type = option_item::single;
option_4_params.requirement = item_requirement::mandatory;
schm.add_option("Section 1", option_4_params);


std::cout << "Load and validate config in relaxed mode" << std::endl;
config conf = parser::load(get_config(), schm, schema_mode::relaxed);

std::cout << "Check, if options are properly typed" << std::endl;
std::cout << "  'Option 1' is signed_ini_t type with value '" <<
	conf["Section 1"]["Option 1"].get<signed_ini_t>() << "'" << std::endl;
std::cout << "  'float1' option has value '" << conf["Section 1"]["float1"].get<float_ini_t>() <<
	std::endl;
std::cout << "  'unknown_option' was left as string with value '" <<
	conf["Section 1"]["unknown_option"].get<string_ini_t>() << std::endl;

std::cout << "Validation with strict mode fails due to 'unknown_option'" << std::endl;
try {
	parser::load(get_config(), schm, schema_mode::strict);
} catch (validation_exception) {
	std::cout << "  Strict mode validation failed" << std::endl;
}

std::cout << "Write default configuration from schema to stream" << std::endl;
std::ostringstream str;
str << schm;
std::cout << str.str();

std::cout << "Write current configuration with comments from schema to stream" << std::endl;
str.str("");
parser::save(conf, schm, str);
std::cout << str.str();
```

## Contribution

This project is open for all contributions, but please respect some rules:

- write clean code
- use modern C++ features when possible
- write tests - no need to have 100% coverage, but some tests should be present
- format code using our style in provided `.clang-format` file - `cmake` target `format` on unix handle this

