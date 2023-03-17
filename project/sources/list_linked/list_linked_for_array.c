/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_linked_for_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:39:20 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 14:39:20 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_lstlen(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

int	ft_lsttlen(t_list *lst, int target)
{
	int	number_of_target;

	number_of_target = 0;
	while (lst)
	{
		if (*lst->value == target)
			number_of_target++;
		lst = lst->next;
	}
	return (number_of_target);
}

int	ft_lstnlen(t_list *lst, int target)
{
	int	size;

	size = 0;
	while (lst)
	{
		if (*lst->value == target)
			break ;
		lst = lst->next;
		size++;
	}
	return (size);
}

char	**list_to_array_string(t_list *list)
{
	int		index;
	int		size;
	t_list	*tmp;
	char	**array_string;

	tmp = list;
	if (!tmp)
		return (NULL);
	size = ft_lstlen(tmp);
	array_string = malloc(sizeof(char *) * (size + 1));
	if (!array_string)
		return (NULL);
	index = 0;
	while (tmp && index < size)
	{
		array_string[index] = tmp->value;
		tmp = tmp->next;
		index++;
	}
	array_string[size] = NULL;
	return (array_string);
}
