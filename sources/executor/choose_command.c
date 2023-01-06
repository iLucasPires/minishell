#include <minishell.h>

int	count_tokens(t_list *tokens)
{
	int		count;
	t_list	*temp;

	count = 0;
	temp = tokens;
	while (temp && !fsm_is_state(temp->value, 0))
	{
		count++;
		temp = temp->next;
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
		if (!access(comand_path, F_OK | X_OK))
		{
			free(command);
			return (comand_path);
		}
		free(comand_path);
		index++;
	}
	return (NULL);
}

char	**get_arguments(t_minishell *data)
{
	int		size;
	char	**arguments;
	t_list	*tokens_temp;

	tokens_temp = data->tokens;
	size = count_tokens(tokens_temp);
	arguments = malloc(sizeof(char *) * (size + 1));
	if (!arguments)
		return (NULL);
	arguments[size] = NULL;
	size = 0;
	while (tokens_temp && !fsm_is_state(tokens_temp->value, 0))
	{
		arguments[size] = tokens_temp->value;
		tokens_temp = tokens_temp->next;
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
