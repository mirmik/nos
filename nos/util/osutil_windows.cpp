#include <fcntl.h>
#include <io.h>
#include <nos/util/osutil.h>
#include <stdio.h>
#include <winsock2.h>

int nos::osutil::nonblock(int64_t fd, bool en)
{
    unsigned long mode = en;
    return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
}

int nos::osutil::write(int64_t fd, const void *data, size_t size)
{
    return ::_write((int)fd, data, size);
}

int nos::osutil::read(int64_t fd, void *data, size_t size)
{
    return ::_read((int)fd, data, size);
}

int64_t nos::osutil::open(const char *data, int mode)
{
    return ::_open(data, mode);
}

int nos::osutil::close(int64_t fd)
{
    return ::_close((int)fd);
}