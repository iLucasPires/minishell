#include <minishell.h>

void	verify_quotes(char *line)
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

void	verify_command(t_repl *data)
{
	if (ft_strncmp(data->head->value, "cd", 3) == 0)
		builtin_cd(data);
	else if (ft_strncmp(data->head->value, "echo", 5) == 0)
		builtin_echo(data);
	else if (ft_strncmp(data->head->value, "pwd", 4) == 0)
		builtin_pwd(data);
	else if (ft_strncmp(data->head->value, "exit", 5) == 0)
		builtin_exit(data);
	else if (ft_strncmp(data->head->value, "env", 4) == 0)
		builtin_env(data);
	else if (ft_strncmp(data->head->value, "export", 7) == 0)
		builtin_export(data);
}