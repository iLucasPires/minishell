#include <test.h>
#include <minishell.h>

char **lexer_line(char *line)
{
    char **tokens;
    

    tokens = ft_split(line, ' ');
    return (tokens);
}

void test_lexer(void)
{
    char string[] = "ls -l -a ..";
    char **expected = {"ls", "-l", "-a", ".."};

    char **tokens = lexer(string);

    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 4);
}