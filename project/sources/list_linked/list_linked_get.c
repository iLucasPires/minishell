/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_linked_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:39:22 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 15:05:12 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_two_strncmp(char *string, char *string2)
{
	if ((!ft_strncmp(string, string2, ft_strtlen(string, EQUAL))) && \
		(!ft_strncmp(string2, string, ft_strtlen(string2, EQUAL))))
		return (TRUE);
	return (FALSE);
}

t_list	*get_node(t_list **head, char *target)
{
	t_list	*temp_node;

	temp_node = *head;
	while (temp_node)
	{
		if (ft_two_strncmp(temp_node->value, target))
		{
			return (temp_node);
		}
		temp_node = temp_node->next;
	}
	return (NULL);
}

char	*get_value(t_list **head, char *target)
{
	t_list	*temp_node;

	temp_node = *head;
	while (temp_node)
	{
		if (ft_two_strncmp(temp_node->value, target))
		{
			return (temp_node->value);
		}
		temp_node = temp_node->next;
	}
	return (NULL);
}

char	*my_getenv(t_list **head, char *target)
{
	char	*string_aux;
	char	*temp_value;

	temp_value = get_value(head, target);
	if (temp_value)
	{
		string_aux = ft_strdup(ft_strchr(temp_value, EQUAL) + 1);
		return (string_aux);
	}
	return (NULL);
}
