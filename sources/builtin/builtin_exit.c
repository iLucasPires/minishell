#include <minishell.h>

int	is_numeric(const char *str)
{
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	error_exit_str(char *str)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

int	builtin_exit(char **args)
{
	if (args[1] == NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(0);
	}
	else if (args[2] == NULL)
	{
		if (is_numeric(args[1]))
			destroy_exit_minishell(&g_data, ft_atoi(args[1]));
		else
		{
			error_exit_str(args[1]);
			destroy_exit_minishell(&g_data, EXIT_FAILURE);
		}
	}
	else
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}