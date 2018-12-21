#include <nos/meta/meta.h>
#include <iostream>

ssize_t nos_print(nos::ostream& out, char const* arg);

int main() 
{
	std::cout << nos::has_implicit_nos_print<char const*>::value << std::endl;
	std::cout << nos::has_implicit_nos_print<char const[]>::value << std::endl;
}