#include <iostream>
#include <utility>

#include <nos/io/ostream.h>

class test_ostream : public nos::ostream {};

template <typename>
struct sfinae_true : std::true_type
{ };

template <typename T> static auto nos_test_has_implicit_overload(int)
-> sfinae_true<decltype(
     nos_print(std::declval<test_ostream&>(), std::declval<T>())
)>;

template <typename T> static auto nos_test_has_implicit_overload(...)
-> std::false_type;

template <typename T>
struct nos_has_implicit_overload : decltype(nos_test_has_implicit_overload<T>(0)) { };

ssize_t nos_print(nos::ostream&, const char*) {}

int main() 
{
	std::cout << nos_has_implicit_overload<const char*>::value << std::endl;
}