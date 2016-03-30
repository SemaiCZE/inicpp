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

**Inicpp** is build as shared and static library using `cmake`. Also C++ compiler with at least C++11 support is required.

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
