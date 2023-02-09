#include <minishell.h>

void	make_redirects(t_command *cmd, int child_index, t_minishell *data)
{
	if (cmd->outfile > 2)
		dup2(cmd->outfile, STDOUT_FILENO);
	else if (child_index < data->count_cmd - 1)
	{
		dup2(data->pipe[child_index][STDOUT_FILENO], STDOUT_FILENO);
		close(data->pipe[child_index][STDIN_FILENO]);
	}
	if (cmd->infile > 2)
		dup2(cmd->infile, STDIN_FILENO);
	else if (child_index > 0)
		dup2(data->pipe[child_index - 1][STDIN_FILENO], STDIN_FILENO);
}


void close_files(t_command *cmd)
{
	if (cmd->infile > 2)
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
}

void	close_pipe_fds(t_minishell *data, int child_index)
{
	if (child_index > 0)
		close(data->pipe[child_index - 1][STDIN_FILENO]);
	if (child_index < data->count_cmd - 1)
		close(data->pipe[child_index][STDOUT_FILENO]);
}

void	builtin_redirect(t_command *cmd)
{
	if (cmd->outfile > 2)
		dup2(cmd->outfile, STDOUT_FILENO);
	if (cmd->infile > 2)
		dup2(cmd->infile, STDIN_FILENO);
}

void	init_resources(t_command *cmd, t_minishell *data)
{
	data->aux_in = dup(STDIN_FILENO);
	data->aux_out = dup(STDOUT_FILENO);
	builtin_redirect(cmd);
}


void	reset_int_out(t_minishell *data)
{
	dup2(data->aux_in, STDIN_FILENO);
	dup2(data->aux_out, STDOUT_FILENO);
	close(data->aux_in);
	close(data->aux_out);
}

void	destroy_executor(t_minishell *data)
{
	int index;
	int size;

	index = 0;
	size = ft_lsttlen(data->tokens, BAR);
	while (index < size)
	{
		free(data->pipe[index]);
		index++;
	}
	free(data->pipe);
	free(data->pid);
}