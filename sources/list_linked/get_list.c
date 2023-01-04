#include <minishell.h>

t_token	*get_node_list_linked(t_token **head, char *value)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		if (!ft_strncmp(token->value, value, ft_strtlen(value, EQUAL)) &&
			!ft_strncmp(value, token->value, ft_strtlen(token->value, EQUAL)))
		{
			return (token);
		}
		token = token->next;
	}
	return (NULL);
}

char	*get_value_list_linked(t_token **head, char *value)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		if (!ft_strncmp(token->value, value, ft_strtlen(value, EQUAL)) &&
			!ft_strncmp(value, token->value, ft_strtlen(token->value, EQUAL)))
		{
			return (token->value);
		}
		token = token->next;
	}
	return (NULL);
}

char	*get_value_env(t_token **head, char *value)
{
	char	*temp;
	char	*temp2;

	temp = get_value_list_linked(head, value);
	if (temp)
	{
		temp2 = ft_strchr(temp, '=');
		return (temp2 + 1);
	}
	return (NULL);
}
