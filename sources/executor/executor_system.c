#include <minishell.h>

void	execute_builtin(t_command *cmd, t_minishell *data);

void	create_executor(t_minishell *data)
{
	int	index;
	int	size;

	index = 0;
	size = ft_lsttlen(data->tokens, BAR);
	data->count_cmd = size + 1;
	data->pipe = malloc(sizeof(int *) * size);
	data->pid = malloc(sizeof(int) * data->count_cmd);
	while (index < size)
	{
		data->pipe[index] = malloc(sizeof(int) * 2);
		index++;
	}
}

void	close_fds2(t_command *cmd_list)
{
	t_command	*cmd;
	int			i;

	i = 3;
	while (!close(i))
	{
		i++;
	}
	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->infile > 0)
			close(cmd->infile);
		if (cmd->outfile > 0)
			close(cmd->outfile);
		cmd = cmd->next;
	}
}

void	destroy_execute_system(t_command *cmd, t_minishell *data)
{
	destroy_cmd_list(cmd);
	destroy_executor(data);
	destroy_list(&data->tokens);
	destroy_list(&data->envs);
	free(data->line);
	free(data->envp);
	free_all(data->paths);
}

void	execute_system(t_command *cmd, t_minishell *data, int child_index)
{
	//(void)child_index;
	if (cmd->pathname)
	{
		data->exit_code = 0;
		close_files(cmd);
		close_pipe_fds(data, child_index);
		execve(cmd->pathname, cmd->args, data->envp);
	}
	else
	{
		close_files(cmd);
		close_pipe_fds(data, child_index);
		message_command_not_found(cmd->args[0], &data->exit_code);
		destroy_execute_system(cmd, data);
		exit(127);
	}
}

void	execute_children(t_command *cmd, t_minishell *data, int child_index)
{
	data->pid[child_index] = fork();
	if (data->pid[child_index] < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (data->pid[child_index] == 0)
	{
		clear_history();
		make_redirects(cmd, child_index, data);
		if (is_builtin(*cmd->args))
		{
			execute_builtin_child(cmd, data, child_index);
			destroy_execute_system(cmd, data);
			exit(data->exit_code);
		}
		else
		{
			execute_system(cmd, data, child_index);
		}
	}
}

void	wait_childrens(t_minishell *data)
{
	int	index;

	index = 0;
	while (index < data->count_cmd)
	{
		waitpid(data->pid[index], &data->status, 0);
		if (WIFEXITED(data->status))
			data->exit_code = WEXITSTATUS(data->status);
		index++;
	}
}

void	execute_childrens(t_command *cmd_list, t_minishell *data)
{
	int	index;

	index = 0;
	if (is_builtin(*cmd_list->args) && data->count_cmd == 1)
		execute_builtin(cmd_list, data);
	else
	{
		while (index < data->count_cmd)
		{
			if (index < data->count_cmd - 1)
				pipe(data->pipe[index]);
			execute_children(cmd_list, data, index);
			close_pipe_fds(data, index);
			cmd_list = cmd_list->next;
			index++;
		}
		wait_childrens(data);
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
	if (cmd_list->args[0] != NULL && cmd_list->infile != -1 && cmd_list->outfile != -1)
	{
		create_executor(data);
		execute_childrens(cmd_list, data);
		destroy_executor(data);
	}
	destroy_cmd_list(cmd_list);
	destroy_data(data);
	return (data->exit_code);
}
