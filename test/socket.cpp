#include <doctest/doctest.h>
#include <nos/inet/socket.h>

TEST_CASE("socket") 
{
	nos::inet::socket a(22);
	nos::inet::socket b(22);

	CHECK_EQ(a, b);
}