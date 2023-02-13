#include <minishell.h>

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

void	fsm_expander_quote(t_fsm *expander, char *line_temp)
{
	if (line_temp[expander->index] == DQUOTE
		|| line_temp[expander->index] == SQUOTE)
	{
		if (line_temp[expander->index] == SQUOTE)
		{
			if (expander->act_squote == TRUE)
			{
				expander->act_squote = FALSE;
				expander->expand = TRUE;
				return ;
			}
			if (expander->act_dquote == TRUE)
				return ;
			expander->act_squote = TRUE;
			expander->expand = !expander->expand;
		}
		else if (line_temp[expander->index] == DQUOTE)
		{
			if (expander->act_dquote == TRUE)
			{
				expander->act_dquote = FALSE;
				return ;
			}
			if (expander->act_squote == TRUE)
				return ;
			expander->act_dquote = TRUE;
			expander->expand = TRUE;
		}
	}
}

void cleaning_str(t_fsm *expander)
{
	int index = 0;

	if (expander->line[index] == SQUOTE)
		ft_rmchr(expander->line, "\'");
	else if (expander->line[index] == DQUOTE)
		ft_rmchr(expander->line, "\"");
}

void	fsm_expander(char *line_temp, t_minishell *data)
{
	t_fsm	expander;

	ft_bzero(&expander, sizeof(t_fsm));
	expander.tokens = &data->envs;
	expander.expand = TRUE;
	while (TRUE)
	{
		fsm_expander_quote(&expander, line_temp);
		if (line_temp[expander.index] == DOLLAR && expander.expand)
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
			cleaning_str(&expander);
			append_list(&data->tokens, expander.line, WORD);
			return (free(line_temp), free(expander.line));
		}
		expander.index++;
	}
}

void	fsm_filter_word(t_fsm *fsm, t_minishell *data)
{
	char	quote_char[2];

	if (fsm->limit > 0)
	{
		ft_strlcpy(quote_char, fsm->line + fsm->index - 1, 2);
		fsm->line_aux = ft_substr(fsm->line, fsm->index - fsm->limit,
				fsm->limit);
		if (ft_strchr(fsm->line_aux, DOLLAR))
			fsm_expander(fsm->line_aux, data);
		else if (quote_char[0] == DQUOTE)
		{
			ft_rmchr(fsm->line_aux, quote_char);
			append_list(fsm->tokens, fsm->line_aux, WORD);
		}
		else if (quote_char[0] == SQUOTE)
		{
			ft_rmchr(fsm->line_aux, quote_char);
			append_list(fsm->tokens, fsm->line_aux, WORD);
		}
		else
			append_list(fsm->tokens, fsm->line_aux, WORD);
		fsm->limit = 0;
	}
}

void	fsm_filter_special(t_fsm *fsm)
{
	int	identifier;

	identifier = fsm_is_state(fsm->line, fsm->index);
	if (identifier == RED_IN || identifier == RED_OUT || identifier == PIPE)
		append_list(fsm->tokens, fsm_identified(identifier), identifier);
	if (identifier == RED_APPEND || identifier == HEREDOC)
	{
		append_list(fsm->tokens, fsm_identified(identifier), identifier);
		fsm->index++;
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