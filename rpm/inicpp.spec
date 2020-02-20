Name: inicpp
Version: 1.1.0
Release: 1%{?dist}
Summary: C++ parser of INI files.
License: MIT
BuildRequires: cmake, make, (gcc-c++ or clang)
URL: https://github.com/SemaiCZE/%{name}
Source0: https://github.com/SemaiCZE/%{name}/archive/v%{version}.tar.gz#/%{name}-%{version}.tar.gz

%description
Modern C++ library for parsing INI files with schema validation.

%prep
%autosetup

%build
mkdir build
cd build
%cmake -DNO_GOOGLE_TEST=ON ..
%make_build

%install
cd build
%make_install

%files
%license LICENSE
%{_libdir}/libinicpp.so

%package devel
Summary: Header and static library for %{name}.
Recommends: %{name}

%description devel
%{name} is a modern C++ library for parsing INI files with schema validation. This %{name}-devel package contains the headers and optional static library for compiling against the library.

%files devel
%{_libdir}/libinicpp_static.a
%{_includedir}/inicpp/*.h

%changelog
* Sun Feb 16 2020 Petr Stefan <ptr.stef@gmail.com> - 1.1.0-1
- Using std::variant instead of type switch
* Thu Jun 27 2019 Petr Stefan <ptr.stef@gmail.com> - 1.0.2-1
- GNU install dirs
* Mon Jan 21 2019 Benjamin Kay <benjamin@benkay.net> - 1.0.1-1
- Upstream version bump, cmake build system changes
* Wed Jan 16 2019 Benjamin Kay <benjamin@benkay.net> - 1.0.0-1
- First package of inicpp
