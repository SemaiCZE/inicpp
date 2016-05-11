#ifndef INICPP_DLL_H
#define INICPP_DLL_H

#ifdef INICPP_DLL
#    ifdef INICPP_EXPORT
#		define INICPP_API __declspec(dllexport)
#    else
#        define INICPP_API __declspec(dllimport)
#    endif
#else
#    define INICPP_API
#endif

#endif // INICPP_DLL_H
