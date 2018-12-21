#include <nos/print/stdtype.h>
#include <nos/util/numconvert.h>

#include <nos/io/ostream.h>

ssize_t nos_print(nos::ostream& out, const char* str) 
{
	out.write(str, strlen(str));
}

ssize_t nos_print(nos::ostream& out, int8_t obj) 
{
		char buf[48];
		i64toa(obj, buf, 10);
		return nos_print(out, buf);
}

ssize_t nos_print(nos::ostream& out, int16_t obj) 
{
		char buf[48];
		i64toa(obj, buf, 10);
		return nos_print(out, buf);
}

ssize_t nos_print(nos::ostream& out, int32_t obj) 
{
		char buf[48];
		i64toa(obj, buf, 10);
		return nos_print(out, buf);
}

ssize_t nos_print(nos::ostream& out, int64_t obj) 
{
		char buf[48];
		i64toa(obj, buf, 10);
		return nos_print(out, buf);
}

ssize_t nos_print(nos::ostream& out, uint8_t obj) 
{
		char buf[48];
		u64toa(obj, buf, 10);
		return nos_print(out, buf);
}

ssize_t nos_print(nos::ostream& out, uint16_t obj) 
{
		char buf[48];
		u64toa(obj, buf, 10);
		return nos_print(out, buf);
}

ssize_t nos_print(nos::ostream& out, uint32_t obj) 
{
		char buf[48];
		u64toa(obj, buf, 10);
		return nos_print(out, buf);
}

ssize_t nos_print(nos::ostream& out, uint64_t obj) 
{
		char buf[48];
		u64toa(obj, buf, 10);
		return nos_print(out, buf);
}