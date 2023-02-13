#include <minishell.h>

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "pwd") ||
		!ft_strcmp(str, "echo") || !ft_strcmp(str, "env") ||
		!ft_strcmp(str, "export") || !ft_strcmp(str, "unset") ||
		!ft_strcmp(str, "exit"))
		return (TRUE);
	else
		return (FALSE);
}

int	exec_builtins(char **args, t_minishell *data)
{
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args, data));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, data));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args, data));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, data));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, data));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, data));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, data));
	return (0);
}

void	execute_builtin(t_command *cmd, t_minishell *data)
{
	data->exec.aux_in = dup(STDIN_FILENO);
	data->exec.aux_out = dup(STDOUT_FILENO);
	if (cmd->infile > 2)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile > 2)
		dup2(cmd->outfile, STDOUT_FILENO);
	exec_builtins(cmd->args, data);
	close_files(cmd);
	dup2(data->exec.aux_in, STDIN_FILENO);
	dup2(data->exec.aux_out, STDOUT_FILENO);
	close(data->exec.aux_in);
	close(data->exec.aux_out);
}

void	execute_builtin_child(t_command *cmd, t_minishell *data,
		int child_index)
{
	int	index;

	index = 0;
	while (index < data->exec.count_cmd)
	{
		if (index != child_index)
			close_pipe_fds(&data->exec, index);
		index++;
	}
	make_redirects(cmd, child_index, &data->exec);
	exec_builtins(cmd->args, data);
	close_files(cmd);
	close_pipe_fds(&data->exec, child_index);
	destroy_execute_system(data);
	destroy_minishell(data);
	exit(data->exit_code);
}
