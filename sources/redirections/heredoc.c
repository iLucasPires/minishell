#include <minishell.h>

void	heredoc_stop(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_clear_history();
	exit(130);
}

static int	init_file(int *fd)
{
	*fd = open(HERE_FILE, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (*fd == -1)
	{		
		dprintf(2, "ERROR NA INITFILE <<!\n");
		return (-1);
	}
	return (*fd);
}

static void	write_in_file(int fd, t_list *list, t_minishell *data)
{
	char *line;

	while (TRUE)
	{
		line = readline("> ");
		if (!line)
		{
			destroy_minishell(data);
			close(fd);
			exit(0);
		}
		if (!ft_strncmp(line, list->next->value,
				ft_strlen(line) + 1))
		{
			destroy_minishell(data);
			close(fd);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	exit(0);
}

void	make_heredoc(t_list *token, t_minishell *data, int *fd)
{
	int		pid;
	int		status;
	int 	temp_fd;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	temp_fd = init_file(&temp_fd);
	if (pid < 0)
		exit(0);
	if (pid == 0)
	{
		write_in_file(temp_fd, token, data);
	}
	else
	{
		waitpid(pid, &status, 0);
		*fd = open(HERE_FILE, O_RDONLY);
	}
	close(*fd);
	close(temp_fd);
	unlink(HERE_FILE);
}
