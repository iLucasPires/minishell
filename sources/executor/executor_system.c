#include <minishell.h>

void	execute_builtin(t_command *cmd, t_minishell *data);

void	create_executor(t_minishell *data)
{
	int	index;
	int	size;

	index = 0;
	size = ft_lsttlen(data->tokens, BAR);
	data->count_cmd = size + 1;
	data->pid = malloc(sizeof(int) * data->count_cmd);
	data->pipe = malloc(sizeof(int *) * size);
	while (index < size)
	{
		data->pipe[index] = malloc(sizeof(int) * 2);
		index++;
	}
}

void	execute_system(t_command *cmd, t_minishell *data, int child_index)
{
	dup_fds(cmd);
	dup_pipe_fds(data, child_index);
	if (cmd->pathname)
	{
		data->exit_code = 0;
		execve(cmd->pathname, cmd->args, data->envp);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
}

void	execute_children(t_command *cmd, t_minishell *data, int child_index)
{
	pid_t	pid_current;

	if (is_builtin(*cmd->args) && data->count_cmd == 1)
		execute_builtin(cmd, data);
	else
	{
		pid_current = fork();
		if (pid_current < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid_current == 0)
		{
			if (is_builtin(*cmd->args))
			{
				dup_fds(cmd);
				dup_pipe_fds(data, child_index);
				execute_builtin(cmd, data);
				exit(data->exit_code);
			}
			else
				execute_system(cmd, data, child_index);
		}
		data->pid[child_index] = pid_current;
	}
}

void	execute_childrens(t_command *cmd_list, t_minishell *data)
{
	int	index;

	index = 0;
	while (index < data->count_cmd)
	{
		if (index < data->count_cmd - 1)
			pipe(data->pipe[index]);
		execute_children(cmd_list, data, index);
		close_pipe_fds(data, index);
		waitpid(data->pid[index], &data->status, 0);
		if (WIFEXITED(data->status))
			data->exit_code = WEXITSTATUS(data->status);
		cmd_list = cmd_list->next;
		index++;
	}
}

void	destroy_data(t_minishell *data)
{
	free_all(data->paths);
	free(data->envp);
}

int	system_command(t_minishell *data)
{
	t_command	*cmd_list;

	if (syntax_error_pipe(data->tokens) != 0)
	{
		data->exit_code = 2;
		return (EXIT_FAILURE);
	}
	data->paths = ft_split(get_value(&data->envs, "PATH"), ':');
	data->envp = list_to_array_string(data->envs);
	data->tokens_aux = data->tokens;
	cmd_list = create_cmd_list(data);
	check_redirected(data, cmd_list);
	if (cmd_list->args[0] != NULL)
	{
		create_executor(data);
		execute_childrens(cmd_list, data);
		destroy_executor(data);
	}
	destroy_cmd_list(cmd_list);
	destroy_data(data);
	return (data->exit_code);
}
