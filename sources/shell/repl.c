#include <minishell.h>

char	*get_acess_cmd(const char *path, char **dirs)
{
	char	*aux;
	int		index;

	index = 0;
	while (dirs[index])
	{
		aux = ft_strjoin(dirs[index], path);
		if (!access(aux, F_OK))
			return (aux);
		free(aux);
		index++;
	}
	return (NULL);
}

t_command	get_cmd_path(char *line, char **dirs)
{
	char		*path;
	t_command	command;

	command.name = ft_strtrim(line, " ");
	path = ft_strjoin("/", command.name);
	command.path = get_acess_cmd(path, dirs);
	command.args = ft_split(line, ' ');
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

void	excute_comand(t_command command, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execve(command.path, command.args, envp);
	waitpid(pid, &status, 0);
}

void	read_eval_print_loop(t_repl *data)
{
	while (true)
	{
		data->line = readline(PROMPT);
		error_readline(data->line);
		add_history(data->line);
		excute_comand(get_cmd_path(data->line, data->dirs), data->envp);
		free(data->line);
	}
}
