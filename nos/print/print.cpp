#include <nos/print/print.h>
#include <nos/io/ostream.h>

ssize_t nos::putchar_to(nos::ostream& o, char c)
{
	return o.write(&c, 1);
}

ssize_t nos::println_to(nos::ostream& o)
{
	return o.write("\r\n", 2);
}

ssize_t nos::print_dump_to(nos::ostream& out, const void *mem, size_t len, unsigned int columns)
{
	unsigned int i, j;

	for (i = 0; i < len + ((len % columns) ? (columns - len % columns) : 0); i++)
	{
		// print offset
		if (i % columns == 0)
		{
			out.write("0x", 2);
			out.printptr((void*)((char*)mem + i));
			out.putchar(':');
		}

		// print hex data
		if (i < len)
		{
			out.printhex(((char*)mem)[i]);
			out.putchar(' ');
		}
		else
		{
			// end of block, just aligning for ASCII dump
			out.write("   ", 3);
		}

		// print ASCII dump
		if (i % columns == (columns - 1))
		{
			for (j = i - (columns - 1); j <= i; j++)
			{
				if (j >= len)
				{
					// end of block, not really printing
					out.putchar(' ');
				}
				else if (isprint(((char*)mem)[j]))
				{
					// printable char
					out.putchar((char)0xFF & ((char*)mem)[j]);
				}
				else
				{
					// other char
					out.putchar('.');
				}
			}
			out.println();
		}
	}
}

ssize_t nos::print_dump(const void* ptr, size_t sz, unsigned int columns)
{
	return nos::print_dump_to(*nos::current_ostream, ptr, sz, columns);
}
