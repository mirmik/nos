#ifndef NOS_IO_ISTREAM_H
#define NOS_IO_ISTREAM_H

namespace nos 
{
	class istream 
	{
	protected:
		virtual ssize_t readData(char* ptr, size_t sz) = 0;	
	};
}

#endif