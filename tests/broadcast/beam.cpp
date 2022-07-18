#include <chrono>
#include <nos/inet/udp_socket.h>
#include <thread>

int main()
{
    nos::inet::udp_broadcast_socket sock(9000);

    while (true)
    {
        sock.sendto("hello", 5, "127.0.0.1", 9001);
        nos::println("sended");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        //        auto [data, addr, port] = sock2.recvfrom();
        //      nos::println(data);
    }
}