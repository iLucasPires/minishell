#include <minishell.h>

void	init_env(t_minishell *data, char **envp)
{
	int	index;

	index = 0;
	while (envp[index] != NULL)
	{
		add_env(&data->envs, envp[index]);
		index++;
	}
}

void	init_data(t_minishell *data, char **envp)
{
	data->tokens = NULL;
	data->line = NULL;
	data->envs = NULL;
	data->envp = envp;
	data->home = getenv("HOME");
	data->paths = ft_split(getenv("PATH"), ':');
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	if (argc != 1 || argv[1] != NULL)
	{
		ft_putstr_fd(ERROR_ARGUMENTS, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	init_data(&data, envp);
	init_env(&data, envp);
	read_eval_print_loop(&data);
	return (EXIT_SUCCESS);
}
