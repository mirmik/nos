#ifndef GXX_SSTREAM_H
#define GXX_SSTREAM_H

#include <iostream>
#include <nos/io/iostream.h>

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

	class file_ostream : public nos::ostream
	{
	private:
		FILE* out;

	public:
		file_ostream(FILE* f) : out(f) {}

		ssize_t writeData(const char* ptr, size_t sz) override
		{
			return fwrite(ptr, sizeof(char), sz, out);
		}

		virtual void flush()
		{
			fflush(out);
		}
	};

	class file_istream : public nos::istream
	{
	private:
		FILE* in;

	public:
		file_istream(FILE* f) : in(f) {}

		ssize_t readData(char* ptr, size_t sz) override
		{
			return fread(ptr, sizeof(char), sz, in);
		}
	};


	extern file_ostream cout;
	extern file_ostream cerr;
	extern file_istream cin;

}

#endif
