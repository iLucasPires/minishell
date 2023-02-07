#include <minishell.h>

t_minishell	g_data;

void	init_env(t_minishell *data, char **envp)
{
	int	index;

	index = 0;
	while (envp[index] != NULL)
	{
		new_node(&data->envs, envp[index], TRUE);
		index++;
	}
}

void	init_data(t_minishell *data)
{
	data->tokens = NULL;
	data->line = NULL;
	data->envs = NULL;
	data->home = getenv("HOME");
	data->status = 0;
	data->pid = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*data;

	g_data.exit_code = 0;
	data = &g_data;
	if (argc != 1 || argv[1] != NULL)
	{
		ft_putstr_fd(ERROR_ARGUMENTS, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	init_data(data);
	init_env(data, envp);
	read_eval_print_loop(data);
	return (EXIT_SUCCESS);
}
