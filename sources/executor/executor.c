#include <minishell.h>

int	system_command(t_minishell *data)
{
	pid_t	pid;
	char	*command;
	char	**arguments;

	command = get_commando(data);
	if (!command)
	{
		ft_putstr_fd(data->tokens->value, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free(command);
		return (EXIT_FAILURE);
	}
	arguments = get_arguments(data);
	pid = fork();
	if (pid == 0)
	{
		execve(command, arguments, data->envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(arguments);
		free(command);
	}
	return (EXIT_SUCCESS);
}

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
