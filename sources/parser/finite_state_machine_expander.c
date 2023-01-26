#include <minishell.h>

void	expander_word(t_expander *expander, char *string)
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

void	expander_dollar(t_expander *expander, char *string, t_list **envs)
{
	char *string_aux;
	char *string_aux2;

	if (string[expander->index] == DOLLAR && string[expander->index
		+ 1] != NULL_CHAR)
	{
		string_aux = ft_strrchar(&string[expander->index + 1], '$');
		string_aux2 = my_getenv(envs, string_aux);
		expander->line = ft_strfjoin(expander->line, string_aux2);
		expander->index += ft_strlen(string_aux);
		free(string_aux);
	}
	else if (string[expander->index] == DOLLAR && string[expander->index
			+ 1] == NULL_CHAR)
	{
		if (expander->line == NULL)
			expander->line = ft_strdup("$");
		else
		{
			string_aux = expander->line;
			expander->line = ft_strjoin(expander->line, "$");
			free(string_aux);
			expander->index++;
		}
	}
}