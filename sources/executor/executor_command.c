#include <minishell.h>

char	*get_path(char *command, char **paths)
{
	int		index;
	char	*command_path;

	index = 0;
	if (paths == NULL)
		return (NULL);
	while (paths[index])
	{
		command_path = ft_strjoin(paths[index], command);
		if (command_path == NULL)
			return (NULL);
		if (!access(command_path, F_OK | X_OK))
			return (command_path);
		free(command_path);
		index++;
	}
	return (NULL);
}

char	*get_path_command(t_list *list, char **paths)
{
	char	*command;
	char	*command_path;

	if (!list)
		return (NULL);
	if (!access(list->value, F_OK | X_OK))
		return (ft_strdup(list->value));
	else
	{
		while ((is_redirect(list->type) || list->type == DOCUMENT)
			&& list->next)
			list = list->next;
		command = ft_strjoin("/", list->value);
		if (command == NULL)
			return (NULL);
		command_path = get_path(command, paths);
		if (command_path == NULL)
		{
			free(command);
			return (NULL);
		}
		free(command);
		return (command_path);
	}
}

t_command	*new_cmd(t_minishell *data)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (new_cmd == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	new_cmd->pathname = get_path_command(data->tokens_aux, data->paths);
	new_cmd->args = create_arguments(data->tokens_aux);
	new_cmd->infile = STDIN_FILENO;
	new_cmd->outfile = STDOUT_FILENO;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_lstadd_back(t_command **list_cmd, t_minishell *data)
{
	t_command	*aux;

	aux = *list_cmd;
	if (*list_cmd == NULL)
	{
		*list_cmd = new_cmd(data);
		return ;
	}
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new_cmd(data);
	}
}
