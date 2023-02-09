#include <minishell.h>

void	clean_heredoc(t_minishell *data)
{
	destroy_list(&data->tokens);
	destroy_list(&data->envs);
	free(data->line);
	free_all(data->paths);
	free(data->envp);
}

int	open_file(char *file, int flags, int other_flags)
{
	int	fd;
	int	is_file;

	if (other_flags == 0)
	{
		is_file = access(file, F_OK);
		if (is_file == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		fd = open(file, flags);
	}
	else
		fd = open(file, flags, other_flags);
	if (fd == FAILURE)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
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
		cmd->infile = open_file(HERE_FILE, O_CREAT | O_RDWR, 0664);
		clean_heredoc(data);
		write_in_file(cmd, file_name);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		cmd->infile = open_file(HERE_FILE, O_RDONLY, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		unlink(HERE_FILE);
	}
}
