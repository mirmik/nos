#ifndef NOS_META_META_H
#define NOS_META_META_H

namespace nos 
{
	template <typename T> class has_nos_print;
}

#include <nos/io/ostream.h>

class nos_test_ostream : public nos::ostream {};

namespace nos 
{
	template <typename T>
	class has_nos_print
	{
	private:
		template <typename U>
		static decltype( nos_print(
				std::declval<nos_test_ostream&>(), std::declval<U>()
			), std::true_type()) test(int);

		template <typename> static std::false_type test(...);

	public:
		static constexpr const bool value = decltype(test<T>(0))::value;
	};	
}

#endif