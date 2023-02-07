#include <minishell.h>

static t_list	*create_node(char *value, int type)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	new_node->value = ft_strdup(value);
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	new_node(t_list **head, char *value, int type)
{
	t_list	*node;

	if (*head == NULL)
		*head = create_node(value, type);
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = create_node(value, type);
	}
}
