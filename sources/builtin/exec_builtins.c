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

int	exec_builtins(char **args)
{
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args));
	return (0);
}

void	execute_builtin(t_command *cmd)
{
	int	saved[2];

	saved[STDIN_FILENO] = dup(STDIN_FILENO);
	saved[STDOUT_FILENO] = dup(STDOUT_FILENO);
	dup_fds(cmd);
	exec_builtins(cmd->args);
	dup_saved_fds(saved);
	close_saved_fds(saved);
	close_fds(cmd);
}
