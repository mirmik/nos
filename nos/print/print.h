#ifndef NOS_PRINT_PRINT_H
#define NOS_PRINT_PRINT_H

#include <nos/dprint/dprint.h>

#include <stdlib.h>
#include <nos/print/meta.h>

namespace nos
{
	class ostream;
	extern ostream* current_ostream;
	ssize_t putchar_to(nos::ostream&, char);
	ssize_t println_to(nos::ostream&);

	ssize_t print_dump_to(nos::ostream&, const void *mem, size_t len, unsigned int columns = 8);
	ssize_t print_dump(const void *mem, size_t len, unsigned int columns = 8);

	template<typename Arg>
	ssize_t print_to(nos::ostream& out, const Arg& arg)
	{
		return nos::print_implementation<Arg>::print_to(out, arg);
	}

	template<typename Head, typename ... Tail>
	ssize_t print_to(nos::ostream& out, const Head& head, const Tail& ... tail)
	{
		ssize_t res = 0;
		res += print_to(out, head);
		res += nos::putchar_to(out, ' ');
		res += print_to(out, tail ...);
		return res;
	}

	template<typename ... Args>
	ssize_t println_to(nos::ostream& out, const Args& ... args)
	{
		ssize_t res = 0;
		res += print_to(out, args ...);
		res += nos::println_to(out);
		return res;
	}

	template<typename Arg>
	ssize_t print(const Arg& arg)
	{
		return print_to(*current_ostream, arg);
	}

	template<typename ... Args>
	ssize_t print(const Args& ... args)
	{
		return print_to(*current_ostream, args ...);
	}

	template<typename Arg>
	ssize_t println(const Arg& arg)
	{
		return println_to(*current_ostream, arg);
	}

	template<typename ... Args>
	ssize_t println(const Args& ... args)
	{
		return println_to(*current_ostream, args ...);
	}

	static inline ssize_t putchar(char c)
	{
		return putchar_to(*current_ostream, c);
	}

	ssize_t write_to(nos::ostream& out, const void* buf, size_t sz);

	static inline ssize_t write(const void* buf, size_t sz) {
		return nos::write_to(*current_ostream, buf, sz);
	}

	ssize_t writeln_to(nos::ostream& out, const void* buf, size_t sz);

	static inline ssize_t writeln(const void* buf, size_t sz) {
		return nos::writeln_to(*current_ostream, buf, sz);
	}
}

#endif