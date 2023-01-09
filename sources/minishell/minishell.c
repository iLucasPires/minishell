#include <minishell.h>

void	handle_line(t_minishell *data)
{
	handle_sigquit(data);
	if (*data->line)
	{
		add_history(data->line);
		syntax_quotes(data->line);
		finite_state_machine(data);
		choose_command(data);
		destroy_list(&data->tokens);
	}
}

void	read_eval_print_loop(t_minishell *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (TRUE)
	{
		data->line = readline(BHBLUE "minishell$> " RESET);
		handle_line(data);
		destroy_repl(data);
	}
	exit(EXIT_SUCCESS);
}
