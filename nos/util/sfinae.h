#ifndef NOS_UTIL_SFINAE_H
#define NOS_UTIL_SFINAE_H

#include <utility>

namespace nos {
	namespace detail
	{
		template <typename>
		struct sfinae_true : std::true_type
		{ };
	}
}

#endif