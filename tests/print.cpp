#include <doctest/doctest.h>
#include <nos/io/string_writer.h>
#include <nos/print.h>

struct A
{
    int i = 42;
    int print_to(nos::ostream &os) const
    {
        return nos::print_to(os, i);
    };
};
struct B
{
    int i = 42;
};
struct C
{
    int i = 42;
};
struct D
{
    int i = 42;
};

int nos_print(nos::ostream &os, const B &b)
{
    return nos::print_to(os, b.i);
}
std::ostream &operator<<(std::ostream &os, const C &c)
{
    return os << c.i;
}
namespace nos
{
    template <> struct print_implementation<D>
    {
        static int print_to(nos::ostream &os, const D &d)
        {
            return nos::print_to(os, d.i);
        }
    };
}

TEST_CASE("fprint")
{
    std::string output;
    nos::string_writer writer{output};
    nos::current_ostream = &writer;

    SUBCASE("print")
    {
        nos::print("print");
        CHECK_EQ(output, "print");
    }

    SUBCASE("integer")
    {
        nos::print(88);
        CHECK_EQ(output, "88");
    }

    SUBCASE("number")
    {
        nos::print(0.88);
        CHECK_EQ(output[0], '0');
        CHECK_EQ(output[1], '.');
        CHECK_EQ(output[2], '8');
        CHECK_EQ(output[3], '8');
    }

    SUBCASE("method")
    {
        nos::print(A());
        CHECK_EQ(output, "42");
    }

    SUBCASE("nos_print_test")
    {
        nos::print(B());
        CHECK_EQ(output, "42");
    }

    SUBCASE("std_ostream")
    {
        nos::print(C());
        CHECK_EQ(output, "42");
    }

    SUBCASE("std_pair")
    {
        nos::print(std::make_pair(33, 55));
        CHECK_EQ(output, "{33,55}");
    }

    SUBCASE("print.numeric")
    {
        nos::print(std::numeric_limits<double>::max());
        nos::print(std::numeric_limits<double>::min());
        nos::print(std::numeric_limits<double>::lowest());

        nos::print(std::numeric_limits<float>::max());
        nos::print(std::numeric_limits<float>::min());
        nos::print(std::numeric_limits<float>::lowest());
    }

    SUBCASE("printhex")
    {
        nos::printhex(16);
        CHECK_EQ(output, "10");
    }
}
