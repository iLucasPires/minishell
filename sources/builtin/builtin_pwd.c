#include <minishell.h>

int	builtin_pwd(char **args, t_minishell *data)
{
	char *path;

	(void)args;
	path = getcwd(NULL, 0);
	if (path == NULL || path[0] == '\0')
	{
		perror("getcwd");
		data->exit_code = 1;
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}
