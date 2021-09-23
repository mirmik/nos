#include <nos/timestamp.h>
#include <igris/time.h>

void nos::timestamp(char * buffer, size_t maxsz) 
{
	i64toa(millis(), buffer, 10);
}
