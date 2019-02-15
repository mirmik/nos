#ifndef NOS_PRINT_STDTYPE_H
#define NOS_PRINT_STDTYPE_H

#include <stdlib.h>
#include <stdint.h>
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

	template <typename T, size_t M> struct print_implementation<std::array<T,M>>
	{
		static ssize_t print_to(nos::ostream& out, const std::array<T,M>& obj)
		{
			return nos::print_list_to<std::array<T,M>>(out, obj);
		}
	};
}


//namespace nos
//{

	/*	template <> struct print_implementation<const char*>
		{
			static ssize_t print_to(nos::ostream& out, const char* obj)
			{
				return out.write(obj, strlen(obj));
			}
		};

		template <size_t N> struct print_implementation<char[N]>
		{
			static ssize_t print_to(nos::ostream& out, const char* obj)
			{
				return print_implementation<const char*>::print_to(out, obj);
			}
		};

		template <> struct print_implementation<int64_t>
		{
			static ssize_t print_to(nos::ostream& out, int obj)
			{
				char buf[48];
				i64toa(obj, buf, 10);
				return print_implementation<const char*>::print_to(out, buf);
			}
		};

		template <> struct print_implementation<int32_t>
		{
			static ssize_t print_to(nos::ostream& out, int obj)
			{
				char buf[48];
				i32toa(obj, buf, 10);
				return print_implementation<const char*>::print_to(out, buf);
			}
		};

		template <> struct print_implementation<int16_t>
		{
			static ssize_t print_to(nos::ostream& out, int obj)
			{
				char buf[48];
				i16toa(obj, buf, 10);
				return print_implementation<const char*>::print_to(out, buf);
			}
		};

		template <> struct print_implementation<int8_t>
		{
			static ssize_t print_to(nos::ostream& out, int obj)
			{
				char buf[48];
				i8toa(obj, buf, 10);
				return print_implementation<const char*>::print_to(out, buf);
			}
		};

		template <> struct print_implementation<uint64_t>
		{
			static ssize_t print_to(nos::ostream& out, int obj)
			{
				char buf[48];
				u64toa(obj, buf, 10);
				return print_implementation<const char*>::print_to(out, buf);
			}
		};

		template <> struct print_implementation<uint32_t>
		{
			static ssize_t print_to(nos::ostream& out, int obj)
			{
				char buf[48];
				u32toa(obj, buf, 10);
				return print_implementation<const char*>::print_to(out, buf);
			}
		};

		template <> struct print_implementation<uint16_t>
		{
			static ssize_t print_to(nos::ostream& out, int obj)
			{
				char buf[48];
				u16toa(obj, buf, 10);
				return print_implementation<const char*>::print_to(out, buf);
			}
		};

		template <> struct print_implementation<uint8_t>
		{
			static ssize_t print_to(nos::ostream& out, int obj)
			{
				char buf[48];
				u8toa(obj, buf, 10);
				return print_implementation<const char*>::print_to(out, buf);
			}
		};

		template <> struct print_implementation<std::string>
		{
			static ssize_t print_to(nos::ostream& out, const std::string& obj)
			{
				return print_implementation<const char*>::print_to(out, obj.c_str());
			}
		};*/
//}

#endif