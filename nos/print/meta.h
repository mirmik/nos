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

	template <typename T, bool HasNosPrint = false, bool HasMtdPrint = false> 
	struct print_implementation_solver;
	//{
		//static_assert(0, "strange type");
	//};

	template <typename T, bool HasMtdPrint> struct print_implementation_solver<T, true, HasMtdPrint> 
	{
		static ssize_t print_to(nos::ostream& os, const T& obj) {
			return nos_print(adsl_finder(os), obj);
		}
	};	

	template <typename T> struct print_implementation_solver<T, false, true> 
	{
		static ssize_t print_to(nos::ostream& os, const T& obj) {
			return obj.print_to(os);
		}
	};	

	template <typename T>
	struct print_implementation : print_implementation_solver<
		typename std::remove_cv<T>::type, 
		nos::has_nos_print<typename std::remove_cv<T>::type>::value,
		nos::has_print_method<typename std::remove_cv<T>::type>::value
	>
	{};
}

#endif