#include <nos/util/osutil.h>
#include <fcntl.h>
#include <stdio.h>
#include <winsock2.h>

int nos::osutil::nonblock(int fd, bool en)
{
    unsigned long mode = en;
    return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
}
