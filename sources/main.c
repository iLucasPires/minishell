#include <minishell.h>

void	init_env(t_repl *data, char **envp)
{
	int	index;

	index = 0;
	while (envp[index] != NULL)
	{
		if (ft_strchr(envp[index], '='))
			add_item_end(&data->env , envp[index], true);
		else
			add_item_end(&data->env , envp[index], false);
		index++;
	}
}

void	init_data(t_repl *data)
{
	data->head = NULL;
	data->line = NULL;
	data->env = NULL;
	data->status = EXIT_SUCCESS;
	data->home = getenv("HOME");
}

int	main(int argc, char **argv, char **envp)
{
	t_repl	data;

	if (argc != 1 || argv[1] != NULL)
	{
		ft_putstr_fd(ERROR_ARGUMENTS, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	init_data(&data);
	path_current(&data);
	init_env(&data, envp);
	read_eval_print_loop(&data);
	return (EXIT_SUCCESS);
}
