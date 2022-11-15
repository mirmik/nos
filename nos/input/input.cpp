#include <nos/input.h>
#include <nos/io/istream.h>
#include <nos/print.h>
#include <nos/util/error.h>
#include <nos/util/expected.h>
#include <stdexcept>

nos::expected<std::string, nos::input_error>
nos::readline_from(nos::istream &is)
{
    char c;
    std::string str;

    while (1)
    {
        auto ret = is.read(&c, 1);

        if (!ret)
            return ret.error();

        if (c == '\r')
        {
            continue;
        }

        if (c == '\n')
        {
            return str;
        }

        str.push_back(c);
    }
}

nos::expected<std::string, nos::input_error>
nos::read_until_from(nos::istream &is, const std::string_view &delimiters)
{
    std::string ret;

    while (true)
    {
        char c;
        auto sts = is.read(&c, 1);

        if (!sts)
        {
            return sts.error();
        }

        ret.push_back(c);

        if (delimiters.find(c) != std::string::npos)
        {
            return ret;
        }
    }
}

int nos::read_until(nos::istream &is, char *buf, size_t buflen, char delim)
{
    char c;
    int count = 0;
    char *last = buf + buflen - 1;

    while (buf != last)
    {
        int readed = is.read(&c, 1);

        if (readed < 0)
        {
            return readed;
        }

        if (readed == 0)
        {
            *buf = 0;
            return count;
        }

        *buf++ = c;
        count++;

        if (c == delim)
        {
            *buf = 0;
            return count;
        }
    }

    //*buf = 0;
    return count;
}

/// Считывает из потока ввода содержимое строки между открывающейся скобкой 'a'
/// и закрывающейся скобкой 'b' Параметр ignore позволяет отбростить данные
/// перед первой скобкой.
int nos::read_paired(
    nos::istream &is, char *buf, size_t buflen, char a, char b, bool ignore)
{
    char c;
    int count = 0;
    char *last = buf + buflen - 1;

    int paircount = 0;

    if (ignore)
        do
        {
            int ret = is.read(&c, 1);
            if (ret <= 0)
                return ret;
        } while (c != a);
    else
    {
        is.read(&c, 1);
        if (c != a)
            return -1;
    }

    paircount = 1;
    *buf++ = c;
    count++;

    while (paircount != 0 && buf != last)
    {
        int readed = is.read(&c, 1);

        if (readed <= 0)
        {
            *buf = 0;
            return count;
        }

        if (c == a)
        {
            ++paircount;
        }

        if (c == b)
        {
            if (--paircount == 0)
            {
                *buf++ = c;
                count++;
                *buf = 0;
                return count;
            }
        }

        *buf++ = c;
        count++;
    }

    *buf = 0;
    return count;
}

std::string nos::readall_from(nos::istream &is)
{
    return is.readall();
}

nos::expected<std::string, nos::input_error> nos::readline()
{
    return nos::readline_from(*nos::current_istream);
}

nos::expected<std::string, nos::input_error> nos::read_from(nos::istream &is,
                                                            size_t sz)
{
    return is.read(sz);
}

nos::expected<std::string, nos::input_error>
nos::timeouted_readline_from(nos::istream &is, std::chrono::nanoseconds ms)
{
    is.set_input_timeout(ms);
    auto ret = nos::readline_from(is);
    return ret;
}