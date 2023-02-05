#include <minishell.h>

int	size_args(t_list *list)
{
	int	count;

	count = 0;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == WORD)
			count++;
		list = list->next;
	}
	return (count + 1);
}

char	**create_arguments(t_list *list)
{
	int		index;
	char	**args;

	index = 0;
	args = malloc(sizeof(char *) * size_args(list));
	if (args == NULL)
		return (NULL);
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == WORD)
		{
			args[index] = list->value;
			index++;
		}
		list = list->next;
	}
	return (args);
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
