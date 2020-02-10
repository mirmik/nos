#include <nos/io/serial_port.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <igris/util/bug.h>

int nos::serial_port_file::open(const char * path,
                                unsigned int baud,
                                uart_parity_e parity,
                                uint8_t bytesize,
                                uart_stopbits_e stopbits,
                                uart_flowcontrol_e flowcontrol)
{
	int ret;

	int fd = ::open(path, O_RDWR | O_NOCTTY);
	if (fd < 0)
	{
		perror("serial::open");
		exit(0);
	}

	fdopen(fd);
	setvbuf( filp, (char *)NULL, _IONBF, 0 );

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
			BUG();
	}

	/*switch (parity)
	{
		case serial::parity_none:
			tattr.c_cflag &= ~(PARENB);
			tattr.c_cflag &= ~(PARODD);
			break;

		case serial::parity_odd:
			tattr.c_cflag |= (PARENB);
			tattr.c_cflag |= (PARODD);
			break;

		case serial::parity_even:
			tattr.c_cflag |= (PARENB);
			tattr.c_cflag &= ~(PARODD);
			break;

		case serial::parity_mark:
			PANIC_TRACED();

		case serial::parity_space:
			PANIC_TRACED();
	}*/

	if (baud == 115200)
	{
		cfsetispeed(&tattr, B115200);
		cfsetospeed(&tattr, B115200);
	}
	else
	{
		BUG();
	}

	/* put terminal in raw mode after flushing */
	ret = tcsetattr(fd, TCSAFLUSH, &tattr);

	if (ret < 0)
	{
		perror("serial::tcsetattr");
		exit(0);
	}

	return 0;
}