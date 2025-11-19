#ifndef nos_TRENT_JSON_H
#define nos_TRENT_JSON_H

/**
    @file
*/

#include <cctype>
#include <cstdint>
#include <exception>
#include <nos/trent/trent.h>
#include <nos/util/numconvert.h>
#include <sstream>
#include <utility>

using namespace std::literals::string_literals;

namespace nos
{
    namespace json
    {
        class parser
        {
            int symbno = 0;
            int lineno = 1;
            char onebuf = 0;

            class unexpected_symbol : public std::runtime_error
            {
            public:
                unexpected_symbol(char symb)
                    : std::runtime_error(std::string("unexpected:") + symb)
                {
                }
            };

            static void append_utf8_codepoint(trent::string_type &out,
                                              uint32_t codepoint)
            {
                if (codepoint <= 0x7F)
                {
                    out.push_back(static_cast<char>(codepoint));
                }
                else if (codepoint <= 0x7FF)
                {
                    out.push_back(
                        static_cast<char>(0xC0 | ((codepoint >> 6) & 0x1F)));
                    out.push_back(
                        static_cast<char>(0x80 | (codepoint & 0x3F)));
                }
                else if (codepoint <= 0xFFFF)
                {
                    out.push_back(
                        static_cast<char>(0xE0 | ((codepoint >> 12) & 0x0F)));
                    out.push_back(
                        static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
                    out.push_back(
                        static_cast<char>(0x80 | (codepoint & 0x3F)));
                }
                else if (codepoint <= 0x10FFFF)
                {
                    out.push_back(
                        static_cast<char>(0xF0 | ((codepoint >> 18) & 0x07)));
                    out.push_back(
                        static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F)));
                    out.push_back(
                        static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
                    out.push_back(
                        static_cast<char>(0x80 | (codepoint & 0x3F)));
                }
                else
                {
                    throw std::runtime_error("json: invalid codepoint");
                }
            }

            uint8_t hex_to_value(char c)
            {
                if (c >= '0' && c <= '9')
                    return c - '0';
                if (c >= 'a' && c <= 'f')
                    return 10 + (c - 'a');
                if (c >= 'A' && c <= 'F')
                    return 10 + (c - 'A');
                throw std::runtime_error("json: invalid hex digit"s + errloc());
            }

            void append_unicode_escape(trent::string_type &out)
            {
                uint32_t codepoint = 0;
                for (int i = 0; i < 4; ++i)
                {
                    char c = readnext();
                    if (!std::isxdigit(static_cast<unsigned char>(c)))
                        throw std::runtime_error(
                            "json: invalid unicode escape"s + errloc());
                    codepoint = (codepoint << 4) | hex_to_value(c);
                }

                if (codepoint >= 0xD800 && codepoint <= 0xDBFF)
                {
                    char slash = readnext();
                    char u = readnext();
                    if (slash != '\\' || u != 'u')
                        throw std::runtime_error(
                            "json: invalid surrogate pair"s + errloc());
                    uint32_t low = 0;
                    for (int i = 0; i < 4; ++i)
                    {
                        char c = readnext();
                        if (!std::isxdigit(static_cast<unsigned char>(c)))
                            throw std::runtime_error(
                                "json: invalid unicode escape"s + errloc());
                        low = (low << 4) | hex_to_value(c);
                    }
                    if (low < 0xDC00 || low > 0xDFFF)
                        throw std::runtime_error(
                            "json: invalid surrogate pair"s + errloc());

                    codepoint =
                        0x10000 + ((codepoint - 0xD800) << 10) + (low - 0xDC00);
                }

                append_utf8_codepoint(out, codepoint);
            }

        public:
            virtual ~parser() {}
            virtual char readnext_impl() = 0;

            char readnext()
            {
                symbno++;
                char c = readnext_impl();
                if (c == '\n')
                {
                    lineno++;
                    symbno = 0;
                }
                return c;
            }

            std::string errloc()
            {
                return " lineno:" + std::to_string(lineno) +
                       " symbno:" + std::to_string(symbno);
            }

            char readnext_skipping()
            {
                char c;

            __try__:
                c = readnext();

                if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
                    goto __try__;

                if (c == '/')
                {
                    c = readnext();

                    switch (c)
                    {
                    case '*':
                        while (true)
                        {
                            c = readnext();

                            if (c == '*')
                                if ((c = readnext()) == '/')
                                {
                                    goto __try__;
                                }
                        }

                    case '/':

                        // is.ignore(INT_MAX, '\n');
                        while (c != '\n')
                            c = readnext();

                        goto __try__;

                    default:
                        // is.unget();
                        break;
                    }
                }

                // is.unget();
                return c;
            }

            template <template <class Allocator> class TAlloc = std::allocator>
            trent_basic<TAlloc> parse()
            {
                // TRACE();

                if (onebuf == 0)
                {
                    onebuf = readnext_skipping();
                }

                if (isdigit(onebuf) || onebuf == '-')
                    return parse_numer();

                if (onebuf == '"')
                    return parse_string();

                if (onebuf == '\'')
                    return parse_string();

                if (onebuf == '[')
                    return parse_list();

                if (onebuf == '{')
                    return parse_dict();

                if (isalpha(onebuf))
                    return parse_mnemonic();

                throw std::runtime_error("unexpected_symbol "s + onebuf +
                                         errloc());
            }

            template <template <class Allocator> class TAlloc = std::allocator>
            trent_basic<TAlloc> parse_mnemonic()
            {
                char buf[32];
                char *ptr = &buf[1];

                buf[0] = onebuf;

                while (isalpha(onebuf = readnext_skipping()))
                {
                    *ptr++ = onebuf;
                }

                *ptr = 0;

                if (strcmp("true", buf) == 0)
                {
                    return true;
                }
                if (strcmp("false", buf) == 0)
                {
                    return false;
                }
                if (strcmp("nil", buf) == 0 || strcmp("null", buf) == 0)
                {
                    return trent_basic<TAlloc>();
                }

                throw std::runtime_error("unexpected_mnemonic "s + errloc());
            }

            template <template <class Allocator> class TAlloc = std::allocator>
            trent_basic<TAlloc> parse_numer()
            {
                std::string buf;
                buf.push_back(onebuf);
                bool allow_sign = false;

                while (true)
                {
                    char c = readnext();

                    if (std::isdigit(static_cast<unsigned char>(c)) ||
                        c == '.')
                    {
                        buf.push_back(c);
                        allow_sign = false;
                        continue;
                    }

                    if (c == 'e' || c == 'E')
                    {
                        buf.push_back(c);
                        allow_sign = true;
                        continue;
                    }

                    if ((c == '+' || c == '-') && allow_sign)
                    {
                        buf.push_back(c);
                        allow_sign = false;
                        continue;
                    }

                    onebuf = c;
                    break;
                }

                if (std::isspace(static_cast<unsigned char>(onebuf)))
                    onebuf = 0;

                return strtod(buf.c_str(), nullptr);
            }

            template <template <class Allocator> class TAlloc = std::allocator>
            trent_basic<TAlloc> parse_string()
            {
                trent::string_type str;

                char delim = onebuf;

                while (true)
                {
                    char c = readnext();

                    if (c == 0)
                        throw std::runtime_error("json: unterminated string"s +
                                                 errloc());

                    if (c == delim)
                        break;

                    if (c == '\\')
                    {
                        char esc = readnext();
                        switch (esc)
                        {
                        case '"':
                            str.push_back('"');
                            break;
                        case '\'':
                            str.push_back('\'');
                            break;
                        case '\\':
                            str.push_back('\\');
                            break;
                        case '/':
                            str.push_back('/');
                            break;
                        case 'b':
                            str.push_back('\b');
                            break;
                        case 'f':
                            str.push_back('\f');
                            break;
                        case 'n':
                            str.push_back('\n');
                            break;
                        case 'r':
                            str.push_back('\r');
                            break;
                        case 't':
                            str.push_back('\t');
                            break;
                        case 'u':
                            append_unicode_escape(str);
                            break;
                        default:
                            throw std::runtime_error(
                                "json: invalid escape sequence"s + errloc());
                        }

                        continue;
                    }

                    if (c == '\n' || c == '\r')
                        throw std::runtime_error("json: unexpected newline"s +
                                                 errloc());

                    str.push_back(c);
                }

                onebuf = 0;
                return str;
            }

            template <template <class Allocator> class TAlloc = std::allocator>
            trent_basic<TAlloc> parse_list()
            {
                // TRACE();
                trent_basic<TAlloc> js(trent::type::list);

                onebuf = readnext_skipping();

                if (onebuf == ']')
                {
                    onebuf = 0;
                    return js;
                }

                while (true)
                {
                    trent_basic<TAlloc> r = parse();
                    js.as_list().push_back(r);

                    if (onebuf == 0)
                        onebuf = readnext_skipping();

                    if (onebuf == ']')
                    {
                        onebuf = 0;
                        return js;
                    }

                    if (onebuf != ',')
                    {
                        throw std::runtime_error(
                            "json::parse_list: wait_, expect_"s + onebuf +
                            errloc());
                    }

                    onebuf = readnext_skipping();
                }
            }

            template <template <class Allocator> class TAlloc = std::allocator>
            trent_basic<TAlloc> parse_dict()
            {
                // TRACE();
                trent_basic<TAlloc> js(trent::type::dict);

                onebuf = readnext_skipping();

                if (onebuf == '}')
                {
                    return js;
                }

                while (true)
                {
                    // Изменить на строку
                    trent_basic<TAlloc> key = parse();

                    if (!key.is_string())
                        throw std::runtime_error(
                            "json: object key must be string"s + errloc());

                    onebuf = readnext_skipping();

                    if (onebuf != ':')
                        throw std::runtime_error(
                            "json:parse_dict_0 wait_: expect_"s + onebuf +
                            " lineno:" + std::to_string(lineno) +
                            " symbno:" + std::to_string(symbno));

                    onebuf = 0;

                    trent_basic<TAlloc> value = parse();

                    auto keystr = std::move(key.as_string());

                    js.as_dict().emplace(std::move(keystr), std::move(value));

                    if (onebuf == 0)
                        onebuf = readnext_skipping();

                    if (onebuf == '}')
                    {
                        onebuf = 0;
                        return js;
                    }

                    if (onebuf != ',')
                    {
                        throw std::runtime_error(
                            "json:parse_dict_1 wait_, expect_"s + onebuf +
                            " lineno:" + std::to_string(lineno) +
                            " symbno:" + std::to_string(symbno));
                    }

                    onebuf = readnext_skipping();

                    if (onebuf == '}')
                    {
                        onebuf = 0;
                        return js;
                    }
                }
            }
        };

        class parser_cstr : public parser
        {
            const char *ptr = nullptr;

        public:
            parser_cstr(const char *str) : ptr(str) {}
            parser_cstr(const parser_cstr &) = default;
            parser_cstr &operator=(const parser_cstr &) = default;

            char readnext_impl()
            {
                return *ptr++;
            }
        };

        class parser_str : public parser
        {
            std::string storage = {};
            size_t index = 0;

        public:
            parser_str(const std::string &str) : storage(str) {}
            parser_str(std::string &&str) : storage(std::move(str)) {}
            parser_str(const parser_str &) = default;
            parser_str &operator=(const parser_str &) = default;

            char readnext_impl()
            {
                if (index >= storage.size())
                    return 0;
                return storage[index++];
            }
        };

        class parser_input_stream : public parser
        {
            std::istream &is;

        public:
            parser_input_stream(std::istream &is) : is(is) {}

            char readnext_impl()
            {
                return is.get();
            }
        };

        nos::trent parse(const char *str);
        nos::trent parse(const std::string &str);
        nos::trent parse_file(const std::string &str);
    }
}

#endif
