#include <minishell.h>

int	cmd_builtins(t_minishell *data, int size)
{
	if (ft_strncmp(data->tokens->value, "cd", 3) == 0)
		return (builtin_cd(data), 1);
	else if (ft_strncmp(data->tokens->value, "echo", 5) == 0)
		return (builtin_echo(data, size), 1);
	else if (ft_strncmp(data->tokens->value, "pwd", 4) == 0)
		return (builtin_pwd(data), 1);
	else if (ft_strncmp(data->tokens->value, "exit", 5) == 0)
		return (builtin_exit(data), 1);
	else if (ft_strncmp(data->tokens->value, "env", 4) == 0)
		return (builtin_env(data), 1);
	else if (ft_strncmp(data->tokens->value, "export", 7) == 0)
		return (builtin_export(data), 1);
	else if (ft_strncmp(data->tokens->value, "unset", 6) == 0)
		return (builtin_unset(data), 1);
	return (0);
}
