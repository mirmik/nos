#include <nos/print/stdtype.h>
#include <nos/util/numconvert.h>

#include <nos/io/ostream.h>

//ssize_t nos_print(nos::ostream& out, const char* const & obj) { dprln("1"); }
//ssize_t nos_print(nos::ostream& out, unsigned int const & obj) { dprln("2"); }

ssize_t nos_print(nos::ostream& out, const char* str) 
{
	out.write(str, strlen(str));
}

ssize_t nos_print(nos::ostream& out, int obj) 
{
		char buf[48];
		i64toa(obj, buf, 10);
		return nos_print(out, buf);
}