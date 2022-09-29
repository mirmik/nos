#ifndef NOS_UTIL_EXPECTED_H
#define NOS_UTIL_EXPECTED_H

#include <nos/util/error.h>

namespace nos
{
    template <typename T, typename E> class expected
    {
        bool _is_ok;
        union
        {
            T _ok;
            E _err;
        };

    public:
        expected() : _is_ok(false) {}
        expected(const T &val) : _is_ok(true), _ok(val) {}
        expected(const E &err) : _is_ok(false), _err(err) {}
        ~expected()
        {
            if (_is_ok)
                _ok.~T();
            else
                _err.~E();
        }

        T &value()
        {
            return _ok;
        }

        const T &value() const
        {
            return _ok;
        }

        T value_or(const T &defval) const
        {
            return _is_ok ? _ok : defval;
        }

        E &error()
        {
            return _err;
        }

        const E &error() const
        {
            return _err;
        }

        operator bool() const
        {
            return _is_ok;
        }

        T &operator*()
        {
            return _ok;
        }

        const T &operator*() const
        {
            return _ok;
        }

        T *operator->()
        {
            return &_ok;
        }

        const T *operator->() const
        {
            return &_ok;
        }
    };
}

#endif