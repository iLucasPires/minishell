#include <minishell.h>

void	heredoc_stop(int signal)
{
	(void)signal;
	destroy_minishell(data);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_clear_history();
	exit(130);
}

void	init_file(t_file *file)
{
	file->fd = open(HERE_FILE, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (file->fd == -1)
		exit(1);
}

void	write_in_file(t_file *file, t_list *list, t_minishell *data)
{
	while (true)
	{
		file->keepli = readline("> ");
		if (!file->keepli)
		{
			destroy_minishell(data);
			close(file->fd);
			exit(0);
		}
		if (!ft_strncmp(file->keepli, list->next->value,
				ft_strlen(file->keepli)))
		{
			destroy_minishell(data);
			close(file->fd);
			exit(0);
		}
		ft_putendl_fd(file->keepli, file->fd);
		free(file->keepli);
	}
}

void	make_heredoc(t_minishell *data)
{
	int	pid;
	int	status;

	t_file	*file;
	t_list	*list;

	list = data->tokens;
	file = &data->file;
	signal(SIGINT, SIG_IGN);
	init_file(file);
	pid = fork();
	if (pid < 0)
		exit(0);
	if (pid == 0)
		write_in_file(file, list, data);
	else
	{
		waitpid(pid, &status, 0);
		file->fd = open(HERE_FILE, O_RDONLY);
	}
	unlink(HERE_FILE);
}
