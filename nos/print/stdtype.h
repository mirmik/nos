#ifndef NOS_PRINT_STDTYPE_H
#define NOS_PRINT_STDTYPE_H

#include <string.h>

#include <nos/print/print.h>
#include <nos/io/ostream.h>

#include <nos/util/numconvert.h>

namespace nos
{
	template <> struct print_implementations<const char*>
	{
		static ssize_t print_to(nos::ostream& out, const char* obj)
		{
			return out.write(obj, strlen(obj));
		}
	};

	template <size_t N> struct print_implementations<char[N]>
	{
		static ssize_t print_to(nos::ostream& out, const char* obj)
		{
			return print_implementations<const char*>::print_to(out, obj);
		}
	};

	template <> struct print_implementations<int64_t>
	{
		static ssize_t print_to(nos::ostream& out, int obj)
		{
			char buf[48];
			i64toa(obj, buf, 10);
			return print_implementations<const char*>::print_to(out, buf);
		}
	};

	template <> struct print_implementations<int32_t>
	{
		static ssize_t print_to(nos::ostream& out, int obj)
		{
			char buf[48];
			i32toa(obj, buf, 10);
			return print_implementations<const char*>::print_to(out, buf);
		}
	};

	template <> struct print_implementations<int16_t>
	{
		static ssize_t print_to(nos::ostream& out, int obj)
		{
			char buf[48];
			i16toa(obj, buf, 10);
			return print_implementations<const char*>::print_to(out, buf);
		}
	};

	template <> struct print_implementations<int8_t>
	{
		static ssize_t print_to(nos::ostream& out, int obj)
		{
			char buf[48];
			i8toa(obj, buf, 10);
			return print_implementations<const char*>::print_to(out, buf);
		}
	};

	template <> struct print_implementations<uint64_t>
	{
		static ssize_t print_to(nos::ostream& out, int obj)
		{
			char buf[48];
			u64toa(obj, buf, 10);
			return print_implementations<const char*>::print_to(out, buf);
		}
	};

	template <> struct print_implementations<uint32_t>
	{
		static ssize_t print_to(nos::ostream& out, int obj)
		{
			char buf[48];
			u32toa(obj, buf, 10);
			return print_implementations<const char*>::print_to(out, buf);
		}
	};

	template <> struct print_implementations<uint16_t>
	{
		static ssize_t print_to(nos::ostream& out, int obj)
		{
			char buf[48];
			u16toa(obj, buf, 10);
			return print_implementations<const char*>::print_to(out, buf);
		}
	};

	template <> struct print_implementations<uint8_t>
	{
		static ssize_t print_to(nos::ostream& out, int obj)
		{
			char buf[48];
			u8toa(obj, buf, 10);
			return print_implementations<const char*>::print_to(out, buf);
		}
	};

	template <> struct print_implementations<std::string>
	{
		static ssize_t print_to(nos::ostream& out, const std::string& obj)
		{
			return print_implementations<const char*>::print_to(out, obj.c_str());
		}
	};
}

#endif