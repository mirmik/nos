#ifndef NOS_INPUT_H
#define NOS_INPUT_H

namespace nos 
{
	class istream;
	extern istream* current_istream;

	std::string readline();	
}

#include <nos/io/istream.h>

namespace nos
{
	std::string readline() 
	{
		return current_istream->readline();
	}
}

#endif