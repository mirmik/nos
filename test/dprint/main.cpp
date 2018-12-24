#define NOTRACE 0

#include <nos/dprint.h>
#include <nos/print.h>

#include <nos/dtrace.h>
#include <nos/trace.h>

#include <nos/io/std.h>

int func(int a, int b) 
{
	TRACE_ARGS(a, b);
	return TRRET(a);
}

struct A 
{
	int a = 3;
	ssize_t print_to(nos::ostream& os) const {
		os.print("helloWorld");
	}
};

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

	nos::println(std::vector<float> {0,1,23,4});

//	nos::fprintln("mirmik {} {}", 33, a);
}