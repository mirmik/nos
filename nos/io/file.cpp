#include <nos/io/file.h>
#ifdef __WIN32__
#include <winsock2.h>
#define pipe(ptr) _pipe(ptr, 1024, 0)
using suseconds_t = int32_t;
using socklen_t = int32_t;
#else
#include <sys/select.h>
#endif

std::pair<int, bool>
nos::file::timeouted_read(void *ptr, size_t sz, std::chrono::nanoseconds ms)
{
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd(), &fds);

    struct timeval tv;
    tv.tv_sec = ms.count() / 1000000000;
    tv.tv_usec = (ms.count() % 1000000000) / 1000;

    int ret = select(fd() + 1, &fds, NULL, NULL, &tv);

    if (ret < 0)
    {
        return {ret, false};
    }

    if (ret == 0)
    {
        return {0, true};
    }

    return {read(ptr, sz), false};
}