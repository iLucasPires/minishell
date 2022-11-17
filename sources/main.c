#include <minishell.h>

static void error_arguments(void)
{
	ft_putstr_fd(ERROR_ARGUMENTS, STDERR_FILENO);
	exit(EXIT_FAILURE);
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1] != NULL)
		error_arguments();
	data.envp = envp;
	read_eval_print_loop(&data.repl);
	return (0);
}
