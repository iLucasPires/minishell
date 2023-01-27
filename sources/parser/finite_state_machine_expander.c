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

	if (string[expander->index] == DOLLAR && string[expander->index + 1] == '$')
	{
		if (expander->line == NULL)
		{
			expander->line = ft_itoa(getpid());
			expander->index = expander->index + 1;
		}
		else
		{
			string_aux = expander->line;
			expander->line = ft_strjoin(expander->line, ft_itoa(getpid()));
			free(string_aux);
			expander->index = expander->index + 1;
		}
	}
	else if (string[expander->index] == DOLLAR && string[expander->index
			+ 1] == '?')
	{
		if (expander->line == NULL)
		{
			expander->line = ft_itoa(312);
			expander->index = expander->index + 1;
		}
		else
		{
			string_aux = expander->line;
			expander->line = ft_strjoin(expander->line, ft_itoa(12));
			free(string_aux);
			expander->index = expander->index + 1;
		}
	}
	else if (string[expander->index] == DOLLAR && (string[expander->index
				+ 1] != NULL_CHAR && string[expander->index + 1] != SPACE))
	{
		string_aux = ft_strrchar(&string[expander->index + 1], '$');
		string_aux2 = my_getenv(envs, string_aux);
		expander->line = ft_strfjoin(expander->line, string_aux2);
		expander->index += ft_strlen(string_aux);
		free(string_aux);
	}
	else if (string[expander->index] == DOLLAR && (string[expander->index + 1] == NULL_CHAR || string[expander->index + 1] == SPACE))
	{
		// if (expander->line == NULL)
		// {
			if (string[expander->index + 1] == SPACE)
			{
				string_aux = expander->line;
				if (expander->line == NULL)
					expander->line = ft_strdup("$ ");
				else
					expander->line = ft_strjoin(expander->line, "$ ");
				free(string_aux);
				expander->index++;
			}
			else
			{
				if (expander->line == NULL)
					expander->line = ft_strdup("$");
				else 
				{
					string_aux = expander->line;
					expander->line = ft_strjoin(expander->line, "$");
					free(string_aux);
				}
				expander->index++;
			}
		// }
		// else
		// {
		// 	if (string[expander->index + 1] == SPACE)
		// 	{
		// 		string_aux = expander->line;
		// 		expander->line = ft_strjoin(expander->line, "$ ");
		// 		free(string_aux);
		// 		expander->index++;
		// 	}
		// 	else
		// 	{
		// 		string_aux = expander->line;
		// 		expander->line = ft_strjoin(expander->line, "$");
		// 		free(string_aux);
		// 		expander->index++;
		// 	}			
		// }
	}
}