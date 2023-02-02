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

int	init_file(t_command **cmd)
{
	((*cmd)->infile) = open(HERE_FILE, O_CREAT | O_RDWR, 0664);
	if ((*cmd)->infile == -1)
	{		
		dprintf(2, "ERROR NA INITFILE <<!\n");
		return (-1);
	}
	return ((*cmd)->infile);
}

static void	write_in_file(t_command **cmd, char *file_name)
{
	char *line;

	signal(SIGINT, heredoc_stop);
	while (TRUE)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			ft_putchar_fd('\n', STDOUT_FILENO);
			destroy_minishell(&g_data);
			close((*cmd)->infile);
			exit(0);
		}
		if (!ft_strcmp(line, file_name))
		{
			free(line);
			close((*cmd)->infile);
			destroy_minishell(&g_data);
			exit(0);
		}
		ft_putendl_fd(line, (*cmd)->infile);
		free(line);
	}
	exit(0);
}

void	make_heredoc(t_command **cmd, char *file_name)
{
	int	pid;
	int	status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("fork: creating error\n", STDERR_FILENO);
	if (pid == 0)
	{
		init_file(cmd);
		if ((*cmd)->infile == -1)
			return ;
		write_in_file(cmd, file_name);
	}
	else
	{
		waitpid(pid, &status, 0);
		(*cmd)->infile = open(HERE_FILE, O_RDONLY);
		WIFEXITED(status);
		g_data.exit_code = WEXITSTATUS(status);
		unlink(HERE_FILE);
	}
}