#include <nos/print.h>
#include <nos/fprint.h>

#include <doctest/doctest.h>

struct A { int i = 42; int print_to(nos::ostream& os) const { return os.print(i); }; };
struct B
{
	int i = 42;

	template <class Out>
	int print_to(Out& os) const
	{
		return os.print(i);
	}
};

struct C
{
	int i = 42;

	template <class Out>
	size_t print_to(Out& os) const
	{
		return os.print(i);
	}
};

using namespace nos::argument_literal;

TEST_CASE("fprint")
{
	std::string output;
	nos::string_writer writer{output};
	nos::current_ostream = &writer;

	SUBCASE("fprint(A)")
	{
		nos::fprint("{}", A());
		CHECK_EQ(output, "42");
	}
	
	SUBCASE("fprint(B)")
	{
		nos::fprint("{}", B());
		CHECK_EQ(output, "42");
	}

	SUBCASE("fprint(C)")
	{
		nos::fprint("{}", C());
		CHECK_EQ(output, "42");
	}

	SUBCASE("fprint")
	{
		nos::fprint("fprint {} {} {}", "aaa", "bbb", "ccc");
		CHECK_EQ(output, "fprint aaa bbb ccc");
	}

	SUBCASE("fprint_integer")
	{
		nos::fprint("integer({})", 42);
		CHECK_EQ(output, "integer(42)");
	}

	SUBCASE("fprint_named")
	{
		nos::fprint("fprint {a} {b} {c}", "a"_a = "aaa", "b"_a = "bbb", "c"_a = "ccc");
		CHECK_EQ(output, "fprint aaa bbb ccc");
	}

	SUBCASE("fprint_named_and_numers1")
	{
		nos::fprint("fprint {b} {2} {0}", "a"_a = "aaa", "b"_a = "bbb", "c"_a = "ccc");
		CHECK_EQ(output, "fprint bbb ccc aaa");
	}

	SUBCASE("fprint_named_and_numers3")
	{
		nos::fprint("fprint {a1}", "a1"_a = "aaa");
		CHECK_EQ(output, "fprint aaa");
	}

	SUBCASE("fprint_zero_size_arglist")
	{
		nos::fprint("zerosize");
		CHECK_EQ(output, "zerosize");
	}

	SUBCASE("fprint_named_and_numers2")
	{
		nos::fprint("fprint {a1} {b2}", "a1"_a = "aaa", "b2"_a = "bbb");
		CHECK_EQ(output, "fprint aaa bbb");
	}

	SUBCASE("format_named_and_numers2")
	{
		auto str = nos::format("fprint {a1} {b2}", "a1"_a = "aaa", "b2"_a = "bbb");
		CHECK_EQ(str, "fprint aaa bbb");
	}

	SUBCASE("fprint_longstring")
	{
		nos::fprint("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
		CHECK_EQ(output, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
	}

	SUBCASE("format")
	{
		std::string out = nos::format("format {} {} {}", "aaa", "bbb", "ccc");
		CHECK_EQ(out, "format aaa bbb ccc");
	}


	SUBCASE("format cmd")
	{
		auto cmd = nos::format("cnc G01 {poses} {speed} {accel}",
		                       "poses"_a = "Hello", "speed"_a = "World", "accel"_a = "!");
		CHECK_EQ(cmd, "cnc G01 Hello World !");
	}


	SUBCASE("format_nan")
	{
		std::string out = nos::format("{}", std::nan(""));
		CHECK_EQ(out, "nan");
	}

	SUBCASE("format_nanf")
	{
		std::string out = nos::format("{}", std::nanf(""));
		CHECK_EQ(out, "nan");
	}

	SUBCASE("format_string_arg")
	{
		std::string out = nos::format("{}", std::string("hello"));
		CHECK_EQ(out, "hello");
	}

#if __has_include(<string_view>)
	SUBCASE("format_string_view_arg")
	{
		std::string str = "hello";
		std::string out = nos::format("{}", std::string_view(str));
		CHECK_EQ(out, "hello");
	}
#endif
}
