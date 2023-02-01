#include <minishell.h>

void	message_command_not_found(t_list *tokens)
{

	ft_putstr_fd(tokens->value, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_data.exit_code = 127;
}

void message_pipe_error(t_list *tokens)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(tokens->value, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	g_data.exit_code = 1;
}

void	message_syntax_error(t_list *tokens)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(tokens->value, STDERR_FILENO);
	g_data.exit_code = 2;
}


