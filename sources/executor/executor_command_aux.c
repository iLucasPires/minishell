#include <minishell.h>

char	**create_arguments(t_list **list)
{
	int		index;
	int		size;
	char	**array_string;

	index = 0;
	size = ft_lstnlen(*list, BAR);
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

int	create_command(t_command *cmd, t_minishell *data)
{
	cmd->cmd = get_path_command(data->tokens_aux, data->paths);
	cmd->envp = list_to_array_string(data->envs);
	cmd->args = create_arguments(&data->tokens_aux);
	return (EXIT_SUCCESS);
}
