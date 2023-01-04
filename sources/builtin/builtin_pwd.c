#include <minishell.h>

int	builtin_pwd(t_repl *data)
{
	char *path;
	t_token *token;

	token = data->head;
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