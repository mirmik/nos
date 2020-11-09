#ifndef NOS_UTIL_BUFFER_H
#define NOS_UTIL_BUFFER_H

#include <string.h>
#include <string>

#ifdef __has_include
	#if __has_include(<string_view>) && (__cplusplus >= 201703L)
	#include <string_view>
	#define HAS_STRING_VIEW 1
	#else
	#define HAS_STRING_VIEW 0
	#endif
#else
#include <string_view>
#define HAS_STRING_VIEW 1
#endif

namespace nos
{
	class buffer
	{
	private:
		char * _data;
		size_t _size;

	public:
		buffer() :
			_data(nullptr), _size(0)
		{}

		buffer(char * data, size_t size) :
			_data(data), _size(size)
		{}

		buffer(const char * data, size_t size) :
			_data((char*)data), _size(size)
		{}

		const char *  data() const { return _data; }
		char *  data()             { return _data; }

		size_t   size() const { return _size; }

		buffer(const std::string& str) : buffer(str.data(), str.size()) {}
		
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

		bool empty()
		{
			return _data == nullptr;
		}
	};
}

#endif