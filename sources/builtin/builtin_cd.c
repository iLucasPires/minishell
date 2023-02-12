#include <minishell.h>

void	update_pwd(t_minishell *data)
{
	char	*string_aux;
	char	*old_path;
	char	*path;

	path = getcwd(NULL, 0);
	old_path = my_getenv(&data->envs, "PWD");
	string_aux = ft_strjoin("OLDPWD=", old_path);
	substitute_env(get_node(&data->envs, "OLDPWD"), string_aux);
	free(string_aux);
	string_aux = ft_strjoin("PWD=", path);
	substitute_env(get_node(&data->envs, "PWD"), string_aux);
	free(string_aux);
	free(old_path);
	free(path);
}

void	change_directory(char *path, t_minishell *data)
{
	int	result;

	result = chdir(path);
	if (result == -1)
	{
		perror("cd");
		data->exit_code = 1;
	}
	else
	{
		update_pwd(data);
		data->exit_code = 0;
	}
}

void	change_home_directory(t_minishell *data)
{
	char	*path;

	path = my_getenv(&data->envs, "HOME");
	change_directory(path, data);
	free(path);
}

void	change_old_directory(t_minishell *data)
{
	char	*path;
	char	*path_current;

	path = my_getenv(&data->envs, "OLDPWD");
	change_directory(path, data);
	path_current = my_getenv(&data->envs, "PWD");
	ft_putstr_fd(path_current, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(path_current);
	free(path);
}

int	builtin_cd(char **args, t_minishell *data)
{
	char	*path;

	if (args[1] == NULL || !ft_strncmp(args[1], "~", 2))
		change_home_directory(data);
	else if (!ft_strncmp(args[1], "-", 2))
		change_old_directory(data);
	else if (args[2] == NULL)
	{
		path = args[1];
		change_directory(path, data);
	}
	else
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		data->exit_code = 1;
	}
	return (EXIT_SUCCESS);
}
