#include <nos/io/std.h>

namespace nos {
	nos::ostream * current_ostream = &nos::cout;
	nos::istream * current_istream = &nos::cin;
}