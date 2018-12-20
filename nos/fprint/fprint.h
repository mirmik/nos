#ifndef NOS_FPRINT_FPRINT_H
#define NOS_FPRINT_FPRINT_H

#include <utility>
#include <nos/fprint/visitor.h>
#include <nos/print/print.h>

#include <nos/util/numconvert.h>

namespace nos
{
	ssize_t fprint_impl(nos::ostream& out, const char* fmt, const visitable_arglist& args);

	template<typename ... Args>
	ssize_t fprint_to(nos::ostream& out, const char* fmt, Args&& ... args)
	{
		return fprint_impl(out, fmt,
		    visitable_arglist ({ visitable_argument(std::forward<Args>(args), nos::format_visitor()) ... })
		);
	}

	template<typename ... Args>
	ssize_t fprint(const char* fmt, Args&& ... args)
	{
		return nos::fprint_to(*current_ostream, fmt,  std::forward<Args>(args) ...);
	}

	template<typename ... Args>
	ssize_t fprintln(Args&& ... args)
	{
		size_t ret = 0;
		ret += fprint_to(*current_ostream, std::forward<Args>(args) ...);
		ret += println();
		return ret;
	}

	template<typename ... Args>
	ssize_t fprintln_to(nos::ostream& out, Args&& ... args)
	{
		size_t ret = 0;
		ret += fprint_to(out, std::forward<Args>(args) ...);
		ret += println();
		return ret;
	}

	ssize_t fprint(const char* arg);

	ssize_t fprintln(const char* arg);

	ssize_t fprint_to(nos::ostream& out, const char* arg);

	ssize_t fprintln_to(nos::ostream& out, const char* arg);
}

#endif