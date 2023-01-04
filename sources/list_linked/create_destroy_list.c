#include <minishell.h>

static t_token	*create_item(char *value, int type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	new_node->value = ft_strdup(value);
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	add_item_end(t_token **head, char *value, int type)
{
	t_token	*token;

	if (*head == NULL)
		*head = create_item(value, type);
	else
	{
		token = *head;
		while (token->next)
			token = token->next;
		token->next = create_item(value, type);
	}
}

void free_item(t_token **head, t_token *item)
{
	t_token	*token;

	token = *head;
	if (token == item)
	{
		*head = token->next;
		free(token->value);
		free(token);
	}
	else
	{
		while (token->next != item)
			token = token->next;
		token->next = item->next;
		free(item->value);
		free(item);
	}
}


void	free_list_linked(t_token **head)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		*head = token->next;
		free(token->value);
		free(token);
		token = *head;
	}
}
