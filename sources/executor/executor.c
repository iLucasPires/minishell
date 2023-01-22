#include <minishell.h>

int	destroy_child_process(t_minishell *data, t_command *cmd)
{
	destroy_minishell(data);
	destroy_command(cmd);
	free_all(data->paths);
	exit(EXIT_FAILURE);
}

void	execute_child_process(t_minishell *data, t_command *cmd)
{
	if (cmd->cmd != NULL)
		execve(cmd->cmd, cmd->args, cmd->envp);
	destroy_child_process(data, cmd);
}

void	execute_father_process(t_minishell *data, t_command *cmd)
{
	waitpid(data->pid, &data->status, 0);
	destroy_command(cmd);
}

int	execute_commands(t_minishell *data)
{
	t_command	cmd;

	if (pipe(data->pipefd) == FAILURE)
		return (EXIT_FAILURE);
	create_command(&cmd, data);
	data->pid = fork();
	if (!data->pid)
		execute_child_process(data, &cmd);
	else
		execute_father_process(data, &cmd);
	return (EXIT_SUCCESS);
}

