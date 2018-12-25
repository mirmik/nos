#ifndef NOS_ERROR_H
#define NOS_ERROR_H

#include <exception>
#include <string>

namespace nos
{
	class exception : std::exception 
	{
		std::string str;
	public:
		exception(const char* msg) : str(msg) {}
		const char* what() const noexcept override { return str.c_str(); }
	};

	void error(const char* msg);
}

#endif