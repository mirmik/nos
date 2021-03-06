#ifndef NOS_FPRINT_VISITOR_H
#define NOS_FPRINT_VISITOR_H

/**
	@file
*/

#include <string_view>
#include <nos/util/arglist.h>

#include <nos/fprint/meta.h>

namespace nos
{
	class ostream;

	struct format_visitor
	{
		using ftype = int(*)(void*, nos::ostream&, const std::string_view & opts);

		template<typename Object>
		static void* get_visit()
		{
			return reinterpret_cast<void*>(&fprint_implementation<Object>::fprint_to);
		}

		template<typename ... Args>
		static inline int visit(nos::visitable_argument varg, Args&& ... args)
		{
			ftype fptr = (ftype) varg.visit;
			return fptr(varg.ptr, std::forward<Args>(args) ...);
		}
	};
}

#endif
