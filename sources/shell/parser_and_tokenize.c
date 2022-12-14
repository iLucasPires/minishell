#include "minishell.h"

int	check_is_special(char letter, char next_letter)
{
	if (letter == PLUSTHAN)
	{
		if (next_letter == letter)
			return (REDIRECTION_APPEND);
		return (REDIRECTION_OUT);
	}
	else if (letter == LESSTHAN)
	{
		if (next_letter == letter)
			return (HEREDOC);
		return (REDIRECTION_IN);
	}
	else if (letter == BAR)
		return (PIPE);
	else
		return (false);
}

void	filter_word(t_token **head, char *str, int *i, int *limit)
{
	if (*limit > 0)
	{
		add_item_end(head, ft_substr(str, *i - *limit, *limit), WORD);
		*limit = 0;
	}
}

void	filter_couple_special(t_token **head, char *str, int *index)
{
	short	condition;

	condition = check_is_special(str[*index], str[*index + 1]);
	if (condition == REDIRECTION_APPEND)
	{
		add_item_end(head, ft_substr(str, *index, 2), REDIRECTION_APPEND);
		*index = *index + 1;
	}
	else if (condition == HEREDOC)
	{
		add_item_end(head, ft_substr(str, *index, 2), HEREDOC);
		*index = *index + 1;
	}
}

void	filter_special(t_token **head, char *str, int index)
{
	short	condition;

	condition = check_is_special(str[index], str[index + 1]);
	if (condition == REDIRECTION_IN)
		add_item_end(head, ft_substr(str, index, 1), REDIRECTION_IN);
	else if (condition == REDIRECTION_OUT)
		add_item_end(head, ft_substr(str, index, 1), REDIRECTION_OUT);
	else if (condition == PIPE)
		add_item_end(head, ft_substr(str, index, 1), PIPE);
}

void	parser_and_tokenize(char *str, t_token **head)
{
	int index;
	int limit;
	short check_quote;

	index = 0;
	limit = 0;
	check_quote = true;
	while (true)
	{
		if (str[index] == DQUOTE || str[index] == SQUOTE)
			check_quote = !check_quote;
		if (((str[index] == SPACE || str[index] == NULL_CHAR) && check_quote)
			|| check_is_special(str[index], str[index + 1]))
		{
			filter_word(head, str, &index, &limit);
			filter_special(head, str, index);
			filter_couple_special(head, str, &index);
		}
		else
			limit = limit + 1;
		if (str[index] == NULL_CHAR)
			break ;
		index = index + 1;
	}
}