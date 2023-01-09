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
	int	size;
	int	number_of_target;

	size = 0;
	number_of_target = 0;
	while (lst)
	{
		if (*lst->value == target)
			number_of_target++;
		lst = lst->next;
		size++;
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
	int 	size;
	char	**array_string;

	index = 0;
	size = ft_lstlen(list);
	if (list == NULL)
		return (NULL);
	array_string = ft_calloc(size + 1, sizeof(char *));
	if (array_string == NULL)
		return (NULL);
	while (list != NULL && index < size)
	{
		array_string[index] = list->value;
		list = list->next;
		index++;
	}
	array_string[index] = NULL;
	return (array_string);
}
