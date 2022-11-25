#include <test.h>

int counter_string(char *str)
{
  int count = 0;
  int index = 0;

  while (str[index])
  {
    if (str[index] == '>' || str[index] == '<' || str[index] == '|')
      count += 2;
    count++;
    index++;
  }
  return (count);
}

char *add_spaces(char *str)
{
  char *new_str;
  int index;
  int new_index;

  index = 0;
  new_index = 0;
  new_str = malloc(sizeof(char) * counter_string(str) + 1);
  while (str[index] != '\0')
  {
    if (str[index] == '>' || str[index] == '<' || str[index] == '|')
    {
      if (str[index + 1] == '>' || str[index + 1] == '<' || str[index + 1] == '|')
      {
        new_str[new_index++] = INVISIBLE_CHAR;
        new_str[new_index++] = str[index];
        new_str[new_index++] = str[index++ + 1];
        new_str[new_index++] = INVISIBLE_CHAR;
      }
      else
      {
        new_str[new_index++] = INVISIBLE_CHAR;
        new_str[new_index++] = str[index];
        new_str[new_index++] = INVISIBLE_CHAR;
      }
    }
    else
      new_str[new_index++] = str[index];
    index++;
  }
  new_str[new_index] = '\0';
  return (new_str);
}

void mapping_space(char *line)
{
  int index = 0;
  int active_quote = true;

  while (line[index])
  {
    if (line[index] == '\'' || line[index] == '\"')
      active_quote = !active_quote;
    else if (line[index] == ' ' && active_quote)
      line[index] = INVISIBLE_CHAR;
    index++;
  }
}

char **lexer(char *line)
{
  int index;
  char *temp;
  char **tokens;
  
  index = 0;
  temp = add_spaces(line);
  mapping_space(temp);
  tokens = ft_split(temp, INVISIBLE_CHAR);
  while (tokens[index])
  {
    tokens[index] = ft_strtrim(tokens[index], "\"");
    tokens[index] = ft_strtrim(tokens[index], "\'");
    index++;
  }

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
  TEST_ASSERT_EQUAL_STRING("   ", args[5]);
  TEST_ASSERT_EQUAL_STRING("|", args[6]);
  TEST_ASSERT_EQUAL_STRING("tr", args[7]);
  TEST_ASSERT_EQUAL_STRING(" ", args[8]);
  TEST_ASSERT_EQUAL_STRING("x", args[9]);
  TEST_ASSERT_EQUAL_STRING(">", args[10]);
  TEST_ASSERT_EQUAL_STRING("outfile", args[11]);
}


void test_lexer(void)
{
  // RUN_TEST(test_token_simple);
  // RUN_TEST(test_token_simple_pipe);
  // RUN_TEST(test_token_simple_command);
  // RUN_TEST(test_token_simple_quote);
  // RUN_TEST(test_token_simple_quote2);
  // RUN_TEST(test_token_double_quote);
  // RUN_TEST(test_token_mix_quote);

  RUN_TEST(test_token_space);
}
