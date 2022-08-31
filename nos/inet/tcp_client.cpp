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

int nos::inet::tcp_client::read(void *data, size_t size)
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

    int sts = socket::connect(addr, port, PF_INET);
    if (sts < 0)
    {
        _is_connect = false;
        throw nos::inet::tcp_connect_error();
    }
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

nos::inet::tcp_client nos::inet::tcp_client::dial(nos::inet::hostaddr addr,
                                                  uint16_t port)
{
    tcp_client client;
    client.connect(addr, port);
    return client;
}