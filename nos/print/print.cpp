#include <nos/io/ostream.h>
#include <nos/print/print.h>
#include <nos/print/stdtype.h>
#include <string>
#include <string_view>

int nos::write_to(nos::ostream &out, const void *buf, size_t sz)
{
    return out.write(buf, sz);
}

int nos::putbyte_to(nos::ostream &out, char c)
{
    return out.write(&c, 1);
}

int nos::writeln_to(nos::ostream &out, const void *buf, size_t sz)
{
    int ret = 0;
    ret += out.write(buf, sz);
    ret += nos::println_to(out);
    return ret;
}

int nos::println_to(nos::ostream &o)
{
    return o.write("\r\n", 2);
}

int nos::println()
{
    return nos::current_ostream->write("\r\n", 2);
}

void nos::flush()
{
    nos::current_ostream->flush();
}

void flush_to(nos::ostream &out)
{
    out.flush();
}

int nos::print_dump_to(nos::ostream &out,
                       const void *mem,
                       size_t len,
                       unsigned int columns)
{
    size_t ret = 0;
    unsigned int i, j;

    if (len == 0)
    {
        ret += out.write("0x", 2);
        ret += nos::printptr_to(out, (void *)((char *)mem));
        ret += out.putbyte(':');
        ret += nos::println_to(out);
        return ret;
    }

    for (i = 0; i < len + ((len % columns) ? (columns - len % columns) : 0);
         i++)
    {
        // print offset
        if (i % columns == 0)
        {
            ret += out.write("0x", 2);
            ret += nos::printptr_to(out, (void *)((char *)mem + i));
            ret += out.putbyte(':');
        }

        // print hex data
        if (i < len)
        {
            ret += nos::printhex_to(out, ((char *)mem)[i]);
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
                else if (isprint(((char *)mem)[j]))
                {
                    // printable char
                    ret += out.putbyte((char)0xFF & ((char *)mem)[j]);
                }
                else
                {
                    // other char
                    ret += out.putbyte('.');
                }
            }

            ret += nos::println();
        }
    }

    return ret;
}

int nos::print_dump(const void *ptr, size_t sz, unsigned int columns)
{
    return nos::print_dump_to(*nos::current_ostream, ptr, sz, columns);
}

int nos::print_dump(const std::string_view &buf, unsigned int columns)
{
    return nos::print_dump_to(
        *nos::current_ostream, buf.data(), buf.size(), columns);
}

int nos::write(const void *buf, size_t sz)
{
    return nos::write_to(*nos::current_ostream, buf, sz);
}

int nos::putbyte(char c)
{
    return nos::putbyte_to(*nos::current_ostream, c);
}

int nos::writeln(const void *buf, size_t sz)
{
    return nos::writeln_to(*nos::current_ostream, buf, sz);
}

int nos::fill_to(nos::ostream &out, char c, size_t sz)
{
    for (size_t i = 0; i < sz; i++)
        out.putbyte(c);
    return sz;
}

int nos::fill_to(nos::ostream &out, std::string_view &c, size_t sz)
{
    for (size_t i = 0; i < sz; i++)
        nos::print_to(out, c);
    return c.size() * sz;
}

int nos::fill(char c, size_t sz)
{
    return nos::fill_to(*nos::current_ostream, c, sz);
}

int nos::fill(std::string_view &c, size_t sz)
{
    return nos::fill_to(*nos::current_ostream, c, sz);
}

int nos::printhex_to(nos::ostream &out, char c)
{
    char buf[2];
    buf[0] = __nos_half2hex((uint8_t)((c & 0xF0) >> 4));
    buf[1] = __nos_half2hex((uint8_t)(c & 0x0F));
    return out.write(buf, 2);
}

int nos::printhex_to(nos::ostream &out, void *ptr, size_t sz)
{
    size_t ret = 0;
    char *_ptr = (char *)ptr;

    for (unsigned int i = 0; i < sz; ++i)
    {
        ret += printhex_to(out, *_ptr++);
    }

    return ret;
}