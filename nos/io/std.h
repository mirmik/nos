#ifndef GXX_SSTREAM_H
#define GXX_SSTREAM_H

#include <iostream>
#include <nos/io/iostream.h>
#include <nos/io/fstream.h>

namespace nos
{
	/*class std_string_writer : public gxx::io::ostream {
		std::string& str;
	public:
		std_string_writer(std::string& _str) : str(_str) {}
	protected:
		ssize_t writeData(const char* ptr, size_t sz) override {
			str.append(ptr, sz);
			return sz;
		}
	};

	class std_ostream_writer : public gxx::io::ostream {
		std::ostream& out;
	public:
		std_ostream_writer(std::ostream& _out) : out(_out) {}
	protected:
		ssize_t writeData(const char* ptr, size_t sz) override {
			out.write(ptr, sz);
			return sz;
		}
	};*/

	extern fstream cout;
	extern fstream cerr;
	extern fstream cin;

}

#endif
