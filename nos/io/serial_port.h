#ifndef NOS_IO_SERIAL_PORT_H
#define NOS_IO_SERIAL_PORT_H

#include <nos/io/file.h>
#include <unistd.h>

#include <igris/defs/uart.h>

namespace nos
{
	class serial_port : public nos::file
	{
		unsigned int baud;
		uart_parity_e parity;
		uint8_t bytesize;
		uart_stopbits_e stopbits;
		uart_flowcontrol_e flowcontrol;


	public:
		serial_port() {}
		serial_port(const char * path,
		                 unsigned int baud = 9600,
		                 uart_parity_e parity = UART_PARITY_NONE,
		                 uint8_t bytesize = 8,
		                 uart_stopbits_e stopbits = UART_STOPBITS_ONE,
		                 uart_flowcontrol_e flowcontrol = UART_FLOWCONTROL_NONE)
			: file(), baud(baud), parity(parity), bytesize(bytesize), stopbits(stopbits), flowcontrol(flowcontrol)
		{
			open(path, baud, parity, bytesize, stopbits, flowcontrol);
		}

		serial_port(const char * path,
		                 unsigned int baud = 9600,
		                 char parity = UART_PARITY_NONE,
		                 uint8_t bytesize = 8,
		                 uint8_t stopbits = UART_STOPBITS_ONE,
		                 char flowcontrol = UART_FLOWCONTROL_NONE)
			: baud(baud),
			  parity((uart_parity_e)parity),
			  bytesize(bytesize),
			  stopbits((uart_stopbits_e)stopbits),
			  flowcontrol((uart_flowcontrol_e)flowcontrol)
		{
			open(path, baud,
			     (uart_parity_e) parity,
			     bytesize,
			     (uart_stopbits_e) stopbits,
			     (uart_flowcontrol_e) flowcontrol);
		}

		int open(const char * path,
		         unsigned int baud = 9600,
		         uart_parity_e parity = UART_PARITY_NONE,
		         uint8_t bytesize = 8,
		         uart_stopbits_e stopbits = UART_STOPBITS_ONE,
		         uart_flowcontrol_e flowcontrol = UART_FLOWCONTROL_NONE);

		int open(const char * path,
		         unsigned int baud = 9600,
		         char parity = UART_PARITY_NONE,
		         uint8_t bytesize = 8,
		         uint8_t stopbits = UART_STOPBITS_ONE,
		         char flowcontrol = UART_FLOWCONTROL_NONE);

		void reconfigurePort();

		/*int32_t readData(char *data, size_t maxSize) override
		{
		    return ::read(fd, data, maxSize);
		}

		int32_t writeData(const char *data, size_t maxSize) override
		{
		    return ::write(fd, data, maxSize);
		}*/
	};

}

#endif
