#include <minishell.h>

t_token	*create_item(char *value, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->value = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_item_end(t_token **head, char *value, int type)
{
	t_token	*tmp_head;

	if (*head == NULL)
		*head = create_item(value, type);
	else
	{
		tmp_head = *head;
		while (tmp_head->next)
			tmp_head = tmp_head->next;
		tmp_head->next = create_item(value, type);
	}
}

void	show_list_linked(t_token *head)
{
	t_token	*tmp_head;

	tmp_head = head;
	while (tmp_head)
	{
		printf("value: %s type: %d \n", tmp_head->value, tmp_head->type);
		tmp_head = tmp_head->next;
	}
}

void	free_list_linked(t_token **head)
{
	t_token	*tmp_head;

	tmp_head = *head;
	while (tmp_head)
	{
		free(tmp_head->value);
		tmp_head = tmp_head->next;
	}
	*head = NULL;
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