#include <doctest/doctest.h>

#include <nos/print.h>
#include <nos/io/circular_rectangle_stream.h>

TEST_CASE("circular_rectangle_stream") 
{
	const int cols = 20;
	const int rows = 30;
	char buf[cols * rows];

	nos::circular_textframe circbuf(cols, rows, buf);	

	circbuf.print("HelloWorld");
	circbuf.print("HelloMirmik");

	CHECK_EQ(circbuf.get_string(1), "HelloWorldHelloMirmi");
	CHECK_EQ(circbuf.get_string(0), "k                   ");

	circbuf.print("\n");

	CHECK_EQ(circbuf.get_string(2), "HelloWorldHelloMirmi");
	CHECK_EQ(circbuf.get_string(1), "k                   ");
	CHECK_EQ(circbuf.get_string(0), "                    ");
}
