/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_system.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:38:40 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/14 15:16:06 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_system(t_command *cmd, t_minishell *data, int child_index)
{
	if (cmd->pathname)
	{
		data->exit_code = 0;
		close_files(cmd);
		close_pipe_fds(&data->exec, child_index);
		if (execve(cmd->pathname, cmd->args, data->envp) == -1)
		{
			stat_file(cmd->pathname, &data->exit_code);
			destroy_executor(&data->exec, data->tokens);
			destroy_execute_system(data);
			destroy_minishell(data);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		close_files(cmd);
		close_pipe_fds(&data->exec, child_index);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		destroy_executor(&data->exec, data->tokens);
		destroy_execute_system(data);
		destroy_minishell(data);
		exit(127);
	}
}

void	execute_children(t_command *cmd, t_minishell *data, int child_index)
{
	signal(SIGINT, SIG_IGN);
	data->exec.pid[child_index] = fork();
	if (data->exec.pid[child_index] < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (data->exec.pid[child_index] == 0)
	{
		signal(SIGINT, handle_sigint);
		if (cmd->infile != FAILURE && cmd->outfile != FAILURE)
		{
			make_redirects(cmd, child_index, &data->exec);
			if (*cmd->args != NULL)
			{
				if (is_builtin(*cmd->args))
					execute_builtin_child(cmd, data, child_index);
				else
					execute_system(cmd, data, child_index);
			}
			else
				destroy_pathname_not_found(data, child_index);
		}
		exit(data->exit_code);
	}
}

void	wait_childrens(t_executor *exec, u_int8_t *exit_code)
{
	int	index;

	index = 0;
	while (index < exec->count_cmd)
	{
		waitpid(exec->pid[index], &exec->status, 0);
		if (WIFEXITED(exec->status))
			*exit_code = WEXITSTATUS(exec->status);
		index++;
	}
}

void	execute_childrens(t_minishell *data)
{
	int			index;
	t_command	*cmd;

	index = 0;
	cmd = data->cmd_list;
	if (*cmd->args != NULL && (is_builtin(*cmd->args)
			&& data->exec.count_cmd == 1 && cmd->infile != FAILURE
			&& cmd->outfile != FAILURE))
		execute_builtin(cmd, data);
	else
	{
		while (index < data->exec.count_cmd)
		{
			if (index < data->exec.count_cmd - 1)
				pipe(data->exec.pipe[index]);
			execute_children(cmd, data, index);
			close_pipe_fds(&data->exec, index);
			cmd = cmd->next;
			index++;
		}
		wait_childrens(&data->exec, &data->exit_code);
	}
}

int	system_command(t_minishell *data)
{
	if (syntax_error_pipe(data->tokens) != 0)
		return (2);
	data->paths = ft_split(get_value(&data->envs, "PATH"), ':');
	data->envp = list_to_array_string(data->envs);
	data->tokens_aux = data->tokens;
	data->cmd_list = create_cmd_list(data);
	check_redirected(data, data->cmd_list);
	create_executor(data);
	execute_childrens(data);
	destroy_executor(&data->exec, data->tokens);
	destroy_execute_system(data);
	return (data->exit_code);
}
