#include "../test.h"

t_token *create_list_token(char *value, int type)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    new->value = value;
    new->type = type;
    new->next = NULL;
    return (new);
}

void add_token_end(t_token **head, char *value, int type)
{
    t_token *temp_token;

    if (!*head)
        *head = create_list_token(value, type);
    else
    {
        temp_token = *head;
        while (temp_token->next)
            temp_token = temp_token->next;
        temp_token->next = create_list_token(value, type);
    }
}

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

void print_token(t_token *head)
{
    t_token *temp_token;

    temp_token = head;
    while (temp_token)
    {
        printf("value: %s\n", temp_token->value);
        temp_token = temp_token->next;
    }
}

// if (is_space_or_null(str[index]) && !is_redirection(str[index - 1]))
void make_token(char *str, t_token **head)
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
        if ((is_space_or_null(str[index]) && check_quote) || is_redirection(str[index]))
        {
            if (count > 0)
            {
                value = ft_substr(str, index - count, count);
                add_token_end(head, value, WORD);
                count = 0;
            }
            if (is_redirection(str[index]))
            {
                if (is_couple_redirection(str[index], str[index + 1]))
                {
                    value = ft_substr(str, index, 2);
                    add_token_end(head, value, COUPLE_REDIRECTION);
                    index++;
                }
                else
                {
                    value = ft_substr(str, index, 1);
                    add_token_end(head, value, REDIRECTION);
                }
            }
        }
        else
            count++;
        index++;
    }
}

void test_make_token(void)
{
    char *str;
    t_token *token;

    token = NULL;
    str = ft_strdup("ls > < $dsad-l >>test file\"    \" ");
    make_token(str, &token);
    print_token(token);
}