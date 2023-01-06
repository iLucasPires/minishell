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

void	add_env(t_list **env, char *value)
{
	if (ft_isalpha(*value) || *value == UNDERSCORE)
	{
		if (ft_strchr(value, EQUAL) != NULL)
			new_node(env, value, true);
		else
			new_node(env, value, false);
	}
	else
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(value, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	}
}

void	substitute_env(t_list *token_current, char *value)
{
	if (ft_strchr(value, EQUAL) != NULL)
	{
		free(token_current->value);
		token_current->value = ft_strdup(value);
		if (token_current->type == false)
			token_current->type = true;
	}
}
