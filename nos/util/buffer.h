#ifndef NOS_UTIL_BUFFER_H
#define NOS_UTIL_BUFFER_H

#include <stdint.h>
#include <string.h>

#if __has_include(<string_view>) && (__cplusplus >= 201703L)
#include <string_view>
#define HAS_STRING_VIEW 1
#else
#define HAS_STRING_VIEW 0
#endif

//#if __has_include(<string>) && (__cplusplus >= 201703L)
#include <string>
#include <nos/util/numconvert.h>
#include <nos/binary/bytearray.h>
//#define HAS_STRING 1
//#else
//#define HAS_STRING 0
//#endif

namespace nos
{
	class buffer
	{
	private:
		char * _data = nullptr;
		size_t _size = 0;

	public:
		buffer() = default;
		buffer(const buffer & oth) = default;
		buffer(buffer && oth) = default;
		buffer& operator=(const buffer & oth) = default;
		buffer& operator=(buffer && oth) = default;

		buffer(char * data, size_t size) :
			_data(data), _size(size)
		{}

		buffer(const char * data, size_t size) :
			_data((char*)data), _size(size)
		{}

		buffer(const char * data) :
			_data((char*)data), _size(strlen(data))
		{}

		const char *  data() const { return _data; }
		char *  data()             { return _data; }

		size_t   size() const { return _size; }

		buffer(const std::string& str) : buffer(str.data(), str.size()) {}
		buffer(const nos::bytearray& str) : buffer((char*)str.data(), str.size()) {}

#if HAS_STRING_VIEW
		buffer(const std::string_view& str) : buffer(str.data(), str.size()) {}
#endif

		bool operator==(const buffer& other) const
		{
			return (_size == other._size) &&
			       (strncmp(_data, other._data, _size < other._size ?
			                _size : other._size) == 0);
		}

		bool operator!=(const buffer& other) const
		{
			return (_size != other._size) ||
			       (strncmp(_data, other._data, _size < other._size ?
			                _size : other._size) != 0);
		}

		bool operator==(const char* str) const
		{
			return strncmp(_data, str, _size) == 0;
		}

		bool operator!=(const char* str) const
		{
			return strncmp(_data, str, _size) != 0;
		}

		char& operator[](size_t num)
		{
			return *(_data + num);
		}

		char operator[](size_t num) const
		{
			return *(_data + num);
		}

		char * operator * ()
		{
			return _data;
		}

		size_t operator + ()
		{
			return _size;
		}

		char* begin()
		{
			return _data;
		}

		char* end()
		{
			return _data + _size;
		}

		const char* begin() const
		{
			return _data;
		}

		const char* end() const
		{
			return _data + _size;
		}

		bool empty()
		{
			return _data == nullptr;
		}

		std::string to_string() const
		{
			return std::string(_data, _size);
		}

		int to_int() const 
		{
			return std::stoi(std::string(_data, _size));
		}
	};

	/*std::ostream & operator<<(std::ostream & os, const nos::buffer & buf)
	{
		os.write(buf.data(), buf.size());
		return os;
	}*/
}

#endif
