#include <nos/inet/tcp_socket.h>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <fcntl.h>

#define NOTRACE 1
#include <nos/trace.h>

nos::inet::tcp_socket::tcp_socket(nos::inet::hostaddr addr, uint16_t port) : tcp_socket()
{
	TRACE();
	inet::socket::init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(addr, port);
}

int nos::inet::tcp_socket::init()
{
	TRACE();
	return inet::socket::init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

int nos::inet::tcp_socket::connect(nos::inet::hostaddr addr, uint16_t port)
{
	TRACE();
	return socket::connect(addr, port, PF_INET);
}

ssize_t nos::inet::tcp_socket::write(const void* data, size_t size)
{
	TRACE();
	return socket::send(data, size, 0);
}

ssize_t nos::inet::tcp_socket::read(void* data, size_t size)
{
	TRACE();
	return socket::recv((char*)data, size, 0);
}

ssize_t nos::inet::socket::send(const void* data, size_t size, int flags)
{
	TRACE();
	return ::send(fd, data, size, flags);
}

ssize_t nos::inet::socket::recv(char* data, size_t size, int flags)
{
	TRACE();
	return ::recv(fd, data, size, flags);
}
