#include <minishell.h>

void init_data(t_repl *data, char **envp)
{
	data->envp = envp;
	data->dirs = ft_split(getenv("PATH"), ':');
}

int	main(int argc, char **argv, char **envp)
{
	t_repl	data;

	if (argc != 1 || argv[1] != NULL)
		error_generic(ERROR_ARGUMENTS);
	init_data(&data, envp);
	read_eval_print_loop(&data); 
	return (0);
}
