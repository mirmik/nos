#include "littletest.hpp"

#include <nos/print.h>
#include <nos/io/string_writer.h>
#include <unistd.h>
#include <string>

/*class stdout_capture
{
	int p[2];

	int& pipe_in = p[0];
	int& pipe_out = p[1];
	int raw;

public:
	stdout_capture() 
	{
		pipe(p);

		PRINT(pipe_in);
		PRINT(pipe_out);

		raw = dup(STDOUT_FILENO);
		PRINT(raw);
		dup2(pipe_in, STDOUT_FILENO);
	}

	std::string get() 
	{
		char buf[512];
		
		int sts = read(pipe_out, buf, 512);
		if (sts <= 0)
		{
			throw std::runtime_error("capture: read error");
		}

		dup2(raw, STDOUT_FILENO);
		close(raw);
		close(pipe_in);
		close(pipe_out);
		
		nos::println(sts);
		return buf;
	}
};*/

std::string output;

LT_BEGIN_SUITE(nos_test_suite)
	nos::string_writer writer{output};

	void set_up()
	{
		nos::current_ostream = &writer;
	}

	void tear_down()
	{
		output.clear();
	}
LT_END_SUITE(nos_test_suite)

#include "trace.hpp"
#include "print.hpp"
#include "log.hpp"
#include "fprint.hpp"

LT_BEGIN_AUTO_TEST_ENV()
    AUTORUN_TESTS()
LT_END_AUTO_TEST_ENV()