#include <minishell.h>

void	delete_node(t_list **head, t_list *item)
{
	t_list	*node;

	node = *head;
	if (node == item)
	{
		*head = node->next;
		free(node->value);
		free(node);
	}
	else
	{
		while (node->next != item)
			node = node->next;
		node->next = item->next;
		free(item->value);
		free(item);
	}
}

void	destroy_list(t_list **head)
{
	t_list	*node;

	node = *head;
	while (node)
	{
		*head = node->next;
		free(node->value);
		free(node);
		node = *head;
	}
}
