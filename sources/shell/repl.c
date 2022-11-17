#include <minishell.h>

static void	error_readline(void *ptr)
{
	if (ptr == NULL)
	{
		ft_putstr_fd(ERROR_READLINE, STDERR_FILENO);
		free(ptr);
		exit(EXIT_FAILURE);
	}
}

void	read_eval_print_loop(t_repl *repl)
{
	while (true)
	{
		repl->line = readline(PROMPT);
		error_readline(repl->line);
		add_history(repl->line);
		free(repl->line);
	}
}
