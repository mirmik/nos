#ifndef nos_STRING_H
#define nos_STRING_H

#include <cstdint>
#include <list>
#include <vector>
#include <string>

#include <nos/util/buffer.h>
//#include <nos/util/asciiconvert.h>

namespace nos {
	using strvec = std::vector<std::string>;
	using strlst = std::list<std::string>;

	strvec split(const std::string& str, char delim);
	std::string join(const strvec&, char delim);

	static inline std::string serialstr8(const std::string& str) {
		std::string ret;
		ret.push_back((uint8_t)str.size());
		ret.append(str);
		return ret;
	}

	static inline std::string serialstr8(const char* data, size_t size) {
		std::string ret;
		ret.push_back((uint8_t) size);
		ret.append(data, size);
		return ret;
	}

	std::string dstring(const void* data, size_t size);
	std::string dstring(nos::buffer buf);
	std::string dstring(const std::string& str);
}

#endif