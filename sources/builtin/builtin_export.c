#include <minishell.h>

void	show_env(t_token *tokens)
{
	char	*value;

	while (tokens)
	{
		value = tokens->value;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putlstr_fd(value, ft_strtlen(value, EQUAL), STDOUT_FILENO);
		if (tokens->type == true)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(SDQUOTE, STDOUT_FILENO);
			ft_putstr_fd(ft_strchr(value, EQUAL) + 1, STDOUT_FILENO);
			ft_putstr_fd(SDQUOTE, STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		tokens = tokens->next;
	}
}

void	substitute_env(t_token *token_current, char *value)
{
	if (ft_strchr(value, EQUAL) != NULL)
	{
		free(token_current->value);
		token_current->value = ft_strdup(value);
		if (token_current->type == false)
			token_current->type = true;
	}
}

void	add_env(t_token **env, char *value)
{
	if (ft_strchr(value, EQUAL) != NULL)
		add_item_end(env, value, true);
	else
		add_item_end(env, value, false);
}

int	builtin_export(t_repl *data)
{
	t_token *temp;
	t_token *token_current;

	temp = data->head;
	if (temp->next == NULL)
		show_env(data->env);
	else if (temp->next)
	{
		while (temp->next)
		{
			token_current = get_node_list_linked(&data->env, temp->next->value);
			if (token_current == NULL)
				add_env(&data->env, temp->next->value);
			else if (token_current != NULL)
				substitute_env(token_current, temp->next->value);
			temp = temp->next;
		}
	}
	return (EXIT_SUCCESS);
}