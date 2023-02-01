#include <minishell.h>

void	update_pwd(void)
{
	char	*string_aux;
	char	*old_path;
	char	*path;

	path = getcwd(NULL, 0);
	old_path = my_getenv(&g_data.envs, "PWD");
	string_aux = ft_strjoin("OLDPWD=", old_path);
	substitute_env(get_node(&g_data.envs, "OLDPWD"), string_aux);
	substitute_env(get_node(&g_data.envs, "PWD"), path);
	free(string_aux);
	free(old_path);
	free(path);
}

void	change_directory(char *path)
{
	int	result;

	result = chdir(path);
	if (result == -1)
	{
		perror("cd");
		g_data.exit_code = 1;
	}
	else
	{
		update_pwd();
		g_data.exit_code = 0;
	}
}

void	change_home_directory(void)
{
	char	*path;

	path = my_getenv(&g_data.envs, "HOME");
	change_directory(path);
	free(path);
}

void	change_old_directory(void)
{
	char	*path;
	char	*path_current;

	path = my_getenv(&g_data.envs, "OLDPWD");
	change_directory(path);
	path_current = my_getenv(&g_data.envs, "PWD");
	ft_putstr_fd(path_current, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(path_current);
	free(path);
}

int	builtin_cd(char **args)
{
	char	*path;

	if (args[1] == NULL || !ft_strncmp(args[1], "~", 2))
		change_home_directory();
	else if (!ft_strncmp(args[1], "-", 2))
		change_old_directory();
	else if (args[2] == NULL)
	{
		path = args[1];
		change_directory(path);
	}
	else
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		g_data.exit_code = 1;
	}
	return (EXIT_SUCCESS);
}
