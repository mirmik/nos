#ifndef NOS_FPRINT_META_H
#define NOS_FPRINT_META_H

/**
	@file
*/

#include <string_view>

namespace nos 
{
	template <typename T> struct fprint_implementation;

	template <typename T, bool HasNosFPrint = false, bool HasMtdFPrint = false> 
	struct fprint_implementation_solver 
	{
		static int fprint_to(const T& obj, nos::ostream& os, const std::string_view & opts) {
			(void) opts;
			return nos::print_to(os, obj);
		}	
	};

	template <typename T, bool HasMtdFPrint> struct fprint_implementation_solver<T, true, HasMtdFPrint> 
	{
		static int fprint_to(const T& obj, nos::ostream& os, const std::string_view & opts) {
			return nos_fprint(adsl_finder(os), obj, opts);
		}
	};	

	template <typename T> struct fprint_implementation_solver<T, false, true> 
	{
		static int fprint_to(const T& obj, nos::ostream& os, const std::string_view & opts) {
			return obj.fprint_to(os, opts);
		}
	};	

	template <typename T> struct fprint_implementation : public fprint_implementation_solver<
		typename std::remove_cv<T>::type, 
		nos::has_nos_fprint<typename std::remove_cv<T>::type>::value,
		nos::has_fprint_method<typename std::remove_cv<T>::type>::value
	> {};
}

#endif
