#include <nos/print.h>

struct A { int i = 42; ssize_t print_to(nos::ostream& os) const { return os.print(i); }; };
struct B { int i = 42; };
struct C { int i = 42; };
struct D { int i = 42; };

ssize_t nos_print(nos::ostream& os, const B& b) { return os.print(b.i); };
std::ostream& operator << (std::ostream& os, const C& c) { return os << c.i; };
namespace nos { template <> struct print_implementation<D> { static ssize_t print_to(nos::ostream& out, const D& d) { return out.print(d.i); } }; }

LT_BEGIN_TEST(nos_test_suite, print) {
	nos::print("print");
	LT_CHECK_EQ(output, "print");
}
LT_END_TEST(print)

LT_BEGIN_TEST(nos_test_suite, integer) {
	nos::print(88);
	LT_CHECK_EQ(output, "88");
}
LT_END_TEST(integer)

LT_BEGIN_TEST(nos_test_suite, number) {
	nos::print(0.88);
	//LT_CHECK_EQ(output, "0.88");
	LT_CHECK_EQ(output, "0.88000");
	//TODO
}
LT_END_TEST(number)

LT_BEGIN_TEST(nos_test_suite, method) {
	nos::print(A());
	LT_CHECK_EQ(output, "42");
}
LT_END_TEST(method)

LT_BEGIN_TEST(nos_test_suite, nos_print_test) {
	nos::print(B());
	LT_CHECK_EQ(output, "42");
}
LT_END_TEST(nos_print_test)

LT_BEGIN_TEST(nos_test_suite, std_ostream) {
	nos::print(C());
	LT_CHECK_EQ(output, "42");
}
LT_END_TEST(std_ostream)

LT_BEGIN_TEST(nos_test_suite, std_pair) {
	nos::print(std::make_pair(33,55));
	LT_CHECK_EQ(output, "{33,55}");
}
LT_END_TEST(std_pair)
