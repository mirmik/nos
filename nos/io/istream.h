#ifndef NOS_IO_ISTREAM_H
#define NOS_IO_ISTREAM_H

namespace nos
{
	class istream
	{
	public:

		std::string readline()
		{
			std::string ret;
			char c;

			while (1)
			{
				read(&c, 1);
				switch (c)
				{
					case '\r': break;
					case '\n': return ret;
					default: ret += c;
				}
			}
		}

		virtual ssize_t read(char* ptr, size_t sz) = 0;
	};
}

#endif