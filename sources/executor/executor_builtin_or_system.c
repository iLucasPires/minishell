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

int b_exit(char **args) {
  if (args[1] != NULL) {
    int status = ft_atoi(args[1]);
    exit(status);
  } else {
    exit(0);
  }
}

int is_builtin(char *str)
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
	return(0);
}

int builtins(t_command **cmd)
{
	if (ft_strcmp((*cmd)->args[0], "pwd") == 0)
		return(pwd());
	else if (ft_strcmp((*cmd)->args[0], "exit") == 0)
		return(b_exit((*cmd)->args));
	return (0);
}
