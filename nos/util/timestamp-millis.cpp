#include <nos/timestamp.h>
#include <systime/systime.h>
#include <igris/util/numconvert.h>

void nos::timestamp(char * buffer, size_t maxsz) 
{
	i64toa(millis(), buffer, 10);
}
