#include <minishell.h>

void	show_env(t_list *tokens)
{
	char	*value;

	while (tokens)
	{
		value = tokens->value;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putlstr_fd(value, ft_strtlen(value, EQUAL), STDOUT_FILENO);
		if (tokens->type == TRUE)
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


int	builtin_export(t_minishell *data)
{
	t_list *temp;
	t_list *token_current;

	temp = data->tokens;
	if (temp->next == NULL)
		show_env(data->envs);
	else if (temp->next)
	{
		while (temp->next)
		{
			token_current = get_node(&data->envs, temp->next->value);
			if (token_current == NULL)
				add_env(&data->envs, temp->next->value);
			else if (token_current != NULL)
				substitute_env(token_current, temp->next->value);
			temp = temp->next;
		}
	}
	return (EXIT_SUCCESS);
}
