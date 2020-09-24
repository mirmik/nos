#include <nos/print/stdtype.h>
#include <igris/util/numconvert.h>

#include <nos/io/ostream.h>
#include <iostream>

#include <igris/dprint.h>

ssize_t nos_print(nos::ostream& out, const char* str)
{
	return out.write(str, strlen(str));
}

ssize_t nos_print(nos::ostream& out, igris::buffer buf)
{
	return out.write(buf.data(), buf.size());
}

ssize_t nos_print(nos::ostream& out, bool obj) 		{ return nos_print(out, obj ? "true" : "false"); }
ssize_t nos_print(nos::ostream& out, int8_t obj) 	{ char buf[48]; i64toa(obj, buf, 10); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, int16_t obj) 	{ char buf[48]; i64toa(obj, buf, 10); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, int32_t obj) 	{ char buf[48];	i64toa(obj, buf, 10); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, int64_t obj) 	{ char buf[48];	i64toa(obj, buf, 10); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, uint8_t obj) 	{ char buf[48];	u64toa(obj, buf, 10); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, uint16_t obj) 	{ char buf[48];	u64toa(obj, buf, 10); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, uint32_t obj) 	{ char buf[48];	u64toa(obj, buf, 10); return nos_print(out, buf); }
ssize_t nos_print(nos::ostream& out, uint64_t obj) 	{ char buf[48];	u64toa(obj, buf, 10); return nos_print(out, buf); }

ssize_t nos_print(nos::ostream& out, float32_t obj)
{
	char buf[48];
#if defined(NOS_USE_IGRIS_NUMCONVERT)
	f32toa(obj, buf, 5);
#else
	sprintf(buf, "%f", obj);
#endif
	return nos_print(out, buf);
}

#ifndef WITHOUT_FLOAT64
ssize_t nos_print(nos::ostream& out, float64_t obj)
{
	char buf[48];
#if defined(NOS_USE_IGRIS_NUMCONVERT)
	f64toa(obj, buf, 5);
#else
	sprintf(buf, "%f", obj);
#endif
	return nos_print(out, buf);
}
#endif

ssize_t nos_print(nos::ostream& out, const std::string& str)
{
	return nos_print(out, igris::buffer(str));
}

ssize_t nos_print(nos::ostream& out, const std::string_view& str)
{
	return nos_print(out, igris::buffer(str));
}