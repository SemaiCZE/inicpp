Name: inicpp
Version: 1.0.0
Release: 1%{?dist}
Summary: C++ parser of INI files.
License: MIT
BuildRequires: cmake, make, (gcc-c++ or clang)
URL: https://github.com/SemaiCZE/%{name}
Patch0: %{name}-cmake.patch
Source0: https://github.com/SemaiCZE/%{name}/archive/v%{version}.tar.gz#/%{name}-%{version}.tar.gz

%description
Modern, C++14 library for parsing INI files with schema validation.

%prep
%autosetup

%build
mkdir build
cd build
%cmake ..
%make_build
cd ..

%install
mkdir -p %{buildroot}/%{_libdir}
mkdir -p %{buildroot}/%{_includedir}/inicpp
install -m 0644 include/inicpp/*.h %{buildroot}/%{_includedir}/inicpp
install -m 0644 build/libinicpp_static.a %{buildroot}/%{_libdir}
install -m 0755 build/libinicpp.so %{buildroot}/%{_libdir}

%files
%license LICENSE
%{_libdir}/libinicpp.so

%package devel
Summary: Header and static library for %{name}.
Recommends: %{name}

%description devel
%{name} is a modern, C++14 library for parsing INI files with schema validation.  This %{name}-devel package contains the headers and optional static library for compiling against the library.

%files devel
%{_libdir}/libinicpp_static.a
%{_includedir}/inicpp/*.h

%changelog
* Wed Jan 16 2019 Benjamin Kay <benjamin@benkay.net> - 1.0.0-1
- First package of inicpp
