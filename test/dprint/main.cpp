#define NOTRACE 0

#include <nos/print.h>
#include <nos/trace.h>

#include <nos/io/std.h>

int func(int a, int b) 
{
	TRACE_ARGS(a, b);
	return TRRET(a);
}

struct A 
{
	int a = 42;
	friend std::ostream& operator << ( std::ostream& os, const A&);
};

std::ostream& operator << ( std::ostream& os, const A& a) 
{
	os << std::hex << 42 << "A!!!"; 
}

int main() 
{
	TRACE();
	func(55, 33);

	A a;

	nos::fprintln("mirmik");
	nos::fprintln("mirmik {} {}", 33, 35);
	nos::fprintln("mirmik {} {} {}", 33, a, 34);

	nos::println(a);

	nos::printhex(a);

	nos::println(std::array<float,4>{0,1,23,4});

//	nos::fprintln("mirmik {} {}", 33, a);
}