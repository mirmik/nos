#include <nos/io/serial_port.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int nos::serial_port::open(const char * path,
                                unsigned int baud,
                                char parity,
                                uint8_t bytesize,
                                uint8_t stopbits)
{
	int ret;

	int fd = nos::file::open(path, O_RDWR | O_NOCTTY);
	if (fd < 0)
	{
		perror("serial::open");
		exit(0);
	}

	struct termios tattr, orig;
	ret = tcgetattr(fd, &orig);
	if (ret < 0)
	{
		perror("serial::tcgetattr");
		exit(0);
	}

	tattr = orig;  /* copy original and then modify below */

	/* input modes - clear indicated ones giving: no break, no CR to NL,
	   no parity check, no strip char, no start/stop output (sic) control */
	tattr.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	/* output modes - clear giving: no post processing such as NL to CR+NL */
	tattr.c_oflag &= ~(OPOST);

	/* control modes - set 8 bit chars */
	tattr.c_cflag |= (CS8);

	/* local modes - clear giving: echoing off, canonical off (no erase with
	   backspace, ^U,...),  no extended functions, no signal chars (^Z,^C) */
	tattr.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

	/* control chars - set return condition: min number of bytes and timer */
	tattr.c_cc[VMIN] = 1; tattr.c_cc[VTIME] = 0; /* immediate - anything       */

	switch (parity)
	{
		case UART_PARITY_NONE:
			tattr.c_cflag &= ~(PARENB);
			tattr.c_cflag &= ~(PARODD);
			break;

		case UART_PARITY_EVEN:
			tattr.c_cflag |= (PARENB);
			tattr.c_cflag &= ~(PARODD);
			break;

		case UART_PARITY_ODD:
			tattr.c_cflag |= (PARENB);
			tattr.c_cflag |= (PARODD);
			break;

		default:
			return -1;
	}

	if (baud == 115200)
	{
		cfsetispeed(&tattr, B115200);
		cfsetospeed(&tattr, B115200);
	}
	else
	{
		return -1;
	}

	/* put terminal in raw mode after flushing */
	ret = tcsetattr(fd, TCSAFLUSH, &tattr);

	if (ret < 0)
	{
		return -1;
	}

	return 0;
}
