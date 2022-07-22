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

nos::inet::udp_broadcast_socket::udp_broadcast_socket()
{
    init();
}

nos::inet::udp_broadcast_socket::udp_broadcast_socket(uint16_t port)
{
    init();
    bind(port);
}

void nos::inet::udp_broadcast_socket::init()
{
    fd = socket::init(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        throw std::runtime_error("socket failed");
    }

    /*bool broadcast = true;
    if (setsockopt(fd,
                   SOL_SOCKET,
                   SO_BROADCAST,
                   (char *)&broadcast,
                   sizeof(broadcast)) < 0)
    {
        throw std::runtime_error("setsockopt failed");
    }*/
}

void nos::inet::udp_broadcast_socket::bind(uint16_t port)
{
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;
    ::bind(fd, (struct sockaddr *)&saddr, sizeof(saddr));
}

nos::inet::udp_broadcast_socket::~udp_broadcast_socket()
{
    close();
}

int nos::inet::udp_broadcast_socket::sendto(const void *data,
                                             size_t size,
                                             std::string ip,
                                             uint16_t port)
{
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = inet_addr(ip.c_str());
    int ret = ::sendto(fd,
                       (const char *)data,
                       size,
                       0,
                       (struct sockaddr *)&saddr,
                       sizeof(saddr));
    if (ret < 0)
    {
        perror("sendto");
        throw std::runtime_error("sendto failed");
    }
    return ret;
}

void nos::inet::udp_broadcast_socket::allow_broadcast()
{
    int broadcast = 1;
    if (setsockopt(fd,
                   SOL_SOCKET,
                   SO_BROADCAST,
                   (char *)&broadcast,
                   sizeof(broadcast)) < 0)
    {
        throw std::runtime_error("setsockopt failed");
    }
}

int nos::inet::udp_broadcast_socket::send_broadcast(const void *data,
                                                     size_t size,
                                                     uint16_t port)
{
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_BROADCAST;
    int ret = ::sendto(fd,
                       (const char *)data,
                       size,
                       0,
                       (struct sockaddr *)&saddr,
                       sizeof(saddr));
    if (ret < 0)
    {
        perror("sendto");
        throw std::runtime_error("sendto failed");
    }
    return ret;
}

std::tuple<std::string, std::string, uint16_t>
nos::inet::udp_broadcast_socket::recvfrom(size_t maxsize)
{
    struct sockaddr_in saddr;
    socklen_t saddr_len = sizeof(saddr);
    std::string data;
    data.resize(maxsize);
    int ret = ::recvfrom(
        fd, &data[0], maxsize, 0, (struct sockaddr *)&saddr, &saddr_len);
    if (ret < 0)
    {
        if (errno == EAGAIN || errno == 0)
        {
            return std::make_tuple("", "", 0);
        }

        throw std::runtime_error("recvfrom failed");
    }

    data.resize(ret);
    std::string addr = inet_ntoa(saddr.sin_addr);
    uint16_t rport = ntohs(saddr.sin_port);
    return std::make_tuple(data, addr, rport);
}