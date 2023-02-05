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

t_command	*create_cmd_list(t_minishell *data)
{
	int			index;
	t_command	*list_cmd;

	index = 0;
	list_cmd = NULL;
	while (index < count_pipes(data->tokens) + 1)
	{
		ft_lstadd_back(&list_cmd, data);
		while (data->tokens_aux != NULL && data->tokens_aux->type != PIPE)
			data->tokens_aux = data->tokens_aux->next;
		if (data->tokens_aux != NULL)
			data->tokens_aux = data->tokens_aux->next;
		index++;
	}
	return (list_cmd);
}

void	destroy_cmd_list(t_command *list_cmd)
{
	t_command	*aux;

	while (list_cmd)
	{
		aux = list_cmd;
		list_cmd = list_cmd->next;
		free(aux->pathname);
		free(aux->args);
		free(aux);
	}
}