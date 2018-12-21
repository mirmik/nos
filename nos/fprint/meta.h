#ifndef NOS_FPRINT_META_H
#define NOS_FPRINT_META_H

namespace nos 
{
	template <typename T> struct fprint_implementation;

	template <typename T, bool HasNosFPrint = false, bool HasMtdFPrint = false> struct fprint_implementation_solver 
	{
		static ssize_t fprint_to(const T& obj, nos::ostream& os, nos::buffer opts) {
			(void) opts;
			return nos::print_to(os, obj);
		}	
	};

	/*template <typename T, bool HasMtdPrint> struct print_implementation_solver<T, true, HasMtdPrint> 
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
*/
	template <typename T>
	struct fprint_implementation : fprint_implementation_solver<
		typename std::remove_cv<T>::type//, 
		//nos::has_nos_print<typename std::remove_cv<T>::type>::value
		>
	{};
}

#endif