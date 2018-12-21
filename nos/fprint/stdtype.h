#ifndef NOS_FPRINT_STDTYPE_H
#define NOS_FPRINT_STDTYPE_H

#include <nos/util/buffer.h>
#include <nos/io/ostream.h>

#include <nos/dtrace.h>

namespace nos 
{
	template <> struct fprint_implementation<const char*>
	{
		static ssize_t fprint_to(const char* obj, nos::ostream& out, nos::buffer opts)
		{
			(void) opts;
			return out.write(obj, strlen(obj));
		}
	};

	template <> struct fprint_implementation<int>
	{
		static ssize_t fprint_to(const int& obj, nos::ostream& out, nos::buffer opts)
		{	
			(void) opts;
			return out.print(obj);
		}
	};
}

#endif