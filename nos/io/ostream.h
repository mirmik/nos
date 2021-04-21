#ifndef NOS_IO_OSTREAM_H
#define NOS_IO_OSTREAM_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <igris/util/types_extension.h>

static inline char __nos_half2hex(uint8_t n) {
	return (char)(n < 10 ? '0' + n : 'A' - 10 + n);
}

namespace nos
{
	class ostream
	{
	public:
		virtual int write(const void* ptr, size_t sz) = 0;
		int write_upper(const void* ptr, size_t sz);
		int write_lower(const void* ptr, size_t sz);
		
		template<typename ... Args>
		int print(const Args& ... args);

		template<typename Arg>
		ostream& operator << (const Arg& arg) 
		{
			print(arg);
			return *this;
		}


		template<typename ... Args>
		int println(const Args& ... args);

		int println()
		{
			return write("\r\n", 2);
		}

		int putchar(char c)
		{
			return write(&c, 1);
		}

		int printhex(char c)
		{
			putchar(__nos_half2hex((uint8_t)((c & 0xF0) >> 4)));
			putchar(__nos_half2hex((uint8_t)(c & 0x0F)));
			return 2;
		}

		int printhex(void* ptr, size_t sz)
		{
			size_t ret = 0;
			char* _ptr = (char*) ptr;

			for (unsigned int i = 0; i < sz; ++i) 
			{
				ret += printhex(*_ptr++);
			}

			return ret;
		}

		template <typename O>
		int printhex(const O& o)
		{
			return printhex((void*)&o, sizeof(O));
		}

		int fill(char c, size_t len);
		int printptr(const void* ptr);

		virtual int flush() { return 0; }
	};
}

#include <nos/print/print.h>

template<typename ... Args>
int nos::ostream::print(const Args& ... args)
{
	return nos::print_to(*this, args ...);
}

template<typename ... Args>
int nos::ostream::println(const Args& ... args)
{
	return nos::println_to(*this, args ...);
}

#endif
