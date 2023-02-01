#include <minishell.h>

void	change_directory(char *path)
{
	int	status;
	char *old_path;

	old_path = getcwd(NULL, 0);
	status = chdir(path);
	path = getcwd(NULL, 0);
	if (status == 0)
	{
		g_data.exit_code = 0;
		substitute_env(get_node(&g_data.envs, "OLDPWD"), ft_strjoin("OLDPWD=", old_path));
		substitute_env(get_node(&g_data.envs, "PWD"), path);
		free(old_path);
		free(path);
	}
	if (status == -1)
	{
		perror("cd");
		g_data.exit_code = 1;
	}
		
}

int	builtin_cd(char **args)
{
	char	*path;

	if (args[1] == NULL || !ft_strncmp(args[1], "~", 2))
	{
		path = my_getenv(&g_data.envs, "HOME");
		change_directory(path);
	}
	else if (!ft_strncmp(args[1], "-", 2))
	{
		path = my_getenv(&g_data.envs, "OLDPWD");
		change_directory(path);
	}
	else if (args[2] == NULL)
	{
		path = args[1];
		change_directory(path);
	}
	else
	{
		printf("cd: string not in pwd: %s\n", args[2]);
		g_data.exit_code = 1;
	}
	return (EXIT_SUCCESS);
}
