#ifndef NOS_IO_FDLIKE_H
#define NOS_IO_FDLIKE_H

#include <nos/io/iostream.h>
#include <igris/osutil/fd.h>
#include <unistd.h>

namespace nos 
{
	class fdlike : public nos::iostream
	{
	protected:
		int m_fd;
	
	public:
		ssize_t write(const void* ptr, size_t sz) override
		{
			return ::write(m_fd, ptr, sz);
		}

		ssize_t read(void* ptr, size_t sz) override
		{
			return ::read(m_fd, ptr, sz);
		}

		ssize_t read_with_timeout_ms(void* ptr, size_t sz, int ms); 
		
		bool good() { return m_fd >= 0; }

		int flush() override
		{
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