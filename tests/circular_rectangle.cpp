#include <doctest/doctest.h>

#include <nos/print.h>
#include <nos/io/circular_rectangle_stream.h>

TEST_CASE("circular_rectangle_stream") 
{
	const int cols = 20;
	const int rows = 5;
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


	circbuf.print("\n");
	circbuf.print("\n");
	circbuf.print("\nmekek");

	CHECK_EQ(circbuf.get_string(4), "k                   ");
	CHECK_EQ(circbuf.get_string(3), "                    ");
	CHECK_EQ(circbuf.get_string(2), "                    ");
	CHECK_EQ(circbuf.get_string(1), "                    ");
	CHECK_EQ(circbuf.get_string(0), "mekek               ");

	CHECK_EQ(circbuf(0,0), 'm');
	CHECK_EQ(circbuf(0,4), 'k');
}
