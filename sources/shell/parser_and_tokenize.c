#include <minishell.h>

short	check_is_special2(char *str, int index)
{
	if (str[index] == PLUSTHAN)
	{
		if (str[index + 1] == str[index])
			return (REDIRECTION_APPEND);
		return (REDIRECTION_OUT);
	}
	else if (str[index] == LESSTHAN)
	{
		if (str[index + 1] == str[index])
			return (HEREDOC);
		return (REDIRECTION_IN);
	}
	else if (str[index] == BAR)
		return (PIPE);
	else if (str[index] == DQUOTE || str[index] == SQUOTE)
		return (QUOTE);
	else
		return (false);
}

void	filter_word(t_token **head, char *str, int index, int *limit)
{
	int	begin;

	begin = index - *limit;
	if (*limit > 0)
	{
		add_item_end(head, ft_substr(str, begin, *limit), WORD, 0);
		*limit = 0;
	}
}

void	filter_couple_special(t_token **head, char *str, int *index)
{
	short	condition;

	condition = check_is_special2(str, *index);
	if (condition == REDIRECTION_APPEND)
	{
		add_item_end(head, ft_substr(str, *index, 2), REDIRECTION_APPEND, false);
		*index = *index + 1;
	}
	else if (condition == HEREDOC)
	{
		add_item_end(head, ft_substr(str, *index, 2), HEREDOC, false);
		*index = *index + 1;
	}
}

void	filter_special(t_token **head, char *str, int index)
{
	short	condition;

	condition = check_is_special2(str, index);
	if (condition == REDIRECTION_IN)
		add_item_end(head, ft_substr(str, index, 1), REDIRECTION_IN, false);
	else if (condition == REDIRECTION_OUT)
		add_item_end(head, ft_substr(str, index, 1), REDIRECTION_OUT, false);
	else if (condition == PIPE)
		add_item_end(head, ft_substr(str, index, 1), PIPE, false);
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
			|| check_is_special2(str, index))
		{
			filter_word(head, str, index, &limit);
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
