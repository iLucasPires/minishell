#include "../test.h"

int is_redirection(char letter)
{
    if (letter == PLUSTHAN || letter == LESSTHAN)
        return (true);
    return (false);
}

int is_couple_redirection(char letter, char next_letter)
{
    if (letter == PLUSTHAN || letter == LESSTHAN)
        if (letter == next_letter)
            return (true);
    return (false);
}

int is_space_or_null(char letter)
{
    if (letter == SPACE || !letter)
        return (true);
    return (false);
}
// if (is_space_or_null(str[index]) && !is_redirection(str[index - 1]))
void make_token(char *str)
{
    char *value = NULL;
    int index = 0;
    int count = 0;
    int check_quote = true;

    while (str[index] == ' ')
    {
        index++;
        count++;
    }
    while (str[index])
    {
        if (str[index] == DQUOTE || str[index] == SQUOTE)
            check_quote = !check_quote;
        if (is_space_or_null(str[index]) && check_quote)
        {
            value = ft_substr(str, count, index - count + 1);
            printf("Check 1:%s\n", value);
            count = index + 1;
            index++;
        }
        else if (is_redirection(str[index]) && is_couple_redirection(str[index], str[index + 1]))
        {
            value = ft_substr(str, count, index - count + 2);
            printf("Check 2:%s\n", value);
            if (str[index + 2] == SPACE)
                index = index + 3;
            else
                index = index + 2;
            count = index;
        }
        else if (is_redirection(str[index + 1]) && (!is_couple_redirection(str[index + 1], str[index + 2]) || is_couple_redirection(str[index + 1], str[index + 2])))
        {
            value = ft_substr(str, count, index - count + 1);
            printf("Check 3:%s\n", value);
            count = index + 1;
            index++;
        }
        else if (is_redirection(str[index]) && !is_space_or_null(str[index + 1]))
        {
            value = ft_substr(str, count, index - count + 1);
            printf("Check 4:%s\n", value);
            count = index + 1;
            index++;
        }
        else
        {
            index++;
        }
    }
}

void test_make_token(void)
{
    char *str;

    str = ft_strdup("ls >< dsad-l >> test file'    ' ");
    make_token(str);
}