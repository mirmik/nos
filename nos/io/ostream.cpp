#include <nos/print/stdtype.h>
#include <nos/io/ostream.h>

int nos::ostream::fill(char c, size_t len)
{
	size_t _len = len;
	while (_len--)
	{
		this->putbyte(c);
	}

	return len;
}

int nos::ostream::printptr(const void* ptr)
{
	char buf[48];
	//u64toa((uintptr_t)ptr, buf, 16);
	snprintf(buf, sizeof(buf), "%p", ptr);
	size_t len = strlen(buf);
	int ret = fill('0', sizeof(void*) * 2 - len);
	return ret + nos::print_to(*this, (const char*) buf);
}

int nos::ostream::write_upper(const void* _ptr, size_t sz) { char* ptr = (char*)_ptr; size_t _sz = sz; while(_sz--) putchar(toupper(*ptr++)); return sz; }
int nos::ostream::write_lower(const void* _ptr, size_t sz) { char* ptr = (char*)_ptr; size_t _sz = sz; while(_sz--) putchar(tolower(*ptr++)); return sz; }
