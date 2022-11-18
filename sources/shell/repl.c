#include <minishell.h>

void	destruct_command(t_command *command)
{
	char	**array_bi_dimensional;

	array_bi_dimensional = command->args;
	while (*array_bi_dimensional != NULL)
	{
		free(*array_bi_dimensional);
		array_bi_dimensional++;
	}
	free(command->args);
	free(command->command_name);
	free(command->path);
}

void	excute_comand(t_repl *repl, t_command *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == CHILD_PROCESS)
	{
		if (execve(command->path, command->args, repl->envp) == EXE_FALL)
			error_generic(ERROR_EXECVE);
	}
	else
	{
		waitpid(pid, &repl->status, 0);
		destruct_command(command);
	}
}

char	*parse_path(char *command, char **dirs)
{
	int		index;
	char	*aux_path;

	index = 0;
	while (dirs[index] != NULL)
	{
		aux_path = ft_strjoin(dirs[index], command);
		if (access(aux_path, F_OK) != NO_ACCESS)
			return (aux_path);
		free(aux_path);
		index++;
	}
	return (NULL);
}

int	parse_command(t_repl *data, t_command *command)
{
	char	*aux_command;

	command->command_name = ft_strtrim(data->line, " ");
	aux_command = ft_strjoin("/", command->command_name);
	command->path = parse_path(aux_command, data->dirs);
	command->args = ft_split(data->line, ' ');
	if (command->path == NULL)
	{
		printf(ERROR_COMMAND, command->command_name);
		free(aux_command);
		return (false);
	}
	free(aux_command);
	return (true);
}

void	excute_command(t_repl *repl, t_command *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == CHILD_PROCESS)
	{
		if (execve(command->path, command->args, repl->envp) == EXE_FALL)
		{
			destruct_command(command);
			printf(ERROR_EXECVE);
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, &repl->status, CHILD_PROCESS);
}

void	read_eval_print_loop(t_repl *data)
{
	t_command	command;

	while (true)
	{
		data->line = readline(PROMPT);
		if (data->line == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			rl_clear_history();
			free(data->line);
			exit(EXIT_FAILURE);
		}
		if (*data->line != '\0')
		{
			add_history(data->line);
			if (parse_command(data, &command) != false)
			{
				excute_command(data, &command);
				destruct_command(&command);
			}
				
		}
		free(data->line);
	}
}
