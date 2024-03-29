/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_linked_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:39:16 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 14:39:16 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_list	*node_temp;

	if (head == NULL)
		return ;
	while (*head != NULL)
	{
		node_temp = *head;
		*head = (*head)->next;
		free(node_temp->value);
		free(node_temp);
	}
}
