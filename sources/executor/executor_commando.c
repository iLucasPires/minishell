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

void	add_arguments(t_minishell *data, char **arguments)
{
	int		index;
	t_list	*temp_node;

	index = 0;
	temp_node = data->tokens;
	while (temp_node && !fsm_is_state(temp_node->value, 0))
	{
		arguments[index] = temp_node->value;
		temp_node = temp_node->next;
		index++;
	}
	arguments[index] = NULL;
}

char	**get_arguments(t_minishell *data)
{
	int		size;
	char	**arguments;

	size = count_tokens(data->tokens);
	arguments = malloc(sizeof(char *) * (size + 1));
	if (arguments == NULL)
		return (NULL);
	arguments[size] = NULL;
	add_arguments(data, arguments);
	return (arguments);
}
