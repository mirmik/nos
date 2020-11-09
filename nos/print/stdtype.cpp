#include <nos/print/stdtype.h>
#include <nos/io/ostream.h>

#include <iostream>

//#include <igris/util/numconvert.h>

ssize_t nos_print(nos::ostream& out, const char* str)
{
	return out.write(str, strlen(str));
}

ssize_t nos_print(nos::ostream& out, nos::buffer buf)
{
	return out.write(buf.data(), buf.size());
}

#if __has_include(<igris/buffer.h>)
ssize_t nos_print(nos::ostream& out, igris::buffer buf)
{
	return out.write(buf.data(), buf.size());
}
#endif

ssize_t nos_print(nos::ostream& out, bool obj) 		{ return nos_print(out, obj ? "true" : "false"); }
ssize_t nos_print(nos::ostream& out, int8_t obj) 	{ char buf[48]; sprintf(buf, "%d", obj); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, int16_t obj) 	{ char buf[48]; sprintf(buf, "%d", obj); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, int32_t obj) 	{ char buf[48];	sprintf(buf, "%d", obj); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, int64_t obj) 	{ char buf[48];	sprintf(buf, "%ld", obj); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, uint8_t obj) 	{ char buf[48];	sprintf(buf, "%u", obj); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, uint16_t obj) 	{ char buf[48];	sprintf(buf, "%u", obj); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, uint32_t obj) 	{ char buf[48];	sprintf(buf, "%u", obj); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, uint64_t obj) 	{ char buf[48];	sprintf(buf, "%lu", obj); return nos_print(out, buf); }

ssize_t nos_print(nos::ostream& out, float obj)
{
	char buf[48];
//#if 1
//	f32toa(obj, buf, 5);
//#else
	sprintf(buf, "%f", obj);
//#endif
	return nos_print(out, buf);
}

#ifndef WITHOUT_FLOAT64
ssize_t nos_print(nos::ostream& out, double obj)
{
	char buf[48];
//#if 1
//	f64toa(obj, buf, 5);
//#else
	sprintf(buf, "%lf", obj);
//#endif
	return nos_print(out, buf);
}
#endif

ssize_t nos_print(nos::ostream& out, const std::string& str)
{
	return nos_print(out, nos::buffer(str));
}

#if IGRIS_HAS_STRING_VIEW
ssize_t nos_print(nos::ostream& out, const std::string_view& str)
{
	return nos_print(out, nos::buffer(str));
}
#endif