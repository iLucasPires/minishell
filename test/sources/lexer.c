#include <test.h>

void mapping_space(char *line)
{
	int index = 0;
	int active_quote = true;

	while (line[index])
	{
		if (line[index] == '\'')
			active_quote = !active_quote;
		else if (line[index] == ' ' && active_quote)
			line[index] = INVISIBLE_CHAR;
		index++;
	}
}

char **lexer(char *line)
{ 
	
	mapping_space(line);
	char **args = ft_split(line, INVISIBLE_CHAR);
	for (int index = 0; args[index]; index++)
	{
		args[index] = ft_strtrim(args[index], "'");
		args[index] = ft_strtrim(args[index], "\"");
	}

	return (args);
}

void test_token_simple(void)
{
	char line[] = "ls -la ..";
	char **args = lexer(line);

	TEST_ASSERT_EQUAL_STRING("ls", args[0]);
	TEST_ASSERT_EQUAL_STRING("-la", args[1]);
	TEST_ASSERT_EQUAL_STRING("..", args[2]);
	TEST_ASSERT_NULL(args[3]);
}

void test_token_simple_pipe(void)
{
	char line[] = "ls -la .. | cat -e | wc -l";
	char **args = lexer(line);

	TEST_ASSERT_EQUAL_STRING("ls", args[0]);
	TEST_ASSERT_EQUAL_STRING("-la", args[1]);
	TEST_ASSERT_EQUAL_STRING("..", args[2]);
	TEST_ASSERT_EQUAL_STRING("|", args[3]);
	TEST_ASSERT_EQUAL_STRING("cat", args[4]);
	TEST_ASSERT_EQUAL_STRING("-e", args[5]);
	TEST_ASSERT_EQUAL_STRING("|", args[6]);
	TEST_ASSERT_EQUAL_STRING("wc", args[7]);
	TEST_ASSERT_EQUAL_STRING("-l", args[8]);
	TEST_ASSERT_NULL(args[9]);
}

void test_token_simple_command(void)
{
	char line[] = "export MAKE_PATH=./libs/libft ; cd .. ; ls && make -C $MAKE_PATH ; ./minshell";

	char **args = lexer(line);

	TEST_ASSERT_EQUAL_STRING("export", args[0]);
	TEST_ASSERT_EQUAL_STRING("MAKE_PATH=./libs/libft", args[1]);
	TEST_ASSERT_EQUAL_STRING(";", args[2]);
	TEST_ASSERT_EQUAL_STRING("cd", args[3]);
	TEST_ASSERT_EQUAL_STRING("..", args[4]);
	TEST_ASSERT_EQUAL_STRING(";", args[5]);
	TEST_ASSERT_EQUAL_STRING("ls", args[6]);
	TEST_ASSERT_EQUAL_STRING("&&", args[7]);
	TEST_ASSERT_EQUAL_STRING("make", args[8]);
	TEST_ASSERT_EQUAL_STRING("-C", args[9]);
	TEST_ASSERT_EQUAL_STRING("$MAKE_PATH", args[10]);
	TEST_ASSERT_EQUAL_STRING(";", args[11]);
	TEST_ASSERT_EQUAL_STRING("./minshell", args[12]);
}

void test_token_simple_quote(void)
{
	char line[] = "infile < tr a '   ' |   tr ' ' x > outfile";
	char **args = lexer(line);

	TEST_ASSERT_EQUAL_STRING("infile", args[0]);
	TEST_ASSERT_EQUAL_STRING("<", args[1]);
	TEST_ASSERT_EQUAL_STRING("tr", args[2]);
	TEST_ASSERT_EQUAL_STRING("a", args[3]);
	TEST_ASSERT_EQUAL_STRING("   ", args[4]);
	TEST_ASSERT_EQUAL_STRING("|", args[5]);
	TEST_ASSERT_EQUAL_STRING("tr", args[6]);
	TEST_ASSERT_EQUAL_STRING(" ", args[7]);
	TEST_ASSERT_EQUAL_STRING("x", args[8]);
	TEST_ASSERT_EQUAL_STRING(">", args[9]);
	TEST_ASSERT_EQUAL_STRING("outfile", args[10]);
}

void test_token_simple_quote2(void)
{
	char line[] = ".gitignore < tr ex ' X' | tr pi 'P ' > outfile";
	char **args = lexer(line);

	TEST_ASSERT_EQUAL_STRING(".gitignore", args[0]);
	TEST_ASSERT_EQUAL_STRING("<", args[1]);
	TEST_ASSERT_EQUAL_STRING("tr", args[2]);
	TEST_ASSERT_EQUAL_STRING("ex", args[3]);
	TEST_ASSERT_EQUAL_STRING(" X", args[4]);
	TEST_ASSERT_EQUAL_STRING("|", args[5]);
	TEST_ASSERT_EQUAL_STRING("tr", args[6]);
	TEST_ASSERT_EQUAL_STRING("pi", args[7]);
	TEST_ASSERT_EQUAL_STRING("P ", args[8]);
	TEST_ASSERT_EQUAL_STRING(">", args[9]);
	TEST_ASSERT_EQUAL_STRING("outfile", args[10]);
}

void test_token_double_quote(void)
{
	char line[] = "infile < tr a \"   \" |   tr \" \" x > outfile";
	char **args = lexer(line);

	TEST_ASSERT_EQUAL_STRING("infile", args[0]);
	TEST_ASSERT_EQUAL_STRING("<", args[1]);
	TEST_ASSERT_EQUAL_STRING("tr", args[2]);
	TEST_ASSERT_EQUAL_STRING("a", args[3]);
	TEST_ASSERT_EQUAL_STRING("   ", args[4]);
	TEST_ASSERT_EQUAL_STRING("|", args[5]);
	TEST_ASSERT_EQUAL_STRING("tr", args[6]);
	TEST_ASSERT_EQUAL_STRING(" ", args[7]);
	TEST_ASSERT_EQUAL_STRING("x", args[8]);
	TEST_ASSERT_EQUAL_STRING(">", args[9]);
	TEST_ASSERT_EQUAL_STRING("outfile", args[10]);
}

void test_lexer(void)
{	
	RUN_TEST(test_token_simple);
	RUN_TEST(test_token_simple_pipe);
	RUN_TEST(test_token_simple_command);
	RUN_TEST(test_token_simple_quote);
	RUN_TEST(test_token_simple_quote2);
}


