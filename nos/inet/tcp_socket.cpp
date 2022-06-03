#include <nos/inet/tcp_socket.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef __WIN32__
#   include <winsock2.h>
#   include <ws2tcpip.h>
#else
#   include <netinet/in.h>
#   include <netinet/tcp.h>
#   include <arpa/inet.h>
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

int nos::inet::tcp_socket::write(const void *data, size_t size)
{
    return socket::send(data, size, 0);
}

int nos::inet::tcp_socket::read(void *data, size_t size)
{
    return socket::recv((char *)data, size, 0);
}

int nos::inet::socket::send(const void *data, size_t size, int flags)
{
    return ::send(fd, (const char *)data, size, flags);
}

int nos::inet::socket::recv(char *data, size_t size, int flags)
{
    return ::recv(fd, data, size, flags);
}

nos::inet::netaddr nos::inet::tcp_socket::getaddr()
{
    struct sockaddr_in sin;
    socklen_t socklen = sizeof(sin);
    memset(&sin, 0, sizeof(sin));

    getpeername(fd, (struct sockaddr *)&sin, &socklen); // read binding

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

int nos::inet::tcp_client::write(const void *data, size_t size)
{
    int sts = tcp_socket::write(data, size);
    if (sts < 0)
    {
        throw nos::inet::tcp_write_error();
    }
    return sts;
}

int nos::inet::tcp_client::read(void *data, size_t size)
{
    int sts = tcp_socket::read(data, size);
    if (sts < 0)
    {
        throw nos::inet::tcp_read_error();
    }
    return sts;
}

int nos::inet::tcp_client::connect(nos::inet::hostaddr addr, uint16_t port)
{
    init();

    int sts = socket::connect(addr, port, PF_INET);
    if (sts < 0)
    {
        throw nos::inet::tcp_connect_error();
    }
    return sts;
}
