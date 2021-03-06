#include <nos/inet/tcp_server.h>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <fcntl.h>

nos::inet::tcp_server::tcp_server(const nos::inet::hostaddr& addr, uint16_t port, int conn)
{
	this->init();
	this->bind(addr, port);
	this->listen(conn);
}

int nos::inet::tcp_server::init()
{
	return socket::init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

int nos::inet::tcp_server::bind(const nos::hostaddr& addr, uint16_t port)
{
	return socket::bind(addr, port, PF_INET);
}

int nos::inet::tcp_server::listen(int conn)
{
	return inet::socket::listen(conn);
}

int nos::inet::tcp_server::listen()
{
	return inet::socket::listen(10);
}

nos::inet::tcp_socket nos::inet::tcp_server::accept()
{
	int c = sizeof(sockaddr_in);
	sockaddr_in caddr;
	memset(&caddr, 0, sizeof(caddr));
	int cfd = ::accept( fd, (sockaddr*)&caddr, (socklen_t*)&c );

	nos::inet::tcp_socket sock;
	sock.fd = cfd;
	return sock;
}
