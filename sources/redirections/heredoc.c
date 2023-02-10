#include <minishell.h>

void	clean_heredoc(t_minishell *data)
{
	destroy_list(&data->tokens);
	destroy_list(&data->envs);
	free(data->line);
	free_all(data->paths);
	free(data->envp);
}

void	handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		exit(EXIT_SUCCESS);
	}
}

void	write_in_file(t_command *cmd, char *file_name)
{
	char	*line;

	clear_history();
	signal(SIGINT, handle_sigint_heredoc);
	while (TRUE)
	{
		line = readline(BHGREEN"> " RESET);
		if (!line || !ft_strcmp(line, file_name))
		{
			free(line);
			close(cmd->infile);
			free(file_name);
			destroy_cmd_list(cmd);
			exit(EXIT_SUCCESS);
		}
		ft_putendl_fd(line, cmd->infile);
		free(line);
	}
	exit(EXIT_SUCCESS);
}

void	heredoc_child(t_command *cmd, char *file_name, t_minishell *data)
{
	cmd->infile = open_file(HERE_FILE, O_CREAT | O_RDWR, 0664, &data->exit_code);
	clean_heredoc(data);
	write_in_file(cmd, file_name);
	exit(EXIT_SUCCESS);
}

void	make_heredoc(t_command *cmd, char *file_name, t_minishell *data)
{
	int	pid;

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
		waitpid(pid, &data->status, 0);
		cmd->infile = open_file(HERE_FILE, O_RDONLY, 0, &data->exit_code);
		if (WIFEXITED(data->status))
			data->exit_code = WEXITSTATUS(data->status);
		unlink(HERE_FILE);
	}
}
