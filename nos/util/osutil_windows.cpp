#include <nos/util/osutil.h>
#include <fcntl.h>
#include <stdio.h>
#include <winsock2.h>

int nos::osutil::nonblock(int fd, bool en)
{
    unsigned long mode = en;
    return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
}

int nos::osutil::write(int fd, const void * data, size_t size) 
{
	return ::write(fd, data, size);	
}

int nos::osutil::read(int fd, void * data, size_t size) 
{
	return ::read(fd, data, size);
}

int nos::osutil::open(const char * data, int mode) 
{
	return ::open(data, mode);
}

int nos::osutil::close(int fd) 
{
	return ::close(fd);
}