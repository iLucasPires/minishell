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

int	builtin_exit(t_minishell *data)
{
	t_list *token;

	token = data->tokens;
	if (token->next == NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(0);
	}
	else if (token->next->next == NULL)
	{
		if (is_numeric(token->next->value))
			destroy_exit_minishell(data, ft_atoi(token->next->value));
		else
		{
			error_exit_str(token->next->value);
			destroy_exit_minishell(data, 255);
		}
	}
	else
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}