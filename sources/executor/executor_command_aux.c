#include <minishell.h>

void print_tcommand(t_command *c, int i)
{
	int j;

	j = 0;
	printf("%dº TCOMMAND: \n", i);
	printf("ARGS: ");
	while (c->args[j])
	{
		printf("%s ", c->args[j]);
		j++;
	}
	printf("\n");
	printf("CMD: %s\n", c->pathname);
	printf("INFILE: %d\n", c->infile);
	printf("OUTFILE: %d\n", c->outfile);
	printf("---------------------------------------\n");
	if (c->next)
		print_tcommand(c->next, i + 1);
}

int 	size_args(t_list *list)
{
	t_list *aux;
	int i;

	i = 0;
	aux = list;
	while (aux != NULL && aux->type != PIPE)
	{
		if (aux->type == WORD)
			i++;
		aux = aux->next;
	}
	return (i + 1);
}

char	**create_arguments(t_list *list)
{
	char **args;
	int size;
	int i;

	i = 0;
	size = size_args(list);
	args = ft_calloc(sizeof(char *), size);
	while (i < size - 1)
	{
		if (list->type == WORD)
		{
			args[i] = list->value;
			i++;
		}
		list = list->next;
	}
	return (args);
}

t_command *create_command_table(t_minishell *data)
{
	t_command *cmd_table;

	cmd_table = malloc(sizeof(t_command));
	cmd_table->pathname = get_path_command(data->tokens_aux, data->paths);
	cmd_table->args = create_arguments(data->tokens_aux);
	cmd_table->infile = STDIN_FILENO;
	cmd_table->outfile = STDOUT_FILENO;
	cmd_table->next = NULL;
	return (cmd_table);
}

void ft_lstadd_back(t_command **head, t_command *new_cmd_node)
{
	t_command *aux;

	if (*head == NULL)
	{
		*head = new_cmd_node;
		return ;
	}
	aux = *head;
	while (aux->next)
		aux = aux->next;
	aux->next = new_cmd_node;
}

t_command *create_cmd_list(t_minishell *data)
{
	int index;
	t_command *head;

	index = 0;
	head = NULL;
	while (index < count_pipes(data->tokens) + 1)
	{
		ft_lstadd_back(&head, create_command_table(data));
		while (data->tokens_aux != NULL && data->tokens_aux->type != PIPE)
			data->tokens_aux = data->tokens_aux->next;
		if (data->tokens_aux)
			data->tokens_aux = data->tokens_aux->next;
		index++;
	}
	// print_tcommand(*head, 1);
	return (head);
}

void destroy_cmd_list(t_command *cmd_list)
{
	t_command *aux;

	while (cmd_list)
	{
		aux = cmd_list;
		cmd_list = cmd_list->next;
		free(aux->pathname);
		free(aux->args);
		free(aux);
	}
}