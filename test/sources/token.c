#include "../test.h"

void make_token(char *str)
{
    char *value = NULL;
    int index = 0;
    int count = 0;

    while (str[index] == ' ')
    {
        index++;
        count++;
    }
    while (str[index])
    {
        if (str[index] == SPACE || !str[index])
        {
            value = ft_substr(str, count, index - count + 1);
            printf("Check 1:%s\n", value);
            count = index + 1;
            index++;
        }
        else if ((str[index] == PLUSTHAN || str[index] == LESSTHAN) && (str[index + 1] == str[index]))
        {
            value = ft_substr(str, count, index - count + 2);
            printf("Check 2:%s\n", value);
            if (str[index + 2] == SPACE)
                index = index + 3;
            else
                index = index + 2;
            count = index;
        }
        else if ((str[index + 1] == PLUSTHAN || str[index + 1] == LESSTHAN) && ((str[index + 2] != str[index + 1]) || (str[index + 2] == str[index + 1])))
        {
            value = ft_substr(str, count, index - count + 1);
            printf("Check 3:%s\n", value);
            count = index + 1;
            index++;
        }
        else if ((str[index] == PLUSTHAN || str[index] == LESSTHAN) && str[index + 1] != SPACE)
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

    str = ft_strdup("ls>dsad-l>>test file'    ' ");
    make_token(str);
}