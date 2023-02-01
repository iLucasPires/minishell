#include <minishell.h>

void	print_lists(char **args)
{
	int index;

	index = 1;
	while (args[index])
	{
		ft_putstr_fd(args[index], STDOUT_FILENO);
		if (args[index + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		index++;
	}
}

int	builtin_echo(char **args)
{
	if (args[1] == NULL)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else
	{
		if (ft_strncmp(args[1], "-n", 2) == 0)
			print_lists(&args[1]);
		else
		{
			print_lists(args);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
	return (0);
}