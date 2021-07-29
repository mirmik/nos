#include <nos/io/istream.h>
#include <nos/input.h>

std::string nos::istream::readline() 
{
	return nos::readline(*this);
}