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

int	init_file(int *fd)
{
	*fd = open(HERE_FILE, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (*fd == -1)
	{		
		dprintf(2, "ERROR NA INITFILE <<!\n");
		return (-1);
	}
	return (*fd);
}

// static void	write_in_file(int fd, t_list *list, t_minishell *data)
// {
// 	char *line;

// 	signal(SIGINT, heredoc_stop);
// 	while (TRUE)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			destroy_minishell(data);
// 			close(fd);
// 			exit(0);
// 		}
// 		if (!ft_strcmp(line, list->next->value))
// 		{
// 			destroy_minishell(data);
// 			close(fd);
// 			break ;
// 		}
// 		ft_putendl_fd(line, fd);
// 		free(line);
// 	}
// 	exit(0);
// }

// void	make_heredoc(t_list *token, t_minishell *data, int *fd)
// {
// 	int	pid;
// 	int	status;

// 	signal(SIGINT, SIG_IGN);
// 	pid = fork();
// 	if (pid < 0)
// 		ft_putstr_fd("fork: creating error\n", STDERR_FILENO);
// 	if (pid == 0)
// 	{
// 		g_ms.fd_heredoc = open_heredoc_file(error);
// 		if (g_ms.fd_heredoc == -1)
// 			return ;
// 		write_heredoc_file(delimiter);
// 	}
// 	waitpid(pid, &status, 0);
// 	WIFEXITED(status);
// 	g_minishell. = WEXITSTATUS(status);
// 	unlink(HERE_FILE);
// }