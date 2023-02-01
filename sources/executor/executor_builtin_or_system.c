#include <minishell.h>

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	return (0);
}

int	builtins(t_command **cmd, t_executor **exec)
{
	char	**args;

	(void)(exec);
	args = (*cmd)->args;
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
