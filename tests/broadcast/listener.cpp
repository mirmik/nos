#include <chrono>
#include <nos/inet/udp_socket.h>
#include <thread>

int main()
{
    nos::inet::udp_broadcast_socket sock(9001);

    while (true)
    {
        auto [data, addr, port] = sock.recvfrom();
        nos::println(addr, port, data);
    }
}