#include <minishell.h>

int	destroy_child_process(t_minishell *data, t_command *cmd)
{
	(void)cmd;
	destroy_minishell(data);
	// destroy_command(cmd);
	free_all(data->paths);
	exit(EXIT_FAILURE);
}

void	execute_child_process(t_minishell *data, t_command *cmd)
{
	if (cmd->pathname != NULL)
		execve(cmd->pathname, cmd->args, cmd->envp);
	destroy_child_process(data, cmd);
}

void	execute_father_process(t_minishell *data, t_command *cmd)
{
	(void)cmd;
	waitpid(data->pid, &data->status, 0);
	// destroy_command(cmd);
}

int	execute_commands(t_minishell *data)
{
	(void)data;
	// t_command cmd;
	// int i = 0;

	// while (cmd.args[i])
	// {
	// 	printf("ARGS: %s\n", cmd.args[i]);
	// 	i++;
	// }
	// printf("CMD: %s\n", cmd.cmd);
	// printf("FD INPUT: %d\n", cmd.infile);
	// printf("FD OUTPUT: %d\n", cmd.outfile);
	// printf("ENVP: %s\n", cmd.envp[0]);
	// printf("----------------------------------------\n");
	// if (pipe(data->pipefd) == FAILURE)
	// 	return (EXIT_FAILURE);
	// data->pid = fork();
	// if (!data->pid)
	// 	execute_child_process(data, &cmd);
	// else
	// 	execute_father_process(data, &cmd);
	return (EXIT_SUCCESS);
}

int	system_command(t_minishell *data)
{
	t_command **head;
	// int size;

	data->tokens_aux = data->tokens;
	// size = ft_lstnlen(data->tokens_aux, BAR);
	data->paths = ft_split(get_value(&data->envs, "PATH"), ':');
	if (data->paths == NULL)
	{
		message_command_not_found(data->tokens_aux);
		return (EXIT_FAILURE);
	}
	head = build_list(data);
	check_red(data->tokens, *head);


	free_all(data->paths);
	return (EXIT_SUCCESS);
}
