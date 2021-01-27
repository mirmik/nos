#ifndef NOS_PRINT_STDTYPE_H
#define NOS_PRINT_STDTYPE_H

#include <stdlib.h>
#include <stdint.h>

#include <complex>
#include <string>

#include <nos/util/buffer.h>

namespace nos { class ostream; }

ssize_t nos_print(nos::ostream& out, const char* str);
ssize_t nos_print(nos::ostream& out, bool str);

ssize_t nos_print(nos::ostream& out, int8_t str);
ssize_t nos_print(nos::ostream& out, int16_t str);
ssize_t nos_print(nos::ostream& out, int32_t str);
ssize_t nos_print(nos::ostream& out, int64_t str);

ssize_t nos_print(nos::ostream& out, uint8_t str);
ssize_t nos_print(nos::ostream& out, uint16_t str);
ssize_t nos_print(nos::ostream& out, uint32_t str);
ssize_t nos_print(nos::ostream& out, uint64_t str);

ssize_t nos_print(nos::ostream& out, float str);
ssize_t nos_print(nos::ostream& out, double str);

ssize_t nos_print(nos::ostream& out, nos::buffer buf);

#if __has_include(<igris/buffer.h>)
#include <igris/buffer.h>
ssize_t nos_print(nos::ostream& out, igris::buffer buf);
#endif

ssize_t nos_print(nos::ostream& out, const std::string& str);

#if HAS_STRING_VIEW
ssize_t nos_print(nos::ostream& out, const std::string_view& str);
#endif

#include <nos/print.h>
#include <vector>
#include <array>
#include <list>

namespace nos
{
	template <> struct print_implementation<const char *>
	{
		static ssize_t print_to(nos::ostream& out, const char* const obj)
		{
			return nos_print(out, obj);
		}
	};

	template <typename T> struct print_implementation<T*>
	{
		static ssize_t print_to(nos::ostream& out, const T* obj)
		{
			return nos::printptr_to(out, obj);
		}
	};

	template <typename T> struct print_implementation<std::vector<T>>
	{
		static ssize_t print_to(nos::ostream& out, const std::vector<T>& obj)
		{
			return nos::print_list_to<std::vector<T>>(out, obj);
		}
	};

	template <typename T> struct print_implementation<std::list<T>>
	{
		static ssize_t print_to(nos::ostream& out, const std::list<T>& obj)
		{
			return nos::print_list_to<std::list<T>>(out, obj);
		}
	};

	template <class T0, class T1> struct print_implementation<std::pair<T0,T1>>
	{
		static ssize_t print_to(nos::ostream& out, const std::pair<T0,T1>& obj)
		{
			ssize_t res = 0;
			res += nos::print_to(out, "{");
			res += nos::print_to(out, obj.first);
			res += nos::print_to(out, ",");
			res += nos::print_to(out, obj.second);
			res += nos::print_to(out, "}");
			return res;
		}
	};

	template <typename T, size_t M> struct print_implementation<std::array<T,M>>
	{
		static ssize_t print_to(nos::ostream& out, const std::array<T,M>& obj)
		{
			return nos::print_list_to<std::array<T,M>>(out, obj);
		}
	};

	template <typename T> struct print_implementation<std::complex<T>>
	{
		static ssize_t print_to(nos::ostream& out, const std::complex<T>& obj)
		{
			int ret = 0;
			
			T re = obj.real();
			T im = obj.imag();

			ret += nos::print_to(out, re);
			ret += nos::print_to(out, im < 0 ? "-" : "+");
			ret += nos::print_to(out, ABS(im));
			ret += nos::print_to(out, "j");			
			return ret;
		}
	};
}

#endif
