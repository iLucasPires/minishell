/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:39:26 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 15:06:04 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_all(char **pointer)
{
	int	index;

	index = 0;
	if (pointer == NULL)
		return ;
	while (pointer[index])
	{
		free(pointer[index]);
		index++;
	}
	free(pointer);
}

void	destroy_minishell(t_minishell *data)
{
	rl_clear_history();
	destroy_list(&data->envs);
	destroy_list(&data->tokens);
	free(data->line);
}

void	destroy_repl(t_minishell *data)
{
	free(data->line);
	destroy_list(&data->tokens);
}

void	destroy_exit_minishell(t_minishell *data, int status)
{
	destroy_minishell(data);
	exit(status);
}
