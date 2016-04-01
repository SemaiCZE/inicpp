# inicpp

[![License](https://img.shields.io/badge/license-mit-blue.svg)](http://badges.mit-license.org)
[![Wiki](https://img.shields.io/badge/docs-wiki-orange.svg)](https://github.com/SemaiCZE/inicpp/wiki)
[![Docs](https://img.shields.io/badge/docs-latest-brightgreen.svg)](http://semaicze.github.io/inicpp)

C++ parser of INI files with schema validation.

## About

This project started as semestral work for _Recommended Programming Practices_ class at **MFF UK**, Prague, in 2016. After deadline the project was published at _GitHub_ under MIT license.

Great emphasis was put on qualities of object oriented design and clean implementation with modern C++14 features.

Originally written by:

- Petr Stefan (_[SemaiCZE](https://github.com/SemaiCZE/)_)
- Martin Polanka (_[Neloop](https://github.com/Neloop/)_)

## Build instructions

**Inicpp** is build as shared and static library using `cmake`. There are two options to control which libraries are built, by default both are set to ON. Basic syntax is:

```
cmake [-G generator] [-DBUILD_STATIC=ON|OFF] [-DBUILD_SHARED=ON|OFF] source_dir
```

Also C++ compiler with at least C++14 support is required.

### Linux

To build the library run following commands from root of source code directory:

```Shell
$ mkdir -p build
$ cd build
$ cmake ..
$ make
```

To build and run unit tests using Google Test framework run additional commands:

```Shell
$ make -f tests/Makefile
$ ./tests/run_tests
```

**Note:** For building tests you must have all the sources including git submodules. This could be done using `git clone --recursive https://github.com/SemaiCZE/inicpp.git` command when clonning or `git submodule update --init` when you already have the sources.

### Windows

_**To be done...**_

## Examples

### Basic usage without schema

```C++
using namespace inicpp;

// Load config file from file
config example_conf = parser::load_file("conf.ini");

// Iterate through sections
for(auto &sect : example_conf) {
	std::cout << "Section: " << sect.get_name() << std::endl;
	// Iterate through options in a section
	for(auto &opt : sect) {
		std::cout << "Option: " << opt.get_name() << " with value "
			<< opt.get<string_t>() << std::endl;
	}
}

// Get known item from known section
try {
	signed_t port = config["github"]["port"].get<signed_t>();
} catch (bad_cast_exception) {
	// item cannot be casted to signed_t type
}
// Get a string always wotk
string_t port_str = config["github"]["port"].get<string_t>();

// Change some values
config["github"]["port"].set<signed_t>(42222);
config["github"]["address"].set<string_t>("www.github.com");

// Save changes
std::ofstream ofs("conf_new.ini");
ofs << config;
```

Without schema all items are treated as string type, but runtime conversion could be done to one of supported types if possible.

### Schema validation support

Schema validation can bring you ability to make sure, that a config file contain what you expect with type safety. In addition, this implies better performance on heavy reading of validated configuration.

```C++
using namespace inicpp;

// First prepare the schema:
schema conf_schm;

// Add first section
conf_schm.add_section("github"); // default is mandatory
// Add option named "port" into "github" section. The option is mandatory\
// and it's type is unsigned. Default value makes no sense for mandatory
// options.
conf_schm.add_option("github", "port", true, option_type::unsigned_e);
// Mandatory string option "address" with default value "www.github.com" (one value, not list)
conf_schm.add_option("github", "address", false, option_type::string_e, false, "www.github.com");

// Alternatively, create the classes first and add them to schema
option_schema autoconnect_option("autoconnect", false, option_type::boolean_e, false, "off");
section_schema connect_section("connect", false); // optional section
connect_section.add_option(autoconnect_option);
conf_schm.add_section(connect_section);

// Then load file with validation (from stream conf_istream, just to show a different way)
try {
	config example_conf = parser::load(conf_istream, conf_schm, schema_mode::strict);
} catch (invalid_config_exception) {
	// config is not valid
}

// Or you can validate already loaded config!
config example_conf = parser::load_file("conf.ini");
if(example_conf.validate(conf_schm, schema_mode::relaxed)) {
	// now the config is valid and all values are internaly
	// stored as their correct type
}
```
