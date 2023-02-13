#include <minishell.h>

void	fsm_expander_env(t_fsm *var, char *line)
{
	char	*line_aux;
	char	*line_aux2;

	line_aux = ft_strrchar(&line[var->index + 1], '$');
	line_aux2 = my_getenv(var->tokens, line_aux);
	var->line = ft_strfjoin(var->line, line_aux2);
	var->index += ft_strlen(line_aux);
	free(line_aux);
}

void	fsm_expander_word(t_fsm *expander, char *string)
{
	char	*string_aux;

	string_aux = NULL;
	if (expander->limit > 0)
	{
		expander->begin = expander->index - expander->limit;
		string_aux = ft_substr(string, expander->begin, expander->limit);
		expander->line = ft_strfjoin(expander->line, string_aux);
		expander->limit = 0;
	}
}

void	fsm_expander_dollar(t_fsm *var, char *line)
{
	if (line[var->index] == DOLLAR && line[var->index + 1] == '$')
		fsm_expander_special(var, ft_itoa(ft_getpid()));
	else if (line[var->index] == DOLLAR && line[var->index + 1] == '?')
		fsm_expander_special(var, ft_itoa(g_data.exit_code));
	else if (line[var->index] == DOLLAR)
	{
		if (line[var->index + 1] == NULL_CHAR || line[var->index + 1] == SPACE)
		{
			fsm_expander_special(var, ft_strdup("$"));
			var->index--;
		}
		else if (line[var->index + 1] == DQUOTE || line[var->index
				+ 1] == SQUOTE)
		{
			fsm_expander_special(var, ft_strdup("$"));
			var->index--;
		}
		else
			fsm_expander_env(var, line);
	}
}

void	fsm_expander(char *line_temp, t_minishell *data)
{
	t_fsm	expander;

	ft_bzero(&expander, sizeof(t_fsm));
	expander.expand = TRUE;
	expander.tokens = &data->envs;
	while (TRUE)
	{
		fsm_expander_quote(&expander, line_temp);
		if (line_temp[expander.index] == DOLLAR && expander.expand)
		{
			fsm_expander_word(&expander, line_temp);
			fsm_expander_dollar(&expander, line_temp);
		}
		else
			expander.limit++;
		if (line_temp[expander.index] == NULL_CHAR)
		{
			expander.limit--;
			fsm_expander_word(&expander, line_temp);
			fsm_clean_quote(&expander);
			append_list(&data->tokens, expander.line, WORD);
			return (free(expander.line));
		}
		expander.index++;
	}
}
