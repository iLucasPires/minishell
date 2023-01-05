#include <minishell.h>

void	path_current(t_minishell *data)
{
	char	*path;
	char	*temp;

	path = getcwd(NULL, 0);
	if (ft_strncmp(path, getenv("HOME"), ft_strlen(path)))
		data->path = ft_strjoin(BHGREEN "~", path + ft_strlen(getenv("HOME")));
	else
		data->path = ft_strjoin(BHGREEN, path);
	temp = data->path;
	data->path = ft_strjoin(data->path, BHGREEN " $ " RESET);
	free(temp);
	free(path);
}

void	handle_line(t_minishell *data)
{
	handle_sigquit(data);
	if (*data->line != NULL_CHAR)
	{
		add_history(data->line);
		syntax_quotes(data->line);
		finite_state_machine(data);
		choose_command(data);
		// executor(data);
	}
}

void	read_eval_print_loop(t_minishell *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (true)
	{
		data->line = readline(BHRED "my shell> " RESET);
		handle_line(data);
		destroy_repl(data);
	}
	exit(EXIT_SUCCESS);
}
