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
	destroy_executor(&data->exec, data->tokens);
	free_all(data->paths);
	free(data->envp);
}

void	destroy_executor(t_executor *exec, t_list *tokens)
{
	int index;
	int size;

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