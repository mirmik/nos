#ifndef NOS_IO_FDFILE_H
#define NOS_IO_FDFILE_H

#include <nos/io/iostream.h>
#include <igris/osutil/fd.h>
#include <unistd.h>
#include <fcntl.h>

namespace nos
{

	class file : public nos::iostream
	{
	protected:
		int m_fd;

	public:
		file(int fd) : m_fd(fd) {}
		file() {}
		file(const char * path, int flags)
		{
			open(path, flags);
		}

		ssize_t write(const void* ptr, size_t sz) override
		{
			return ::write(m_fd, ptr, sz);
		}

		ssize_t read(void* ptr, size_t sz) override
		{
			return ::read(m_fd, ptr, sz);
		}

		bool good()
		{
			return m_fd >= 0;
		}

		int open(const char * path, int mode)
		{
			m_fd = ::open(path, mode);
			return m_fd;
		}

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