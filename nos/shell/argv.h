#ifndef NOS_SHELL_ARGV_H
#define NOS_SHELL_ARGV_H

#include <nos/util/buffer.h>
#include <string.h>
#include <vector>

namespace nos 
{
	class tokens 
	{
		std::string data;
		std::vector<nos::buffer> list;
		const char * delims = " \t\n";
		int offset = 0;

	public:
		tokens() = default;
		tokens(const tokens&) = default;
		tokens(tokens&&) = default;
		tokens& operator=(const tokens&) = default;
		tokens& operator=(tokens&&) = default;

		tokens(nos::buffer buffer) : 
			data(buffer.data(), buffer.size()) 
		{
			if (data.size())
				parse();
		}
		
		nos::buffer operator[](int i) 
		{
			return list[offset + i];
		}

		const nos::buffer operator[](int i) const 
		{
			return list[offset + i];
		}

		size_t size() const { 
			return list.size(); 
		}

		const nos::buffer * first() const 
		{ 
			return &list[0];
		}

		nos::buffer * first() 
		{ 
			return &list[0];
		}

	private:
		void parse() 
		{
			char * rest;
			char * token = strtok_r((char*)data.c_str(), delims, &rest);
 
		    while (token != NULL) {
		    	list.push_back(nos::buffer(token));
        		token = strtok_r(NULL, delims, &rest);
    		}
		}		
	};

	class argv 
	{
		const nos::buffer * list;
		size_t _size;

	public:
		argv() = default;
		argv(const argv&) = default;
		argv(argv&&) = default;
		argv& operator=(const argv&) = default;
		argv& operator=(argv&&) = default;

		argv(const tokens& args) : list(args.first()), _size(args.size()) {}
		argv(const nos::buffer * buf, size_t sz) : list(buf), _size(sz) {}

		argv without(size_t i) const 
		{
			return argv(list+i, _size-i);
		}

		const nos::buffer& operator[](size_t i) const
		{ 
			return list[i]; 
		}

		size_t size() const
		{ 
			return _size; 
		}

		const nos::buffer * begin() const
		{
			return list;
		}

		const nos::buffer * end() const 
		{
			return list + _size;
		}
	};
}

#endif