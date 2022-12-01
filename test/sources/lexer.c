#include <test.h>

int ft_is_special(char c)
{
  if (c == '>' || c == '<' || c == '|')
    return (1);
  return (0);
}

int counter_special(char *str)
{
  int i;
  int count;

  i = 0;
  count = 0;
  while (str[i])
  {
    if (ft_is_special(str[i]))
      count++;
    i++;
  }
  return (count);
}

char *add_spaces(char *line)
{
  int index;
  int size_string;
  int new_index;
  char *new_line;

  index = 0;
  new_index = 0;
  size_string = ft_strlen(line) + counter_special(line);
  new_line = calloc(sizeof(char), size_string);
  while (line[index] != '\0')
  {
    if (ft_is_special(line[index]))
    {
      new_line[new_index++] = INVISIBLE_CHAR;
      new_line[new_index++] = line[index];
      if (ft_is_special(line[index + 1]))
        new_line[new_index++] = line[++index];
      new_line[new_index++] = INVISIBLE_CHAR;
    }
    else
      new_line[new_index++] = line[index];
    index++;
  }
  new_line[new_index] = '\0';
  return (new_line);
}

char *mapping_space(char *line)
{
  int index = 0;
  int active_quote;
  char *new_line;

  active_quote = true;
  new_line = add_spaces(line);
  while (new_line[index])
  {
    if (new_line[index] == '\'')
			active_quote = !active_quote;
		else if (new_line[index] == ' ' && active_quote)
			new_line[index] = INVISIBLE_CHAR;
		index++;
  }
  return (new_line);
}

char **lexer(char *line)
{
  char *new_line;
  char **tokens;

  new_line = mapping_space(line);
  tokens = ft_split(new_line, INVISIBLE_CHAR);
  free(new_line);
  return (tokens);
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

void test_token_mix_quote(void)
{
  char line[] = "infile   < tr a \"   \" |   tr \' \' x > outfile";
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

void test_token_space(void)
{
  char line[] = "infile<<< tr a \"   \" |   tr \' \' x > outfile";
  char **args = lexer(line);

  TEST_ASSERT_EQUAL_STRING("infile", args[0]);
  TEST_ASSERT_EQUAL_STRING("<<", args[1]);
  TEST_ASSERT_EQUAL_STRING("<", args[2]);
  TEST_ASSERT_EQUAL_STRING("tr", args[3]);
  TEST_ASSERT_EQUAL_STRING("a", args[4]);
  TEST_ASSERT_EQUAL_STRING(" ", args[5]);
  TEST_ASSERT_EQUAL_STRING("|", args[6]);
  TEST_ASSERT_EQUAL_STRING("tr", args[7]);
  TEST_ASSERT_EQUAL_STRING(" ", args[8]);
  TEST_ASSERT_EQUAL_STRING("x", args[9]);
  TEST_ASSERT_EQUAL_STRING(">", args[10]);
  TEST_ASSERT_EQUAL_STRING("outfile", args[11]);
}

void test_lexer(void)
{
  RUN_TEST(test_token_simple);
  RUN_TEST(test_token_simple_pipe);
  RUN_TEST(test_token_simple_command);
  RUN_TEST(test_token_simple_quote);
  RUN_TEST(test_token_simple_quote2);
  RUN_TEST(test_token_double_quote);
  RUN_TEST(test_token_mix_quote);
  RUN_TEST(test_token_space);
}
