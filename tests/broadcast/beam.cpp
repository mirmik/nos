#include <chrono>
#include <nos/inet/udp_socket.h>
#include <thread>

int main(int argc, char *argv[])
{

    std::vector<std::string> args(argv + 1, argv + argc);
    if (args.size() != 1)
    {
        std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    int sendport = std::stoi(args[0]);

    nos::inet::udp_broadcast_socket sock;
    sock.allow_broadcast();

    while (true)
    {
        sock.send_broadcast("hello\n", 6, sendport);
        nos::println("sended");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}