/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:37:41 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 15:53:51 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_env(char **args, t_minishell *data)
{
	t_list	*token_current;

	token_current = data->envs;
	if (args[1] == NULL)
	{
		while (token_current)
		{
			if (token_current->type == TRUE)
			{
				ft_putstr_fd(token_current->value, STDOUT_FILENO);
				ft_putstr_fd("\n", STDOUT_FILENO);
			}
			token_current = token_current->next;
		}
	}
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}
