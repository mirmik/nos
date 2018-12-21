#ifndef NOS_IO_OSTREAM_H
#define NOS_IO_OSTREAM_H

#include <string.h>

#include <nos/util/hexascii.h>
#include <nos/util/numconvert.h>

namespace nos
{
	class ostream
	{
	public:
		template<typename ... Args>
		ssize_t print(const Args& ... args);

		template<typename ... Args>
		ssize_t println(const Args& ... args);

		ssize_t println()
		{
			return writeData("\r\n", 2);
		}

		ssize_t write(const void* ptr, size_t sz)
		{
			return writeData((const char*) ptr, sz);
		}

		ssize_t putchar(char c)
		{
			return writeData(&c, 1);
		}

		ssize_t printhex(char c)
		{
			putchar(half2hex((uint8_t)((c & 0xF0) >> 4)));
			putchar(half2hex((uint8_t)(c & 0x0F)));
			return 2;
		}

		ssize_t printhex(void* ptr, size_t sz)
		{
			size_t ret = 0;
			char* _ptr = (char*) ptr;

			for (uint i = 0; i < sz; ++i) 
			{
				ret += printhex(*_ptr++);
			}

			return ret;
		}

		template <typename O>
		ssize_t printhex(const O& o)
		{
			return printhex((void*)&o, sizeof(O));
		}

		ssize_t fill(char c, size_t len);
		ssize_t printptr(const void* ptr);

		virtual void flush() { }

	protected:
		virtual ssize_t writeData(const char* ptr, size_t sz) = 0;
	};
}

#include <nos/print/print.h>

template<typename ... Args>
ssize_t nos::ostream::print(const Args& ... args)
{
	return nos::print_to(*this, args ...);
}

template<typename ... Args>
ssize_t nos::ostream::println(const Args& ... args)
{
	return nos::println_to(*this, args ...);
}

#endif