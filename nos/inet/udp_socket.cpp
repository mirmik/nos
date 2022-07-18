#include <nos/inet/udp_socket.h>
#ifdef __WIN32__
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif

/*udp_socket::udp_socket()
{
    _fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_fd < 0)
    {
        throw std::runtime_error("socket failed");
    }
}

~udp_socket::udp_socket()
{
    ::close(_fd);
}

int udp_socket::sendto(const char *addr,
                       int port,
                       const void *data,
                       size_t size)
{
    struct sockaddr_in saddr;
    int retcode =
        ::sendto(_fd, data, size, 0, (struct sockaddr *)&saddr, sizeof(saddr));
    if (retcode < 0)
    {
        throw std::runtime_error("sendto failed");
    }
    return retcode;
}

int udp_socket::sendto(const std::string &addr,
                       int port,
                       const void *data,
                       size_t size)
{
    return sendto(addr.c_str(), port, data, size);
}

int udp_socket::broadcast_send(uint16_t port, const void *data, size_t size)
{
    return sendto("0.0.0.0", port, data, size);
}

int udp_socket::recvfrom(const char *&addr, int &port, void *data, size_t size)
{
}

int udp_socket::recvfrom(const std::string &addr,
                         int &port,
                         void *data,
                         size_t size)
{
    return recvfrom(addr.c_str(), port, data, size);
}

int udp_socket::recvfrom(int &port, void *data, size_t size)
{
    return recvfrom("0.0.0.0", port, data, size);
}*/

nos::inet::udp_broadcast_socket::udp_broadcast_socket(uint16_t port)
{
    fd = init(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        throw std::runtime_error("socket failed");
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_BROADCAST;

    int retcode = ::bind(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (retcode < 0)
    {
        throw std::runtime_error("bind failed");
    }
}

nos::inet::udp_broadcast_socket::~udp_broadcast_socket()
{
    close();
}

void nos::inet::udp_broadcast_socket::send(const void *data, size_t size)
{
    int retcode = ::sendto(fd, data, size, 0, NULL, 0);
    if (retcode < 0)
    {
        throw std::runtime_error("sendto failed");
    }
}

std::tuple<std::string, std::string, uint16_t>
nos::inet::udp_broadcast_socket::recv(size_t maxsize)
{
    std::string data;
    struct sockaddr_in saddr;
    socklen_t saddrlen = sizeof(saddr);
    data.resize(maxsize);
    int retcode = ::recvfrom(
        fd, &data[0], maxsize, 0, (struct sockaddr *)&saddr, &saddrlen);
    if (retcode < 0)
    {
        throw std::runtime_error("recvfrom failed");
    }

    data.resize(retcode);

    return std::make_tuple(
        data, inet_ntoa(saddr.sin_addr), ntohs(saddr.sin_port));
}