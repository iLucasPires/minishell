#include <minishell.h>

int	size_args(t_list *list)
{
	int count;

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
	args[index] = NULL;
	return (args);
}


t_command	*create_cmd_list(t_minishell *data)
{
	int			index;
	t_command	*list_cmd;

	index = 0;
	list_cmd = NULL;
	while (index < ft_lsttlen(data->tokens, BAR) + 1)
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

void	create_executor(t_minishell *data)
{
	int	index;
	int	size;

	index = 0;
	size = ft_lsttlen(data->tokens, BAR);
	data->exec.count_cmd = size + 1;
	data->exec.pipe = malloc(sizeof(int *) * size);
	data->exec.pid = malloc(sizeof(int) * data->exec.count_cmd);
	while (index < size)
	{
		data->exec.pipe[index] = malloc(sizeof(int) * 2);
		index++;
	}
}
