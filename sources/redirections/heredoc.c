#include <minishell.h>

void	handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		destroy_execute_system(&g_data);
		destroy_minishell(&g_data);
		exit(EXIT_SUCCESS);
	}
}

void	write_in_file(t_minishell *data, char *file_name)
{
	char	*line;

	signal(SIGINT, handle_sigint_heredoc);
	while (TRUE)
	{
		line = readline(BHGREEN "> " RESET);
		if (!line || !ft_strcmp(line, file_name))
		{
			free(line);
			free(file_name);
			close(data->cmd_list->infile);
			return ;
		}
		ft_putendl_fd(line, data->cmd_list->infile);
		free(line);
	}
}

void	heredoc_child(t_command *cmd, char *file_name, t_minishell *data)
{
	signal(SIGINT, handle_sigint_heredoc);
	cmd->infile = open_file(HERE_FILE, O_CREAT | O_RDWR, 0664,
			&data->exit_code);
	write_in_file(data, file_name);
	destroy_execute_system(data);
	destroy_minishell(data);
	exit(EXIT_SUCCESS);
}

void	make_heredoc(t_command *cmd, char *file_name, t_minishell *data)
{
	int		status;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == CHILD)
		heredoc_child(cmd, file_name, data);
	else
	{
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_sigint);
		cmd->infile = open_file(HERE_FILE, O_RDONLY, 0, &data->exit_code);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		unlink(HERE_FILE);
	}
}
