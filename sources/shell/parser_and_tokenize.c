#include <minishell.h>

int check_is_state(char *str, int index)
{
	if (str[index] == PLUSTHAN)
	{
		if (str[index + 1] == PLUSTHAN)
			return (REDIRECTION_APPEND);
		return (REDIRECTION_OUT);
	}
	else if (str[index] == LESSTHAN)
	{
		if (str[index + 1] == LESSTHAN)
			return (REDIRECTION_IN);
		return (REDIRECTION_IN);
	}
	else if (str[index] == BAR)
		return (PIPE);
	else
		return (0);
}

int check_is_space(char *str, int index)
{
	if (str[index] == SPACE || str[index] == NULL_CHAR)
		return (true);
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
	int	condition;

	condition = check_is_state(str, *index);
	if (condition == REDIRECTION_APPEND)
	{
		add_item_end(head, ft_substr(str, *index, 2), REDIRECTION_APPEND,
				false);
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
	int	condition;

	condition = check_is_state(str, index);
	if (condition == REDIRECTION_IN)
		add_item_end(head, ft_substr(str, index, 1), REDIRECTION_IN, false);
	else if (condition == REDIRECTION_OUT)
		add_item_end(head, ft_substr(str, index, 1), REDIRECTION_OUT, false);
	else if (condition == PIPE)
		add_item_end(head, ft_substr(str, index, 1), PIPE, false);
}

void	finite_state_machine(char *str, t_token **head)
{
	t_fsmachine	var;

	var.index = 0;
	var.limit = 0;
	var.check_quote = false;
	var.quote_type = 0;
	while (true)
	{
		if (str[var.index] == DQUOTE || str[var.index] == SQUOTE)
		{
			if (var.check_quote && str[var.index] == var.quote_type) {
				var.check_quote = false;
			}
			else if (!var.check_quote) {
				var.check_quote = true;
				var.quote_type = str[var.index];
			}
		}
		if (!var.check_quote && (check_is_space(str, var.index) || check_is_state(str, var.index)))
		{
			filter_word(head, str, var.index, &var.limit);
			filter_special(head, str, var.index);
			filter_couple_special(head, str, &var.index);
		}
		else
    		var.limit++;
		if (str[var.index] == NULL_CHAR)
			break ;
		var.index = var.index + 1;
	}
}

