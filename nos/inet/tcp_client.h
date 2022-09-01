#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <chrono>
#include <nos/inet/tcp_socket.h>
#include <string_view>

namespace nos
{
    namespace inet
    {
        class tcp_client : public tcp_socket
        {
            bool _is_connect = false;

        public:
            tcp_client() {}
            tcp_client(int fd) : tcp_socket(fd) {}
            tcp_client(const tcp_client &oth) = default;
            tcp_client &operator=(const tcp_client &oth) = default;

            [[deprecated("use connected() instead")]] bool is_connected()
            {
                return _is_connect;
            }

            bool connected()
            {
                return _is_connect;
            }

            int write(const void *data, size_t size) override;
            int read(void *data, size_t size) override;

            int connect(nos::inet::hostaddr addr,
                        uint16_t port,
                        std::chrono::milliseconds timeout);
            int connect(nos::inet::hostaddr addr, uint16_t port);
            int disconnect();
            using istream::read;

            int send(const void *data, size_t size)
            {
                return write(data, size);
            }
            int recv(void *data, size_t size)
            {
                return read(data, size);
            }

            int send(const std::string_view &data)
            {
                return send(data.data(), data.size());
            }

            static tcp_client dial(nos::inet::hostaddr addr,
                                   uint16_t port,
                                   std::chrono::milliseconds timeout);
        };
    }
}

#endif // TCP_CLIENT_H