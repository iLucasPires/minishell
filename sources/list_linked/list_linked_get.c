#include <minishell.h>

static int	ft_two_strncmp(char *string, char *string2)
{
	return (!ft_strncmp(string, string2, ft_strtlen(string, EQUAL)) &&
			!ft_strncmp(string2, string, ft_strtlen(string2, EQUAL)));
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

char	*get_value_env(t_list **head, char *target)
{
	char	*temp_value;

	temp_value = get_value(head, target);
	if (temp_value)
	{
		return (temp_value + ft_strtlen(temp_value, EQUAL) + 1);
	}
	return (NULL);
}
