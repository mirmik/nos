#include <nos/trace.h>

static void bar() 
{
	TRACE();
}

static void foo() 
{
	TRACE();
	bar();
}

static void bar_a(int a) 
{
	TRACE_ARGS(a);
}

static void foo_a(int a) 
{
	TRACE_ARGS(a);
	bar_a(a);
}

LT_BEGIN_TEST(nos_test_suite, TRACE_test) {
	foo();
	LT_CHECK_EQ(output, 
		"TRACE: 1: -> void foo()\r\n"
		"TRACE: 2: -> void bar()\r\n"
		"TRACE: 2: <- void bar()\r\n"
		"TRACE: 1: <- void foo()\r\n");
}
LT_END_TEST(TRACE_test)

LT_BEGIN_TEST(nos_test_suite, TRACE_ARGS_test) {
	foo_a(42);
	LT_CHECK_EQ(output, 
		"TRACE: 1: -> void foo_a(int) args: a:42 \r\n"
		"TRACE: 2: -> void bar_a(int) args: a:42 \r\n"
		"TRACE: 2: <- void bar_a(int)\r\n"
		"TRACE: 1: <- void foo_a(int)\r\n");
}
LT_END_TEST(TRACE_ARGS_test)