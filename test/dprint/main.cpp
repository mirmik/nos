#include <nos/dprint.h>
#include <nos/print.h>
#include <nos/io/std.h>

int main() 
{
	dprf("HelloWorld %d %d %d\n", 35, 78, 98);
	dprln(33, 34, 35, 36, 37);

	nos::println(33);
	nos::println(33, "mirmik", 333);

	nos::print_dump("mirmik", 6);
}