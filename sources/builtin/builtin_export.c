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

int	builtin_export(char **args)
{
	int index;
	t_list *token_current;

	index = 1;
	if (args[1] == NULL)
		show_env(g_data.envs);
	else if (args[1])
	{
		while (args[index] != NULL)
		{
			token_current = get_node(&g_data.envs, args[index]);
			if (token_current == NULL)
				add_env(&g_data.envs, args[index]);
			else if (token_current != NULL)
				substitute_env(token_current, args[index]);
			index++;
		}
	}
	return (EXIT_SUCCESS);
}
