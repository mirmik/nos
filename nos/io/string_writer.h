#ifndef NOS_IO_STRING_WRITER_H
#define NOS_IO_STRING_WRITER_H

/**
	@file
*/

#include <string>
#include <nos/io/ostream.h>

namespace nos {
	class string_writer : public nos::ostream {
	private:
		std::string& str;

	public:
		string_writer(std::string& _str) : str(_str) {}
	
		int write(const void* ptr, size_t sz) override {
			str.append((char*)ptr, sz);
			return sz;
		}
	};

	class string_buffer : public nos::ostream {
	private:
		std::string _str;

	public:	
		int write(const void* ptr, size_t sz) override {
			_str.append((char*)ptr, sz);
			return sz;
		}

		std::string & str() { return _str; }
	};

	class cstring_writer : public nos::ostream {
	private:
		char* str;

	public:
		cstring_writer(char* _str) : str(_str) {}
	
		int write(const void* ptr, size_t sz) override {
			memcpy(str, ptr, sz);
			str += sz;
			return sz;
		}
	};
}

#endif
