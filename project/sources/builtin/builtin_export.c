/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:37:52 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 16:10:54 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	export(t_minishell *data, char *value)
{
	t_list	*token_current;

	token_current = get_node(&data->envs, value);
	if (token_current == NULL)
		export_add(data, value);
	else if (token_current != NULL)
		export_update(token_current, value);
}

int	builtin_export(char **args, t_minishell *data)
{
	int	index;

	index = 1;
	if (args[1] == NULL)
		show_env(data->envs);
	else if (args[1])
	{
		while (args[index] != NULL)
		{
			if (verify_identifier(args[index]) == FALSE)
			{
				ft_putstr_fd("export: not a valid identifier\n", 2);
				data->exit_code = 1;
			}
			else
			{
				export(data, args[index]);
			}
			index++;
		}
	}
	return (EXIT_SUCCESS);
}
