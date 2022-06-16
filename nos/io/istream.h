#ifndef NOS_IO_ISTREAM_H
#define NOS_IO_ISTREAM_H

#include <nos/input.h>
#include <stdlib.h>
#include <string>

namespace nos
{
	class istream
	{
	public:

		std::string readline();/*
		{
			std::string ret;
			char c;

			while (1)
			{
				read(&c, 1);
				switch (c)
				{
					case '\r': break;
					case '\n': return ret;
					default: ret += c;
				}
			}
		}*/

		std::string readall() 
		{
			std::string ret;

			int len;
			char buf[1024];

			while(( len = read(buf, 1024) ) != 0) 
			{
				ret.append(buf, len);
			}

			return ret;
		}

		int ignore() { char c; int readed = read(&c,1); return readed; }
		int ignore(int i) { int j = i; while(j--) ignore(); return i; }

		int read_until(char* buf, size_t buflen, char delim) 
		{
			return nos::read_until(*this, buf, buflen, delim);
		}

		int read_paired(char* buf, size_t buflen, char a, char b, bool ignore=true) 
		{
			return nos::read_paired(*this, buf, buflen, a, b, ignore);
		}

		std::string read(size_t size) 
		{
			std::string ret;
			ret.resize(size);
			size_t readlen = read(&ret[0], size);
			ret.resize(readlen);
			return ret;
		}

		virtual int read(void* ptr, size_t sz) = 0;
		virtual ~istream() = default;
	};
}

#endif
