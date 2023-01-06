#include <minishell.h>

void	handle_line(t_minishell *data)
{
	char	*temp_line;

	handle_sigquit(data);
	temp_line = data->line;
	if (*data->line)
	{
		add_history(data->line);
		data->line = ft_strtrim(data->line, " ");
		if (*data->line)
		{
			syntax_quotes(data->line);
			finite_state_machine(data);
			choose_command(data);
			destroy_list(&data->tokens);
		}
	}
	free(temp_line);
}

void	read_eval_print_loop(t_minishell *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (true)
	{
		data->line = readline(BHBLUE "minishell$> " RESET);
		handle_line(data);
		destroy_repl(data);
	}
	exit(EXIT_SUCCESS);
}
