#ifndef NOS_IO_SOCKET2_H
#define NOS_IO_SOCKET2_H

#include <nos/inet/hostaddr.h>
#include <nos/io/file.h>
#include <string.h>

namespace nos
{
	namespace inet
	{
		class socket : public nos::file
		{
		public:
			int fd=-1;

		public:
			bool good()
			{
				return fd >= 0;
			}

			socket() = default;
			socket(int _fd) : fd(_fd) {}
			socket(const socket& oth) = default;
			socket(socket&& oth) = default;
			socket& operator=(const socket& oth) = default;
			socket& operator=(socket&& oth) = default;

			int send(const void* data, size_t size, int flags);
			int recv(char* data, size_t size, int flags);

			int init(int domain, int type, int proto); //posix ::socket
			int bind(const hostaddr& haddr, uint16_t port, int family);
			int connect(const hostaddr& haddr, uint16_t port, int family);
			int clean();
			int listen(int conn);

			int nodelay(bool en);
			int nonblock(bool en);
			int reusing(bool en);

			int close();

			bool operator == (const nos::inet::socket & oth) const { return fd == oth.fd; }
			bool operator != (const nos::inet::socket & oth) const { return fd != oth.fd; }
			bool operator > (const nos::inet::socket & oth) const { return fd > oth.fd; }
			bool operator < (const nos::inet::socket & oth) const { return fd < oth.fd; }

			virtual ~socket() = default;
		};
	}
}

namespace std
{
	template<> 
	struct hash<nos::inet::socket>
	{
		typedef nos::inet::socket argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& s) const
		{
			return std::hash<int>()(s.fd);
		}
	};
}

#endif
