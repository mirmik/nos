#include <nos/io/std.h>
#include <nos/util/init_priority.h>

namespace nos {
	nos::file_ostream NOS_PRIORITY_INITIALIZATION_SUPER cout(stdout);
	nos::file_ostream NOS_PRIORITY_INITIALIZATION_SUPER cerr(stderr);
	nos::file_istream NOS_PRIORITY_INITIALIZATION_SUPER cin(stdin);
}
