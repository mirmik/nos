#ifndef NOS_CONVERT_COLOR
#define NOS_CONVERT_COLOR

#include <string>

namespace nos
{
	static inline std::string bright_black		(const std::string str) { return nos::format("\x1B[30;1m{}\x1B[0m", str); }	
	static inline std::string bright_red		(const std::string str)	{ return nos::format("\x1B[31;1m{}\x1B[0m", str); }	
	static inline std::string bright_green		(const std::string str)	{ return nos::format("\x1B[32;1m{}\x1B[0m", str); }	
	static inline std::string bright_yellow		(const std::string str)	{ return nos::format("\x1B[33;1m{}\x1B[0m", str); }	
	static inline std::string bright_blue		(const std::string str)	{ return nos::format("\x1B[34;1m{}\x1B[0m", str); }	
	static inline std::string bright_magenta	(const std::string str)	{ return nos::format("\x1B[35;1m{}\x1B[0m", str); }	
	static inline std::string bright_cyan		(const std::string str)	{ return nos::format("\x1B[36;1m{}\x1B[0m", str); }	
	static inline std::string bright_white		(const std::string str)	{ return nos::format("\x1B[37;1m{}\x1B[0m", str); }	
	static inline std::string black 			(const std::string str)	{ return nos::format("\x1B[30m{}\x1B[0m", str);	}	
	static inline std::string red 				(const std::string str)	{ return nos::format("\x1B[31m{}\x1B[0m", str);	}	
	static inline std::string green 			(const std::string str)	{ return nos::format("\x1B[32m{}\x1B[0m", str);	}	
	static inline std::string yellow 			(const std::string str)	{ return nos::format("\x1B[33m{}\x1B[0m", str);	}	
	static inline std::string blue 				(const std::string str)	{ return nos::format("\x1B[34m{}\x1B[0m", str);	}	
	static inline std::string magenta 			(const std::string str)	{ return nos::format("\x1B[35m{}\x1B[0m", str);	}	
	static inline std::string cyan 				(const std::string str)	{ return nos::format("\x1B[36m{}\x1B[0m", str);	}	
	static inline std::string white 			(const std::string str)	{ return nos::format("\x1B[37m{}\x1B[0m", str);	}
}

#define COLOR_BLACK(str) 	"\x1B[30m" str "\x1B[0m"
#define COLOR_RED(str) 		"\x1B[31m" str "\x1B[0m"
#define COLOR_GREEN(str) 	"\x1B[32m" str "\x1B[0m"
#define COLOR_YELLOW(str) 	"\x1B[33m" str "\x1B[0m"
#define COLOR_BLUE(str) 	"\x1B[34m" str "\x1B[0m"
#define COLOR_MAGENTA(str) 	"\x1B[35m" str "\x1B[0m"
#define COLOR_CYAN(str) 	"\x1B[36m" str "\x1B[0m"
#define COLOR_WHITE(str) 	"\x1B[37m" str "\x1B[0m"

#endif