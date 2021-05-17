#include <nos/print.h>
#include <nos/fprint.h>

#include <doctest/doctest.h>

using namespace nos::argument_literal;

TEST_CASE("fprint")
{
	std::string output;
	nos::string_writer writer{output};
	nos::current_ostream = &writer;

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

	SUBCASE("format_string_view_arg")
	{
		std::string str = "hello";
		std::string out = nos::format("{}", std::string_view(str));
		CHECK_EQ(out, "hello");
	}
}
