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
	int	saved[2];

	saved[STDIN_FILENO] = dup(STDIN_FILENO);
	saved[STDOUT_FILENO] = dup(STDOUT_FILENO);
	dup_fds(cmd);
	exec_builtins(cmd->args, data);
	dup_saved_fds(saved);
	close_saved_fds(saved);
	close_fds(cmd);
}
