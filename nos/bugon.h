#ifndef NOS_BUGON_H
#define NOS_BUGON_H

#include <nos/util/location.h>

#ifdef __cplusplus
#include <cstring>
#include <cstdio>
#endif

__BEGIN_DECLS

void bugon_impl(const char* str);

__END_DECLS

#define BUGON()					\
{								\
	CURRENT_LOCATION(loc);		\
	debug_print_location(loc);	\
	bugon_impl("BUGON");		\
}

#define BUGON_(msg)					\
{								\
	CURRENT_LOCATION(loc);		\
	debug_print_location(loc);	\
	bugon_impl(msg);			\
}

#endif
