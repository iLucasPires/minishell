#include <minishell.h>

void	dup_pipe_fds(t_minishell *cmd, int child_index)
{
	if (child_index > 0)
		dup2(cmd->pipe[child_index - 1][STDIN_FILENO], STDIN_FILENO);
	if (child_index < cmd->count_cmd - 1)
		dup2(cmd->pipe[child_index][STDOUT_FILENO], STDOUT_FILENO);
}

void	close_pipe_fds(t_minishell *cmd, int child_index)
{
    if (child_index > 0)
        close(cmd->pipe[child_index - 1][STDIN_FILENO]);
    if (child_index < cmd->count_cmd - 1)
        close(cmd->pipe[child_index][STDOUT_FILENO]);
}


void destroy_executor(t_minishell *data)
{
	int	index;
	int	size;

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