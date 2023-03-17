/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:37:57 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 15:37:58 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_unset(char **args, t_minishell *data)
{
	int		index;
	t_list	*token_current;

	index = 1;
	while (args[index])
	{
		token_current = get_node(&data->envs, args[index]);
		if (token_current)
			delete_node(&data->envs, token_current);
		index++;
	}
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}
