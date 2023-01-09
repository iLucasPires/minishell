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
