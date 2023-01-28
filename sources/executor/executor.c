#include <minishell.h>

int	destroy_child_process(t_minishell *data, t_command *cmd)
{
	(void)cmd;
	destroy_minishell(data);
	// destroy_command(cmd);
	free_all(data->paths);
	exit(EXIT_FAILURE);
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
		if (WIFEXITED(status))
		{
			g_exit_code = WEXITSTATUS(status);
		}
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
	if (is_builtin((*cmd)->args[0]) && (*executor)->n_cmds == 1)
	{
		builtins(cmd);
		return ;
	}
	(*executor)->pid[i] = fork();
	if ((*executor)->pid[i] == 0)
	{
		make_redirects(*cmd, executor, i);
		close_pipes(executor);
		execve((*cmd)->pathname, (*cmd)->args, (*cmd)->envp);
		exit(1);
	}
}

int syntax_error_pipe(t_list *tokens)
{
	if (tokens->type == PIPE)
		return(ft_putstr_fd(ERROR_SYNTAX, 2), 2);
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (tokens->next == NULL)
				return(ft_putstr_fd(ERROR_SYNTAX, 2), 2);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	system_command(t_minishell *data)
{
	t_command **head;
	t_command *cmd_aux;
	t_executor *executor;
	int i;

	i = 0;
	if (syntax_error_pipe(data->tokens) != 0)
	{
		// limpar a porra toda
		g_exit_code = 2;
		return(g_exit_code);
	}
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
	free_all(data->paths);
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


	return (g_exit_code);
}
