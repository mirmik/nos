#include <nos/error.h>
#include <exception>

void nos::error(const char * msg) 
{
	throw nos::exception(msg);
}