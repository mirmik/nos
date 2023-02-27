/**
    @file
*/

#ifndef NOS_PRINT_PRINT_H
#define NOS_PRINT_PRINT_H

#include <cstdlib>
#include <cstring>
#include <nos/input/input_error.h>
#include <nos/util/size.h>
#include <string_view>

namespace nos
{
    class ostream;
    extern ostream *current_ostream;

    nos::expected<size_t, nos::output_error> putbyte_to(nos::ostream &out,
                                                        char c);
    nos::expected<size_t, nos::output_error>
    write_to(nos::ostream &out, const void *buf, size_t sz);
    nos::expected<size_t, nos::output_error>
    writeln_to(nos::ostream &out, const void *buf, size_t sz);
    template <typename Arg>
    nos::expected<size_t, nos::output_error> print_to(nos::ostream &out,
                                                      const Arg &arg);
    template <typename Head, typename... Tail>
    nos::expected<size_t, nos::output_error>
    print_to(nos::ostream &out, const Head &head, const Tail &...tail);
    nos::expected<size_t, nos::output_error> println_to(nos::ostream &);
    template <typename... Args>
    nos::expected<size_t, nos::output_error> println_to(nos::ostream &out,
                                                        const Args &...args);
    template <typename V>
    nos::expected<size_t, nos::output_error> print_list_to(nos::ostream &out,
                                                           const V &vec);
    template <typename M>
    nos::expected<size_t, nos::output_error> print_matrix_to(nos::ostream &out,
                                                             const M &mat);
    template <typename... Args>
    nos::expected<size_t, nos::output_error> printhex_to(nos::ostream &out,
                                                         const Args &...args);
    template <typename Arg>
    nos::expected<size_t, nos::output_error> printptr_to(nos::ostream &out,
                                                         const Arg *arg);
    template <typename Arg>
    nos::expected<size_t, nos::output_error> printptrln_to(nos::ostream &out,
                                                           const Arg *arg);
    nos::expected<size_t, nos::output_error> print_dump_to(
        nos::ostream &, const void *mem, size_t len, unsigned int columns = 8);

    nos::expected<size_t, nos::output_error> putbyte(char c);
    nos::expected<size_t, nos::output_error> write(const void *buf, size_t sz);
    nos::expected<size_t, nos::output_error> writeln(const void *buf,
                                                     size_t sz);
    template <typename... Args>
    nos::expected<size_t, nos::output_error> print(const Args &...args);
    nos::expected<size_t, nos::output_error> println();
    template <typename... Args>
    nos::expected<size_t, nos::output_error> println(const Args &...args);
    template <typename V>
    nos::expected<size_t, nos::output_error> print_list(const V &vec);
    template <typename M>
    nos::expected<size_t, nos::output_error> print_matrix(const M &mat);
    template <typename... Args>
    nos::expected<size_t, nos::output_error> printhex(const Args &...args);
    template <typename... Args>
    nos::expected<size_t, nos::output_error> printhexln(const Args &...args);
    template <typename Arg>
    nos::expected<size_t, nos::output_error> printptr(const Arg &arg);
    nos::expected<size_t, nos::output_error>
    print_dump(const void *mem, size_t len, unsigned int columns = 8);
    void flush();
    void flush_to(nos::ostream &out);
    nos::expected<size_t, nos::output_error>
    fill_to(nos::ostream &out, char c, size_t sz);
    nos::expected<size_t, nos::output_error>
    fill_to(nos::ostream &out, std::string_view &c, size_t sz);
    nos::expected<size_t, nos::output_error> fill(char c, size_t sz);
    nos::expected<size_t, nos::output_error> fill(std::string_view &c,
                                                  size_t sz);

    nos::expected<size_t, nos::output_error> printhex_to(nos::ostream &out,
                                                         char c);
    nos::expected<size_t, nos::output_error>
    printhex_to(nos::ostream &out, const void *ptr, size_t sz);
    nos::expected<size_t, nos::output_error> printbin_to(nos::ostream &out,
                                                         char c);
    nos::expected<size_t, nos::output_error>
    printbin_to(nos::ostream &out, const void *ptr, size_t size);
    nos::expected<size_t, nos::output_error>
    printhex_to(nos::ostream &out, void *ptr, size_t sz);
    nos::expected<size_t, nos::output_error>
    printbin_to(nos::ostream &out, void *ptr, size_t size);

    template <typename O>
    nos::expected<size_t, nos::output_error> printhex_to(nos::ostream &out,
                                                         const O &o);

#if __has_include(<string_view>)
    nos::expected<size_t, nos::output_error>
    print_dump(const std::string_view &buf, unsigned int columns = 8);
#endif

    static inline nos::expected<size_t, nos::output_error> print(void *ptr)
    {
        return nos::printptr(ptr);
    }
    static inline nos::expected<size_t, nos::output_error>
    print_to(nos::ostream &out, void *ptr)
    {
        return nos::printptr_to(out, ptr);
    }
}

#include <nos/io/ostream.h>
#include <nos/print/meta.h>

template <typename O>
nos::expected<size_t, nos::output_error> nos::printhex_to(nos::ostream &out,
                                                          const O &o)
{
    return nos::printhex_to(out, (const void *)&o, sizeof(O));
}

template <typename Arg>
nos::expected<size_t, nos::output_error> nos::print_to(nos::ostream &out,
                                                       const Arg &arg)
{
    return nos::print_implementation<Arg>::print_to(out, arg);
}

template <typename... Args>
nos::expected<size_t, nos::output_error> nos::print(const Args &...args)
{
    return print_to(*current_ostream, args...);
}

template <typename... Args>
nos::expected<size_t, nos::output_error> nos::println(const Args &...args)
{
    return println_to(*current_ostream, args...);
}

template <typename... Args>
nos::expected<size_t, nos::output_error> nos::printhex(const Args &...args)
{
    return printhex_to(*current_ostream, args...);
}

template <typename V>
nos::expected<size_t, nos::output_error> nos::print_list(const V &vec)
{
    return print_list_to(*current_ostream, vec);
}

template <typename M>
nos::expected<size_t, nos::output_error> nos::print_matrix(const M &mat)
{
    return print_matrix_to(*current_ostream, mat);
}

template <typename T>
nos::expected<size_t, nos::output_error> nos::printptr_to(nos::ostream &out,
                                                          const T *ptr)
{
    char buf[48];
    snprintf(buf, sizeof(buf), "%p", ptr);
    size_t len = std::strlen(buf);
    auto ret = nos::fill_to(out, '0', sizeof(void *) * 2 - len);
    return ret + nos::print_to(out, (const char *)buf);
}

template <typename... Args>
nos::expected<size_t, nos::output_error> nos::printhexln(const Args &...args)
{
    auto ret = nos::printhex_to(*current_ostream, args...);
    ret += nos::println_to(*current_ostream);
    return ret;
}

template <typename Head, typename... Tail>
nos::expected<size_t, nos::output_error>
nos::print_to(nos::ostream &out, const Head &head, const Tail &...tail)
{
    char c = ' ';
    size_t res = 0;
    res += print_to(out, head);
    res += nos::write_to(out, &c, 1);
    res += print_to(out, tail...);
    return res;
}

template <typename... Args>
nos::expected<size_t, nos::output_error> nos::println_to(nos::ostream &out,
                                                         const Args &...args)
{
    size_t res = 0;
    res += print_to(out, args...);
    res += nos::println_to(out);
    return res;
}

template <typename V>
nos::expected<size_t, nos::output_error> nos::print_list_to(nos::ostream &out,
                                                            const V &vec)
{
    size_t ret = 0;

    if (std::size(vec) == 0)
    {
        return out.write("{}", 2);
    }

    ret += out.putbyte('{');

    for (unsigned int i = 0; i < std::size(vec) - 1; ++i)
    {
        ret += print_to(out, vec[i]);
        ret += out.putbyte(',');
    }
    ret += print_to(out, vec[std::size(vec) - 1]);
    ret += out.putbyte('}');

    return ret;
}

template <typename M>
nos::expected<size_t, nos::output_error> nos::print_matrix_to(nos::ostream &out,
                                                              const M &mat)
{
    size_t ret = 0;
    for (unsigned int i = 0; i < mat.size1(); ++i)
    {
        for (unsigned int j = 0; j < mat.size2(); ++j)
        {
            ret += nos::print_to(out, mat(i, j));
            ret += nos::print_to(out, " ");
        }
        ret += nos::println_to(out);
    }
    return ret;
}

#endif
