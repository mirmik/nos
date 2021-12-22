#include <nos/print/stdtype.h>
#include <nos/io/ostream.h>

int nos_print(nos::ostream& out, const char* str)
{
	return out.write(str, strlen(str));
}

int nos_print(nos::ostream& out, char* str) 
{
	return out.write(str, strlen(str));	
}

#if __has_include(<string_view>)
int nos_print(nos::ostream& out, const std::string_view & buf)
{
	return out.write(buf.data(), buf.size());
}
#endif

int nos_print(nos::ostream& out, bool obj) 		{ return nos_print(out, obj ? "true" : "false"); }

int nos_print(nos::ostream& out, signed char obj) 	    { char buf[48]; sprintf(buf, "%d", obj);   return nos_print(out, buf); }
int nos_print(nos::ostream& out, signed short obj) 	    { char buf[48]; sprintf(buf, "%d", obj);   return nos_print(out, buf); }
int nos_print(nos::ostream& out, signed int obj) 	    { char buf[48];	sprintf(buf, "%d", obj);   return nos_print(out, buf); }
int nos_print(nos::ostream& out, signed long obj) 	    { char buf[48];	sprintf(buf, "%ld", obj);  return nos_print(out, buf); }
int nos_print(nos::ostream& out, signed long long obj) 	{ char buf[48];	sprintf(buf, "%lld", obj); return nos_print(out, buf); }

int nos_print(nos::ostream& out, unsigned char obj) 	{ char buf[48]; sprintf(buf, "%u", obj);   return nos_print(out, buf); }
int nos_print(nos::ostream& out, unsigned short obj) 	{ char buf[48]; sprintf(buf, "%u", obj);   return nos_print(out, buf); }
int nos_print(nos::ostream& out, unsigned int obj) 	    { char buf[48];	sprintf(buf, "%u", obj);   return nos_print(out, buf); }
int nos_print(nos::ostream& out, unsigned long obj) 	{ char buf[48];	sprintf(buf, "%lu", obj);  return nos_print(out, buf); }
int nos_print(nos::ostream& out, unsigned long long obj){ char buf[48];	sprintf(buf, "%llu", obj); return nos_print(out, buf); }

int nos_print(nos::ostream& out, float obj)
{
	char buf[48];
	sprintf(buf, "%f", obj);
	return nos_print(out, buf);
}

#ifndef WITHOUT_FLOAT64
int nos_print(nos::ostream& out, double obj)
{
	char buf[48];
	sprintf(buf, "%lf", obj);
	return nos_print(out, buf);
}
#endif
