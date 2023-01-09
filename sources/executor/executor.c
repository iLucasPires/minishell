#include <minishell.h>

char	**create_arguments(t_list **list, int size)
{
	int		index;
	char	**array_string;

	index = 0;
	if (*list == NULL)
		return (NULL);
	array_string = ft_calloc(size + 1, sizeof(char *));
	array_string[size] = NULL;
	while (index < size)
	{
		array_string[index] = (*list)->value;
		*list = (*list)->next;
		index++;
	}
	return (array_string);
}

int	destroy_command(t_command *cmd)
{
	free(cmd->cmd);
	free(cmd->envp);
	free(cmd->args);
	return (EXIT_SUCCESS);
}

int	init_cmd(t_command *cmd, t_minishell *data, char **paths)
{
	cmd->cmd = get_path_command(data->tokens, paths);
	cmd->envp = list_to_array_string(data->envs, ft_lstlen(data->envs));
	cmd->args = create_arguments(&data->tokens, ft_lstnlen(data->tokens, BAR));
	return (EXIT_SUCCESS);
}

int	destroy_child_process(t_minishell *data, t_command *cmd, char **paths)
{
	destroy_minishell(data);
	destroy_command(cmd);
	free_all(paths);
	exit(EXIT_FAILURE);
}

int	execute_commands(t_minishell *data, char **paths)
{
	int			status;
	pid_t		pid;
	t_command	cmd;

	if (pipe(data->pipefd) == -1)
		return (EXIT_FAILURE);
	init_cmd(&cmd, data, paths);
	pid = fork();
	if (pid == 0)
	{
		if (cmd.cmd != NULL)
			execve(cmd.cmd, cmd.args, cmd.envp);
		destroy_child_process(data, &cmd, paths);
	}
	else
	{
		waitpid(pid, &status, 0);
		destroy_command(&cmd);
	}
	return (EXIT_SUCCESS);
}

int	system_command(t_minishell *data)
{
	char	**path;
	t_list	*temp;

	temp = data->tokens;
	path = ft_split(get_value_env(&data->envs, "PATH"), ':');
	if (path == NULL)
	{
		message_command_not_found(data->tokens);
		return (EXIT_FAILURE);
	}
	while (data->tokens != NULL)
	{
		execute_commands(data, path);
		if (data->tokens != NULL && data->tokens->value[0] == BAR)
			data->tokens = data->tokens->next;
	}
	data->tokens = temp;
	free_all(path);
	return (EXIT_SUCCESS);
}
