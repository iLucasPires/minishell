#include <minishell.h>

void	change_directory(char *path)
{
	int	status;

	status = chdir(path);
	if (status == -1)
		perror("cd");
}

int	builtin_cd(t_minishell *data)
{
	char	*path;
	t_list	*token;

	token = data->tokens;
	if (token->next == NULL || !ft_strncmp(token->next->value, "~", 2))
	{
		path = my_getenv(&data->envs, "HOME");
		change_directory(path);
	}
	else if (!ft_strncmp(token->next->value, "-", 2))
	{
		path = my_getenv(&data->envs, "OLDPWD");
		change_directory(path);
	}
	else if (token->next->next == NULL)
	{
		path = token->next->value;
		change_directory(path);
	}
	else
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
	return (EXIT_SUCCESS);
}
