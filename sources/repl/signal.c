#include <minishell.h>

void	handle_sigquit(t_repl *data)
{
	if (data->line == NULL)
	{
		ft_putstr_fd(ERROR_EXIT, STDERR_FILENO);
		rl_clear_history();
		free_minishell(data);
		exit(EXIT_FAILURE);
	}
}

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}