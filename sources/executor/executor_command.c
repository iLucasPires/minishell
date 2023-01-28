#include <minishell.h>

char	*get_path(char *command, char **paths)
{
	int		index;
	char	*command_path;

	index = 0;
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
