/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:38:34 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 19:28:42 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	destroy_cmd_list(t_command *list_cmd)
{
	t_command	*aux;

	while (list_cmd)
	{
		aux = list_cmd;
		list_cmd = list_cmd->next;
		free(aux->pathname);
		free(aux->args);
		free(aux);
	}
}

void	destroy_execute_system(t_minishell *data)
{
	t_command	*aux;

	while (data->cmd_list)
	{
		aux = data->cmd_list;
		data->cmd_list = data->cmd_list->next;
		free(aux->pathname);
		free(aux->args);
		free(aux);
	}
	free_all(data->paths);
	free(data->envp);
}

void	destroy_executor(t_executor *exec, t_list *tokens)
{
	int	index;
	int	size;

	index = 0;
	size = ft_lsttlen(tokens, BAR);
	while (index < size)
	{
		free(exec->pipe[index]);
		index++;
	}
	free(exec->pipe);
	free(exec->pid);
}

void	destroy_pathname_not_found(t_minishell *data, int child_index)
{
	close_files(data->cmd_list);
	close_pipe_fds(&data->exec, child_index);
	destroy_executor(&data->exec, data->tokens);
	destroy_execute_system(data);
	destroy_minishell(data);
}
