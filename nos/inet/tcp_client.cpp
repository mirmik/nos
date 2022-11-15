#include <fcntl.h>
#include <nos/inet/tcp_client.h>
#include <unistd.h>

#ifdef __WIN32__
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif

int nos::inet::tcp_client::write(const void *data, size_t size)
{
    int sts = tcp_socket::write(data, size);
    if (sts < 0)
    {
        _is_connect = false;
        throw nos::inet::tcp_write_error();
    }
    return sts;
}

nos::expected<int, nos::input_error> nos::inet::tcp_client::read(void *data,
                                                                 size_t size)
{
    int sts = tcp_socket::read(data, size);
    if (sts < 0)
    {
        _is_connect = false;
        throw nos::inet::tcp_read_error();
    }
    return sts;
}

int nos::inet::tcp_client::connect(nos::inet::hostaddr addr, uint16_t port)
{
    init();
    reusing(true);
    int sts = tcp_socket::connect(addr, port);
    reusing(true);
    if (sts < 0)
    {
        _is_connect = false;
        throw nos::inet::tcp_connect_error();
    }
    _is_connect = true;
    return sts;
}

int nos::inet::tcp_client::connect(nos::inet::hostaddr addr,
                                   uint16_t port,
                                   std::chrono::milliseconds timeout)
{
    init();
    nonblock(true);
    reusing(true);
    int sts = tcp_socket::connect(addr, port);
    reusing(true);

    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(fd(), &writefds);

    struct timeval tv;
    tv.tv_sec = timeout.count() / 1000;
    tv.tv_usec = (timeout.count() % 1000) * 1000;

    sts = select(fd() + 1, NULL, &writefds, NULL, &tv);
    if (sts < 0)
    {
        throw nos::inet::tcp_connect_error();
    }
    else if (sts == 0)
    {
        throw nos::inet::tcp_timeout_error();
    }
    else
    {
        int so_error;
        socklen_t len = sizeof(so_error);

        getsockopt(fd(), SOL_SOCKET, SO_ERROR, (char *)&so_error, &len);

        if (so_error != 0)
        {
            throw nos::inet::tcp_connect_error();
        }
    }
    nonblock(false);
    _is_connect = true;
    return sts;
}

int nos::inet::tcp_client::disconnect()
{
    int sts = socket::close();
    _is_connect = false;
    if (sts < 0)
    {
        throw nos::inet::tcp_disconnect_error();
    }
    return sts;
}

nos::inet::tcp_client nos::inet::tcp_client::dial(
    nos::inet::hostaddr addr, uint16_t port, std::chrono::milliseconds timeout)
{
    tcp_client client;
    client.connect(addr, port, timeout);
    return client;
}