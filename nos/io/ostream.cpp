#include <nos/print/stdtype.h>
#include <nos/io/ostream.h>

ssize_t nos::ostream::fill(char c, size_t len)
{
	while (len--)
	{
		putchar(c);
	}

	return len;
}

ssize_t nos::ostream::printptr(const void* ptr)
{
	char buf[48];
	nos_util_u64toa((uintptr_t)ptr, buf, 16);
	size_t len = strlen(buf);
	ssize_t ret = fill('0', sizeof(void*) * 2 - len);
	return ret + nos::print_to(*this, (const char*) buf);
}