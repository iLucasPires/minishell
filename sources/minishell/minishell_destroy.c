#include <minishell.h>

void free_all(char **pointer)
{
	int	index;

	index = 0;
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
