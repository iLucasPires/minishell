/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:39:29 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 14:39:29 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigquit(t_minishell *data)
{
	if (data->line == NULL)
	{
		ft_putstr_fd("exit \n", 1);
		rl_clear_history();
		destroy_minishell(data);
		exit(g_data.exit_code);
	}
}

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_data.exit_code = 130;
	}
}
