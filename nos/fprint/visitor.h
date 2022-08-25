#ifndef NOS_FPRINT_VISITOR_H
#define NOS_FPRINT_VISITOR_H

/**
    @file
*/

#include <nos/fprint/meta.h>
#include <nos/util/arglist.h>

namespace nos
{
    class ostream;

    class format_visitor
    {
        using ftype = int (*)(void *, nos::ostream &, const nos::buffer &opts);

    public:
        template <typename Object> static void *get_visit_implementation()
        {
            return reinterpret_cast<void *>(
                &fprint_implementation<Object>::fprint_to);
        }

        template <typename... Args>
        static inline int visit(nos::visitable_argument varg, Args &&... args)
        {
            ftype fptr = (ftype)varg.visit;
            return fptr(varg.ptr, std::forward<Args>(args)...);
        }
    };
}

#endif
