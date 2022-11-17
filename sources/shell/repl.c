#include <minishell.h>


char	*get_acess_cmd(const char *path, char **dirs)
{
	t_command	c;
	int 		index;

	index = 0;
	while (dirs[index])
	{
		c.path = ft_strjoin(dirs[index], path);
		if (!access(c.path, F_OK))
			return (c.path);
		free(c.path);
		index++;
	}
	return (NULL);
}

char	*get_cmd_path(char *line)
{
	char *command;
	char **dirs;

	dirs = ft_split(getenv("PATH"), ':');
	command = get_acess_cmd(ft_strjoin("/", line), dirs);
	

	return (command);
}

static void	error_readline(void *ptr)
{
	if (ptr == NULL)
	{
		ft_putstr_fd(ERROR_READLINE, STDERR_FILENO);
		free(ptr);
		exit(EXIT_FAILURE);
	}
}

void	read_eval_print_loop(t_repl *repl)
{
	while (true)
	{
		repl->line = readline(PROMPT);
		error_readline(repl->line);
		add_history(repl->line);
		printf("path command: %s\n", get_cmd_path(repl->line));
		free(repl->line);
	}
}
