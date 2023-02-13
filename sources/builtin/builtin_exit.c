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

int	ft_islong_long(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (0);
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (1);
	out = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		if (out > (9223372036854775807 - c) / 10)
			return (0);
		out = out * 10 + c;
		str++;
	}
	return (1);
}
int	builtin_exit(char **args, t_minishell *data)
{
	if (args[1] == NULL)
		exit(0);
	else if (args[2] == NULL)
	{
		if (!is_numeric(args[1]) || !ft_islong_long(args[1]))
			return (ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO),
					destroy_exit_minishell(data, 2),
					EXIT_FAILURE);
		data->exit_code = ft_atoi(args[1]);
		destroy_exit_minishell(data, data->exit_code);
	}
	else
		return (ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO),
				data->exit_code = 1,
				EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
