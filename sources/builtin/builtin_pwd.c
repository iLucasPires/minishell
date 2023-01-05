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