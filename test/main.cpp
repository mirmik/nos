#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#define LT_END_TEST(a)
#define LT_BEGIN_TEST(a,b) TEST_CASE(#b)

#include <nos/print.h>
#include <nos/io/string_writer.h>
#include <unistd.h>
#include <string>

std::string output;
nos::string_writer writer{output};

#include "trace.hpp"
#include "print.hpp"
#include "log.hpp"
#include "fprint.hpp"
