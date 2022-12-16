#include <minishell.h>

void	verify_quotes(char *line)
{
	int	index;
	int	value;

	index = 0;
	value = 0;
	while (line[index] != NULL_CHAR)
	{
		if (line[index] == SQUOTE || line[index] == DQUOTE)
		{
			value = line[index];
			index = index + 1;
			while (line[index] && line[index] != value)
				index = index + 1;
			if (line[index] == NULL_CHAR)
				ft_putstr_fd("test", 2);
		}
		index = index + 1;
	}
}

void	handle_line(t_repl *data)
{
	if (data->line == NULL)
	{
		ft_putendl_fd("exit", 1);
		rl_clear_history();
		free_list_linked(&data->head);
		free(data->line);
		exit(EXIT_SUCCESS);
	}
	if (*data->line != NULL_CHAR)
	{
		add_history(data->line);
		// verify_quotes(data->line);
		parser_and_tokenize(data->line, &data->head);
		expansion(data);
		show_list_linked(data->head);
	}
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	read_eval_print_loop(t_repl *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (true)
	{
		data->line = readline(PROMPT);
		handle_line(data);
		free_list_linked(&data->head);
		free(data->line);
	}
}
