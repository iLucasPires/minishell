#include <minishell.h>

int	builtin_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (path == NULL || path[0] == '\0')
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (EXIT_SUCCESS);
}
