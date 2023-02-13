/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:38:18 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 14:38:18 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	dup_fds(t_command *cmd)
{
	if (cmd->infile > 2)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile > 2)
		dup2(cmd->outfile, STDOUT_FILENO);
}

void	close_fds(t_command *cmd)
{
	if (cmd->infile > 2)
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
}
