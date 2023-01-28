#include <minishell.h>

void	remove_chars(char *str, char *targets)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_strchr(targets, str[i]))
		{
			str[j++] = str[i];
		}
		i++;
	}
	str[j] = '\0';
}

void	fsm_expander(char *line_temp, t_minishell *data)
{
	t_expander	expander;

	ft_bzero(&expander, sizeof(t_expander));
	printf("line_temp: %s \n", line_temp);
	while (TRUE)
	{
		if (line_temp[expander.index] == DOLLAR)
		{
			expander_word(&expander, line_temp);
			expander_dollar(&expander, line_temp, &data->envs);
		}
		else
			expander.limit++;
		if (line_temp[expander.index] == NULL_CHAR)
		{
			expander.limit--;
			expander_word(&expander, line_temp);
			new_node(&data->tokens, expander.line, WORD);
			return (free(line_temp), free(expander.line));
		}
		expander.index++;
	}
}

char	*ft_chartostr(char c)
{
	char	*str;

	str = ft_calloc(sizeof(char) , 2);
	str[0] = c;
	return (str);
}

void	add_node_remove_quote(t_minishell *data, char **line_temp,
		char *quote_type)
{
	remove_chars(*line_temp, quote_type);
	new_node(&data->tokens, *line_temp, WORD);
	free(*line_temp);
}

int	is_expander(char *line, char quote_type)
{
	if (line && quote_type != SQUOTE)
		return (1);
	else if ((line && quote_type == SQUOTE) || (quote_type == DQUOTE)
			|| (quote_type == SQUOTE))
		return (2);
	return (0);
}

void	fsm_filter_word(t_fsm *fsm, t_minishell *data)
{
	char	*line_temp;
	char	*quote_type;

	if (fsm->limit > 0)
	{
		quote_type = ft_chartostr(fsm->line[fsm->index - fsm->limit]);
		line_temp = ft_substr(fsm->line, fsm->index - fsm->limit, fsm->limit);
		if (is_expander(ft_strchr(line_temp, '$'), *quote_type) == 1)
		{
			remove_chars(line_temp, "\"");
			fsm_expander(line_temp, data);
		}
		else if (is_expander(ft_strchr(line_temp, '$'), *quote_type) == 2)
			add_node_remove_quote(data, &line_temp, quote_type);
		else
			add_node_remove_quote(data, &line_temp, "\"\'");
		free(quote_type);
		fsm->limit = 0;
	}
}

int count_index(char *line)
{
	int  i;

	i = 0;

	while (line[i] != 0 && line[i] != SPACE)
		i++;
	return (i);
}

int is_redirect(int identifier)
{
	return (identifier == RED_IN || identifier == RED_OUT || identifier == RED_APPEND || identifier == HEREDOC);
}

void	fsm_filter_special(t_fsm *fsm, t_minishell *data)
{
	int	identifier;
	char *document;
	int size_index;

	identifier = fsm_is_state(fsm->line, fsm->index);
	if (is_redirect(identifier))
	{
		new_node(&data->tokens, fsm_identified(identifier), identifier);
		fsm->index++;
		fsm->index += (identifier == RED_APPEND || identifier == HEREDOC);
		fsm->index += (fsm->line[fsm->index] == SPACE);
		size_index = count_index(&fsm->line[fsm->index]);
		document = ft_substr(&fsm->line[fsm->index], 0, size_index);
		new_node(&data->tokens, document, DOCUMENT);
		fsm->index += size_index;
		free(document);
	}
	if (identifier == PIPE)
	{
		new_node(&data->tokens, fsm_identified(identifier), identifier);
		fsm->index++;
	}
}

void	fsm_is_inside_quote(t_fsm *fsm, t_minishell *data)
{
	(void)(data);
	if (fsm->line[fsm->index] == DQUOTE || fsm->line[fsm->index] == SQUOTE)
	{
		if (fsm->check_quote && fsm->line[fsm->index] == fsm->quote_type)
		{
			fsm->check_quote = FALSE;
		}
		else if (!fsm->check_quote)
		{
			fsm->check_quote = TRUE;
			fsm->quote_type = fsm->line[fsm->index];
		}
	}
}

void	init_fsm(t_fsm *fsm, t_minishell *data)
{
	fsm->index = 0;
	fsm->limit = 0;
	fsm->begin = 0;
	fsm->check_quote = FALSE;
	fsm->quote_type = 0;
	fsm->line = data->line;
}

void	finite_state_machine(t_minishell *data)
{
	t_fsm	fsm;

	init_fsm(&fsm, data);
	while (TRUE)
	{
		fsm_is_inside_quote(&fsm, data);
		if (fsm_is_special(fsm.line, fsm.index) && !fsm.check_quote)
		{
			fsm_filter_word(&fsm, data);
			fsm_filter_special(&fsm, data);
		}
		else
			fsm.limit++;
		if (fsm.line[fsm.index] == NULL_CHAR)
			break ;
		fsm.index++;
	}
}
