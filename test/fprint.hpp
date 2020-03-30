#include <nos/print.h>
#include <nos/fprint.h>

using namespace nos::argument_literal;

LT_BEGIN_TEST(nos_test_suite, fprint) {
	nos::fprint("fprint {} {} {}", "aaa", "bbb", "ccc");
	LT_CHECK_EQ(output, "fprint aaa bbb ccc");
}
LT_END_TEST(fprint)


LT_BEGIN_TEST(nos_test_suite, fprint_integer) {
	nos::fprint("integer({})", 42);
	LT_CHECK_EQ(output, "integer(42)");
}
LT_END_TEST(fprint_integer)


LT_BEGIN_TEST(nos_test_suite, fprint_named) {
	nos::fprint("fprint {a} {b} {c}", "a"_a="aaa", "b"_a="bbb", "c"_a="ccc");
	LT_CHECK_EQ(output, "fprint aaa bbb ccc");
}
LT_END_TEST(fprint_named)


LT_BEGIN_TEST(nos_test_suite, fprint_named_and_numers) {
	nos::fprint("fprint {b} {2} {0}", "a"_a="aaa", "b"_a="bbb", "c"_a="ccc");
	LT_CHECK_EQ(output, "fprint bbb ccc aaa");
}
LT_END_TEST(fprint_named_and_numers)


LT_BEGIN_TEST(nos_test_suite, fprint_zero_size_arglist) {
	nos::fprint("zerosize");
	LT_CHECK_EQ(output, "zerosize");
}
LT_END_TEST(fprint_zero_size_arglist)


LT_BEGIN_TEST(nos_test_suite, fprint_longstring) {
	nos::fprint("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
	LT_CHECK_EQ(output, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
}
LT_END_TEST(fprint_longstring)


LT_BEGIN_TEST(nos_test_suite, format) {
	std::string out = nos::format("format {} {} {}", "aaa", "bbb", "ccc");
	LT_CHECK_EQ(out, "format aaa bbb ccc");
}
LT_END_TEST(format)


LT_BEGIN_TEST(nos_test_suite, format_nan) {
	std::string out = nos::format("{}", std::nan(""));
	LT_CHECK_EQ(out, "nan");
}
LT_END_TEST(format_nan)


LT_BEGIN_TEST(nos_test_suite, format_nanf) {
	std::string out = nos::format("{}", std::nanf(""));
	LT_CHECK_EQ(out, "nan");
}
LT_END_TEST(format_nanf)
