#ifndef NOS_IO_OSTREAM_H
#define NOS_IO_OSTREAM_H

#include <string.h>

#include <nos/print/print.h>
#include <nos/util/hexascii.h>
#include <nos/util/numconvert.h>

namespace nos
{
	class ostream
	{
	public:
		template<typename ... Args>
		ssize_t print(const Args& ... args)
		{
			nos::print_to(*this, args ...);
		}

		template<typename ... Args>
		ssize_t println(const Args& ... args)
		{
			nos::println_to(*this, args ...);
		}

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

		ssize_t fill(char c, size_t len);
		ssize_t printptr(const void* ptr);

	protected:
		virtual ssize_t writeData(const char* ptr, size_t sz) = 0;
	};
}

#endif