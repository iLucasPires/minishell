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

int	verify_identifier(char *value)
{
	int	index;

	index = 0;
	if (ft_isdigit(*value))
		return (FALSE);
	while (value[index] != EQUAL && value[index] != '\0')
	{
		if (!ft_isalnum(value[index]) && value[index] != UNDERSCORE)
			return (FALSE);
		index++;
	}
	return (TRUE);
}

void	export_add(t_minishell *data, char *value)
{
	if (ft_isalnum(*value) || *value == UNDERSCORE)
	{
		if (ft_strchr(value, EQUAL) != NULL)
			new_node(&data->envs, value, TRUE);
		else
			new_node(&data->envs, value, FALSE);
		data->exit_code = 0;
	}
	else
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
		data->exit_code = 1;
	}
}

void	substitute_env(t_list *token_current, char *value)
{
	if (ft_strchr(value, EQUAL) != NULL)
	{
		free(token_current->value);
		token_current->value = ft_strdup(value);
		if (token_current->type == FALSE)
			token_current->type = TRUE;
			
	}
}

int	builtin_export(char **args, t_minishell *data)
{
	int		index;
	t_list	*token_current;

	index = 1;
	if (args[1] == NULL)
		show_env(data->envs);
	else if (args[1])
	{
		while (args[index] != NULL)
		{
			if (verify_identifier(args[index]) == FALSE)
			{
				ft_putstr_fd("export: ", STDERR_FILENO);
				ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
				data->exit_code = 1;
			}
			else
			{
				token_current = get_node(&data->envs, args[index]);
				if (token_current == NULL)
					export_add(data, args[index]);
				else if (token_current != NULL)
					substitute_env(token_current, args[index]);
			}
			index++;
		}
	}
	return (EXIT_SUCCESS);
}
