#ifndef NOS_IO_SERIAL_PORT_H
#define NOS_IO_SERIAL_PORT_H

#include <nos/io/file.h>
#include <unistd.h>

#define UART_PARITY_NONE 'n'
#define UART_PARITY_EVEN 'e'
#define UART_PARITY_ODD  'o'

#define UART_STOPBITS_ONE 1
#define UART_STOPBITS_TWO 2

namespace nos
{
	class serial_port : public nos::file
	{
		unsigned int baud;
		char parity;
		uint8_t bytesize;
		uint8_t stopbits;

	public:
		serial_port() {}

		serial_port(const char * path,
		            unsigned int baud = 9600,
		            char parity = UART_PARITY_NONE,
		            uint8_t bytesize = 8,
		            uint8_t stopbits = UART_STOPBITS_ONE)
			: baud(baud),
			  parity((char)parity),
			  bytesize(bytesize),
			  stopbits((uint8_t)stopbits)
		{
			open(path,
			     baud,
			     parity,
			     bytesize,
			     (uint8_t) stopbits);
		}

		int open(const char * path,
		         unsigned int baud = 9600,
		         char parity = UART_PARITY_NONE,
		         uint8_t bytesize = 8,
		         uint8_t stopbits = UART_STOPBITS_ONE);

		void reconfigurePort();
	};
}

#endif
