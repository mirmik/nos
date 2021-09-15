#include <nos/print/print.h>
#include <nos/io/ostream.h>

int nos::write_to(nos::ostream& out, const void* buf, size_t sz)
{
	return out.write(buf, sz);
}

int nos::putbyte_to(nos::ostream& out, char c)
{
	return out.write(&c, 1);
}

int nos::writeln_to(nos::ostream& out, const void* buf, size_t sz)
{
	int ret = 0;
	ret += out.write(buf, sz);
	ret += out.println();
	return ret;
}

int nos::println_to(nos::ostream& o)
{
	return o.write("\r\n", 2);
}

int nos::println()
{
	return nos::current_ostream->write("\r\n", 2);
}

int nos::print_dump_to(nos::ostream& out, const void *mem, size_t len, unsigned int columns)
{
	size_t ret = 0;
	unsigned int i, j;

	if (len == 0)
	{
		ret += out.write("0x", 2);
		ret += out.printptr((void*)((char*)mem));
		ret += out.putbyte(':');
		ret += out.println();
		return ret;
	}

	for (i = 0; i < len + ((len % columns) ? (columns - len % columns) : 0); i++)
	{
		// print offset
		if (i % columns == 0)
		{
			ret += out.write("0x", 2);
			ret += out.printptr((void*)((char*)mem + i));
			ret += out.putbyte(':');
		}

		// print hex data
		if (i < len)
		{
			ret += out.printhex(((char*)mem)[i]);
			ret += out.putbyte(' ');
		}
		else
		{
			// end of block, just aligning for ASCII dump
			ret += out.write("   ", 3);
		}

		// print ASCII dump
		if (i % columns == (columns - 1))
		{
			for (j = i - (columns - 1); j <= i; j++)
			{
				if (j >= len)
				{
					// end of block, not really printing
					ret += out.putbyte(' ');
				}
				else if (isprint(((char*)mem)[j]))
				{
					// printable char
					ret += out.putbyte((char)0xFF & ((char*)mem)[j]);
				}
				else
				{
					// other char
					ret += out.putbyte('.');
				}
			}

			ret += out.println();
		}
	}

	return ret;
}

int nos::print_dump(const void* ptr, size_t sz, unsigned int columns)
{
	return nos::print_dump_to(*nos::current_ostream, ptr, sz, columns);
}

#if __has_include(<string_view>)
int nos::print_dump(const std::string_view & buf, unsigned int columns)
{
	return nos::print_dump_to(*nos::current_ostream, buf.data(), buf.size(), columns);
}
#endif

int nos::write(const void* buf, size_t sz)
{
	return nos::write_to(*nos::current_ostream, buf, sz);
}

int nos::putbyte(char c)
{
	return nos::putbyte_to(*nos::current_ostream, c);
}

int nos::writeln(const void* buf, size_t sz)
{
	return nos::writeln_to(*nos::current_ostream, buf, sz);
}
