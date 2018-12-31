#include <nos/bugon.h>
#include <stdlib.h>

void bugon_impl(const char* str) {
	dprln(str);
	abort();
}