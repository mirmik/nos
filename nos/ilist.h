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
}

#endif