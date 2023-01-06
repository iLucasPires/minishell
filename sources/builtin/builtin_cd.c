#include <minishell.h>

void	change_directory(char *path, t_minishell *data)
{
	int	status;

	status = chdir(path);
	if (status == -1)
		perror("cd");
	else
	{
		substitute_env(get_node(&data->envs, "OLDPWD"), data->path);
		free(data->path);
	}
}

int	builtin_cd(t_minishell *data)
{
	char	*path;
	t_list	*token;

	token = data->tokens;
	if (token->next == NULL || !ft_strncmp(token->next->value, "~", 2))
	{
		path = get_value_env(&data->envs, "HOME");
		change_directory(path, data);
	}
	else if (!ft_strncmp(token->next->value, "-", 2))
	{
		path = get_value_env(&data->envs, "OLDPWD");
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
