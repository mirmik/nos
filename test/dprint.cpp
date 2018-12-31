#include <gtest/gtest.h>
#include <nos/dprint.h>

TEST(dprint, dpr) {
	testing::internal::CaptureStdout();
	dpr("HelloWorld");
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "HelloWorld");
}

TEST(dprint, dpr_integer) {
	testing::internal::CaptureStdout();
	dpr(42);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "42");
}

TEST(dprint, dpr_multi) {
	testing::internal::CaptureStdout();
	dpr("Hello", "World", 42);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Hello World 42");
}