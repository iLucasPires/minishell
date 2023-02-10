#include <minishell.h>

void	fsm_expander(char *line_temp, t_minishell *data)
{
	t_fsm	expander;

	ft_bzero(&expander, sizeof(t_fsm));
	expander.tokens = &data->envs;
	while (TRUE)
	{
		if (line_temp[expander.index] == DOLLAR)
		{
			expander_word(&expander, line_temp);
			expander_dollar(&expander, line_temp);
		}
		else
			expander.limit++;
		if (line_temp[expander.index] == NULL_CHAR)
		{
			expander.limit--;
			expander_word(&expander, line_temp);
			new_node(&data->tokens, expander.line, WORD);
			free(expander.line);
			break ;
		}
		expander.index++;
	}
}

int	fsm_is_expander(char *line, char quote_type)
{
	if (ft_strchr(line, DOLLAR) && quote_type != SQUOTE)
		return (1);
	else if ((ft_strchr(line, DOLLAR) && quote_type == SQUOTE)
			|| (quote_type == DQUOTE) || (quote_type == SQUOTE))
		return (2);
	return (0);
}

void	fsm_filter_word(t_fsm *fsm, t_minishell *data)
{
	char	quote_char[2];

	if (fsm->limit > 0)
	{
		ft_strlcpy(quote_char, fsm->line + fsm->index - fsm->limit, 2);
		fsm->line_aux = ft_substr(fsm->line, fsm->index - fsm->limit,
				fsm->limit);
		if (fsm_is_expander(fsm->line_aux, *quote_char) == 1)
		{
			ft_rmchr(fsm->line_aux, "\"");
			fsm_expander(fsm->line_aux, data);
		}
		else if (fsm_is_expander(fsm->line_aux, *quote_char) == 2)
		{
			ft_rmchr(fsm->line_aux, quote_char);
			new_node(fsm->tokens, fsm->line_aux, WORD);
		}
		else
		{
			ft_rmchr(fsm->line_aux, "\"\'");
			new_node(fsm->tokens, fsm->line_aux, WORD);
		}
		free(fsm->line_aux);
		fsm->limit = 0;
	}
}

void	fsm_filter_special(t_fsm *fsm)
{
	int	identifier;

	identifier = fsm_is_state(fsm->line, fsm->index);
	if (identifier == RED_IN || identifier == RED_OUT || identifier == PIPE)
		new_node(fsm->tokens, fsm_identified(identifier), identifier);
	if (identifier == RED_APPEND || identifier == HEREDOC)
	{
		new_node(fsm->tokens, fsm_identified(identifier), identifier);
		fsm->index++;
	}
}

void	fsm_is_inside_quote(t_fsm *fsm)
{
	if (fsm->line[fsm->index] == DQUOTE || fsm->line[fsm->index] == SQUOTE)
	{
		if (fsm->check_quote && fsm->line[fsm->index] == fsm->quote_type)
			fsm->check_quote = FALSE;
		else if (!fsm->check_quote)
		{
			fsm->check_quote = TRUE;
			fsm->quote_type = fsm->line[fsm->index];
		}
	}
}

void	finite_state_machine(t_minishell *data)
{
	t_fsm fsm;

	ft_bzero(&fsm, sizeof(t_fsm));
	fsm.line = data->line;
	fsm.tokens = &data->tokens;
	while (TRUE)
	{
		fsm_is_inside_quote(&fsm);
		if (fsm_is_special(fsm.line, fsm.index) && !fsm.check_quote)
		{
			fsm_filter_word(&fsm, data);
			fsm_filter_special(&fsm);
		}
		else
			fsm.limit++;
		if (fsm.line[fsm.index] == NULL_CHAR)
			break ;
		fsm.index++;
	}
}