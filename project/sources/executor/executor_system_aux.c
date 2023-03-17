/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_system_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:38:37 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 15:00:32 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	make_redirects(t_command *cmd, int child_index, t_executor *exec)
{
	if (cmd->outfile > 2)
		dup2(cmd->outfile, STDOUT_FILENO);
	else if (child_index < exec->count_cmd - 1)
	{
		dup2(exec->pipe[child_index][STDOUT_FILENO], STDOUT_FILENO);
		close(exec->pipe[child_index][STDIN_FILENO]);
	}
	if (cmd->infile > 2)
		dup2(cmd->infile, STDIN_FILENO);
	else if (child_index > 0)
		dup2(exec->pipe[child_index - 1][STDIN_FILENO], STDIN_FILENO);
}

void	close_files(t_command *cmd)
{
	if (cmd->infile > 2)
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
}

void	close_pipe_fds(t_executor *exec, int child_index)
{
	if (child_index > 0)
		close(exec->pipe[child_index - 1][STDIN_FILENO]);
	if (child_index < exec->count_cmd - 1)
		close(exec->pipe[child_index][STDOUT_FILENO]);
}
