#include <minishell.h>

int destroy_child_process(t_minishell *data, t_command *cmd)
{
	(void)cmd;
	destroy_minishell(data);
	free_all(data->paths);
	exit(EXIT_FAILURE);
}

void create_executor(t_minishell *data)
{
	int index;
	int size;

	index = 0;
	size = ft_lsttlen(data->tokens, BAR);
	data->executor = malloc(sizeof(t_executor));
	data->executor->count_commands = size + 1;
	data->executor->pipe = malloc(sizeof(int *) * size);
	data->executor->pid = malloc(sizeof(int) * data->executor->count_commands);
	while (index < size)
	{
		data->executor->pipe[index] = malloc(sizeof(int) * 2);
		index++;
	}
}

void destroy_executor(t_executor *executor)
{
	int index;

	index = 0;
	while (index < executor->count_commands - 1)
	{
		free(executor->pipe[index]);
		index++;
	}
	free(executor->pipe);
	free(executor->pid);
	free(executor);
}

void open_pipes(t_executor *executor)
{
	int i;

	i = 0;
	while (i < (executor->count_commands - 1))
	{
		pipe(executor->pipe[i]);
		i++;
	}
}

void close_pipes(t_executor *executor)
{
	int index;

	index = 0;
	while (index < (executor->count_commands - 1))
	{
		close(executor->pipe[index][STDIN_FILENO]);
		close(executor->pipe[index][STDOUT_FILENO]);
		index++;
	}
}

void wait_children(t_executor *executor)
{
	int status;
	int i;

	i = 0;
	while (i < (executor->count_commands))
	{
		waitpid(executor->pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			g_data.exit_code = WEXITSTATUS(status);
		}
		i++;
	}
}

void make_redirects(t_command *cmd, t_executor *executor, int i)
{
	if (i == 0)
	{
		if (cmd->outfile > 2)
			dup2(cmd->outfile, STDOUT_FILENO);
		if (cmd->infile > 2)
			dup2(cmd->infile, STDIN_FILENO);
		if (executor->count_commands > 1)
			dup2(executor->pipe[i][1], STDOUT_FILENO);
	}
	else if (i == (executor->count_commands - 1))
	{
		if (cmd->outfile > 2)
			dup2(cmd->outfile, STDOUT_FILENO);
		if (cmd->infile > 2)
			dup2(cmd->infile, STDIN_FILENO);
		if (executor->count_commands > 1)
			dup2(executor->pipe[i - 1][0], STDIN_FILENO);
	}
	else
	{
		if (cmd->outfile > 2)
			dup2(cmd->outfile, STDOUT_FILENO);
		if (cmd->infile > 2)
			dup2(cmd->infile, STDIN_FILENO);
		dup2(executor->pipe[i - 1][0], STDIN_FILENO);
		dup2(executor->pipe[i][1], STDOUT_FILENO);
	}
}

void builtin_redirect(t_command *cmd)
{
	if (cmd->infile > 2)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile > 2)
		dup2(cmd->outfile, STDOUT_FILENO);
}

void init_resources(t_executor *exec, t_command *cmd)
{
	exec->aux_in = dup(STDIN_FILENO);
	exec->aux_out = dup(STDOUT_FILENO);
	cmd->infile = dup(STDIN_FILENO);
	cmd->outfile = dup(STDOUT_FILENO);
}

void reset_int_out(t_executor *executor)
{
	dup2(executor->aux_in, 0);
	dup2(executor->aux_out, 1);
	close(executor->aux_in);
	close(executor->aux_out);
}

void close_files(t_command *cmd)
{
	if (cmd->infile > 2)
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
}

void execute_children(t_command *cmd, t_minishell *data, int i)
{
	if (!cmd->args[0])
		return;
	if (is_builtin(cmd->args[0]) && data->executor->count_commands == 1)
	{
		init_resources(data->executor, cmd);
		builtins(cmd->args);
		close_files(cmd);
		reset_int_out(data->executor);
		return;
	}
	data->executor->pid[i] = fork();
	if (data->executor->pid[i] == 0)
	{
		make_redirects(cmd, data->executor, i);
		close_pipes(data->executor);
		if (execve(cmd->pathname, cmd->args, data->envp) == -1)
		{
			message_command_not_found(cmd->args[0], &data->exit_code);
			exit(EXIT_FAILURE);
		}
	}
}

int syntax_error_pipe(t_list *tokens)
{
	if (tokens->type == PIPE)
		return (ft_putstr_fd(ERROR_SYNTAX, 2), 2);
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (tokens->next == NULL)
				return (ft_putstr_fd(ERROR_SYNTAX, 2), 2);
		}
		tokens = tokens->next;
	}
	return (0);
}

void execute_childrens(t_command *cmd_list, t_minishell *data)
{
	int index;

	index = 0;
	open_pipes(data->executor);
	while (index < data->executor->count_commands)
	{
		execute_children(cmd_list, data, index);
		cmd_list = cmd_list->next;
		index++;
	}
	close_pipes(data->executor);
	wait_children(data->executor);
}

int verify_error_or_create_data(t_minishell *data)
{
	char *aux;

	if (syntax_error_pipe(data->tokens) != 0)
	{
		data->exit_code = 2;
		return (EXIT_FAILURE);
	}
	aux = get_value(&data->envs, "PATH");
	data->paths = ft_split(aux, ':');
	if (data->paths == NULL)
	{
		message_command_not_found(data->tokens->value, &data->exit_code);
		data->exit_code = 127;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int system_command(t_minishell *data)
{
	t_command *cmd_list;

	if (verify_error_or_create_data(data) == EXIT_FAILURE)
		return (data->exit_code);
	data->tokens_aux = data->tokens;
	data->envp = list_to_array_string(data->envs);
	cmd_list = create_cmd_list(data);
	check_red(data->tokens, cmd_list);
	create_executor(data);
	execute_childrens(cmd_list, data);
	destroy_executor(data->executor);
	destroy_cmd_list(cmd_list);
	free_all(data->paths);
	free(data->envp);

	return (data->exit_code);
}
