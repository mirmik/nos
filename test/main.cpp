#include "littletest.hpp"

LT_BEGIN_SUITE(igris_test_suite)
	void set_up()
	{}

	void tear_down()
	{}
LT_END_SUITE(igris_test_suite)

#include "trace.hpp"
#include "print.hpp"
#include "log.hpp"
#include "fprint.hpp"

LT_BEGIN_AUTO_TEST_ENV()
    AUTORUN_TESTS()
LT_END_AUTO_TEST_ENV()