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
	init_resources(cmd, data);
	exec_builtins(cmd->args, data);
	close_files(cmd);
	reset_int_out(data);
}

void close_resources(t_minishell *data)
{
	reset_int_out(data);
	destroy_executor(data);
}

void execute_builtin_child(t_command *cmd, t_minishell *data, int child_index)
{
	for (int i = 0; i < data->count_cmd; i++)
	{
		if (i != child_index)
			close_pipe_fds(data, i);
	}
	make_redirects(cmd, child_index, data);
	exec_builtins(cmd->args, data);
	close_files(cmd);
	close_pipe_fds(data, child_index);

}
