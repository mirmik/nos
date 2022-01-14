#include <nos/shell/argv.h>
#include <nos/shell/executor.h>
#include <nos/io/string_writer.h>
#include <doctest/doctest.h>

TEST_CASE("shell") 
{
	char * cmd = strdup("hello world shell  \t\n jigly");
	nos::tokens argv(cmd);

	CHECK_EQ(argv[0], "hello");
	CHECK_EQ(argv[1], "world");
	CHECK_EQ(argv[2], "shell");
	CHECK_EQ(argv[3], "jigly");

	free(cmd);
}

int hello(const nos::argv& argv, nos::ostream& os) 
{
	os.print("lalala");
	CHECK_EQ(argv[0], "a");
	CHECK_EQ(argv.size(), 1);
	return 0;
}

TEST_CASE("executor") 
{
	char * cmd = strdup("hello a");
	nos::string_buffer answer;

	nos::executor executor({
		{ "hello", "help example", hello }
	});

	executor.execute(cmd, answer);
	CHECK_EQ(answer.str(), "lalala");
}