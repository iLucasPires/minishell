#include <minishell.h>

void	executor(t_minishell *data)
{
	t_list *token;
	char **command_current;

	token = data->tokens;
	// printf("token->value: %s\n", token->value);
	command_current = ft_calloc(2, sizeof(char *));
	command_current[0] = ft_strdup(token->value);
	command_current[1] = NULL;

	if (execve("/usr/bin/ls", command_current, data->envp) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(token->value, STDERR_FILENO);
		ft_putstr_fd(": token not found\n", STDERR_FILENO);
	}
}