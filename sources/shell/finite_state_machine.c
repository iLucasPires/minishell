#include <minishell.h>

void	handle_dollar(t_fsmachine *var)
{
	int		index;
	int		limit;
	char	*string;

	index = 1;
	limit = 0;
	while (true)
	{
		if (var->temp[index] == DOLLAR || var->temp[index] == NULL_CHAR)
		{
			string = ft_substr(var->temp, limit + 1, index - 1);
			add_item_end(var->head, getenv(string), EXPAND);
			limit = index;
			free(string);
		}
		if (var->temp[index] == NULL_CHAR)
			break ;
		index = index + 1;
	}
}

void hadle_dollar_quote(t_fsmachine *var)
{
	int		index;
	int		limit;
	char	*string;

	index = 1;
	limit = 0;
	while (true)
	{
		if (var->temp[index] == DOLLAR || var->temp[index] == NULL_CHAR)
		{
			string = ft_substr(var->temp, limit + 1, index - 1);
			add_item_end(var->head, getenv(string), EXPAND);
			limit = index;
			free(string);
		}
		if (var->temp[index] == NULL_CHAR)
			break ;
		index = index + 1;
	}
}

char	*identified_type(int identifier)
{
	if (identifier == RED_IN)
		return (">");
	if (identifier == RED_OUT)
		return ("<");
	if (identifier == PIPE)
		return ("|");
	if (identifier == RED_APPEND)
		return (">>");
	if (identifier == HEREDOC)
		return ("<<");
	return ("");
}

void	filter_special(t_fsmachine *var)
{
	int	identifier;

	identifier = is_state(var->line, var->index);
	if (identifier == RED_IN || identifier == RED_OUT || identifier == PIPE)
		add_item_end(var->head, identified_type(identifier), identifier);
	if (identifier == RED_APPEND || identifier == HEREDOC)
	{
		add_item_end(var->head, identified_type(identifier), identifier);
		var->index++;
	}
}

void	filter_word(t_fsmachine *var)
{
	if (var->limit > 0)
	{
		var->begin = var->index - var->limit;
		var->temp = ft_substr(var->line, var->begin, var->limit);
		if (*var->temp == DOLLAR && !is_space(var->temp, 1) && var->temp[1] != DOLLAR)
			handle_dollar(var);
		else
			add_item_end(var->head, var->temp, WORD);
		free(var->temp);
		var->limit = 0;
	}
}

void	is_inside_quote(t_fsmachine *var)
{
	if (var->line[var->index] == DQUOTE || var->line[var->index] == SQUOTE)
	{
		if (var->check_quote && var->line[var->index] == var->quote_type)
			var->check_quote = false;
		else if (!var->check_quote)
		{
			var->check_quote = true;
			var->quote_type = var->line[var->index];
		}
	}
}

void	finite_state_machine(char *line, t_token **head)
{
	t_fsmachine	var;

	var = (t_fsmachine){0, 0, 0, 0, 0, 0, NULL, line, head};
	while (true)
	{
		is_inside_quote(&var);
		if (is_special(var.line, var.index) && !var.check_quote)
		{
			filter_word(&var);
			filter_special(&var);
		}
		else
			var.limit++;
		if (var.line[var.index++] == NULL_CHAR)
			break ;
	}
}
