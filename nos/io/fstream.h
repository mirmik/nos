#ifndef NOS_IO_FSTREAM_H
#define NOS_IO_FSTREAM_H

#include <nos/io/iostream.h>

namespace nos {

	class fstream : public nos::iostream
	{
	private:
		FILE* file;

	public:
		fstream(FILE* f) : file(f) {}
		fstream() : file(nullptr) {}
		fstream(const char * path, const char * mode) 
		{
			open(path, mode);
		}

		ssize_t write(const void* ptr, size_t sz) override
		{
			return fwrite(ptr, sizeof(char), sz, file);
		}

		ssize_t read(char* ptr, size_t sz) override
		{
			return fread(ptr, sizeof(char), sz, file);
		}

		bool good() { return file != nullptr; }

		int open(const char * path, const char * mode) 
		{
			file = fopen(path, mode);
			return 0;
		}

		virtual int flush()
		{
			return fflush(file);
		}
	};

}

#endif