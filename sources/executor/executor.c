#include <minishell.h>

int	destroy_child_process(t_minishell *data, t_command *cmd)
{
	(void)cmd;
	destroy_minishell(data);
	// destroy_command(cmd);
	free_all(data->paths);
	exit(EXIT_FAILURE);
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

t_executor *malloc_executor(int size)
{
	t_executor *new_executor;
	int i;

	i = 0;
	new_executor = malloc(sizeof(t_executor));
	new_executor->n_cmds = size + 1;
	new_executor->pipe = malloc(sizeof(int *) * size);
	new_executor->pid = malloc(sizeof(int) * new_executor->n_cmds);
	while (i < size)
	{
		new_executor->pipe[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (new_executor);
}

void open_pipes(t_executor **executor)
{
	int i;

	i = 0;
	while (i < ((*executor)->n_cmds - 1))
	{
		pipe((*executor)->pipe[i]);
		i++;
	}
}

void close_pipes(t_executor **executor)
{
	int i;

	i = 0;
	while (i < ((*executor)->n_cmds - 1))
	{
		close((*executor)->pipe[i][0]);
		close((*executor)->pipe[i][1]);
		i++;
	}
}

void wait_children(t_executor **executor)
{
	int status;
	int i;

	i = 0;
	while (i < ((*executor)->n_cmds))
	{
		waitpid((*executor)->pid[i], &status, 0);
		i++;
	}
}

void make_redirects(t_command *cmd, t_executor **executor, int i)
{
	if (cmd->outfile > 2)
		dup2(cmd->outfile, STDOUT_FILENO);
	else if (i < (*executor)->n_cmds - 1)
		dup2((*executor)->pipe[i][1], STDOUT_FILENO);
	if (cmd->infile > 2)
		dup2(cmd->infile, STDIN_FILENO);
	else if (i > 0)
		dup2((*executor)->pipe[i - 1][0], STDIN_FILENO);
}

void execute_children(t_command **cmd, t_executor **executor, int i)
{
	(void)cmd;
	(*executor)->pid[i] = fork();
	if ((*executor)->pid[i] == 0)
	{
		make_redirects(*cmd, executor, i);
		close_pipes(executor);
		execve((*cmd)->pathname, (*cmd)->args, (*cmd)->envp);
		exit (1);
	}
}

int	system_command(t_minishell *data)
{
	t_command **head;
	t_command *cmd_aux;
	t_executor *executor;
	int i;

	i = 0;
	data->tokens_aux = data->tokens;
	data->paths = ft_split(get_value(&data->envs, "PATH"), ':');
	if (data->paths == NULL)
	{
		message_command_not_found(data->tokens_aux);
		return (EXIT_FAILURE);
	}
	head = build_list(data);
	check_red(data->tokens, *head);
	executor = malloc_executor(count_pipes(data->tokens));
	open_pipes(&executor);
	cmd_aux = *head;
	while (i < executor->n_cmds)
	{
		execute_children(&cmd_aux, &executor, i);
		cmd_aux = cmd_aux->next;
		i++;
	}
	close_pipes(&executor);
	wait_children(&executor);


	free_all(data->paths);
	return (EXIT_SUCCESS);
}










	// int j;

	// j = 0;
	// printf("%dº TCOMMAND: \n", i);
	// printf("ARGS: ");
	// while ((*cmd)->args[j])
	// {
	// 	printf("%s ", (*cmd)->args[j]);
	// 	j++;
	// }
	// printf("\n");
	// printf("CMD: %s\n", (*cmd)->pathname);
	// printf("ENVP: %s\n", (*cmd)->envp[0]);
	// printf("INFILE: %d\n", (*cmd)->infile);
	// printf("OUTFILE: %d\n", (*cmd)->outfile);
	// printf("\n%dº EXECUTOR: \n", i);
	// printf("Nº CMDS: %d\n", executor->n_cmds);
	// printf("---------------------------------------\n");