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

int main() 
{
	TRACE();
	func(55, 33);
}