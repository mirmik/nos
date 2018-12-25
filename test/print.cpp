#include <gtest/gtest.h>
#include <nos/print.h>

TEST(print, print) {
	testing::internal::CaptureStdout();
	nos::print("print");
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "print");
}

TEST(print, integer) {
	testing::internal::CaptureStdout();
	nos::print(88);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "88");
}

TEST(print, number) {
	testing::internal::CaptureStdout();
	nos::print(0.88);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "0.88000");
}