#include <minishell.h>

void	handle_line(t_repl *data)
{
	handle_sigquit(data);
	if (*data->line != NULL_CHAR)
	{
		add_history(data->line);
		verify_quotes(data->line);
		finite_state_machine(data->line, &data->head);
		verify_command(data);
	}
}

void	read_eval_print_loop(t_repl *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (true)
	{
		data->line = readline(data->path);
		handle_line(data);
		free_repl(data);
	}
	exit(EXIT_SUCCESS);
}
