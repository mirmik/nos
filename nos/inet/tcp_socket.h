#ifndef NOS_INET_TCP_SOCKET_H
#define NOS_INET_TCP_SOCKET_H

#include <nos/io/iostream.h>
#include <nos/inet/socket.h>
#include <nos/inet/hostaddr.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <exception>

namespace nos
{
	namespace inet
	{
		class tcp_stream_error : public std::exception
		{
		public:
			const char * what() const noexcept override
			{
				return "tcp_stream_error";
			}
		};

		class tcp_write_error : public tcp_stream_error 
		{
			const char * what() const noexcept override
			{
				return "tcp_write_error";
			}
		};

		class tcp_read_error : public tcp_stream_error 
		{
			const char * what() const noexcept override
			{
				return "tcp_read_error";
			}
		};

		class tcp_connect_error : public tcp_stream_error 
		{
			const char * what() const noexcept override
			{
				return "tcp_connect_error";
			}
		};

		class tcp_disconnect_error : public tcp_stream_error 
		{
			const char * what() const noexcept override
			{
				return "tcp_disconnect_error";
			}
		};

		class tcp_socket : public nos::inet::socket
		{
		public:
			tcp_socket() = default;
			tcp_socket(int fd) : nos::inet::socket(fd) {}

			//Копируется номер файлового дескриптора.
			tcp_socket(const tcp_socket& oth) = default;
			tcp_socket& operator=(const tcp_socket& oth) = default;

			//Перемещается номер файлового дескриптора.
			tcp_socket(tcp_socket&& oth) = default;
			tcp_socket& operator=(tcp_socket&& oth) = default;

			tcp_socket(nos::inet::hostaddr addr, uint16_t port);
			tcp_socket(nos::inet::netaddr naddr) : tcp_socket(naddr.addr, naddr.port) {}

			//create and connect
			int init();
			int connect(nos::inet::hostaddr addr, uint16_t port);

			//io api implementation
			int write(const void* data, size_t size) override;
			int read(void* data, size_t size) override;

			netaddr getaddr();

			using nos::inet::socket::operator==;
			using nos::inet::socket::operator!=;
			using nos::inet::socket::operator>;
			using nos::inet::socket::operator<;
		};

		class tcp_client : public tcp_socket
		{
			bool _is_connect = false;
		public:
			tcp_client() 
			{}

			bool is_connected() { return _is_connect; }
			
			tcp_client(int fd) : tcp_socket(fd) {}
			tcp_client(const tcp_client& oth) = default;
			tcp_client& operator=(const tcp_client& oth) = default;

			int write(const void* data, size_t size) override; 
			int read(void* data, size_t size) override;
			int connect(nos::inet::hostaddr addr, uint16_t port);
			int disconnect();
			using istream::read;
		};
	}
}

namespace std
{
	template<> 
	struct hash<nos::inet::tcp_socket>
	{
		typedef nos::inet::tcp_socket argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& s) const
		{
			return std::hash<int>()(s.fd);
		}
	};
}

#endif