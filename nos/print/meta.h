#ifndef NOS_PRINT_META_H
#define NOS_PRINT_META_H

#include <nos/meta/meta.h>

struct adsl_finder 
{
	nos::ostream& o;
	adsl_finder(nos::ostream& _o) : o(_o) {}
	operator nos::ostream& () { return o; }
};

namespace nos 
{
	template <typename T> struct print_implementation;

	template <typename T, bool HasNosPrint = false, bool HasMtdPrint = false, bool HasStdOstream = false> 
	struct print_implementation_solver;

	template <typename T, bool HasMtdPrint, bool HasStdOstream> struct print_implementation_solver<T, true, HasMtdPrint, HasStdOstream> 
	{
		static ssize_t print_to(nos::ostream& os, const T& obj) {
			return nos_print(adsl_finder(os), obj);
		}
	};	

	template <typename T, bool HasStdOstream> struct print_implementation_solver<T, false, true, HasStdOstream> 
	{
		static ssize_t print_to(nos::ostream& os, const T& obj) {
			return obj.print_to(os);
		}
	};	

	template <typename T> struct print_implementation_solver<T, false, false, true> 
	{
		static ssize_t print_to(nos::ostream& os, const T& obj) {
			//TODO
			std::cout << obj;
		}
	};	

	template <typename T>
	struct print_implementation : print_implementation_solver<
		typename std::remove_cv<T>::type, 
		nos::has_nos_print<typename std::remove_cv<T>::type>::value,
		nos::has_print_method<typename std::remove_cv<T>::type>::value,
		nos::has_std_ostream<typename std::remove_cv<T>::type>::value
	>
	{};
}

#endif