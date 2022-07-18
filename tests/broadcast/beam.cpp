#include <chrono>
#include <nos/inet/udp_socket.h>
#include <thread>

int main()
{
    nos::inet::udp_broadcast_socket sock(9000);
    sock.allow_broadcast();

    while (true)
    {
        sock.send_broadcast("hello\n", 6, 9001);
        nos::println("sended");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}