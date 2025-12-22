#ifndef NOS_IO_STRING_WRITER_H
#define NOS_IO_STRING_WRITER_H

#include <nos/io/ostream.h>
#include <string>

namespace nos
{
    class string_writer : public nos::ostream
    {
    private:
        std::string &str;

    public:
        string_writer(std::string &_str) : str(_str) {}

        nos::expected<size_t, nos::output_error> write(const void *ptr,
                                                       size_t sz) override
        {
            str.append((char *)ptr, sz);
            return sz;
        }
    };

    class string_buffer : public nos::ostream
    {
    private:
        std::string _str = {};

    public:
        nos::expected<size_t, nos::output_error> write(const void *ptr,
                                                       size_t sz) override
        {
            _str.append((char *)ptr, sz);
            return sz;
        }

        std::string &str()
        {
            return _str;
        }
    };

    class cstring_writer : public nos::ostream
    {
    private:
        char *str;

    public:
        cstring_writer(char *_str) : str(_str) {}
        cstring_writer(const cstring_writer &_str) = default;
        cstring_writer &operator=(const cstring_writer &_str) = default;

        nos::expected<size_t, nos::output_error> write(const void *ptr,
                                                       size_t sz) override
        {
            memcpy(str, ptr, sz);
            str += sz;
            return (int)sz;
        }
    };

    /// Output stream that writes to a fixed-size buffer.
    /// Tracks written size and prevents buffer overflow.
    class static_buffer_ostream : public nos::ostream
    {
    private:
        char *_buf;
        size_t _capacity;
        size_t _size = 0;

    public:
        static_buffer_ostream(char *buf, size_t capacity)
            : _buf(buf), _capacity(capacity)
        {
        }

        static_buffer_ostream(const static_buffer_ostream &) = delete;
        static_buffer_ostream &operator=(const static_buffer_ostream &) = delete;

        nos::expected<size_t, nos::output_error> write(const void *ptr,
                                                       size_t sz) override
        {
            size_t to_write =
                (_size + sz <= _capacity) ? sz : (_capacity - _size);
            memcpy(_buf + _size, ptr, to_write);
            _size += to_write;
            return to_write;
        }

        size_t size() const
        {
            return _size;
        }
        const char *data() const
        {
            return _buf;
        }
        size_t capacity() const
        {
            return _capacity;
        }
        size_t room() const
        {
            return _capacity - _size;
        }
        void reset()
        {
            _size = 0;
        }
    };
}

#endif
