#include <minishell.h>

t_token	*create_item(char *value, int type, int is_space)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->value = value;
	new->type = type;
	new->next = NULL;
	new->is_space = is_space;
	return (new);
}

void	add_item_end(t_token **head, char *value, int type, int is_space)
{
	t_token	*tmp_head;

	if (*head == NULL)
		*head = create_item(value, type, is_space);
	else
	{
		tmp_head = *head;
		while (tmp_head->next)
			tmp_head = tmp_head->next;
		tmp_head->next = create_item(value, type, is_space);
	}
}

void	show_list_linked(t_token *head)
{
	t_token	*tmp_head;

	tmp_head = head;
	while (tmp_head)
	{
		printf("value: %s type: %d is_space: %d \n", tmp_head->value, tmp_head->type, tmp_head->is_space);
		tmp_head = tmp_head->next;
	}
}

void	free_list_linked(t_token **head)
{
	t_token	*tmp_head;

	tmp_head = *head;
	while (tmp_head)
	{
		*head = tmp_head->next;
		free(tmp_head->value);
		free(tmp_head);
		tmp_head = *head;
	}
}

char	*next_item_list_linked(t_token **head)
{
	char *value;
	t_token *tmp_head;

	tmp_head = *head;
	value = tmp_head->value;
	*head = tmp_head->next;
	return (value);
}