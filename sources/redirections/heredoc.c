#include <minishell.h>

void	clean_heredoc(t_minishell *data)
{
	destroy_list(&data->tokens);
	destroy_list(&data->envs);
	free(data->line);
	free_all(data->paths);
	free(data->envp);
}

void	open_file(int *infile, int flags, int other_flags)
{
	if (other_flags == 0)
		*infile = open(HERE_FILE, flags);
	else
		*infile = open(HERE_FILE, flags, other_flags);
	if (*infile == FAILURE)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
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
		line = readline("> ");
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

void	make_heredoc(t_command *cmd, char *file_name, t_minishell *data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		open_file(&cmd->infile, O_CREAT | O_RDWR, 0664);
		clean_heredoc(data);
		write_in_file(cmd, file_name);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		open_file(&cmd->infile, O_RDONLY, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		unlink(HERE_FILE);
	}
}
