#include <nos/panic.h>
#include <nos/print.h>
#include <stdlib.h>

void nos::panic(const char* str) {
	nos::println(str);
	nos::current_ostream->flush();
	abort();
}