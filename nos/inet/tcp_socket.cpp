#include <fcntl.h>
#include <nos/inet/tcp_socket.h>
#include <unistd.h>

#ifdef __WIN32__
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#endif

nos::inet::tcp_socket::tcp_socket(nos::inet::hostaddr addr, uint16_t port)
    : tcp_socket()
{
    inet::socket::init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(addr, port);
}

int nos::inet::tcp_socket::init()
{
    return inet::socket::init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

int nos::inet::tcp_socket::connect(nos::inet::hostaddr addr, uint16_t port)
{
    return socket::connect(addr, port, PF_INET);
}

int nos::inet::socket::send(const void *data, size_t size, int flags)
{
    return ::send(fd(), (const char *)data, size, flags);
}

int nos::inet::socket::recv(char *data, size_t size, int flags)
{
    return ::recv(fd(), data, size, flags);
}

nos::inet::netaddr nos::inet::tcp_socket::getaddr()
{
    struct sockaddr_in sin;
    socklen_t socklen = sizeof(sin);
    memset(&sin, 0, sizeof(sin));

    getpeername(fd(), (struct sockaddr *)&sin, &socklen); // read binding

    return nos::inet::netaddr{sin.sin_addr.s_addr, sin.sin_port};
}

int nos::inet::socket::clean()
{
#ifndef __WIN32__
    char buf[16];
    int ret;
    do
    {
        ret = recv(buf, 16, MSG_DONTWAIT);
    } while (ret > 0);
#endif
    return 0;
}
