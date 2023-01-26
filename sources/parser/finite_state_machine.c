#include <minishell.h>

void	fsm_expander(char *line_temp, t_minishell *data)
{
	t_expander	expander;

	ft_bzero(&expander, sizeof(t_expander));
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
			new_node(&data->tokens, expander.line, WORD);
			return (free(line_temp), free(expander.line));
		}
		expander.index++;
	}
}

void	fsm_expander_quote(char *line_temp, t_minishell *data)
{
	t_expander	expander;
	char		*temp;

	(void)(data);
	ft_bzero(&expander, sizeof(t_expander));
	if (line_temp[0] == DQUOTE)
	{
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
				temp = ft_substr(line_temp, 1, ft_strlen(line_temp) - 2);
				new_node(&data->tokens, temp, WORD);
				return (free(line_temp), free(expander.line));
			}
			expander.index++;
		}
	}
}

void	fsm_filter_word(t_fsm *fsm, t_minishell *data)
{
	char	*line_temp;

	if (fsm->limit > 0)
	{
		fsm->begin = fsm->index - fsm->limit;
		line_temp = ft_substr(fsm->line, fsm->begin, fsm->limit);
		if (ft_strchr(line_temp, '$'))
			fsm_expander(line_temp, data);
		else
		{
			new_node(&data->tokens, line_temp, WORD);
			free(line_temp);
		}
		fsm->limit = 0;
	}
}

void	fsm_filter_special(t_fsm *fsm, t_minishell *data)
{
	int	identifier;

	identifier = fsm_is_state(fsm->line, fsm->index);
	if (identifier == RED_IN || identifier == RED_OUT || identifier == PIPE)
	{
		new_node(&data->tokens, fsm_identified(identifier), identifier);
		fsm->index++;
	}
	if (identifier == RED_APPEND || identifier == HEREDOC)
	{
		new_node(&data->tokens, fsm_identified(identifier), identifier);
		fsm->index += 2;
	}
}

void	fsm_is_inside_quote(t_fsm *fsm, t_minishell *data)
{
	if (fsm->line[fsm->index] == DQUOTE || fsm->line[fsm->index] == SQUOTE)
	{
		if (fsm->check_quote && fsm->line[fsm->index] == fsm->quote_type)
		{
			fsm_expander_quote(fsm->line, data);
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
