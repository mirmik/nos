#ifndef NOS_IO_DEBUG_OSTREAM_H
#define NOS_IO_DEBUG_OSTREAM_H

#include <nos/io/ostream.h>
#include <igris/dprint.h>

namespace nos 
{
	class debug_ostream : public nos::ostream 
	{
		int write(const void* ptr, size_t sz) 
		{
			debug_write((const char*)ptr, sz);
			return sz;
		}
	};
}

#endif
