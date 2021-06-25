#include <nos/timestamp.h>

void nos::timestamp(char * buffer, size_t maxsz) 
{
	i64toa(millis(), buffer, 10);
}
