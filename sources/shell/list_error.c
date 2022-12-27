#include <minishell.h>

void error_generic(char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void error_command(char *command)
{
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	error_pointer(char *message, void *pointer)
{
	if (pointer == NULL)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		rl_clear_history();
		free(pointer);
		exit(EXIT_FAILURE);
	}
}

