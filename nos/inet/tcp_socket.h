#ifndef nos_INET_TCP_SOCKET_H
#define nos_INET_TCP_SOCKET_H

#include <nos/io/iostream.h>
#include <nos/inet/socket.h>
#include <nos/inet/hostaddr.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace nos
{
	namespace inet
	{
		struct tcp_socket : public nos::inet::socket
		{
			tcp_socket() = default;

			//Копируется номер файлового дескриптора.
			tcp_socket(const tcp_socket& oth) = default;
			tcp_socket& operator=(const tcp_socket& oth) = default;

			//Перемещается номер файлового дескриптора.
			tcp_socket(tcp_socket&& oth) = default;
			tcp_socket& operator=(tcp_socket&& oth) = default;

			tcp_socket(nos::inet::hostaddr addr, uint16_t port);

			//create and connect
			int init();
			int connect(nos::inet::hostaddr addr, uint16_t port);

			//io api implementation
			int write(const void* data, size_t size) override;
			int read(void* data, size_t size) override;

			netaddr getaddr();
		};
	}
}

#endif
