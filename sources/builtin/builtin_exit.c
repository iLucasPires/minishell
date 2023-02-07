#include <minishell.h>

int	is_numeric(char *str)
{
	int	index;

	index = 0;
	if (str == NULL)
		return (0);
	if (str[index] == '-' || str[index] == '+')
		index++;
	while (str[index] != '\0')
	{
		if (!ft_isdigit(str[index]))
			return (FALSE);
		index++;
	}
	return (TRUE);
}

void	error_exit_str(char *str)
{
	(void)str;
	ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
}

int isBetween(char *num) {
    int index;

	index = 0;
	while (num[index] != '\0')
	{
		if (!ft_isdigit(num[index]))
			return (FALSE);
		index++;
	}
	if (WEXITSTATUS(ft_atoi(num)) == ft_atoi(num))
		return (TRUE);
	return (FALSE);
}

int	builtin_exit(char  **args, t_minishell *data)
{
	if (args[1] == NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(0);
	}
	else if (args[2] == NULL)
	{
		if (is_numeric(args[1]))
		{
			if (isBetween(args[1]) == TRUE)
			{
				ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
				destroy_exit_minishell(data, 2);
			}
			data->exit_code = ft_atoi(args[1]);
			destroy_exit_minishell(data, data->exit_code);
		}
		else
		{
			error_exit_str(args[1]);
			destroy_exit_minishell(data, 2);
		}
	}
	else
	{
		ft_putstr_fd("exit: too many arguments", STDERR_FILENO);
		data->exit_code = 1;
	}
	return (EXIT_FAILURE);
}