#include <minishell.h>

void	expander_word(t_fsm *expander, char *string)
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

void	expander_special(t_fsm *var, char *string)
{
	char	*string_aux;

	if (var->line == NULL)
	{
		var->line = string;
		var->index = var->index + 1;
		return ;
	}
	string_aux = var->line;
	var->line = ft_strjoin(var->line, string);
	var->index = var->index + 1;
	free(string_aux);
	free(string);
}

void	expander_env(t_fsm *var, char *line)
{
	char	*line_aux;
	char	*line_aux2;

	line_aux = ft_strrchar(&line[var->index + 1], '$');
	line_aux2 = my_getenv(var->tokens, line_aux);
	var->line = ft_strfjoin(var->line, line_aux2);
	var->index += ft_strlen(line_aux);
	free(line_aux);
}

void	expander_dollar(t_fsm *var, char *line)
{
	int new_index;

	new_index = var->index + 1;
	if (line[var->index] == DOLLAR && line[new_index] == '$')
		expander_special(var, ft_itoa(my_getpid()));
	else if (line[var->index] == DOLLAR && line[new_index] == '?')
		expander_special(var, ft_itoa(g_data.exit_code));
	else if (line[var->index] == DOLLAR)
	{
		if (line[new_index] == NULL_CHAR || line[new_index] == SPACE)
		{
			expander_special(var, ft_strdup("$"));
			var->index--;
		}
		else if (line[new_index] == DQUOTE || line[new_index] == SQUOTE)
		{
			expander_special(var, ft_strdup("$"));
			var->index--;
		}
		else
			expander_env(var, line);
	}
}