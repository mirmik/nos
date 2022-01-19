#include <nos/shell/argv.h>
#include <nos/shell/executor.h>
#include <nos/shell/aggregate_executor.h>
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
	CHECK_EQ(argv[1], "a");
	CHECK_EQ(argv.size(), 2);
	return 0;
}

int af(const nos::argv& argv, nos::ostream& os) 
{
	os.print("a");
	return 0;
}

int bf(const nos::argv& argv, nos::ostream& os) 
{
	os.print("b");
	return 0;
}

int cf(const nos::argv& argv, nos::ostream& os) 
{
	os.print("c");
	return 0;
}

int df(const nos::argv& argv, nos::ostream& os) 
{
	os.print("d");
	return 0;
}

TEST_CASE("tokens") 
{
	char * cmd = strdup("hello a");
	auto tokens = nos::tokens(cmd);
	CHECK_EQ(tokens[0], "hello");
	CHECK_EQ(tokens[1], "a");
	free(cmd);
}

TEST_CASE("executor") 
{
	char * cmd = strdup("hello a");
	nos::string_buffer answer;

	nos::executor executor({
		{ "hello", "help example", hello }
	});

	auto tokens = nos::tokens(cmd);
	auto argv = nos::argv(tokens);
	CHECK_EQ(tokens.size(), 2);
	CHECK_EQ(argv.size(), 2);

	executor.execute(tokens, answer);
	CHECK_EQ(answer.str(), "lalala");
	free(cmd);
}


TEST_CASE("aggregate_executor") 
{
	nos::string_buffer answer;

	nos::executor abexecutor({
		{ "af", "", af },
		{ "bf", "", bf },
	});

	nos::executor cdexecutor({
		{ "cf", "", cf },
		{ "df", "", df },
	});

	nos::aggregate_executor executor({ &abexecutor, &cdexecutor });

	executor.execute("af", answer);
	CHECK_EQ(answer.str(), "a");

	executor.execute("bf", answer);
	CHECK_EQ(answer.str(), "ab");

	executor.execute("cf", answer);
	CHECK_EQ(answer.str(), "abc");

	executor.execute("df", answer);
	CHECK_EQ(answer.str(), "abcd");
}