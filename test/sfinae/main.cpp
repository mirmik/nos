#include <iostream>
#include <utility>

#include <nos/print.h>

struct A 
{
	ssize_t print_to(nos::ostream& os) const;
};

int main() 
{
	std::cout << nos::has_nos_print<const char*>::value << std::endl;
	std::cout << nos::has_print_method<A>::value << std::endl;
}