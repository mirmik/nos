#include <nos/input.h>
#include <nos/io/istream.h>
#include <nos/print.h>
#include <nos/util/error.h>
#include <nos/util/expected.h>
#include <stdexcept>

nos::expected<std::string, nos::errstring> nos::readline_from(nos::istream &is)
{
    char c;
    std::string ret;

    while (1)
    {
        int readed = is.read(&c, 1);

        if (readed < 0)
        {
            return nos::errstring("read error");
        }

        if (readed == 0)
        {
            return ret;
        }

        if (c == '\r')
        {
            continue;
        }

        if (c == '\n')
        {
            return ret;
        }

        ret.push_back(c);
    }
}

nos::expected<std::string, nos::read_error>
nos::timeouted_readline_from(nos::istream &is, std::chrono::nanoseconds ms)
{
    std::string ret;
    auto curtime = std::chrono::system_clock::now();
    auto endtime = curtime + ms;

    while (true)
    {
        char c;
        auto ellapsed = endtime - curtime;
        auto pair = is.timeouted_read(&c, 1, ellapsed);
        auto sts = pair.first;
        auto is_timeout = pair.second;

        if (is_timeout)
        {
            return read_error::timeout();
        }

        if (sts < 0)
        {
            return read_error::closed();
        }

        if (sts == 0)
        {
            return read_error::closed();
        }

        if (c == '\r')
        {
            continue;
        }

        if (c == '\n')
        {
            return ret;
        }

        ret.push_back(c);
    }
}

/*std::pair<std::string, bool>
nos::timeouted_read_until_from(std::chrono::nanoseconds ms,
                               nos::istream &is,
                               const std::string_view &delimiters)
{
    std::string ret;
    auto curtime = std::chrono::system_clock::now();
    auto endtime = curtime + ms;

    while (true)
    {
        char c;
        auto curtime = std::chrono::system_clock::now();
        auto ellapsed = endtime - curtime;
        auto pair = is.timeouted_read(&c, 1, ellapsed);
        auto sts = pair.first;
        auto is_timeout = pair.second;

        // nos::current_ostream->write(&c, 1);
        // nos::print(" ");
        // nos::println((uint8_t)c);

        if (is_timeout)
        {
            return {ret, true};
        }

        if (sts < 0)
        {
            return {ret, false};
        }

        if (sts == 0)
        {
            return {ret, false};
        }

        ret.push_back(c);

        if (delimiters.find(c) != std::string::npos)
        {
            return {ret, false};
        }
    }
}

nos::expected<std::string, nos::errstring>
nos::read_until_from(nos::istream &is, const std::string_view &delimiters)
{
    std::string ret;

    while (true)
    {
        char c;
        auto sts = is.read(&c, 1);

        if (sts < 0)
        {
            return nos::errstring("read error");
        }

        if (sts == 0)
        {
            // eof
            return ret;
        }

        ret.push_back(c);

        if (delimiters.find(c) != std::string::npos)
        {
            return ret;
        }
    }
}*/

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

nos::expected<std::string, nos::errstring> nos::readline()
{
    return nos::readline_from(*nos::current_istream);
}

nos::expected<std::string, nos::errstring> nos::read_from(nos::istream &is,
                                                          size_t sz)
{
    std::string ret;
    ret.resize(sz);
    int size = is.read(&ret[0], sz);
    if (size < 0)
        return nos::errstring("read error");
    ret.resize(size);
    return ret;
}