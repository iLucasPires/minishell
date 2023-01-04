#include <minishell.h>

// void	handle_dollar(t_fsmachine *var, char special, char *temp)
// {
// 	int		index;
// 	int		limit;
// 	char	*string_temp;

// 	index = 1;
// 	limit = 0;
// 	while (true)
// 	{
// 		if (temp[index] == DOLLAR || temp[index] == special)
// 		{
// 			string_temp = ft_substr(temp, limit + 1, index - 1);
// 			add_item_end(var->head, getenv(string_temp), EXPAND);
// 			limit = index;
// 			free(string_temp);
// 		}
// 		if (temp[index++] == NULL_CHAR)
// 			break ;
// 	}
// }

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

void	filter_special(t_fsmachine *var, char *line)
{
	int	identifier;

	identifier = is_state(line, var->index);
	if (identifier == RED_IN || identifier == RED_OUT || identifier == PIPE)
		add_item_end(var->head, identified_type(identifier), identifier);
	if (identifier == RED_APPEND || identifier == HEREDOC)
	{
		add_item_end(var->head, identified_type(identifier), identifier);
		var->index++;
	}
}

void	filter_word(t_fsmachine *var, char *line)
{
	char	*temp;

	if (var->limit > 0)
	{
		temp = ft_substr(line, var->index - var->limit, var->limit);
		// if (temp[0] == DOLLAR && !is_space(temp, 1) && temp[1] != DOLLAR)
		// 	handle_dollar(var, NULL_CHAR, temp);
		// else
		add_item_end(var->head, temp, WORD);
		free(temp);
		var->limit = 0;
	}
}

void	is_inside_quote(t_fsmachine *var, char *line)
{
	if (line[var->index] == DQUOTE || line[var->index] == SQUOTE)
	{
		if (var->check_quote && line[var->index] == var->quote_type)
			var->check_quote = false;
		else if (!var->check_quote)
		{
			var->check_quote = true;
			var->quote_type = line[var->index];
		}
	}
}

void	finite_state_machine(char *line, t_token **head)
{
	t_fsmachine	var;

	var = (t_fsmachine){0, 0, 0, 0, 0, head};
	while (true)
	{
		is_inside_quote(&var, line);
		if (is_special(line, var.index) && !var.check_quote)
		{
			filter_word(&var, line);
			filter_special(&var, line);
		}
		else
			var.limit++;
		if (line[var.index++] == NULL_CHAR)
			break ;
	}
}
