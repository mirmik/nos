#ifndef NOS_UTIL_FD_H
#define NOS_UTIL_FD_H

#include <stdint.h>
#include <stdlib.h>

namespace nos
{
	namespace osutil
	{
		int nonblock(int fd, bool en);
		int write(int fd, const void * data, size_t size);
		int read(int fd, void * data, size_t size);
		int open(const char * data, int mode);
		int close(int fd);
	}
}

#endif
