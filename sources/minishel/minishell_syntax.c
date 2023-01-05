#include <minishell.h>

void	syntax_quotes(char *line)
{
	int	index;
	int	value;

	index = 0;
	value = 0;
	while (line[index] != NULL_CHAR)
	{
		if (line[index] == SQUOTE || line[index] == DQUOTE)
		{
			value = line[index];
			index++;
			while (line[index] && line[index] != value)
				index++;
			if (line[index] == NULL_CHAR)
			{
				ft_putstr_fd(ERROR_SYNTAX, 2);
				return ;
			}
		}
		index++;
	}
}
