#ifndef NOS_SOCKET_H
#define NOS_SOCKET_H

#include <nos/io/iostream.h>

namespace nos
{
	class socket : nos::iostream
	{
	private:
		int fd;

	public:
		socket(int domain, int type, int proto);

		ssize_t send(const char* data, size_t size, int flags);
		ssize_t recv(char* data, size_t size, int flags);

		ssize_t write(const void* data, size_t size) override;
		ssize_t read(void* data, size_t size) override;

		int create(int domain, int type, int proto); //posix ::socket
		int bind(const hostaddr& haddr, uint16_t port, int family);
		int connect(const hostaddr& haddr, uint16_t port, int family);
		int listen(int conn);

		int nodelay(bool en);
		int nonblock(bool en);
		int reusing(bool en);
	}
}

#endif