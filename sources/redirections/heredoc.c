#include <minishell.h>

void	clean_heredoc(t_minishell *data)
{
	destroy_list(&data->tokens);
	destroy_list(&data->envs);
	free(data->line);
	free_all(data->paths);
	free(data->envp);
}

void	handle_sigquit_heredoc(char *line, char *file_name, t_command *cmd)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	destroy_cmd_list(cmd);
	free(line);
	close(cmd->infile);
	free(file_name);
	exit(EXIT_SUCCESS);
}

int	init_file(int *infile)
{
	*infile = open(HERE_FILE, O_CREAT | O_RDWR, 0664);
	if (*infile == FAILURE)
	{
		perror("open");
		return (FAILURE);
	}
	return (*infile);
}

static void	write_in_file(t_command *cmd, char *file_name)
{
	char	*line;

	signal(SIGINT, handle_sigint);
	while (TRUE)
	{
		line = readline("> ");
		if (!line)
		{
		}
		if (!ft_strcmp(line, file_name))
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

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (init_file(&cmd->infile) == -1)
			exit(EXIT_FAILURE);
		clean_heredoc(data);
		write_in_file(cmd, file_name);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		cmd->infile = open(HERE_FILE, O_RDONLY);
		if (cmd->infile == FAILURE)
			perror("open");
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		unlink(HERE_FILE);
	}
}
