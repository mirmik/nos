#include <iostream>
#include <utility>

namespace nos
{
	class ostream;
}

struct nos_ostream_ref {
	nos::ostream* ref;	
};

ssize_t nos_print(nos_ostream_ref, auto);

namespace nos
{
	class ostream;

	namespace detail
	{
		template <typename>
		struct sfinae_true : std::true_type
		{ };

		template <typename T> static auto test_has_implicit_overload(int)
		-> sfinae_true<decltype(
            ::nos_print(std::declval<nos_ostream_ref>(), std::declval<T>())
		)>;

		template <typename T> static auto test_has_implicit_overload(...)
		-> std::false_type;
	}

	template <typename T>
	struct has_implicit_overload : decltype(detail::test_has_implicit_overload<T>(0)) { };

}

template<> ssize_t nos_print<int>(nos_ostream_ref, int) {}

void func() {
	int i = 0;
	nos_print(nos_ostream_ref(), i);
}

int main() 
{
	std::cout << nos::has_implicit_overload<const char*>::value << std::endl;

}