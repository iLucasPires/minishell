#include <minishell.h>

void init_file(t_file **file)
{
    file->fd = open(HERE_FILE, O_CREAT | O_RDWR | O_TRUNC, 0664);
    if (file->fd == -1)
        exit(1);
}

void write_in_file(t_file **file)
{
	while (true)
	{
		file->keepli = readline("> ");
		if (!file->keepli)
		{
			free(file->keepli);
			close(fd);
			exit(0);
		}
    	ft_putstr_fd(file->keepli, file->fd);
	}
    ft_putendl_fd(file->keepli, file->fd);
}

void	make_heredoc(t_file *file)
{
	int	pid;
	int	status;

    init_file(&file);
	pid = fork();
	if (pid < 0)
		exit(0);
	if (pid == 0)
		write_in_file(&file);
	else
	{
		waitpid(pid, &status, 0);
		*fd = open(TMP_FILE, O_RDONLY);
	}
	unlink(HERE_FILE);
}
