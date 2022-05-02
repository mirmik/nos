#ifndef NOS_FPRINT_FPRINT_H
#define NOS_FPRINT_FPRINT_H

/**
	@file
*/

#include <nos/fprint/visitor.h>
#include <nos/fprint/stdtype.h>
#include <nos/print/print.h>
#include <nos/io/string_writer.h>

namespace nos
{
	int fprint_impl(nos::ostream& out, const char* fmt, const visitable_arglist& args);

	template<typename ... Args>
	int fprint_to(nos::ostream& out, const char* fmt, const Args& ... args)
	{
		return fprint_impl(out, fmt,
		    visitable_arglist ({ 
		    	visitable_argument(args, 
		    	nos::format_visitor()) 
		    	... 
		    })
		);
	}

	template<typename ... Args>
	int fprint(const char* fmt, const Args& ... args)
	{
		return nos::fprint_to(*current_ostream, fmt,  args ...);
	}

	template<typename ... Args>
	int fprintln(const Args& ... args)
	{
		size_t ret = 0;
		ret += fprint_to(*current_ostream, args ...);
		ret += println_to(*current_ostream);
		return ret;
	}

	template<typename ... Args>
	int fprintln_to(nos::ostream& out, const Args& ... args)
	{
		size_t ret = 0;
		ret += fprint_to(out, args ...);
		ret += println_to(*current_ostream);
		return ret;
	}

	int fprint(const char* arg);

	int fprintln(const char* arg);

	int fprint_to(nos::ostream& out, const char* arg);

	int fprintln_to(nos::ostream& out, const char* arg);

	inline std::string format(const char* fmt, const visitable_arglist& args)
	{
		std::string ret;
		nos::string_writer writer(ret);
		nos::fprint_impl(writer, fmt, args);
		return ret;
	}

	template<typename ... Args>
	std::string format(const char* fmt, const Args& ... args)
	{
		std::string ret;
		nos::string_writer writer(ret);
		nos::fprint_to(writer, fmt, args ...);
		return ret;
	}

	static inline int format_buffer(char* buf, const char* fmt, const visitable_arglist& args)
	{
		nos::cstring_writer writer(buf);
		int ret = nos::fprint_impl(writer, fmt, args);
		writer.putbyte('\0');
		return ret;
	}

	template<typename ... Args>
	int format_buffer(char* buf, const char* fmt, const Args& ... args)
	{
		nos::cstring_writer writer(buf);
		int ret = nos::fprint_to(writer, fmt, args ...);
		writer.putbyte('\0');
		return ret;
	}
}

#endif
