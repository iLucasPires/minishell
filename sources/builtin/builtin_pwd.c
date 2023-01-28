#include <minishell.h>

int	builtin_pwd(t_minishell *data)
{
	char *path;
	t_list *token;

	token = data->tokens;
	path = getcwd(NULL, 0);
	if (path == NULL || path[0] == '\0' || token->next != NULL)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (EXIT_SUCCESS);
}

int	pwd(void)
{
	char c[1024];

	if (!getcwd(c, sizeof(c)))
		g_exit_code = EXIT_FAILURE;
	printf("%s\n", c);
	return (1);
}
