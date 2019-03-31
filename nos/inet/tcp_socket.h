#ifndef nos_INET_TCP_SOCKET_H
#define nos_INET_TCP_SOCKET_H

#include <nos/io/iostream.h>
#include <nos/inet/socket.h>
#include <stdio.h>
#include <unistd.h>

namespace nos {
	namespace inet {
		struct tcp_socket : public nos::inet::socket, public nos::iostream {
			//do nothing
			tcp_socket() = default;

			//
			tcp_socket(const tcp_socket& oth) = default;
			tcp_socket(tcp_socket&& oth) = default;
			tcp_socket& operator=(const tcp_socket& oth) = default;
			tcp_socket& operator=(tcp_socket&& oth) = default;

			//create socket
			int init();

			int connect(nos::inet::hostaddr addr, uint16_t port);

			//create and connect
			tcp_socket(nos::inet::hostaddr addr, uint16_t port);
			
			//io api implementation
			ssize_t write(const void* data, size_t size) override;
			ssize_t read(char* data, size_t size) override;
		};
	}
}

#endif