#ifndef NOS_IO_FDFILE_H
#define NOS_IO_FDFILE_H

#include <nos/io/iostream.h>
#include <igris/osutil/fd.h>
#include <unistd.h>
#include <fcntl.h>

namespace nos {

	class fdfile : public nos::iostream
	{
	protected:
		int m_fd;

	public:
		fdfile(int fd) : m_fd(fd) {}
		fdfile(){}
		fdfile(const char * path, int flags) 
		{
			open(path, flags);
		}

		ssize_t write(const void* ptr, size_t sz) override
		{
			return ::write(m_fd, ptr, sz);
			//fwrite(ptr, sizeof(char), sz, filp);
		}

		ssize_t read(void* ptr, size_t sz) override
		{
			return ::read(m_fd, ptr, sz);
			//fread(ptr, sizeof(char), sz, filp);
		}

		bool good() { return m_fd >= 0; }

		int open(const char * path, int mode) 
		{
			m_fd = ::open(path, mode);
			return m_fd;
			//filp = fopen(path, mode);
			//return filp == NULL ? -1 : 0;
		}

		//int fdopen(int fd, const char* mode = "rw") 
		//{
		//	filp = ::fdopen(fd, mode);
		//	return filp == NULL ? -1 : 0;
		//}

		int flush() override
		{
			//return fflush(filp);
			return 0;
		}

		int close() 
		{
			return ::close(m_fd);
		}

		int fd() const 
		{ 
			return m_fd; 
		}
		
		int nonblock(bool en) 
		{ 
			return igris::osutil::nonblock(fd(), en); 
		}

	};

}

#endif