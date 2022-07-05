#ifndef NOS_IO_BUFFERED_FILE_H
#define NOS_IO_BUFFERED_FILE_H

#include <string>
#include <nos/io/iostream.h>
#include <nos/util/osutil.h>

namespace nos
{

	class buffered_file : public nos::iostream
	{
	protected:
		FILE* filp=nullptr;

	public:
		buffered_file(FILE* f) : filp(f) {}
		buffered_file() : filp(nullptr) {}
		
		buffered_file(const char * path, const char * mode)
		{
			open(path, mode);
		}

		buffered_file(const std::string& path, const std::string& mode)
		{
			open(path.c_str(), mode.c_str());
		}

		buffered_file(const buffered_file&) = default;
		buffered_file& operator= (const buffered_file&) = default;		

		int write(const void* ptr, size_t sz) override
		{
			return fwrite(ptr, sizeof(char), sz, filp);
		}

		int read(void* ptr, size_t sz) override
		{
			return fread(ptr, sizeof(char), sz, filp);
		}

		bool good()
		{
			return filp != nullptr;
		}

		int open(const char * path, const char * mode)
		{
			filp = fopen(path, mode);
			return filp == NULL ? -1 : 0;
		}

		int fdopen(int fd, const char* mode = "rw")
		{
			filp = ::fdopen(fd, mode);
			return filp == NULL ? -1 : 0;
		}

		int flush() override
		{
			return fflush(filp);
		}

		int close()
		{
			return fclose(filp);
		}

		int fd() const
		{
			return fileno(filp);
		}

		int nonblock(bool en)
		{
			return nos::osutil::nonblock(fd(), en);
		}

	};

}

#endif
