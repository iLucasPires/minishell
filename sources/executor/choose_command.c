#include <minishell.h>

int	count_tokens(t_list *tokens)
{
	int	count;

	count = 0;
	while (tokens && !fsm_is_state(tokens->value, 0))
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

char	*get_commando(t_minishell *data)
{
	int		index;
	char	*command;
	char	*comand_path;

	index = 0;
	command = ft_strjoin("/", data->tokens->value);
	while (data->paths[index])
	{
		comand_path = ft_strjoin(data->paths[index], command);
		if (access(comand_path, F_OK) == 0)
			return (comand_path);
		index++;
	}
	return (NULL);
}

char	**get_arguments(t_minishell *data)
{
	int		size;
	char	**arguments;

	size = count_tokens(data->tokens);
	arguments = malloc(sizeof(char *) * (size + 1));
	if (!arguments)
		return (NULL);
	arguments[size] = NULL;
	size = 0;
	while (data->tokens && !fsm_is_state(data->tokens->value, 0))
	{
		arguments[size] = data->tokens->value;
		data->tokens = data->tokens->next;
		size++;
	}
	return (arguments);
}

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
		return (1);
	}
	arguments = get_arguments(data);
	pid = fork();
	if (pid == 0)
	{
		execve(command, arguments, data->envp);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
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
