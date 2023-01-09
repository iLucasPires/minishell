#include <minishell.h>

void	choose_command(t_minishell *data)
{
	if (ft_strncmp(data->tokens->value, "cd", 3) == 0)
		builtin_cd(data);
	else if (ft_strncmp(data->tokens->value, "echo", 5) == 0)
		builtin_echo(data);
	else if (ft_strncmp(data->tokens->value, "pwd", 4) == 0)
		builtin_pwd(data);
	else if (ft_strncmp(data->tokens->value, "exit", 5) == 0)
		builtin_exit(data);
	else if (ft_strncmp(data->tokens->value, "env", 4) == 0)
		builtin_env(data);
	else if (ft_strncmp(data->tokens->value, "export", 7) == 0)
		builtin_export(data);
	else if (ft_strncmp(data->tokens->value, "unset", 6) == 0)
		builtin_unset(data);
	else
		system_command(data);
}
