#include <nos/util/osutil.h>

#ifndef _MSC_VER
#include <fcntl.h>
#include <unistd.h>

int nos::osutil::nonblock(int fd, bool en)
{
    if (fd < 0)
        return -1;
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0)
        return -1;
    flags = en ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    return fcntl(fd, F_SETFL, flags) == 0;
}

int nos::osutil::write(int fd, const void *data, size_t size)
{
    return ::write(fd, data, size);
}

int nos::osutil::read(int fd, void *data, size_t size)
{
    return ::read(fd, data, size);
}

int nos::osutil::open(const char *data, int mode)
{
    return ::open(data, mode);
}

int nos::osutil::close(int fd)
{
    return ::close(fd);
}

int nos::osutil::access(const std::string &path)
{
    return ::access(path.c_str(), F_OK);
}

// file is exists
int nos::osutil::access(const char *path)
{
    return ::access(path, F_OK);
}

bool nos::osutil::is_accessible(const std::string &path)
{
    return ::access(path.c_str(), F_OK) == 0;
}

bool nos::osutil::is_accessible(const char *path)
{
    return ::access(path, F_OK) == 0;
}

#endif
