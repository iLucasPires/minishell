#include <minishell.h>

void	change_directory(char *path, t_repl *data)
{
	int	status;

	status = chdir(path);
	if (status == -1)
		perror("cd");
	else
	{
		free(data->path);
		path_current(data);
	}
}

int	builtin_cd(t_repl *data)
{
	char	*path;
	t_token	*token;

	token = data->head;
	if (token->next == NULL || !ft_strncmp(token->next->value, "~", 2))
	{
		path = getenv("HOME");
		change_directory(path, data);
	}
	else if (!ft_strncmp(token->next->value, "-", 2))
	{
		path = getenv("OLDPWD");
		change_directory(path, data);
	}
	else if (token->next->next == NULL)
	{
		path = token->next->value;
		change_directory(path, data);
	}
	else
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
	return (EXIT_SUCCESS);
}