#ifndef NOS_ILIST_H
#define NOS_ILIST_H

#include <cstddef>

namespace nos
{
    template <typename T> class ilist_adapter
    {
        T &list;

    public:
        ilist_adapter(T &list) : list(list) {}

        auto begin()
        {
            return list.begin();
        }
        auto end()
        {
            return list.end();
        }
        auto begin() const
        {
            return list.begin();
        }
        auto end() const
        {
            return list.end();
        }

        auto size() const
        {
            return list.size();
        }

        const auto &operator[](size_t index) const
        {
            return list[index];
        }
    };

    template <typename T> ilist_adapter<T> ilist(T &list)
    {
        return ilist_adapter<T>(list);
    }

    template <typename T> class ibin_adapter
    {
        T &bin;

    public:
        ibin_adapter(T &bin) : bin(bin) {}

        const T &ref() const
        {
            return bin;
        }
    };

    template <typename T> ibin_adapter<T> ibin(T &bin)
    {
        return ibin_adapter<T>(bin);
    }

    template <typename T> class ihex_adapter
    {
        T &hex;

    public:
        ihex_adapter(T &hex) : hex(hex) {}

        const T &ref() const
        {
            return hex;
        }
    };

    template <typename T> ihex_adapter<T> ihex(T &hex)
    {
        return ihex_adapter<T>(hex);
    }
}

#endif