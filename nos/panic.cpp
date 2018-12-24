#include <nos/panic.h>
#include <nos/print.h>
#include <stdlib.h>

void nos::panic(const char* str) {
	nos::println(str);
	nos::current_ostream->flush();
	abort();
}

void nos::location_panic(struct location loc, const char* str) {
	nos::print("file: "); nos::print(loc.file); nos::println();
	nos::print("func: "); nos::print(loc.func); nos::println();
	nos::print("line: "); nos::print(loc.line); nos::println();
	nos::panic(str);
}