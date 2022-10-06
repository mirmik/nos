#ifndef NOS_UTIL_EXPECTED_H
#define NOS_UTIL_EXPECTED_H

#include <nos/util/error.h>

namespace nos
{
    template <typename T, typename E> class expected
    {
        bool _is_ok = false;
        union storage_u
        {
            T _ok = {};
            E _err;
            storage_u() {}
            ~storage_u() {}
        } u = {};

    public:
        expected() : _is_ok(false) {}
        expected(const T &val) : _is_ok(true)
        {
            new (&u._ok) T(val);
        }

        expected(const E &err) : _is_ok(false)
        {
            new (&u._err) E(err);
        }

        expected(const expected &other) : _is_ok(other._is_ok)
        {
            if (_is_ok)
            {
                new (&u._ok) T(other.u._ok);
            }
            else
            {
                new (&u._err) E(other.u._err);
            }
        }

        expected(expected &&other) : _is_ok(other._is_ok)
        {
            if (_is_ok)
            {
                new (&u._ok) T(std::move(other.u._ok));
            }
            else
            {
                new (&u._err) E(std::move(other.u._err));
            }
        }

        ~expected()
        {
            if (_is_ok)
                u._ok.~T();
            else
                u._err.~E();
        }

        T &value()
        {
            return u._ok;
        }

        const T &value() const
        {
            return u._ok;
        }

        T value_or(const T &defval) const
        {
            return _is_ok ? u._ok : defval;
        }

        E &error()
        {
            return u._err;
        }

        const E &error() const
        {
            return u._err;
        }

        operator bool() const
        {
            return _is_ok;
        }

        T &operator*()
        {
            return u._ok;
        }

        const T &operator*() const
        {
            return u._ok;
        }

        T *operator->()
        {
            return &u._ok;
        }

        const T *operator->() const
        {
            return &u._ok;
        }
    };
}

#endif