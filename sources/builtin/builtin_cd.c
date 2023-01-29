#include <minishell.h>

void	change_directory(char *path)
{
	int	status;

	status = chdir(path);
	if (status == -1)
		perror("cd");
}

int	builtin_cd(t_command **cmd)
{
	char	*path;

	if ((*cmd)->args[1] == NULL || !ft_strncmp((*cmd)->args[1], "~", 2))
	{
		path = my_getenv(&g_minishell.envs, "HOME");
		change_directory(path);
	}
	else if (!ft_strncmp((*cmd)->args[1], "-", 2))
	{
		path = my_getenv(&g_minishell.envs, "OLDPWD");
		change_directory(path);
	}
	else if ((*cmd)->args[2] == NULL)
	{
		path = (*cmd)->args[1];
		change_directory(path);
	}
	else
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
	return (EXIT_SUCCESS);
}
