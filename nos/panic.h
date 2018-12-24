#ifndef NOS_PANIC_H
#define NOS_PANIC_H

#include <nos/util/location.h>

namespace nos 
{
	void panic(const char* str);
	void location_panic(struct location loc, const char* str);
}

#define PANIC_LOCATION()					\
{											\
	CURRENT_LOCATION(loc);					\
	nos::location_panic(loc, "TRACED");		\
}

#define PANIC_LOCATION_MSG(msg)				\
{											\
	CURRENT_LOCATION(loc);					\
	nos::location_panic(loc, msg);			\
}

#define NOT_IMPLEMENTED() PANIC_LOCATION_MSG("not implemented")


#endif