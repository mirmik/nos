#ifndef NOS_IO_STRING_WRITER_H
#define NOS_IO_STRING_WRITER_H

#include <string>
#include <nos/io/ostream.h>

namespace nos {
	class string_writer : public nos::ostream {
	private:
		std::string& str;

	public:
		string_writer(std::string& _str) : str(_str) {}
	
		ssize_t write(const void* ptr, size_t sz) override {
			str.append((char*)ptr, sz);
			return sz;
		}
	};

	class cstring_writer : public nos::ostream {
	private:
		char* str;

	public:
		cstring_writer(char* _str) : str(_str) {}
	
		ssize_t write(const void* ptr, size_t sz) override {
			memcpy(str, ptr, sz);
			str += sz;
			return sz;
		}
	};
}

#endif
