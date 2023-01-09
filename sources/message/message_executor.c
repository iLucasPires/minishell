#include <minishell.h>

void	message_command_not_found(t_list *tokens)
{

	ft_putstr_fd(tokens->value, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}
