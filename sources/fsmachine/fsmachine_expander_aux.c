#include <minishell.h>

void	fsm_expander_squote(t_fsm *expander, char *line_temp)
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
}

void	fsm_expander_dquote(t_fsm *expander, char *line_temp)
{
	if (line_temp[expander->index] == DQUOTE)
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

void	fsm_expander_quote(t_fsm *expander, char *line_temp)
{
	if (line_temp[expander->index] == DQUOTE
		|| line_temp[expander->index] == SQUOTE)
	{
		fsm_expander_squote(expander, line_temp);
		fsm_expander_dquote(expander, line_temp);
	}
}

void	fsm_clean_quote(t_fsm *expander)
{
	int	index;

	index = 0;
	while (expander->line[index] != SQUOTE && expander->line[index] != DQUOTE
		&& expander->line[index] != NULL_CHAR)
		index++;
	if (expander->line[index] == SQUOTE)
		ft_rmchr(expander->line, "\'");
	else if (expander->line[index] == DQUOTE)
		ft_rmchr(expander->line, "\"");
}

void	fsm_expander_special(t_fsm *var, char *string)
{
	char	*string_aux;

	if (var->line == NULL)
	{
		var->line = string;
		var->index++;
		return ;
	}
	string_aux = var->line;
	var->line = ft_strjoin(var->line, string);
	var->index++;
	free(string_aux);
	free(string);
}

