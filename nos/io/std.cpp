#include <nos/io/std.h>
#include <nos/util/init_priority.h>

namespace nos {
	nos::fstream NOS_PRIORITY_INITIALIZATION_SUPER cout(stdout);
	nos::fstream NOS_PRIORITY_INITIALIZATION_SUPER cerr(stderr);
	nos::fstream NOS_PRIORITY_INITIALIZATION_SUPER cin(stdin);
}
