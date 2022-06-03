#include <nos/input.h>
#include <nos/io/file.h>

int nos::read_with_timeout_ms(
    nos::istream& is,
    char* buf, size_t buflen,
    int timeout_ms)
{
	(void) is;
	(void) buf;
	(void) buflen;
	(void) timeout_ms;
	return 0;
}

/*
int nos::fdlike::read_with_timeout_ms(void* ptr, size_t sz, int ms)
{
	fd_set set;
	struct timeval timeout;

	int rv;
	FD_ZERO(&set);
	FD_SET(m_fd, &set);

	timeout.tv_sec = ms / 1000;
	timeout.tv_usec = (ms % 1000) * 1000;

	rv = select(m_fd + 1, &set, NULL, NULL, &timeout);
	if (rv == -1)
		return -1;
		//perror("select");
	else if (rv == 0)
		return -2;
		//printf("timeout");
	else
		return read( ptr, sz );
}
*/
